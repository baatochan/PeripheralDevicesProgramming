// UP_lab14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
// Link to ws2_32.lib
#include <Winsock2.h>
#include <Ws2bth.h>
// Link to Bthprops.lib
#include <BluetoothAPIs.h>
#include <iostream>
#include <ctime>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Bthprops.lib")

BLUETOOTH_FIND_RADIO_PARAMS m_bt_find_radio = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };

BLUETOOTH_RADIO_INFO m_bt_info = { sizeof(BLUETOOTH_RADIO_INFO), 0, };

BLUETOOTH_DEVICE_SEARCH_PARAMS m_search_params = {
	sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS),
	1,
	1,
	1,
	1,
	1,
	10,
	NULL
};

BLUETOOTH_DEVICE_INFO m_device_info[10];



// Note:
// Radio - is the thing plugged in/attached to the local machine.
// Device - is the thing that is connected to via the Bluetooth connection.

int main(int argc, char **args)
{
	HANDLE m_radio = NULL;
	HBLUETOOTH_RADIO_FIND m_bt = NULL;
	HBLUETOOTH_DEVICE_FIND m_bt_dev = NULL;
	int m_device_id;
	DWORD mbtinfo_ret;
	m_device_info[0].dwSize = sizeof(BLUETOOTH_DEVICE_INFO);

	m_bt = BluetoothFindFirstRadio(&m_bt_find_radio, &m_radio);

	if (m_bt != NULL)
		printf("BluetoothFindFirstRadio() is OK!\n");
	else
		printf("BluetoothFindFirstRadio() failed with error code %d\n", GetLastError());



	// Then get the radio device info....
	mbtinfo_ret = BluetoothGetRadioInfo(m_radio, &m_bt_info);
	if (mbtinfo_ret == ERROR_SUCCESS)
		printf("BluetoothGetRadioInfo() looks fine!\n");
	else
		printf("BluetoothGetRadioInfo() failed wit herror code %d\n", mbtinfo_ret);


	wprintf(L"\tInstance Name: %s\r\n", m_bt_info.szName);
	wprintf(L"\tAddress: %02X:%02X:%02X:%02X:%02X:%02X\r\n", m_bt_info.address.rgBytes[5],
		m_bt_info.address.rgBytes[4], m_bt_info.address.rgBytes[3], m_bt_info.address.rgBytes[2],
		m_bt_info.address.rgBytes[1], m_bt_info.address.rgBytes[0]);
	wprintf(L"\tClass: 0x%08x\r\n", m_bt_info.ulClassofDevice);
	wprintf(L"\tManufacturer: 0x%04x\r\n", m_bt_info.manufacturer);

	m_search_params.hRadio = m_radio;
	ZeroMemory(&m_device_info[0], sizeof(BLUETOOTH_DEVICE_INFO));
	m_device_info[0].dwSize = sizeof(BLUETOOTH_DEVICE_INFO);

	// Next for every radio, get the device
	m_bt_dev = BluetoothFindFirstDevice(&m_search_params, &m_device_info[0]);

	if (m_bt_dev != NULL)
		printf("\nBluetoothFindFirstDevice() is working!\n");
	else
		printf("\nBluetoothFindFirstDevice() failed with error code %d\n", GetLastError());

	m_device_id = 0;

	// Get the device info
	do
	{
		wprintf(L"\n\tDevice %d:\r\n", m_device_id);
		wprintf(L"  \tInstance Name: %s\r\n", m_device_info[m_device_id].szName);
		wprintf(L"  \tAddress: %02X:%02X:%02X:%02X:%02X:%02X\r\n", m_device_info[m_device_id].Address.rgBytes[5],
			m_device_info[m_device_id].Address.rgBytes[4], m_device_info[m_device_id].Address.rgBytes[3], m_device_info[m_device_id].Address.rgBytes[2],
			m_device_info[m_device_id].Address.rgBytes[1], m_device_info[m_device_id].Address.rgBytes[0]);
		wprintf(L"  \tClass: 0x%08x\r\n", m_device_info[m_device_id].ulClassofDevice);
		wprintf(L"  \tConnected: %s\r\n", m_device_info[m_device_id].fConnected ? L"true" : L"false");
		wprintf(L"  \tAuthenticated: %s\r\n", m_device_info[m_device_id].fAuthenticated ? L"true" : L"false");
		wprintf(L"  \tRemembered: %s\r\n", m_device_info[m_device_id].fRemembered ? L"true" : L"false");
		m_device_id++;

		// Well, the found device information can be used for further socket
		// operation such as creating a socket, bind, listen, connect, send, receive etc..
		// If no more device, exit the loop
		//if (!BluetoothFindNextDevice(m_bt_dev, &m_device_info))
		//	break;

	} while (BluetoothFindNextDevice(m_bt_dev, &m_device_info[m_device_id]));
	int chosen;
	std::cout << "Device ID: ";
	std::cin >> chosen;
	
	HRESULT status = BluetoothAuthenticateDeviceEx(NULL, m_radio, &m_device_info[chosen], NULL, MITMProtectionNotRequired);
	Sleep(10000);

	if (status == ERROR_SUCCESS)
		std::cout << "Authenticate OK" << std::endl;
	else
		std::cout << "ERROR:" << status << std::endl;

	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != NO_ERROR) {
		std::cout << "Blad WSAStartup: " << result;
		return 0;
	}

	SOCKET sck = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
	SOCKADDR_BTH sadr;

	if (sck == INVALID_SOCKET) {
		std::cout << "Blad przy tworzeniu gniazda. Kod bledu: " << GetLastError() << std::endl;
		return 0;
	}
	else {
		std::cout << "Socket OK" << std::endl;
		sadr.addressFamily = AF_BTH;
		sadr.btAddr = m_device_info[chosen].Address.ullLong;
		sadr.port = (ULONG)BT_PORT_ANY;
		sadr.serviceClassId = OBEXObjectPushServiceClass_UUID;
		if (connect(sck, (SOCKADDR *)&sadr, sizeof(sadr)) == SOCKET_ERROR) {
			std::cout << "Blad laczenia. Kod bledu: " << GetLastError() << std::endl;
			closesocket(sck);
			WSACleanup();
			return 0;
		}
		else{
			std::cout << "Connection OK" << std::endl;
		}

		
		char b = 0xA0;
		char* inform = new char[7];
		char* inc = new char[7];
		inform[0] = 0x80;
		inform[1] = 0x00;
		inform[2] = 0x07;
		inform[3] = 0x10;
		inform[4] = 0x00;
		inform[5] = 0x20;
		inform[6] = 0x00;
		send(sck, inform, 7, 0);
		delete[]inform;
		recv(sck, inc, 7, 0);

		if (inc[0] != b) {
			printf("Blad polaczenia OBEX.\n");
			system("pause");
		}
		else {
			printf("Send OK\n");
		}

		delete[]inc;

		closesocket(sck);
	}

	// NO more device, close the device handle
	if (BluetoothFindDeviceClose(m_bt_dev) == TRUE)
		printf("\nBluetoothFindDeviceClose(m_bt_dev) is OK!\n");
	else
		printf("\nBluetoothFindDeviceClose(m_bt_dev) failed with error code %d\n", GetLastError());


	// No more radio, close the radio handle
	if (BluetoothFindRadioClose(m_bt) == TRUE)
		printf("BluetoothFindRadioClose(m_bt) is OK!\n");
	else
		printf("BluetoothFindRadioClose(m_bt) failed with error code %d\n", GetLastError());

	BluetoothRemoveDevice(&m_device_info[chosen].Address);


	system("PAUSE");
	return 0;
}
