#include <stdio.h>
#include <iostream>
#include <winsock2.h>
#include <Ws2bth.h>
#include <BluetoothAPIs.h>
#include <windows.h>
#include <cstring>

#pragma comment ( lib, "Irprops.lib")
using namespace std;

#define MAX_BT_DEVICES 10
#define MAX_BT_RADIOS 10

typedef struct
{
	HANDLE handle;
	BLUETOOTH_RADIO_INFO info;
} BT_RADIO;

int obex_send_file (SOCKET s, char* path);

TCHAR *GetLastErrorMessage(DWORD last_error)
{
   static TCHAR errmsg[512];
   if (!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, last_error, 0, errmsg, 511, NULL))
   {	return (GetLastErrorMessage(GetLastError()));  
   }
  
   return errmsg;
}

BOOL bt_auth_func (LPVOID parametr, PBLUETOOTH_DEVICE_INFO dev)
{
	DWORD result = BluetoothSendAuthenticationResponse ((HANDLE)parametr, dev, L"1111");	
	if (ERROR_SUCCESS != result)
	{	return FALSE;
	}

	return TRUE;
}

BLUETOOTH_DEVICE_INFO* bt_find_devices (HANDLE* radio, unsigned& num_found)
{
	/* Parametry wyszukiwania */
	BLUETOOTH_DEVICE_SEARCH_PARAMS bt_search_params;
	bt_search_params.dwSize = sizeof (BLUETOOTH_DEVICE_SEARCH_PARAMS);
	bt_search_params.fReturnAuthenticated = true;
	bt_search_params.fReturnRemembered = true;
	bt_search_params.fReturnConnected = true;
	bt_search_params.fReturnUnknown = true;
	bt_search_params.fIssueInquiry = true;
	bt_search_params.cTimeoutMultiplier = 10;
	bt_search_params.hRadio = radio;

	BLUETOOTH_DEVICE_INFO* btdev_info = new BLUETOOTH_DEVICE_INFO[MAX_BT_DEVICES];
	num_found = 0;
	btdev_info[num_found].dwSize = sizeof (BLUETOOTH_DEVICE_INFO);

	/* Szukamy pierwszego urzadzenia */
	HBLUETOOTH_DEVICE_FIND devresult;
	devresult = BluetoothFindFirstDevice (&bt_search_params, &btdev_info[num_found]);

	/* Szukamy pozostalych jezeli znaleziono pierwsze */
	if (devresult)
	{
		do
		{
			BluetoothGetDeviceInfo (radio, &btdev_info[num_found]);
			btdev_info[++num_found].dwSize = sizeof (BLUETOOTH_DEVICE_INFO);
		} while (TRUE == BluetoothFindNextDevice (devresult, &btdev_info[num_found]));
	}
	else
	{	return NULL;
	}

	/* Konczymy prace */
	BluetoothFindDeviceClose (devresult);
	return btdev_info;
}

BT_RADIO* bt_find_radios (unsigned& num_found)
{
	/* Miejsce na wyniki, parametry wyszukiwania */
	BT_RADIO* radios = new BT_RADIO[MAX_BT_RADIOS];
	num_found = 0;
	BLUETOOTH_FIND_RADIO_PARAMS bt_find_params;
	bt_find_params.dwSize = sizeof (BLUETOOTH_FIND_RADIO_PARAMS);

	/* Szukamy pierwsze radio w komputerze */
	HBLUETOOTH_RADIO_FIND result; 
	result = BluetoothFindFirstRadio (&bt_find_params, &(radios[num_found].handle));
	radios[num_found].info.dwSize = sizeof (BLUETOOTH_RADIO_INFO);

	/* Szukamy pozostale radia (jezeli pierwsze istnieje) */
	if (result)
	{
		do
		{
			/* Wpisujemy radio do tablicy wynikow */
			BluetoothGetRadioInfo (radios[num_found].handle, &(radios[num_found].info));
			radios[++num_found].info.dwSize = sizeof (BLUETOOTH_RADIO_INFO);
		} while (TRUE == BluetoothFindNextRadio (result, &(radios[num_found].handle)));
	}
	else
	{	return NULL;
	}

	/* Konczymy prace */
	BluetoothFindRadioClose (result);
	return radios;
}

void bt_connect (BLUETOOTH_DEVICE_INFO dev_info)
{
	WORD wVersionRequested = 0x202;
	WSADATA m_data;

	/* Startujemy machine WSA */
	if (0 == ::WSAStartup(wVersionRequested, &m_data))
	{
		/* Tworzymy socket */
		SOCKET s = ::socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);

		if (INVALID_SOCKET == GetLastError())
		{
			wprintf (L"Invalid socket!\n");
			return;
		}

		/* Tworzymy adres bluetoothowy */
		SOCKADDR_BTH sab;
		memset (&sab, 0, sizeof (sab));
		sab.addressFamily = AF_BTH;
		sab.btAddr = dev_info.Address.ullLong;
		sab.port = (ULONG)BT_PORT_ANY;
		sab.serviceClassId = OBEXObjectPushServiceClass_UUID;

		/* Probujemy sie polaczyc */
		if (connect (s, (SOCKADDR *)&sab, sizeof(sab)))
		{
			wprintf (L"Ojjj wystapil blad... [%d] %s\n", GetLastError(), GetLastErrorMessage (GetLastError()));
			closesocket (s);
			WSACleanup();
			return;
		}
		else
		{
			/* Wszystko sie udalo :) Wysylamy pliczek */
			//OBEXsendtxt2 ("a.txt", strlen("a.txt"), s);
			obex_send_file (s, "a.txt");
		}
	}
}

int main()
{
	/* Szukamy radia */
	unsigned i = 0, N_FOUND_RADIOS = 0;
	BT_RADIO* radios = bt_find_radios (N_FOUND_RADIOS);

	wprintf (L"Znalazlem %d adapterow BT: \n", N_FOUND_RADIOS);
	for (int i = 0; i < N_FOUND_RADIOS; ++i)
	{	wprintf (L"%d. %s\n", i+1, radios[i].info.szName);
	}

	wprintf (L"\nWybierz adapter: ");
	int selection = 0;
	do
	{
		scanf ("%d", &selection);
	} while (selection < 1 && selection >= N_FOUND_RADIOS);

	/* Ustawiamy radio */
	HANDLE bt_selected_radio = radios[selection-1].handle;
	BluetoothEnableDiscovery (bt_selected_radio, TRUE);
	BluetoothEnableIncomingConnections (bt_selected_radio, TRUE);

	/* Szukamy urzadzen BT */
	unsigned N_FOUND_DEVICES = 0;
	BLUETOOTH_DEVICE_INFO* devices = bt_find_devices (&bt_selected_radio, N_FOUND_DEVICES);
	wprintf (L"Znalazlem %d urzadzen: \n", N_FOUND_DEVICES);
	for (int i = 0; i < N_FOUND_DEVICES; ++i)
	{	wprintf (L"%d. %s\n", i+1, devices[i].szName);
	}

	wprintf (L"\nWybierz urzadzenie: ");
	selection = 0;
	do
	{
		scanf ("%d", &selection);
	} while (selection < 1 && selection >= N_FOUND_DEVICES);

	/* Rejestrujemy funkcje, ktora obsluzy autoryzacje */
	BLUETOOTH_DEVICE_INFO btdev_info = devices[selection-1];
	HBLUETOOTH_AUTHENTICATION_REGISTRATION bt_reg_func_handle;
	BluetoothRegisterForAuthentication (&btdev_info, &bt_reg_func_handle, bt_auth_func, bt_selected_radio);

	/* Podlaczamy sie i wysylamy pliczek */
	bt_connect (btdev_info);	
	system ("PAUSE");
	return 0;
}
#if 0
int obex_send_file (char* path, SOCKET s)
{
	int res = 0;
	bool final_bit = false;
	int packet_data_size = 1024;
	int packet_max_size = 1024;

	/* Otwieramy pliczek */
	FILE* fp = fopen (path, "r"); // rb ?
	if (!fp)
	{
		printf ("obex_send_file: Failed opening file!\n");
		return -1;
	}

	/* Sprawdzamy ile wazy */
	fseek (fp, 0, SEEK_END);
	int file_size = ftell (fp);
	fseek (fp, 0, SEEK_SET);

	/* Pobieramy dane i zamykamy */
	char* file_data = new char[file_size];
	fread (file_data, file_size, 1, fp);
	fclose (fp);

	char data[] = "20101103T183000";
	printf ("obex_send_file: file size: %d bytes\n", file_size);

	/**
	 * Probujemy sie polaczyc... znaczenie bajtow:
	 * 0x80			- connect request
	 * 0x00 0x07	- dlugosc pakietu
	 * 0x10			- obex version (1.0)
	 * 0x00			- ?
	 * 0x20 0x00	- maksymalny rozmiar pakietu
	 */

	unsigned char conn_buf[] = {0x80, 0x00, 0x07, 0x10, 0x00, 0x20, 0x00};
	res = send (s, (char *)conn_buf, 7, 0);
    if (SOCKET_ERROR == res)
	{
        printf("send1 failed with error: %d\n", WSAGetLastError());
        closesocket (s);
        WSACleanup();
        return -1;
    }
	else
	{
		printf ("obex_send_file: sent %d bytes\n", res);
	}

	/**
	 * Oczekujemy odpowiedzi. W przypadku powodzenia otrzymamy:
	 * 0x00			- ?
	 * 0x00			- ?
	 * 0x00			- ?
	 */

	res = recv (s, (char *)conn_buf, 3, 0); // 100 -> 3 (arg.3)
	if (res > 0)
	{	printf("Bytes received: %d\n", res);
	}
	else if (res == 0 )
	{	printf("Connection closed\n");
	}
	else
	{	printf("recv failed with error: %d\n", WSAGetLastError());
	}

	/* Wysylamy pierwsza paczke. Najpierw sprawdzamy, czy trzeba dzielic plik na pakiety */     
	if (file_size <= packet_max_size)
	{
		packet_data_size = file_size; 
		final_bit = true;
	}
 
	/* Wyznaczamy faktyczna wielkosc pakietu (tzn z meta-danymi) */
	int packet_size = 6 + strlen(path)*2 + 8 + strlen(data) + 3 + packet_data_size;
    //int packet_size = 3 + (strlen(path)*2 + 3) + 5 + 18 + 3 + packet_data_size;
    unsigned char* buf = new unsigned char[packet_size];

	/**
	 * Tworzymy pakiet dla pierwszej paczki danych. Znaczenie bitow jest nastepujace.
	 * 0x02/0x82			- "nie-ostatni"/ostatni pakiet
	 * 0xAA 0xBB			- rozmiar pakietu
	 * 0x01					- header "za chwile bedzie nazwa pakietu"
	 * 0xAA 0xBB			- rozmiar nazwy pakietu (uwaga! nazwa jest w unikodzie (wchar))
	 * 0xAA ... 0xZZ		- nazwa pakietu
	 * 0xc3					- header "za chwile beda dane pakietu"
	 * 0xAA 0xBB 0xCC 0xDD  - rozmiar pliku
	 * 0x44					- header "za chwile bedzie data"
	 * 0xAA 0xBB			- rozmiar danych daty
	 * 0xAA ... 0xZZ		- data
	 * 0x48/0x49			- ?????????????
	 * 0xAA 0xBB			- wielkosc czesci pliku w pakiecie
	 * 0xAA ...				- tresc pliku
	 */

	buf[0] = 0x02;
    if (final_bit)
	{	buf[0] = 0x82;
	}

    buf[1] = (char)(packet_size >> 8); 
	buf[2] = (char)packet_size;
    buf[3] = 0x01;
    buf[4] = (char)((strlen (path)*2)>>8);
	buf[5] = (char)(strlen (path)*2);

	/* Konwersja z str na wstr */
	int i = 0;
	for (i = 0; i < strlen (path); i += 2)
	{	buf[i+6] = (i%2) == 0 ? 0x00 : path[(int)(i/2)];
	}
    
	i += 6;
	buf[i++] = 0xc3;
	memcpy (buf + i++, (char *)&file_size, sizeof (int));
	buf[i++] = 0x44;
	buf[i++] = 0x00;
	buf[i++] = 0x12;
	memcpy (buf + i++, data, 14);
	buf[i++] = final_bit ? 0x49 : 0x48;
	memcpy (buf + i++, (char *)&packet_data_size, sizeof (short));
	memcpy (buf + i++, (char *)file_data, packet_data_size);

	/* W koncu wysylamy dane */
	res = send (s, (char *)buf, packet_size, 0);
	if (SOCKET_ERROR == res)
	{
		printf ("failor \n");
		closesocket (s);
		WSACleanup();
		return -1;
	}
	else
	{
		printf ("obex_send_file: sent %d bytes\n", res);
	}

	/* Odbieramy odpowiedz urzadzenia */
	res = recv (s, (char *)conn_buf, 3, 0);
	if (res <= 0)
	{
		printf ("failor! \n");
		closesocket (s);
		WSACleanup();
		return -1;
	}
	else
	{
		printf ("obex_send_file: received %d bytes\n", res);
	}

    delete[] buf;

	/* Wysylamy reszte paczuszek */
	int fpos = packet_data_size;
	final_bit = false;

	while (fpos < file_size)
	{
		packet_size = packet_data_size + 6;
		if (file_size - fpos <= packet_max_size)
		{
			packet_data_size = file_size - fpos;
			final_bit = true;
		}

		buf[0] = final_bit ? 0x82 : 0x02;
		memcpy (buf + 1, (char *)packet_data_size, sizeof (short));
		buf[3] = final_bit ? 0x49 : 0x48;
		memcpy (buf + 4, (char *)packet_data_size, sizeof (short)); //?
		memcpy (buf + 6, (char *)file_data + fpos, packet_data_size);

		res = send (s, (char *)buf, packet_size, 0);
		if (SOCKET_ERROR == res)
		{
			printf ("failor!! \n");
			closesocket (s);
			WSACleanup();
			return -1;
		}

		res = recv (s, (char *)conn_buf, 3, 0);
		if (res < 0)
		{
			printf ("failor!!! \n");
			closesocket (s);
			WSACleanup();
			return -1;
		}
	}

	return 0;
}
#endif 

int wsa_cleanup (SOCKET& s, const char* msg)
{
	printf ("%s", msg);
	closesocket (s);
	WSACleanup();
	return 1;
}

int obex_send_file (SOCKET s, char* path)
{
	int result = 0;
	int max_data_packet_size = 1024; // maksymalny rozmiar paczki danych
	int data_packet_size = 1024; // przyjety rozmiar paczki danych
	bool final_bit = false; // final bit okresla ostatnia paczke
	int name_len = strlen (path); // dlugosc nazwy pliku
   
	FILE* fp = fopen (path, "r"); // otwieramy plik
	if (!fp)
	{	return wsa_cleanup (s, "Blad otwierania pliku!");
	}

	fseek (fp, 0, SEEK_END); // pobieramy dlugosc pliku
	int file_size = ftell (fp);
	fseek (fp, 0, SEEK_SET);

	char* file_data = new char[file_size]; // ladujemy plik
	fread (file_data, file_size, 1, fp);
	fclose (fp);

	char send_date[] = "20101103T183000"; // tworzymy date

	int fdp = 0; // =file-data pointer... wskaznik na kolejny bajt w pliku
	int pdp = 0; // =packet-data pointer... wskaznik na kolejny bajt w pakiecie

	/**
	 * Probujemy sie polaczyc... znaczenie bajtow:
	 * 0x80			- connect request
	 * 0x00 0x07	- dlugosc pakietu
	 * 0x10			- obex version (1.0)
	 * 0x00			- ?
	 * 0x20 0x00	- maksymalny rozmiar pakietu
	 */

	unsigned char* buf = new unsigned char[7];
	buf[0] = 0x80; buf[1] = 0x00; buf[2] = 0x07; buf[3] = 0x10;
	buf[4] = 0x00; buf[5] = 0x20; buf[6] = 0x00;

	result = send (s, (char *)buf, 7, 0 ); // wysylamy pakiet
	if (SOCKET_ERROR == result)
	{	return wsa_cleanup (s, "Sending failed [failor-0]");
	}
   
	result = recv (s, (char *)buf, 3, 0); // odbieramy odpowiedz
	if (SOCKET_ERROR == result)
	{	return wsa_cleanup (s, "Receiving failed [failor-0");
	}
     
	delete [] buf;

	/**
	 * Tworzymy pakiet dla pierwszej paczki danych. Znaczenie bajtow jest nastepujace.
	 * 0x02/0x82			- "nie-ostatni"/ostatni pakiet
	 * 0xAA 0xBB			- rozmiar pakietu
	 * 0x01					- header "za chwile bedzie nazwa pakietu"
	 * 0xAA 0xBB			- rozmiar nazwy pakietu (uwaga! nazwa jest w unikodzie (wchar))
	 * 0xAA ... 0xZZ		- nazwa pakietu
	 * 0xc3					- header "za chwile beda dane pakietu"
	 * 0xAA 0xBB 0xCC 0xDD  - rozmiar pliku
	 * 0x44					- header "za chwile bedzie data"
	 * 0xAA 0xBB			- rozmiar danych daty
	 * 0xAA ... 0xZZ		- data
	 * 0x48/0x49			- ?????????????
	 * 0xAA 0xBB			- wielkosc czesci pliku w pakiecie
	 * 0xAA ...				- tresc pliku
	 */

	if (file_size <= max_data_packet_size) // jezeli plik sie zmiesci w jednej paczce
	{
		data_packet_size = file_size;
		final_bit = true; // ustawiamy final_bit
	}
 
	// wyznaczamy faktyczny rozmiar pakietu (dane + meta-dane)
    int real_packet_size = 3 + (name_len*2 + 3) + 5 + 18 + 3 + data_packet_size;
    buf = new unsigned char[real_packet_size]; // tworzymy pakiet
	buf[0] = final_bit ? 0x82 : 0x02;
    buf[1] = (char)(real_packet_size>>8); 
	buf[2] = (char)real_packet_size;
    buf[3] = 0x01;
    buf[4] = (char)((name_len*2+3)>>8);
	buf[5] = (char)(name_len*2+3);
	pdp = 6;
    
	for(int i = 0; i < name_len; i++, pdp += 2 ) //wpisujemy nazwe pakietu do bufora
    {	buf[pdp] = 0x00; buf[pdp+1] = path[i]; // przy okazji konwertujemy ASCII->UNICODE
	}
    
    buf[pdp++] = 0xC3; buf[pdp++] = 0x00; 
	buf[pdp++] = (char)(file_size>>16); 
	buf[pdp++] = (char)(file_size>>8); 
	buf[pdp++] = (char)(file_size); 
	buf[pdp++] = 0x44; buf[pdp++] = 0x00; buf[pdp++] = 0x12;

	for (int i = 0; i < 15; i++) // wpisujemy date do bufora
	{	buf[pdp++] = send_date[i]; 
	}

	buf[pdp++] = final_bit ? 0x49 : 0x48;
	buf[pdp++] = (char)((data_packet_size+3)>>8); 
	buf[pdp++] = (char)(data_packet_size+3);
   
	for (int i = 0; i < data_packet_size; i++) // wpisujemy dane pliku do bufora
	{	buf[pdp++] = file_data[fdp++];
	}

	result = send( s, (char *)buf, real_packet_size, 0 ); // wysylamy dziadostwo
	if (SOCKET_ERROR == result)
	{	return wsa_cleanup (s, "Sending failed [failor-1]");
	}
   
	result = recv(s, (char *)buf, 3, 0); // czekamy na odpowiedz
	if (SOCKET_ERROR == result)
	{	return wsa_cleanup (s, "Receiving failed [failor-1]");
	}

	delete [] buf;
		
	/* Kolejne paczuszki - analogia do poprzedniego.
	 * Jedyne co sie zmienia to rozmiar bufora
	 * wynika to z tego, ze nie wysylamy juz daty i innych smieci */
	while(fdp < file_size)
	{
  		if((file_size - fdp) <= max_data_packet_size)
		{
			data_packet_size = file_size - fdp; 
			final_bit = true;
		}
 
		real_packet_size = 6 + data_packet_size;
		buf = new unsigned char [real_packet_size];

		buf[0] = final_bit ? 0x82 : 0x02;
		buf[1] = (char)(real_packet_size>>8); 
		buf[2] = (char)real_packet_size;
		buf[3] = final_bit ? 0x49 : 0x48;
		buf[4] = (char)((data_packet_size+3)>>8); 
		buf[5] = (char)(data_packet_size+3);
    
		for (int i = 0; i < data_packet_size; i++)
		{	buf[i+6] = file_data[fdp++]; 
		}   
   
		result = send (s, (char *)buf, real_packet_size, 0);
		if (SOCKET_ERROR == result) 
		{	return wsa_cleanup (s, "Sending failed [failor-2]");
		}
   
		result = recv(s, (char *)buf, 3, 0);
		if (SOCKET_ERROR == result) 
		{	return wsa_cleanup (s, "Receiving failed [failor-2]");
		}
	}

	return 1;
}
