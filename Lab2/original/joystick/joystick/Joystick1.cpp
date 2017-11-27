#include "stdafx.h"
#include "Joystick1.h"


HRESULT Joystick::Init()
{
	HRESULT hr;

	hr = DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(VOID**)&pDirectInput,
		NULL
		);

	//// Look for the first simple joystick we can find.
	//if (FAILED(hr = pDirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL, enumCallback,
	//	NULL, DIEDFL_ATTACHEDONLY))) {
	//	return hr;
	//}

	// Make sure we got a joystick
	if (pJoystick == NULL) {
		printf("Joystick not found.\n");
		return E_FAIL;
	}
	
	return hr;
}

BOOL CALLBACK
enumCallback(const DIDEVICEINSTANCE* instance, VOID* context, LPDIRECTINPUT8 pDirectInput, LPDIRECTINPUTDEVICE8 &pJoystick)
{
	HRESULT hr;

	// Obtain an interface to the enumerated joystick.
	hr = pDirectInput->CreateDevice(instance->guidInstance, &pJoystick, NULL);

	// If it failed, then we can't use this joystick. (Maybe the user unplugged
	// it while we were in the middle of enumerating it.)
	if (FAILED(hr)) {
		return DIENUM_CONTINUE;
	}

	// Stop enumeration. Note: we're just taking the first joystick we get. You
	// could store all the enumerated joysticks and let the user pick.
	return DIENUM_STOP;
}

//HRESULT Joystick::GetJoystick()
//{
//	HRESULT hr = S_OK;
//
//	//Check for joystick
//	DIJOYCONFIG PreferredJoyCfg = { 0 };
//	DI_ENUM_CONTEXT enumContext;
//	enumContext.pPreferredJoyCfg = &PreferredJoyCfg;
//	enumContext.bPreferredJoyCfgValid = false;
//
//	IDirectInputJoyConfig8* pJoyConfig = NULL;
//	if (FAILED(hr = pDirectInput->QueryInterface(
//		IID_IDirectInputJoyConfig8,
//		(void**)&pJoyConfig
//		)))
//		return hr;
//
//	PreferredJoyCfg.dwSize = sizeof(PreferredJoyCfg);
//	// This function is expected to fail if no joystick is attached
//	if (SUCCEEDED(pJoyConfig->GetConfig(0, &PreferredJoyCfg, DIJC_GUIDINSTANCE)))
//		enumContext.bPreferredJoyCfgValid = true;
//	SafeRelease(&pJoyConfig);
//
//	// Look for a simple joystick we can use for this sample program.
//	hr = pDirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL,
//		EnumJoysticksCallback,
//		&enumContext,
//		DIEDFL_ATTACHEDONLY
//		);
//	if (FAILED(hr))
//		return hr;
//
//	// Make sure we got a joystick
//	if (NULL == pJoystick)
//	{
//		MessageBox(NULL, TEXT("Joystick not found. The sample will now exit."),
//			TEXT("DirectInput Sample"),
//			MB_ICONERROR | MB_OK);
//		return E_FAIL;
//	}
//
//
//	return hr;
//}
//
//BOOL CALLBACK Joystick::EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance,
//	VOID* pContext)
//{
//	DI_ENUM_CONTEXT* pEnumContext = (DI_ENUM_CONTEXT*)pContext;
//	HRESULT hr;
//
//	/* if( g_bFilterOutXinputDevices && IsXInputDevice( &pdidInstance->guidProduct ) )
//	return DIENUM_CONTINUE;*/
//
//	// Skip anything other than the perferred joystick device as defined by the control panel.  
//	// Instead you could store all the enumerated joysticks and let the user pick.
//	if (pEnumContext->bPreferredJoyCfgValid &&
//		!IsEqualGUID(pdidInstance->guidInstance, pEnumContext->pPreferredJoyCfg->guidInstance))
//		return DIENUM_CONTINUE;
//
//	// Obtain an interface to the enumerated joystick.
//	hr = pDirectInput->CreateDevice(pdidInstance->guidInstance, &pJoystick, NULL);
//
//	// If it failed, then we can't use this joystick. (Maybe the user unplugged
//	// it while we were in the middle of enumerating it.)
//	if (FAILED(hr))
//		return DIENUM_CONTINUE;
//
//	// Stop enumeration. Note: we're just taking the first joystick we get. You
//	// could store all the enumerated joysticks and let the user pick.
//	return DIENUM_STOP;
//}