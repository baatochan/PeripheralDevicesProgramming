//Listing 1: Szukanie pierwszego adaptera Bluetooth
BLUETOOTH_FIND_RADIO_PARAMS bt_find_radio_params = {
sizeof(BLUETOOTH_FIND_RADIO_PARAMS)
};
//uchwyty przechowujące znalezione adaptery i urządzenia
HBLUETOOTH_RADIO_FIND bt_radio_find = NULL;
HBLUETOOTH_DEVICE_FIND bt_dev_find = NULL;
cout << "Szukanie adapterow BT:" << endl;
bt_radio_find = BluetoothFindFirstRadio(&bt_find_radio_params, &adapters[0]);


//Listing 2: Wykrywanie pozostałych adapterów
if (bt_radio_find == NULL) {
cout << "Brak dostepnych adapterow. Kod bledu: " << GetLastError() << endl;
} else {
int adapters_found = 1;
while (BluetoothFindNextRadio(&bt_radio_find, &adapters[adapters_found])) {
adapters_found++;
if (adapters_found == MAX_BT_ADAPTERS-1) {
cout << "Podlaczonych jest wiecej niz 10 adapterow BT do komputera.";
break;
}
}
for (int i = 0; i < adapters_found; i++)
Strona: 3/8print_adapter_info(adapters[i], i);
if(!BluetoothFindRadioClose(bt_radio_find))
cout << "Blad zamykania \"BluetoothFindRadioClose(bt_radio_find)\"." << endl;
}


//Listing 3: Drukowanie informacji o adapterze
void print_adapter_info (HANDLE BThandle, int i) {
BluetoothGetRadioInfo(BThandle, &bt_radio_info);
wprintf(L"Adapter %d ) ", i);
wprintf(L"%s ", bt_radio_info.szName);
wprintf(L"MAC: %02x:%02x:%02x:%02x:%02x:%02x ", bt_radio_info.address.rgBytes[1],
bt_radio_info.address.rgBytes[0], bt_radio_info.address.rgBytes[2],
bt_radio_info.address.rgBytes[3], bt_radio_info.address.rgBytes[4],
bt_radio_info.address.rgBytes[5]);
wprintf(L"ClassofDevice: 0x%08x ", bt_radio_info.ulClassofDevice);
wprintf(L"Manufacturer: 0x%04x\n", bt_radio_info.manufacturer);
}


//Listing 4: Wybór adaptera
int wybrany_adapter = 0;
cout << "Wybierz adapter: ";
cin >> wybrany_adapter;


//Listing 5: Struktura BLUETOOTH_DEVICE_SEARCH_PARAMS
BLUETOOTH_DEVICE_SEARCH_PARAMS bt_dev_search_params = {
sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS), //rozmiar struktury
1, //bool: czy zwracać urządzenia autentykowane
0, //bool: czy zwracać urządzenia zapamiętane
1, //bool: czy zwracać urządzenia nieznane
1, //bool: czy zwracać urządzenia połączone
1, //bool: czy zwracać kolejne urządzenie
3, //czas szukania urządzeń - wielokrotność 1.28 sekundy
NULL
};


//Listing 6: Wykrywanie urządzeń
bt_dev_search_params.hRadio = adapters[wybrany_adapter];
cout << endl << "Wyszukiwanie urzadzen BT w poblizu:" << endl;
BLUETOOTH_DEVICE_INFO devices[MAX_BT_DEVICES];
devices[0].dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
bt_dev_find = BluetoothFindFirstDevice(&bt_dev_search_params, &devices[0]);
if (bt_dev_find = NULL) {
cout << "Nie znaleziono zadnych urzadzen BT." << endl;
return 0;
} else {
int devices_found = 1;
devices[devices_found].dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
while(BluetoothFindNextDevice(bt_dev_find, &devices[devices_found])) {
devices_found++;
devices[devices_found].dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
}
BluetoothFindDeviceClose(bt_dev_find);
for (int i = 0; i < devices_found; i++)
print_device_info(devices[i], i);
}
int wybrane_urzadzenie = 0;
cout << "Wybierz urzadzenie:";
cin >> wybrane_urzadzenie;
cout << endl;


//Listing 7: Drukowanie informacji o urządzeniu Bluetooth
void print_device_info (BLUETOOTH_DEVICE_INFO BThandle, int i) {
wprintf(L"Device %d ) ", i);
wprintf(L" Name: %s ", BThandle.szName);
wprintf(L" MAC: %02x:%02x:%02x:%02x:%02x:%02x ", BThandle.Address.rgBytes[1],
Bthandle.Address.rgBytes[0],
BThandle.Address.rgBytes[2],
Bthandle.Address.rgBytes[3],
BThandle.Address.rgBytes[4],
BThandle.Address.rgBytes[5]);
wprintf(L" ClassofDevice: 0x%08x ", BThandle.ulClassofDevice);
wprintf(L" Connected:%s ", BThandle.fConnected ? L"T" : L"N");
wprintf(L" Authenticated:%s ", BThandle.fAuthenticated ? L"T" : L"N");
wprintf(L" Remembered:%s\n", BThandle.fRemembered ? L"T" : L"N");
}


//Listing 8: Autoryzacja urządzenia Bluetooth
BluetoothAuthenticateDeviceEx(NULL, adapters[wybrany_adapter],
&devices[wybrane_urzadzenie],
NULL, MITMProtectionRequired);


//Listing 9: Łączenie z urządzeniem Bluetooth
WSADATA wsaData;
int result = WSAStartup(MAKEWORD(2,2), &wsaData);
if (result != NO_ERROR) {
cout << "Blad WSAStartup: " << result;
return 0;
}
sck = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
if (sck == INVALID_SOCKET) {
cout << "Blad przy tworzeniu gniazda. Kod bledu: " << GetLastError() << endl;
return 0;
} else {
sadr.addressFamily = AF_BTH;
sadr.btAddr = devices[wybrane_urzadzenie].Address.ullLong;
sadr.port = (ULONG)BT_PORT_ANY;
sadr.serviceClassId = OBEXObjectPushServiceClass_UUID;
if (0 != connect (sck, (SOCKADDR *) &sadr, sizeof(sadr))) {
cout << "Blad laczeniu. Kod bledu: " << GetLastError() << endl;
closesocket( sck );
WSACleanup();
return 0;
}
closesocket(sck);
}
