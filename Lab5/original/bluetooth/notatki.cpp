// bluetooth.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <wchar.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <Winsock2.h>
#include <Ws2bth.h>
#include <BluetoothAPIs.h>
#include <MSWSock.h>

#pragma comment(lib, "Ws2_32.lib") // wskazuje na linker, ktory Ws2_32.lib potrzebuje
#define errno WSAGetLastError()
using namespace std;

BLUETOOTH_RADIO_INFO bt_radio_info = { sizeof(BLUETOOTH_RADIO_INFO), 0, }; // informacje o nadajniku
BLUETOOTH_DEVICE_INFO m_device_info = { sizeof(BLUETOOTH_DEVICE_INFO), 0, }; // informacje o odbiorniku

void print_device_info(BLUETOOTH_DEVICE_INFO BThandle, int count) {
    cout << "\n-------------------------\nUrzadzenie: " << count+1 << endl;
    wprintf(L"Nazwa: %s\n ", BThandle.szName);
    wprintf(L"MAC: %02x:%02x:%02x:%02x:%02x:%02x\n ", BThandle.Address.rgBytes[5], BThandle.Address.rgBytes[4], BThandle.Address.rgBytes[3], BThandle.Address.rgBytes[2], BThandle.Address.rgBytes[1], BThandle.Address.rgBytes[0]);
    cout << "Czy polaczono? ";
    if (BThandle.fConnected) cout << "Tak" << endl;
    else cout << "Nie" << endl;
    cout << "Autoryzowano? ";
    if (BThandle.fAuthenticated) cout << "Tak" << endl;
    else cout << "Nie" << endl;
};

void print_adapter_info(HANDLE BThandle) {
    BluetoothGetRadioInfo(BThandle, &bt_radio_info); //pobiera informacje o nadajniku
    cout << "Informacje o radio: " << endl; 
    wprintf(L"%s\n ", bt_radio_info.szName); //nazwa nadajnika dzieki funkcji .szName
    // wypisuje MAC urzadzenia dzieki funkcji .address.rgBytes[]
    wprintf(L"MAC: %02x:%02x:%02x:%02x:%02x:%02x\n ", bt_radio_info.address.rgBytes[5],
        bt_radio_info.address.rgBytes[4], bt_radio_info.address.rgBytes[3],
        bt_radio_info.address.rgBytes[2], bt_radio_info.address.rgBytes[1],
        bt_radio_info.address.rgBytes[0]);
};

int _tmain(int argc, _TCHAR* argv[])
{
    const int MAX_BT_DEVICES = 10; // stala max urzadzen
    HANDLE adapters = NULL; // adapters jest tyou Handle

    BLUETOOTH_DEVICE_SEARCH_PARAMS bt_dev_search_params = {
        sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS), 
        1, //   fReturnAuthenticated;
        0, //   fReturnRemembered;
        1, //   fReturnUnknown;
        1, //   fReturnConnected;
        1, //   fIssueInquiry;
        5, // cTimeoutMultiplier
        NULL
    };

    BLUETOOTH_FIND_RADIO_PARAMS bt_find_radio_params = { //dwSize = 4
        sizeof(BLUETOOTH_FIND_RADIO_PARAMS)
    };

    HBLUETOOTH_RADIO_FIND bt_radio_find = NULL;
    HBLUETOOTH_DEVICE_FIND bt_dev_find = NULL;

    cout << "Szukanie podlaczonego urzadzenia Bluetooth:" << endl;

    bt_radio_find = BluetoothFindFirstRadio(&bt_find_radio_params, &adapters); //szuka pierwszego adaptera, jesli NULL nie znalazlo
    //bt_find_radio_params - wejsciowe, adapters - wyjsciowe
    // wynik - bt_find_radio_params (dwSIZE=4)
    if (bt_radio_find == NULL) {
        cout << "Brak podlaczonych urzadzen. #" << GetLastError() << endl;
        system("pause");
        return 0;
    }
    else {
        print_adapter_info(adapters); //wywolanie funkcji wypisz info z argumentem adapters

        if (!BluetoothFindRadioClose(bt_radio_find)) //zamykanie urzadzenia
            cout << "Blad zamykania" << endl;
    }

    bt_dev_search_params.hRadio = adapters; // przypisanie odbiornikowi parametru HANDLE z nadajnika (wyszukiwanie tylko dla danego nadajnika)
    cout << endl << "Wyszukiwanie urzadzen Bluetooth w poblizu:" << endl;

    BLUETOOTH_DEVICE_INFO devices[MAX_BT_DEVICES]; //stworzenie tablicy urzadzen
    devices[0].dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
    //ZeroMemory(&m_device_info, sizeof(BLUETOOTH_DEVICE_INFO));
    bt_dev_find = BluetoothFindFirstDevice(&bt_dev_search_params, &devices[0]); //wyszukiwanie pierwszego urzadzenia

    if (bt_dev_find == NULL) {
        cout << "Nie znaleziono zadnych urzadzen Bluetooth." << endl;
        return 0;
    }
    else {
        int devices_found = 1;
        devices[devices_found].dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
        while (BluetoothFindNextDevice(bt_dev_find, &devices[devices_found])) {
            devices_found++;
            devices[devices_found].dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
        }
        BluetoothFindDeviceClose(bt_dev_find);

        for (int i = 0; i < devices_found; i++)
            print_device_info(devices[i], i);
    }

    int wybrane_urzadzenie = 0;
    cout << "Wybierz urzadzenie: "; 
    cin >> wybrane_urzadzenie;
    wybrane_urzadzenie--;
    cout << endl;


    BluetoothAuthenticateDeviceEx(NULL, adapters, &devices[wybrane_urzadzenie], NULL, MITMProtectionRequired);//funkcja wysylajaca prosbe autentykacji do odbiornika

    SOCKET sck;
    SOCKADDR_BTH sadr;
    HANDLE outfp;
    outfp = CreateFile((LPCWSTR)"C:\\Users\\lab\\Desktop\\Bluetooth_olek\\bluetooth\\ReadMe.sms", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    cout << "CreateFile() finished with code: " << GetLastError() << endl;

    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != NO_ERROR)
    {
        cout << "Blad WSAStartup: " << result;
        system("pause");
        return 0;
    }

    sck = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);

    if (sck == INVALID_SOCKET) {
        cout << "Blad przy tworzeniu gniazda. #" << GetLastError() << endl;
        system("pause");
        return 0;
    }
    else {
        sadr.addressFamily = AF_BTH;
        sadr.btAddr = devices[wybrane_urzadzenie].Address.ullLong;
        sadr.port = (ULONG)BT_PORT_ANY;
        sadr.serviceClassId = OBEXObjectPushServiceClass_UUID;


        if (0 != connect(sck, (SOCKADDR *)&sadr, sizeof(sadr)))
        {
            cout << "connect finished with code: " << WSAGetLastError() << endl;
        }

        if (TransmitFile(sck, //hSocket,
            outfp, //(HANDLE)outfp, //hFile
            0, //nNumberOfBytesToWrite
            0, //nNumberOfBytesPerSend
            NULL, //lpOverlapped
            NULL, //lpTransmitBuffers
            TF_REUSE_SOCKET  // dwFlags
            ) == FALSE) cout << "TransmitFile returned FALSE" << endl;
        else cout << "TransmitFile returned TRUE" << endl;

        cout << "WSALastError: " << WSAGetLastError() << endl;
        //wprintf(L"WSAGetLastError: %x\n WSAGetLastError #2: %d\n", WSAGetLastError, WSAGetLastError);

        if (sck == SOCKET_ERROR)
        {
            int errCode = WSAGetLastError();
            LPSTR errString = NULL;  
            int size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM, 
                0,
                errCode,
                0,
                (LPWSTR)&errString,
                0,              
                0);              
            printf("Error code %d:  %s\n\nMessage was %d bytes, in case you cared to know this.\n\n", errCode, errString, size);

            LocalFree(errString);

        }
        /*
        if (0 != connect(sck, (SOCKADDR *)&sadr, sizeof(sadr))) {
            cout << "Blad polaczenia. Kod bledu: " << GetLastError() << endl;
            closesocket(sck);
            WSACleanup();
        system("pause");
            return 0;
        }
        */
        closesocket(sck);
    }

    WSACleanup();


    system("pause");
    return 0;
}