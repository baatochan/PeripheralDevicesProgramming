#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <dinput.h>
#pragma comment(lib, "dinput8.lib") 
#pragma comment(lib, "dxguid.lib") 

using namespace std;

LPDIRECTINPUT8 DirectInput;
LPDIRECTINPUTDEVICE8 GamePad;
LPDIRECTINPUTDEVICE8 GamePad2;



enum
{
	ERROR_INITIALIZE = 100,
	ERROR_NO_DEVICE = 101,
	ERROR_SET_JOYSTICK = 102,
	ERROR_CANT_GET_CAPABILITIES = 103,
	ERROR_ENUM_OBJECTS = 104
};


BOOL CALLBACK enumCallback(const DIDEVICEINSTANCE* instance, VOID* context);
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance,
	VOID* pContext);
BOOL CALLBACK enumAxesCallback(const DIDEVICEOBJECTINSTANCE* instance, VOID* context);
HRESULT getState(DIJOYSTATE *js);
void displayDeviceName();
void startMouseSimulation();

int main() {

	HRESULT temp_hrResult;
	

	// DirectInput initialize
	if (FAILED(temp_hrResult = DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&DirectInput, NULL))) {
		return ERROR_INITIALIZE;
	}
	
	// search for joystick
	if (FAILED(temp_hrResult = DirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL, enumCallback,
		NULL, DIEDFL_ALLDEVICES))) {
		
		return ERROR_NO_DEVICE;
	}

	// check for 
	if (GamePad == NULL && GamePad2==NULL ) {
		cout << "Joysctick not found! Please, connect your joystick" << endl;
		system("pause");
		return E_FAIL;
	}
	else {
		//cout << "Device found!" << endl;
		displayDeviceName();
	}

	if (FAILED(temp_hrResult = GamePad->SetDataFormat(&c_dfDIJoystick))) {
		return ERROR_SET_JOYSTICK;
	}

	DIDEVCAPS device_capabilities;
	// count joystick axes
	device_capabilities.dwSize = sizeof(DIDEVCAPS);
	if (FAILED(temp_hrResult = GamePad->GetCapabilities(&device_capabilities))) {
		return ERROR_CANT_GET_CAPABILITIES;
	}

	if (FAILED(temp_hrResult = GamePad->EnumObjects(enumAxesCallback, NULL, DIDFT_AXIS))) {
		return ERROR_ENUM_OBJECTS;
	}

	startMouseSimulation();


	// Disconnect Joystick
	if (GamePad) {
		GamePad->Unacquire();
	}
	system("pause");
	return EXIT_SUCCESS;
}


void startMouseSimulation()
{
	DIJOYSTATE state;
	POINT cursor;
	int button_index = -1;

	int exit_from_program = 0; // if != 0 -> exit
	BlockInput(true);
	while (!getState(&state)) {
		for (int i = 0; i < 32; i++) {
			if (state.rgbButtons[button_index] == 0)
			{
				// left button release
				if (button_index == 0) {
					GetCursorPos(&cursor);
					mouse_event(MOUSEEVENTF_LEFTUP, cursor.x, cursor.y, 0, 0);
					cout << "wcisniety lewy klawisz" << endl;
				}
				button_index = -1;
			}
			if (state.rgbButtons[i] && button_index != i) {
				button_index = i;
				if (i == 0)
				{
					// left button click and hold
					GetCursorPos(&cursor);
					mouse_event(MOUSEEVENTF_LEFTDOWN, cursor.x, cursor.y, 0, 0);
					
				}
				// right button click
				else if (i == 1) {
					GetCursorPos(&cursor);
					mouse_event(MOUSEEVENTF_RIGHTUP, cursor.x, cursor.y, 0, 0);
					cout << "wcisniety prawy klawisz" << endl;
				}
				// third button click - exiting from program
				else if (i == 2) {
					exit_from_program++;
				}
			}
		}

		GetCursorPos(&cursor);

		//cout << state.lX << endl;

		int x, y;
		x = y = 0;

		if (state.lX / 100 < -3 || state.lX / 100 > 3)
			x = state.lX / 100;
		
		
		if (state.lY / 100 < -3 || state.lY / 100 > 3)
			y = state.lY / 100;
		

			SetCursorPos(cursor.x + x, cursor.y + y);

		Sleep(10);

		if (exit_from_program != 0) {
			break;
		}
	}
	BlockInput(0);
}

void displayDeviceName() {
	DIDEVICEINSTANCE device_info;
	

	device_info.dwSize = sizeof(DIDEVICEINSTANCE);
	
	GamePad->GetDeviceInfo(&device_info);
	
	wchar_t* device_name = device_info.tszProductName;
	wprintf(device_name);
	cout << endl;
	
}

// collback from joystick
BOOL CALLBACK enumCallback(const DIDEVICEINSTANCE* instance, VOID* context)
{
	HRESULT device;
		
	// initialize joystick
	device = DirectInput->CreateDevice(instance->guidInstance, &GamePad, NULL);
		
	// No joystick on the system
	if (FAILED(device)) {
		return DIENUM_CONTINUE;
	}
	return DIENUM_STOP;
}

// get information about x,y axis state
BOOL CALLBACK enumAxesCallback(const DIDEVICEOBJECTINSTANCE* instance, VOID* context)
{
	HWND hDlg = (HWND)context;

	DIPROPRANGE propRange;
	propRange.diph.dwSize = sizeof(DIPROPRANGE); 
	propRange.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	propRange.diph.dwHow = DIPH_BYID;
	propRange.diph.dwObj = instance->dwType;
	propRange.lMin = -1000;
	propRange.lMax = +1000;

	if (FAILED(GamePad->SetProperty(DIPROP_RANGE, &propRange.diph))) {
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}

// get information about button and x,y axis state
HRESULT getState(DIJOYSTATE *js)
{
	HRESULT  device_result;

	if (GamePad == NULL) {
		return S_OK;
	}

	// check joystick isn't bussy
	device_result = GamePad->Poll();
	if (FAILED(device_result)) {

		// fix input stream
		device_result = GamePad->Acquire();
		while (device_result == DIERR_INPUTLOST) {
			device_result = GamePad->Acquire();
		}

		// connection lost
		if ((device_result == DIERR_INVALIDPARAM) || (device_result == DIERR_NOTINITIALIZED)) {
			return E_FAIL;
		}

		// wait for joystick
		if (device_result == DIERR_OTHERAPPHASPRIO) {
			return S_OK;
		}
	}

	// get device state 
	if (FAILED(device_result = GamePad->GetDeviceState(sizeof(DIJOYSTATE), js))) {
		return device_result;
	}

	return S_OK;
}