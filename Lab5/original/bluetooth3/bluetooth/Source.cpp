#pragma warning(disable : 4995)
#include <stdlib.h>
#include <stdio.h>
// Link to ws2_32.lib
#include <Winsock2.h>
#include <Ws2bth.h>
// Link to Bthprops.lib
#include <Bthsdpdef.h>
#include <BluetoothAPIs.h>
#undef main
int main(int argc, char **argv)
{
	HANDLE hRadio, hDeviceFind;
	BLUETOOTH_DEVICE_INFO_STRUCT deviceInfo;
	BLUETOOTH_DEVICE_SEARCH_PARAMS deviceSearchParams;
	BLUETOOTH_RADIO_INFO radioInfo;
	GUID guidServices[10];
	DWORD numServices, result, error;
	WCHAR pass[8] = { '6', '8', '5', '4', '5', '6', '2', '6'};
	int i = 1;

	BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
	HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio(&btfrp, &hRadio);

	if (hFind != NULL)
	{
		printf("BluetoothFindFirstRadio() is working!\n");
		do
		{
			// Do something with the radio handle...
			radioInfo.dwSize = sizeof(radioInfo);

			if (BluetoothGetRadioInfo(hRadio, &radioInfo) == ERROR_SUCCESS)
			{
				printf("BluetoothGetRadioInfo() is OK!\n");
				printf(" Radio found: %S\n", radioInfo.szName);
			}
			else
				printf("BluetoothGetRadioInfo() failed with error code %d\n", GetLastError());

			deviceInfo.dwSize = sizeof(deviceInfo);
			memset(&deviceSearchParams, 0, sizeof(deviceSearchParams));
			deviceSearchParams.dwSize = sizeof(deviceSearchParams);

			// deviceSearchParams.fReturnAuthenticated = TRUE;
			deviceSearchParams.fReturnRemembered = TRUE;
			//deviceSearchParams.fReturnUnknown = TRUE;
			//deviceSearchParams.fReturnConnected = TRUE;
			deviceSearchParams.hRadio = hRadio;

			hDeviceFind = BluetoothFindFirstDevice(&deviceSearchParams, &deviceInfo);
			if (hDeviceFind != NULL)
			{
				printf("BluetoothFindFirstDevice() is OK!\n");
				do
				{
					printf(" Device found - Name: %S\n", deviceInfo.szName);
					printf(" Device found - Address: %X\n", deviceInfo.Address);
					printf(" Device found - Device Class: %ul\n", deviceInfo.ulClassofDevice);

					numServices = sizeof(guidServices);

					// guidServices should contains a complete list of enabled service GUIDs.
					result = BluetoothEnumerateInstalledServices(hRadio, &deviceInfo, &numServices, guidServices);

					if (result == ERROR_SUCCESS)
					{
						printf("BluetoothEnumerateInstalledServices() should be fine!\n");
						printf(" ...GUID services\n");
					}
					else
						printf("BluetoothEnumerateInstalledServices() failed with error code %d\n", result);

				} while (BluetoothFindNextDevice(hDeviceFind, &deviceInfo));

				BluetoothFindDeviceClose(hDeviceFind);
			}

			// Need to re-allocate, else BluetoothGetDeviceInfo() will fail
			memset(&deviceInfo, 0, sizeof(deviceInfo));
			deviceInfo.dwSize = sizeof(deviceInfo);

			if (BluetoothGetDeviceInfo(hRadio, &deviceInfo))
			{
				printf("BluetoothGetDeviceInfo() is OK!\n");
				printf(" ...More operations...\n");
				#pragma deprecated(BluetoothAuthenticateDevice); 
				error =	BluetoothAuthenticateDevice(NULL, hRadio, &deviceInfo, NULL, BLUETOOTH_MAX_PASSKEY_SIZE);

				// BluetoothUpdateDeviceRecord() - change name, BluetoothRemoveDevice() etc.
			}
			else
				printf("BluetoothGetDeviceInfo() failed with error code %d\n", GetLastError());

			CloseHandle(hRadio);
		} while (BluetoothFindNextRadio(hFind, &hRadio));
		BluetoothFindRadioClose(hFind);
	}
	return 0;
}