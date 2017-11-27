// joystick.cpp : Defines the entry point for the console application.
//
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include "stdafx.h"
#include <dinput.h>
//#include "Joystick1.h"

LPDIRECTINPUTDEVICE8 joystick = NULL;
LPDIRECTINPUT8 di;
//LPDIRECTINPUTDEVICE8 joystick;
HRESULT hr;
BOOL CALLBACK
enumCallback(const DIDEVICEINSTANCE* instance, VOID* context)
{
	

	//// Obtain an interface to the enumerated joystick.
	//hr = di->CreateDevice(instance->guidInstance, &joystick, NULL);
	//printf("ok");
	//// If it failed, then we can't use this joystick. (Maybe the user unplugged
	//// it while we were in the middle of enumerating it.)
	//if (FAILED(hr)) {
	//	return DIENUM_CONTINUE;
	//}
	// Create a DirectInput device
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&di, NULL))) {
		return hr;
	}

	// Stop enumeration. Note: we're just taking the first joystick we get. You
	// could store all the enumerated joysticks and let the user pick.
	return DIENUM_STOP;
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	// Look for the first simple joystick we can find.
	if (FAILED(hr = di->EnumDevices(DI8DEVCLASS_GAMECTRL, enumCallback,
		NULL, DIEDFL_ATTACHEDONLY))) {
		return hr;
	}
	printf("ok");
	// Make sure we got a joystick
	if (di == NULL) {
		printf("Joystick not found.\n");
		return E_FAIL;
	}
	return 0;
}

