// blue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "winsock2.h"
#include "Ws2bth.h"
#include "BluetoothAPIs.h"
#include "windows.h"
//#include "bthdef.h"
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Irprops.lib")
#define WIN32_LEAN_AND_MEAN



BLUETOOTH_FIND_RADIO_PARAMS find_radio_params = {
	sizeof(BLUETOOTH_FIND_RADIO_PARAMS)
};

BLUETOOTH_RADIO_INFO radio_info = {
	sizeof(BLUETOOTH_RADIO_INFO),
	0
};

BLUETOOTH_DEVICE_SEARCH_PARAMS search_params = {
	sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS),
	1, // autentykowane
	1, // zapamietane
	1, // nieznane
	1, // czy polaczone
	1, // czy zwracac kolejne
	3, // czas szukania
	NULL
};

BLUETOOTH_DEVICE_INFO device_info = {
	sizeof(BLUETOOTH_DEVICE_INFO),
	0
};

void printRadioInfo(HANDLE adapter) {
	BluetoothGetRadioInfo(adapter, &radio_info);
	wprintf(L"%s\n", radio_info.szName); 
	printf("Adres: %02x %02x %02x %02x %02x %02x \n", radio_info.address.rgBytes[5], radio_info.address.rgBytes[4], radio_info.address.rgBytes[3],
		radio_info.address.rgBytes[2], radio_info.address.rgBytes[1], radio_info.address.rgBytes[0]);
	printf("Class: 0x%08x \n\n\n", radio_info.ulClassofDevice);
}

void printDeviceInfo(int id) {
	printf("DeviceID: \t%d\n", id);
	wprintf(L"Device: \t%s \n", device_info.szName);
	wprintf(L"Podlaczony: \t");
	if(device_info.fConnected) {
		wprintf(L"tak.\n");
	} else {
		wprintf(L"nie.\n");
	}
	wprintf(L"Autoryzowany: \t");
	if(device_info.fAuthenticated) {
		wprintf(L"tak.\n");
	} else {
		wprintf(L"nie.\n");
	}
	wprintf(L"Zapamietany: \t");
	if(device_info.fRemembered) {
		wprintf(L"tak.\n");
	} else {
		wprintf(L"nie.\n");
	}
	printf("Address:\t%02x %02x %02x %02x %02x %02x \n\n\n", device_info.Address.rgBytes[5], device_info.Address.rgBytes[4], device_info.Address.rgBytes[3],
		device_info.Address.rgBytes[2], device_info.Address.rgBytes[1], device_info.Address.rgBytes[0]);
}

int _tmain(int argc, _TCHAR* argv[]) {
	HBLUETOOTH_RADIO_FIND radio_find = NULL;

	HANDLE adapter;
	int device_id = 1;

	radio_find = BluetoothFindFirstRadio(&find_radio_params, &adapter);

	HBLUETOOTH_DEVICE_FIND device = NULL;

	BLUETOOTH_DEVICE_INFO devices_info[100];

	if(radio_find == NULL) {
		printf("Nic nie znaleziono");
	} else {
		printRadioInfo(adapter);

		search_params.hRadio = adapter;

		device = BluetoothFindFirstDevice(&search_params, &device_info);

		do {
			printDeviceInfo(device_id);
			devices_info[device_id] = device_info;
			device_id++;
		} while (BluetoothFindNextDevice(device, &device_info));

	}

	int choice = 0;
	printf("Wybierz urzadzenie: ");
	scanf_s("%d", &choice);
	printf("\nTwoj wybor: %d\n", choice);

	device_info = devices_info[choice];

	BluetoothAuthenticateDevice(NULL, adapter, &device_info, NULL, 0);

	printDeviceInfo(choice);

	//zabawa z soketami
	SOCKET soc;
	SOCKADDR_BTH adres;
	WSADATA wsa_Data;

	int wynik = WSAStartup(MAKEWORD(2,2), &wsa_Data);

	if(wynik != NO_ERROR) {
		printf("Wystapil blad WSA");
		system("pause");
		return 0;
	}

	soc = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
	if(soc == INVALID_SOCKET) {
		printf("Blad gniazda.\n");
		system("pause");
 		return 0;
	}
	adres.addressFamily = AF_BTH;
	adres.btAddr = device_info.Address.ullLong;
    adres.port = (ULONG)BT_PORT_ANY;
    adres.serviceClassId = OBEXObjectPushServiceClass_UUID;

	if(connect(soc, (SOCKADDR*) &adres, sizeof(adres)) == SOCKET_ERROR) {
		printf("Blad polaczenia.\n");
		system("pause");
		return 0;
	}

	char b=0xA0;
	char* inform = new char[7];
	char* inc = new char[7];
	inform[0] = 0x80;
	inform[1] = 0x00;
	inform[2] = 0x07;
	inform[3] = 0x10;
	inform[4] = 0x00;
	inform[5] = 0x20;
	inform[6] = 0x00;
	send(soc, inform, 7, 0);
	delete []inform;
	recv(soc, inc, 7, 0);

	if(inc[0] != b) {
		printf("Blad polaczenia OBEX.\n");
		system("pause");
	}

	delete []inc;

	closesocket(soc);

	BluetoothFindDeviceClose(device);
	BluetoothFindRadioClose(radio_find);

	BluetoothRemoveDevice(&device_info.Address);

	system("pause");

	return 0;
}