#include "joystick.h"
#include <stdio.h>

#pragma warning(disable:4996)

#define SAFE_RELEASE(p)     { if(p) { (p)->Release(); (p) = NULL; } }

Joystick::Joystick(unsigned int id)
{
    this->id = id;
    device_counter = 0;

    di = NULL;
    joystick = NULL;
}

Joystick::~Joystick()
{
    close();
}

HRESULT
Joystick::deviceName(char* name)
{
    HRESULT hr;
    DIDEVICEINSTANCE device;
   
    ZeroMemory(&device, sizeof(device));
    device.dwSize = sizeof(device);

    if (!di || !joystick) {
        return E_INVALIDARG;
    }

    if (FAILED(hr = joystick->GetDeviceInfo(&device))) {
        return hr;
    }

    strncpy(name, device.tszProductName, MAX_PATH);

    return hr;
}

HRESULT
Joystick::open()
{
    HRESULT hr;

    if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL),
                                       DIRECTINPUT_VERSION, 
                                       IID_IDirectInput8,
                                       (VOID**)&di, NULL))) {
        return hr;
    }

    if (FAILED(hr = di->EnumDevices(DI8DEVCLASS_GAMECTRL, ::enumCallback,
                                    (LPVOID)this, DIEDFL_ATTACHEDONLY))) {
        return hr;
    }

    if (joystick == NULL) {
        return E_FAIL;
    }
    if (FAILED(hr = joystick->SetDataFormat(&c_dfDIJoystick2))) {
        return hr;
    }

    if (FAILED(hr = joystick->SetCooperativeLevel(NULL, DISCL_EXCLUSIVE | DISCL_FOREGROUND))) {
        return hr;
    }

    return S_OK;
}

HRESULT
Joystick::close()
{
    if (joystick) { 
        joystick->Unacquire();
    }
    
    SAFE_RELEASE(joystick);
    SAFE_RELEASE(di);

    return S_OK;
}

HRESULT
Joystick::poll(DIJOYSTATE2 *js)
{
    HRESULT hr;

    if (joystick == NULL) {
        return S_OK;
    }

    hr = joystick->Poll(); 
    if (FAILED(hr)) {

        hr = joystick->Acquire();
        while (hr == DIERR_INPUTLOST) {
            hr = joystick->Acquire();
        }

        if ((hr == DIERR_INVALIDPARAM) || (hr == DIERR_NOTINITIALIZED)) {
            return E_FAIL;
        }

        if (hr == DIERR_OTHERAPPHASPRIO) {
            return S_OK;
        }
    }

    if (FAILED(hr = joystick->GetDeviceState(sizeof(DIJOYSTATE2), js))) {
        return hr;
    }

    return S_OK;
}

BOOL CALLBACK
Joystick::enumCallback(const DIDEVICEINSTANCE* instance, VOID* context)
{

    if (device_counter == this->id) {
        if (SUCCEEDED(di->CreateDevice(instance->guidInstance, &joystick, NULL))) {
            return DIENUM_STOP;
        }  
    }

    device_counter++;

    return DIENUM_CONTINUE;
}

BOOL CALLBACK
enumCallback(const DIDEVICEINSTANCE* instance, VOID* context)
{
    if (context != NULL) {
        return ((Joystick *)context)->enumCallback(instance, context);
    } else {
        return DIENUM_STOP;
    }
}

unsigned int
Joystick::deviceCount()
{
    unsigned int counter = 0;
    LPDIRECTINPUT8 di = NULL;
    HRESULT hr;

    if (SUCCEEDED(hr = DirectInput8Create(GetModuleHandle(NULL),
                                          DIRECTINPUT_VERSION, 
                                          IID_IDirectInput8,
                                          (VOID**)&di, NULL))) {
        di->EnumDevices(DI8DEVCLASS_GAMECTRL, ::countCallback,
                        &counter, DIEDFL_ATTACHEDONLY);
    }

    return counter;
}

BOOL CALLBACK
countCallback(const DIDEVICEINSTANCE* instance, VOID* counter)
{
    if (counter != NULL) {
        unsigned int *tmpCounter = (unsigned int *)counter;
        (*tmpCounter)++;
        counter = tmpCounter;
    }

    return DIENUM_CONTINUE;
}
