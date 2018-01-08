#include "stdafx.h"
 
#include <Ws2bth.h>
#include <BluetoothAPIs.h>
#include <Bthsdpdef.h>
#include <stdio.h>
#include <WinSock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <bthdef.h>
 
#include <vector>
 
#pragma comment(lib, "Irprops.lib")
 
BLUETOOTH_FIND_RADIO_PARAMS m_bt_find_radio = {
  sizeof(BLUETOOTH_FIND_RADIO_PARAMS)
};
 
BLUETOOTH_RADIO_INFO m_bt_info = {
  sizeof(BLUETOOTH_RADIO_INFO),
  0,
};
 
BLUETOOTH_DEVICE_SEARCH_PARAMS m_search_params = {
  sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS),
  1,
  0,
  1,
  1,
  1,
  15,
  NULL
};
 
BLUETOOTH_DEVICE_INFO m_device_info = {
  sizeof(BLUETOOTH_DEVICE_INFO),
  0,
};
 
HANDLE m_radio = NULL;
HBLUETOOTH_RADIO_FIND m_bt = NULL;
HBLUETOOTH_DEVICE_FIND m_bt_dev = NULL;
 
// lista znalezionych adapterów
std::vector<HANDLE> radios;
 
// lista znalezionych urz¹dzeñ
std::vector<BLUETOOTH_DEVICE_INFO> devices;
 
int wmain(int argc, wchar_t **args) {
    unsigned int j=MAXINT; // numer urz¹dzenia, które bêdziemy parowaæ
    BLUETOOTH_DEVICE_INFO wybrane; // wybrane urz¹dzenie, z którym chcemy siê ³¹czyæ
    SOCKET sck;
    SOCKADDR_BTH sadr;
    char inc[20];
 
    wprintf(L"Szukanie adapterow Bluetooth...\n");
 
    // znajdujemy pierwszy adapter bluetooth
    m_bt = BluetoothFindFirstRadio(&m_bt_find_radio, &m_radio);
 
    // jeœli m_bt to null, to system nie znalaz³ ¿adnych adapterów Bluetooth.
    if (m_bt == NULL) {
        wprintf(L"Nie znaleziono adapterow Bluetooth");
        return 1;
    }
 
    // dodajemy znaleziony adapter do listy
    do {
        // dodajemy ten adapter do listy znalezionych adapterów
        radios.push_back(m_radio);
        // jeœli znaleŸliœmy kolejny adapter, to równie¿ dodajmy go do listy
    } while (BluetoothFindNextRadio(&m_bt_find_radio, &m_radio));
 
    // Przestajemy szukaæ adapterów Bluetoot
 
    // wyœwietlmy listê
    for (unsigned int i=0;i<radios.size();i++) {
        BluetoothGetRadioInfo(m_radio,&m_bt_info);
        wprintf(L"Adapter nr. %d:\r\n", i);
        wprintf(L"\tNazwa:\t\t%s\r\n", m_bt_info.szName);
        wprintf(L"\tMAC\t\t%02x:%02x:%02x:%02x:%02x:%02x\r\n", m_bt_info.address.rgBytes[1], m_bt_info.address.rgBytes[0], m_bt_info.address.rgBytes[2], m_bt_info.address.rgBytes[3], m_bt_info.address.rgBytes[4], m_bt_info.address.rgBytes[5]);
        wprintf(L"\tKlasa:\t\t0x%08x\r\n", m_bt_info.ulClassofDevice);
        wprintf(L"\tProducent:\t0x%04x\r\n", m_bt_info.manufacturer);
    }
 
    // zak³adamy na razie, ¿e wybrany zosta³ zerowy adapter
    // ustawmy wiêc w opcjach wyszukiwania ten w³aœnie adapter
    m_search_params.hRadio = radios[0];
 
    // zaczynamy szukaæ urz¹dzeñ dostêpnych poprzez bluetooth
    wprintf(L"\nSzukam urzadzen widocznych poprzez Bluetooth...\n\n");
    m_bt_dev = BluetoothFindFirstDevice(&m_search_params, &m_device_info);
 
    //BluetoothSelectDevices(*m_search_params);
 
    do {
        devices.push_back(m_device_info);
    } while(BluetoothFindNextDevice(m_bt_dev,&m_device_info));
 
    // wyœwietlmy te urz¹dzenia
    for (unsigned int i=0;i<devices.size();i++) {
        m_device_info = devices[i];
        wprintf(L"Urzadzenie %d:\r\n", i);
        wprintf(L"\tNazwa:\t\t%s\r\n", m_device_info.szName);
        wprintf(L"\tMAC:\t\t%02x:%02x:%02x:%02x:%02x:%02x\r\n", m_device_info.Address.rgBytes[1], m_device_info.Address.rgBytes[0], m_device_info.Address.rgBytes[2], m_device_info.Address.rgBytes[3], m_device_info.Address.rgBytes[4], m_device_info.Address.rgBytes[5]);
        wprintf(L"\tKlasa:\t\t0x%08x\r\n", m_device_info.ulClassofDevice);
        wprintf(L"\tPolaczony:\t%s\r\n", m_device_info.fConnected ? L"tak" : L"nie");
        wprintf(L"\tParowany:\t%s\r\n", m_device_info.fAuthenticated ? L"tak" : L"nie");
        wprintf(L"\tPamietany:\t%s\r\n", m_device_info.fRemembered ? L"tak" : L"nie");
    }
 
    // wybierzmy urz¹dzenie, z którym bêdziemy siê parowaæ
    do {
        printf("Z ktorym urzadzeniem parowac? (nr) ");
        scanf_s("%u",&j); // pobieramy numer urz¹dzenia do parowania
    } while (j > devices.size());
 
    wybrane = devices[j];
 
    // parujmy urz¹dzenia
    BluetoothAuthenticateDevice(NULL,radios[0],&wybrane,NULL,MITMProtectionNotRequired);
 
    // ³¹czymy siê z wybranym urz¹dzeniem
    sck = socket(AF_BTH,SOCK_STREAM,BTHPROTO_RFCOMM);
 
    if (sck == INVALID_SOCKET) {
        printf("Blad przy tworzeniu gniazda");
        BluetoothFindDeviceClose(m_bt_dev);
        BluetoothFindRadioClose(m_bt);
        system("pause");
        return 2;
    }
 
    sadr.addressFamily = AF_BTH;
    sadr.btAddr = wybrane.Address.ullLong;
 
    // dokonujemy po³¹czenia
    connect(sck,(SOCKADDR *) &sadr,sizeof(sadr));
 
    send(sck,OBEX_CONNECT,sizeof(OBEX_CONNECT),0);
    recv(sck,&(inc[0]),25,0);
 
    printf("%s",inc);
 
    // zamykamy gnizado
    closesocket(sck);
 
    // Przestajemy szukaæ urz¹dzeñ Bluetooth
    BluetoothFindDeviceClose(m_bt_dev);
 
    // Przestajemy szukaæ adapterów Bluetooth
    BluetoothFindRadioClose(m_bt);
 
    system("pause");
    return 0;
}