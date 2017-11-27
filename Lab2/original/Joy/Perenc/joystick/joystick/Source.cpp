#include <iostream>
#include <dinput.h>

HRESULT hr;
LPDIRECTINPUT8 di;
LPDIRECTINPUTDEVICE8 joystick;

BOOL CALLBACK
enumCallback(const DIDEVICEINSTANCE* instance, VOID* context)
{
	HRESULT hr;

	// Obtain an interface to the enumerated joystick.
	hr = di->CreateDevice(instance->guidInstance, &joystick, NULL);

	// If it failed, then we can't use this joystick. (Maybe the user unplugged
	// it while we were in the middle of enumerating it.)
	if (FAILED(hr)) {
		return DIENUM_CONTINUE;
	}

	// Stop enumeration. Note: we're just taking the first joystick we get. You
	// could store all the enumerated joysticks and let the user pick.
	return DIENUM_STOP;
}

BOOL CALLBACK
enumAxesCallback(const DIDEVICEOBJECTINSTANCE* instance, VOID* context)
{
	HWND hDlg = (HWND)context;

	DIPROPRANGE propRange;
	propRange.diph.dwSize = sizeof(DIPROPRANGE);
	propRange.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	propRange.diph.dwHow = DIPH_BYID;
	propRange.diph.dwObj = instance->dwType;
	propRange.lMin = -1000;
	propRange.lMax = +1000;

	// Set the range for the axis
	if (FAILED(joystick->SetProperty(DIPROP_RANGE, &propRange.diph))) {
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}

HRESULT
poll(DIJOYSTATE2 *js)
{
	HRESULT     hr;

	if (joystick == NULL) {
		return S_OK;
	}


	// Poll the device to read the current state
	hr = joystick->Poll();
	if (FAILED(hr)) {
		// DInput is telling us that the input stream has been
		// interrupted. We aren't tracking any state between polls, so
		// we don't have any special reset that needs to be done. We
		// just re-acquire and try again.
		hr = joystick->Acquire();
		while (hr == DIERR_INPUTLOST) {
			hr = joystick->Acquire();
		}

		// If we encounter a fatal error, return failure.
		if ((hr == DIERR_INVALIDPARAM) || (hr == DIERR_NOTINITIALIZED)) {
			return E_FAIL;
		}

		// If another application has control of this device, return successfully.
		// We'll just have to wait our turn to use the joystick.
		if (hr == DIERR_OTHERAPPHASPRIO) {
			return S_OK;
		}
	}

	// Get the input's device state
	if (FAILED(hr = joystick->GetDeviceState(sizeof(DIJOYSTATE2), js))) {
		return hr; // The device should have been acquired during the Poll()
	}

	return S_OK;
}

void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;

	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();

	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);

	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void moveMouse(int dx, int dy)
{
	POINT pt;
	int horizontal = 0;
	int vertical = 0;

	GetDesktopResolution(horizontal, vertical);

	GetCursorPos(&pt);

	pt.x += dx;
	pt.y += dy;

	if (pt.x < 0)
	{
		pt.x = 0;
	}
	if (pt.x > horizontal)
	{
		pt.x = horizontal;
	}

	if (pt.y < 0)
	{
		pt.y = 0;
	}
	if (pt.y > vertical)
	{
		pt.y = vertical;
	}

	SetCursorPos(pt.x, pt.y);
}

void clickMouseL()
{
	if (GetKeyState(VK_LBUTTON) >= 0)
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	}
}
void unclickMouseL()
{
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

int main()
{
	// Create a DirectInput device
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&di, NULL))) {
		return hr;
	}

	// Look for the first simple joystick we can find.
	if (FAILED(hr = di->EnumDevices(DI8DEVCLASS_GAMECTRL, enumCallback,
		NULL, DIEDFL_ATTACHEDONLY))) {
		return hr;
	}

	// Make sure we got a joystick
	if (joystick == NULL) {
		printf("Joystick not found.\n");
		return E_FAIL;
	}
	
	DIDEVCAPS capabilities;

	// Set the data format to "simple joystick" - a predefined data format 
	//
	// A data format specifies which controls on a device we are interested in,
	// and how they should be reported. This tells DInput that we will be
	// passing a DIJOYSTATE2 structure to IDirectInputDevice::GetDeviceState().
	if (FAILED(hr = joystick->SetDataFormat(&c_dfDIJoystick2))) {
		return hr;
	}

	// Set the cooperative level to let DInput know how this device should
	// interact with the system and with other DInput applications.
	if (FAILED(hr = joystick->SetCooperativeLevel(NULL, DISCL_NONEXCLUSIVE |
		DISCL_BACKGROUND))) {
		return hr;
	}

	// Determine how many axis the joystick has (so we don't error out setting
	// properties for unavailable axis)
	capabilities.dwSize = sizeof(DIDEVCAPS);
	if (FAILED(hr = joystick->GetCapabilities(&capabilities))) {
		return hr;
	}
	
	// Enumerate the axes of the joyctick and set the range of each axis. Note:
	// we could just use the defaults, but we're just trying to show an example
	// of enumerating device objects (axes, buttons, etc.).
	if (FAILED(hr = joystick->EnumObjects(enumAxesCallback, NULL, DIDFT_AXIS))) {
		return hr;
	}

	DIDEVICEINSTANCE info;

	info.dwSize = sizeof(DIDEVICEINSTANCE);
	if (FAILED(hr = joystick->GetDeviceInfo(&info)))
	{
		return hr;
	}

	for (int i = 0; i < MAX_PATH && info.tszProductName[i] != 0; i++)
	{
		std::cout << (char)info.tszProductName[i];
	}

	std::cout << "INIT" << std::endl;

	DIJOYSTATE2 js;

	while (js.rgbButtons[2]!=128)
	{
		poll(&js);
		std::cout << "x: " << js.lX << "\ty: " << js.lY << "\tz: " << js.lZ << "\n";
		moveMouse(js.lX/75, js.lY/75);

		if (js.rgbButtons[3] == 128)
			clickMouseL();
		else
			unclickMouseL();
	}

	if (joystick) {
		joystick->Unacquire();
	}
	return 0;
}