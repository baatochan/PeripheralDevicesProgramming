#ifndef JOYSTICK_H
#define JOYSTICK_H

#define DIRECTINPUT_VERSION 0x0800
#define _CRT_SECURE_NO_DEPRECATE


//#include <Windows.h>
#include <dinput.h>
#include <dinputd.h>


struct DI_ENUM_CONTEXT
{
	DIJOYCONFIG* pPreferredJoyCfg;
	bool bPreferredJoyCfgValid;
};

#ifndef _SAFE_RELEASE
#define _SAFE_RELEASE
template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}
#endif
class Joystick
{
public:
	static LPDIRECTINPUT8           pDirectInput;
	static LPDIRECTINPUTDEVICE8     pJoystick;
	static BOOL CALLBACK    EnumJoysticksCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
	Joystick()
	{
	}
	~Joystick();

	HRESULT         Init();
	HRESULT         GetJoystick();
};
#endif