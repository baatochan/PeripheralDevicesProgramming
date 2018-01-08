#include "Bluetooth.h"



std::list<HANDLE*> Bluetooth::available_adapters;
std::list<BLUETOOTH_DEVICE_INFO*> Bluetooth::devices;
short Bluetooth::uploadStatus = 0;


Bluetooth::Bluetooth(void)
{
    BLUETOOTH_FIND_RADIO_PARAMS bt_find_radio_params_tmp = { 
        sizeof(BLUETOOTH_FIND_RADIO_PARAMS) 
    };
    bt_find_radio_params = bt_find_radio_params_tmp;
    selected_adapter = NULL;
    selected_device = NULL;

}

Bluetooth::~Bluetooth(void)
{
}

int Bluetooth::FindAdapters(bool refresh /*= true*/)
{
    if(refresh)
        available_adapters.clear();

    HBLUETOOTH_RADIO_FIND bt_radio_find = NULL;
    HANDLE* tmp = new HANDLE;

    BLUETOOTH_FIND_RADIO_PARAMS bt_find_radio_params_tmp = { 
        sizeof(BLUETOOTH_FIND_RADIO_PARAMS) 
    };

    bt_radio_find = BluetoothFindFirstRadio(&bt_find_radio_params, tmp);

    if(bt_radio_find == NULL)
    {
        DWORD error =  GetLastError();
        switch(error)
        {
        case ERROR_NO_MORE_ITEMS :
        default:
            std::cout<< "Nie znaleziono urzadzen." << std::endl;
            break;
        }
        //handle error
        return 0;
    }
    
    available_adapters.push_back(tmp);

    tmp = new HANDLE;
	while (BluetoothFindNextRadio(&bt_radio_find, tmp)) 
    {
        available_adapters.push_back(tmp);
        tmp = new HANDLE;
    }

    std::cout<< "Znaleziono " << available_adapters.size() << "." << std::endl; 
    int i = 0;
    for (std::list<HANDLE*>::iterator it = available_adapters.begin(); it != available_adapters.end(); it++, i++)
{
        std:: cout << "Adapter " << i << ": ";
        show_adapter_details(*it);
}

	if(!BluetoothFindRadioClose(bt_radio_find))
        std::cout << "Blad zamykania \"BluetoothFindRadioClose(bt_radio_find)\"." << std::endl;

    return 0;
}

void Bluetooth::show_adapter_details(HANDLE* handle, bool details /* = false */)
{
    BLUETOOTH_RADIO_INFO *info = new BLUETOOTH_RADIO_INFO;
    info->dwSize = sizeof(BLUETOOTH_RADIO_INFO);

    BluetoothGetRadioInfo(*handle, info);

    wprintf(L"%s \n", info->szName);
    wprintf(L"\tMAC: %02x:%02x:%02x:%02x:%02x:%02x \n\n", info->address.rgBytes[5], 
			info->address.rgBytes[4], info->address.rgBytes[3], 
			info->address.rgBytes[2], info->address.rgBytes[1], 
			info->address.rgBytes[0]);
}


int Bluetooth::Look_For_Devices(bool refresh /* = false */)
{
    if(refresh)
        devices.clear();

    if(selected_adapter == NULL)
    {
        if(available_adapters.size() == 0)
        {
            std::cout << "Nie ma zadnych adapterów przez które mozna by bylo znalesc dostepne urzadzenia."<<  std::endl;
            return 0;
        }
        else
        {
            selected_adapter = available_adapters.front();
            //wyobr?
        }
    }
    HBLUETOOTH_DEVICE_FIND bt_dev_find = NULL;
    BLUETOOTH_DEVICE_SEARCH_PARAMS bt_dev_search_params = {
	sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS), //rozmiar struktury
	0, //bool: czy zwracaæ urz¹dzenia autentykowane
	0, //bool: czy zwracaæ urz¹dzenia zapamiêtane 
	1, //bool: czy zwracaæ urz¹dzenia nieznane 
	1, //bool: czy zwracaæ urz¹dzenia po³¹czone 
	1, //bool: czy zwracaæ kolejne urz¹dzenie 
	5, //czas szukania urz¹dzeñ - wielokrotnoœæ 1.28 sekundy
	NULL
    };


    BLUETOOTH_DEVICE_INFO* tmp = new BLUETOOTH_DEVICE_INFO;
    tmp->dwSize = sizeof(BLUETOOTH_DEVICE_INFO);

    bt_dev_find = BluetoothFindFirstDevice(&bt_dev_search_params, tmp);
    devices.push_back(tmp);


    if (bt_dev_find == NULL) {
        std::cout << "Nie znaleziono zadnych urzadzen BlueTooth." << std::endl;
	    return 0;
    }

    
    tmp = new BLUETOOTH_DEVICE_INFO;
    tmp->dwSize = sizeof(BLUETOOTH_DEVICE_INFO);

    while(BluetoothFindNextDevice(bt_dev_find, tmp)) 
    {
	    devices.push_back(tmp);
	    tmp = new BLUETOOTH_DEVICE_INFO;
        tmp->dwSize = sizeof(BLUETOOTH_DEVICE_INFO);
    }
    BluetoothFindDeviceClose(bt_dev_find);

    std::cout<< "Znaleziono " << devices.size() << " urzadzen." << std::endl; 
    int i = 0;
    for (std::list<BLUETOOTH_DEVICE_INFO*>::iterator it = devices.begin(); it != devices.end(); it++, i++)
    {
            std:: cout << "Urzadzenie " << i << ": ";
            show_device_details(*it);
    }

    return devices.size();
}

void Bluetooth::show_device_details(BLUETOOTH_DEVICE_INFO* dev, bool details /* = false */)
{
    wprintf(L"%s \n", dev->szName);
    wprintf(L"\tMAC: %02x:%02x:%02x:%02x:%02x:%02x \n\n", dev->Address.rgBytes[5], 
			dev->Address.rgBytes[4], dev->Address.rgBytes[3], 
			dev->Address.rgBytes[2], dev->Address.rgBytes[1], 
			dev->Address.rgBytes[0]);
}

void Bluetooth::select_device(int selected)
{
    if((unsigned int)selected > devices.size())
        return;

    int i = 0;
    for (std::list<BLUETOOTH_DEVICE_INFO*>::iterator it = devices.begin(); it != devices.end(); it++, i++)
            if(i == selected)
                selected_device = *it;
}

bool Bluetooth::authenticate_selected_device()
{
    if(selected_device == NULL)
        return false;

    if(BluetoothAuthenticateDeviceEx(NULL, selected_adapter, selected_device,NULL, MITMProtectionRequired)== ERROR_CANCELLED)
        return false;
    return true;
}

bool Bluetooth::send_file(std::string data)
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (result != NO_ERROR) {
	    std::cout << "Blad WSAStartup: " << result;
	    return false;
    }

    SOCKET Socket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
     
    if (Socket == INVALID_SOCKET) 
    {
        std::cout << "Nieprawidlowe gniazdo. ErrId: " << GetLastError() << std::endl;
	    return false;
    } 
    else 
    {
        SOCKADDR_BTH sockAddr;
        memset (&sockAddr, 0, sizeof(sockAddr));

	    sockAddr.addressFamily = AF_BTH;
	    sockAddr.btAddr = selected_device->Address.ullLong;
	    sockAddr.port = (ULONG)BT_PORT_ANY;
	    sockAddr.serviceClassId = OBEXObjectPushServiceClass_UUID;

	    if (connect(Socket, (SOCKADDR *) &sockAddr, sizeof(sockAddr)) != NO_ERROR) 
        {	
            std::cout << "Blad laczeniu. Kod bledu: " << GetLastError() << std::endl;
		    closesocket(Socket);
		    WSACleanup();
		    return false;
	    }
        

		//Wczytanie Pliku Do pamieci
		std::ifstream file;
		file.open(data, std::ios::in | std::ios::binary );
		if(!file.is_open())
		{
			std::cout << std::endl << "Nie znaleziono pliku." << std::endl;
			closesocket(Socket);
			return false;
		}
		int fsize = file.tellg();
		file.seekg( 0, std::ios::end );
		int ffsize = file.tellg(); fsize = ffsize - fsize; //Okreslenie rozmiaru pliku
		file.seekg(0);
		char *Filedata = new char[fsize];
		file.read(Filedata,fsize);
		file.close();
		unsigned char recv_buffor[512];
		//

		uploadStatus = 0;

		int err = 0;
		int tmpint = 0;
		unsigned char connect_request[] = {0x80, 0x00, 0x07, 0x10, 0x00, 0x04, 0x00};
		unsigned char disconnect_request[] = {0x81, 0x00, 0x03};
		if ((err = send (Socket, (char*)connect_request, 7, 0 ))==SOCKET_ERROR) // wysylamy pakiet	
		{
			std::cout << std::endl << "Error while requestion connection. [send]. Err:" << err << "(" << WSAGetLastError() << ")." <<std::endl;
			closesocket(Socket);
			WSACleanup();
			return false;
		}
		if((err = recv (Socket, (char *)recv_buffor, 3, 0))==SOCKET_ERROR) // wysylamy pakiet	
		{
			std::cout << std::endl << "Error while requestion connection. [recv]. Err:" << err << "(" << WSAGetLastError() << ")." <<std::endl;
			closesocket(Socket);
			WSACleanup();
			return false;
		}
		if(recv_buffor[0] == 0xA0)
#ifdef PRINT_INFO
			std::cout << std::endl << "Connection established." << std::endl;
#else
			;
#endif
		else
		{
			std::cout << std::endl << "Connection request Failed. Err:" << recv_buffor[0] << std::hex << (int)recv_buffor[0] << std::dec << std::endl;
			closesocket(Socket);
			WSACleanup();
			return false;
		}
		tmpint = (int) recv_buffor[1]; tmpint = tmpint << 8; tmpint += (int) recv_buffor[2]; tmpint-=3;
		if(tmpint > 0)
		{
			std::cout << std::endl << "Reading "<< tmpint <<" bytes..." << std::endl;
			recv (Socket, (char *)recv_buffor+3, tmpint, 0);
		}

		unsigned char date_now[] = "20111114T183000";

        //Mamy polaczenie mozna wysylac.

		int first_packet = 3 + data.length()*2 + 5 + 3+ strlen((char*)date_now);

		int ptr = 0;
		int pos_now = 0;
		short packet_size = MAX_PACKET_SIZE - 6;
		bool last_packet = false;

		if(fsize < MAX_PACKET_SIZE-first_packet-6)
		{
			packet_size = fsize;
			last_packet = true;
		}
		else
			packet_size -= first_packet;
		//packet_size = fsize;//(packet_size < -6-first_packet); //ilosc danych

		unsigned char *buffer = new unsigned char[packet_size+6+first_packet];
		buffer[0] = last_packet ? 0x82 : 0x02;
		short s = packet_size+6+first_packet;
		buffer[1] = (char) s>>8;
		buffer[2] = (char) s;
		
		
		s = data.length()*2+3;
		buffer[3] = 0x01;
		buffer[4] = (char) s>>8;
		buffer[5] = (char) s;
		//std::cout << std::hex << s << " " << (int) buffer[4] << " " <<(int)buffer[5] << std::endl;
		ptr = 6;
		for(int i = 0; i < data.length(); i++, ptr+=2) 
			{buffer[ptr] = 0x00; buffer[ptr+1] = data.at(i);} 
		//ptr--;
		buffer[ptr++] = 0xC3; //?
		buffer[ptr++] = (char) fsize>24;
		buffer[ptr++] = (char) fsize>>16;
		buffer[ptr++] = (char) fsize>>8;
		buffer[ptr++] = (char) fsize;

		buffer[ptr++] = 0x44; 
		s = strlen((char*)date_now)+3;
		buffer[ptr++] = s>>8;
		buffer[ptr++] = s;
		s-=3;
		for (int i = 0; i < s; i++, ptr++) // wpisujemy date do bufora
			buffer[ptr] = date_now[i]; 
		//size+3?
		packet_size +=3;
		buffer[ptr++] = last_packet ? 0x49 : 0x48;
		buffer[ptr++] = packet_size>>8;
		buffer[ptr++] = packet_size;
		packet_size -=3;
		/*memcpy(buffer+ptr, (char*) Filedata, packet_size);
		pos_now+=packet_size;*/
	
		for (int i = 0; i < packet_size; i++, ptr++, pos_now++) // wpisujemy dane pliku do bufora
			buffer[ptr] = Filedata[pos_now];
		
		//std::cout << "0%";
		
		//std::cout << "(" << fsize << ")";
		if ((err = send (Socket, (char*)buffer, packet_size+6+first_packet, 0 ))==SOCKET_ERROR) // wysylamy pakiet	
		{
			std::cout << std::endl << "Error while sending first packet. [send]. Err:" << err << "(" << WSAGetLastError() << ")." <<std::endl;
			closesocket(Socket);
			WSACleanup();
			return false;
		}
		//std::cout << ", 1%";
		//if(last_packet)
		//{
			recv_buffor[0] = 0; recv_buffor[1] = 0; recv_buffor[2] = 0;
			if((err = recv (Socket, (char *)recv_buffor, 3, 0))==SOCKET_ERROR) // wysylamy pakiet	
			{
				std::cout << std::endl << "Error while sending first packet. [recv]. Err:" << err << "(" << WSAGetLastError() << ")." <<std::endl;
				closesocket(Socket);
				WSACleanup();
				return false;
			}
			//std::cout << ", 2%";
			delete[] buffer;
			if(recv_buffor[0] == 0x90)
#ifdef PRINT_INFO
				std::cout << std::endl << "Packet sent successfully."  <<std::endl;
#else
				;
#endif
			else if(recv_buffor[0] == 0xA0)
#ifdef PRINT_INFO
				std::cout << std::endl << "File sent successfully."  <<std::endl;
#else
				;
#endif
			else
			{
				std::cout << std::endl << "Error while sending first packet. Response:" << std::hex << (int) recv_buffor[0] << std::dec <<std::endl;
				closesocket(Socket);
				WSACleanup();
				return false;
			}
			tmpint = (int) recv_buffor[1]; tmpint = tmpint << 8; tmpint += (int) recv_buffor[2];tmpint-=3;
			if(tmpint > 0)
			{
#ifdef PRINT_INFO
				std::cout << std::endl << "Reading "<< tmpint <<" bytes..." << std::endl;
#endif
				recv (Socket, (char *)recv_buffor+3, tmpint, 0);
			}
		//}

		std::cout << "0%";
		
		int ups = 0;
		if(!last_packet)
			while(!last_packet)
			{
				if(ups < (int)(((double)pos_now/(double)fsize)*100))
				{
					ups = (int)(((double)pos_now/(double)fsize)*100);
					std::cout << ", " << ups << "%";
				}
			
				packet_size = MAX_PACKET_SIZE - 6;
				if(fsize - pos_now < packet_size)
				{
					packet_size = fsize - pos_now;
					last_packet = true;
				}
				buffer = new unsigned char[packet_size+6];
				short s = packet_size+6;
				buffer[0] = last_packet ? 0x82 : 0x02;
				buffer[1] = (char) s>>8;
				buffer[2] = (char) s;
				s = packet_size+3;
				buffer[3] = last_packet ? 0x49 : 0x48;
				buffer[4] = (char) s>>8;
				buffer[5] = (char) s;

				for (int i = 0, j = 6; i < packet_size; j++, i++, pos_now++) // wpisujemy dane pliku do bufora
					buffer[j] = Filedata[pos_now];
				//std::cout << " sending (" << packet_size+6<< "),";
				if((err = send(Socket, (char*)buffer, packet_size+6, 0))==SOCKET_ERROR) // wysylamy pakiet	
				{
					std::cout << std::endl << "Error while sending packet. [send]. Err:" << err << "(" << WSAGetLastError() << ")." <<std::endl;
					closesocket(Socket);
					WSACleanup();
					return false;
				}
				
				recv_buffor[0] = 0; recv_buffor[1] = 0; recv_buffor[2] = 0;
				if((err = recv (Socket, (char *)recv_buffor, 3, 0)) == SOCKET_ERROR) // odbieramy odpowiedz
				{
					std::cout << std::endl << "Error while sending packet. [recv]. Err:" << err << "(" << WSAGetLastError() << ")." <<std::endl;
					closesocket(Socket);
					WSACleanup();
					return false;
				}
				delete[] buffer;
					if(recv_buffor[0] == 0x90)
#ifdef PRINT_INFO
					std::cout << std::endl << "Packet sent successfully."  <<std::endl;
#else
					;
#endif
				else if(recv_buffor[0] == 0xA0)
#ifdef PRINT_INFO
					std::cout << std::endl << "File sent successfully."  <<std::endl;
#else
					;
#endif
				else
				{
					std::cout << std::endl << "Error while sending first packet. Response:" << std::hex << (int) recv_buffor[0] << std::dec <<std::endl;
					closesocket(Socket);
					WSACleanup();
					return false;
				}
				tmpint = (int) recv_buffor[1]; 
				tmpint = tmpint << 8; tmpint += (int) recv_buffor[2];tmpint-=3;
				if(tmpint > 0)
				{
#ifdef PRINT_INFO
					std::cout << std::endl << "Reading "<< tmpint <<" bytes..." << std::endl;
#endif
					recv (Socket, (char *)recv_buffor+3, tmpint, 0);
				}
			}

		//std::cout << std::endl << "Sending disconnect request. " << std::endl;
		if ((err = send (Socket, (char*)disconnect_request, 3, 0 ))==SOCKET_ERROR) // wysylamy pakiet	
		{
			std::cout << std::endl << "Error while sending disconnect request. [send]. Err:" << err << "(" << WSAGetLastError() << ")." <<std::endl;
			closesocket(Socket);
			WSACleanup();
			return false;
		}
		recv_buffor[0] = 0;  recv_buffor[1] = 0; recv_buffor[2] = 0;
		if((err = recv (Socket, (char *)recv_buffor, 3, 0))==SOCKET_ERROR) // wysylamy pakiet	
		{
			std::cout << std::endl << "Error while sending disconnect request. [recv]. Err:" << err << "(" << WSAGetLastError() << ")." <<std::endl;
			closesocket(Socket);
			WSACleanup();
			return false;
		}

		if(recv_buffor[0] == 0xA0 || recv_buffor[0] == 0xD3)
#ifdef PRINT_INFO
			std::cout << std::endl << "Disconencted Successfully."  <<std::endl;
#else
			;
#endif
		else
		{
			std::cout << std::endl << "Error while disconnecting. Response:" << std::hex << (int) recv_buffor[0] << std::dec <<std::endl;
			closesocket(Socket);
			WSACleanup();
			return false;
		}
		tmpint = (int) recv_buffor[1]; tmpint = tmpint << 8; tmpint += (int) recv_buffor[2];tmpint-=3;
		if(tmpint > 0)
		{
#ifdef PRINT_INFO
			std::cout << std::endl << "Reading "<< tmpint <<" bytes..." << std::endl;
#endif
			recv (Socket, (char *)recv_buffor+3, tmpint, 0);
		}

		uploadStatus = 100;
		/*std::cout << "Lastpacket " << (last_packet ? "tak" : "nie") << " " << packet_size+6+first_packet << " " << fsize << std::endl;
		std::cout << std::hex;
		for(int i = 0; i < packet_size+6+first_packet; i++)
			std::cout << "" << (int)buffer[i] << "\t" << (char)buffer[i] <<std::endl;*/
		std::cout << std::endl;
		
        closesocket(Socket);
		WSACleanup();
    }
    return true;

}