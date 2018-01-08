    #include <WinSock2.h>
    #include <ws2bth.h>
    #include <BluetoothAPIs.h>
    #include <iostream>
    #include <vector>
	#include <fstream>
	#include <string>
	#include <stdio.h>
	#include <string.h>
     
    struct BlueRadio
    {
            HANDLE handle;
            BLUETOOTH_RADIO_INFO info;
    };
     
    int main()
    {
            BLUETOOTH_FIND_RADIO_PARAMS bfrp;
            bfrp.dwSize = sizeof(bfrp);
     
            BlueRadio br;
            br.info.dwSize = sizeof(br.info);
            HBLUETOOTH_RADIO_FIND hBlueFind = BluetoothFindFirstRadio(&bfrp,&br.handle);
            if(hBlueFind == NULL)
            {
                    std::cout << GetLastError() << "BluetoothFindFirstRadio\n";
                    return 1;
            }
     
            std::vector<BlueRadio> radia;
     
            do
            {
                    if(BluetoothGetRadioInfo(br.handle,&br.info) != ERROR_SUCCESS)
                    {
                            std::cout << GetLastError() << "BluetoothGetRadioInfo\n";
                            return 1;
                    }
                    radia.push_back(br);
            } while(BluetoothFindNextRadio(hBlueFind,&br.handle));
     
            if(GetLastError() != ERROR_NO_MORE_ITEMS)
            {
                    std::cout << GetLastError() << "BluetoothFindNextRadio\n";
                    return 1;
            }
     
            if(BluetoothFindRadioClose(hBlueFind) != TRUE)
            {
                    std::cout << GetLastError() << "BluetoothFindRadioClose\n";
                    return 1;
            }
     
            for(unsigned int i=0;i<radia.size();++i)
            {
                    std::cout << "radio " << i << "\nadres : " << std::hex <<
                            radia[i].info.address.ullLong << std::dec << "\nklasa : " <<
                            radia[i].info.ulClassofDevice << "\nsubversion : " <<
                            radia[i].info.lmpSubversion << "\nmanufacturer : " <<
                            radia[i].info.manufacturer << '\n';
                    std::cout << "nazwa : " << radia[i].info.szName << '\n';
            }
            std::cout << std::endl;
     
            BLUETOOTH_DEVICE_SEARCH_PARAMS bdsp;
            bdsp.dwSize = sizeof(bdsp);
            bdsp.hRadio = radia.front().handle;
            bdsp.cTimeoutMultiplier = 1;
            bdsp.fIssueInquiry = TRUE;
            bdsp.fReturnAuthenticated = TRUE;
            bdsp.fReturnConnected = TRUE;
            bdsp.fReturnRemembered = TRUE;
            bdsp.fReturnUnknown = TRUE;
     
            BLUETOOTH_DEVICE_INFO bdi;
            bdi.dwSize = sizeof(bdi);
            std::vector<BLUETOOTH_DEVICE_INFO> urzadzenia;
     
            HBLUETOOTH_DEVICE_FIND hBlueDevFind = BluetoothFindFirstDevice(&bdsp,&bdi);
            if(hBlueDevFind == NULL)
            {
                    std::cout << GetLastError() << "BluetoothFindFirstDevice\n";
                    return 1;
            }
			
            do { urzadzenia.push_back(bdi); }
            while(BluetoothFindNextDevice(hBlueDevFind,&bdi));
     
            if(GetLastError() != ERROR_NO_MORE_ITEMS)
            {
                    std::cout << GetLastError() << "BluetoothFindNextDevice\n";
                    return 1;
            }
     
            if(BluetoothFindDeviceClose(hBlueDevFind) != TRUE)
            {
                    std::cout << GetLastError() << "BluetoothFindDeviceClose\n";
                    return 1;
            }
     
            for(unsigned int i=0;i<urzadzenia.size();++i)
            {
                    std::cout << "urzadzenie " << i << "\nadres : " << std::hex <<
                            urzadzenia[i].Address.ullLong << std::dec
                            << "\nklasa : " << urzadzenia[i].ulClassofDevice
                            << "\nconnected : " << urzadzenia[i].fConnected
                            << "\nremembered : " << urzadzenia[i].fRemembered
                            << "\nauthenticated : " << urzadzenia[i].fAuthenticated << '\n';
                    std::cout << "nazwa : " << urzadzenia[i].szName << '\n';
            }
            std::cout << std::endl;


            for(unsigned int i=0;i<radia.size();++i) CloseHandle(radia[i].handle);
     
			
            // winsock
     
            WORD wWSAVersion = MAKEWORD(2,2);
            WSADATA sWSAData;
            if(WSAStartup(wWSAVersion,&sWSAData) != 0)
            {
                    std::cout << WSAGetLastError() << "WSAStartup\n";
                    return 1;
            }
     
            SOCKET s = socket(AF_BTH,SOCK_STREAM,BTHPROTO_RFCOMM);
            if(s == INVALID_SOCKET)
            {
                    std::cout << WSAGetLastError() << "socket\n";
                    return 1;
            }
     
            SOCKADDR_BTH sBlueAddr;
            sBlueAddr.addressFamily = AF_BTH;
            sBlueAddr.btAddr = urzadzenia.front().Address.ullLong;
            sBlueAddr.serviceClassId = OBEXObjectPushServiceClass_UUID;
            sBlueAddr.port = 0;

			unsigned char rcvbuf[512];
     
            if(connect(s,(const sockaddr*)&sBlueAddr,sizeof(sBlueAddr)) != 0)
            {
                    std::cout << WSAGetLastError() << "connect\n";
                    return 1;
            }
     
            unsigned char connect_request[] = {
                    0x80, // opcode
                    0x00, 0x07, // packet length
                    0x10, // obex version
                    0x00, // connect flags
                    0x04, 0x00 // max packet length (1024B = 1KB)
            };
            if(send(s,(const char*)connect_request,7,0) == SOCKET_ERROR)
            {
                    std::cout << WSAGetLastError() << "send\n";
                    return 1;
            }

			if(recv(s,(char*)rcvbuf,512,0) == SOCKET_ERROR)
            {
                    std::cout << WSAGetLastError() << "recv\n";
                    return 1;
            }

			if(rcvbuf[0] == 0xa0) std::cout << "polaczenie ok\n";
            else return 1;
     /////////////////////////////
	std::fstream plik( "c.txt", std::ios::in | std::ios::binary ); //zak³adamy, ¿e plik istnieje
	char bufor[ 1024 ];

	plik.read( bufor, 1024 ); //wczytuje tyle danych ile siê zmieœci do bufora

			unsigned char packet_request[] = {
                    0x02, // 
                    0x0422, 0x01, // 
                    0x0017, // 
                    0x0221, // 
                    0xC3, 0x00001000,
					0x48, 0x0403
					// )
            };

			int len = sizeof(*packet_request)+sizeof(*bufor);

			unsigned char *packet = new unsigned char[len];
			for (int i = 0; i< (int)strlen((const char*)packet_request); i++)
				packet[i] = packet_request[i];
			for (int j=0, i = (int)strlen((const char*)packet_request); i< len; i++,j++)
				packet[i] = bufor[j];

			std::cout<<bufor;


            if(send(s,(const char*)packet,1058,0) == SOCKET_ERROR)
            {
                    std::cout << WSAGetLastError() << "packet\n";
                    return 1;
            }
			std::cout<<"dupa";
			if(recv(s,(char*)rcvbuf,512,0) == SOCKET_ERROR)
            {
                    std::cout << WSAGetLastError() << "recv\n";
                    return 1;
            }

			if(rcvbuf[0] == 0x90) std::cout << "odebrano pakiet ok\n";
            else return 1;
			delete [] packet;
	int i = 0;
	do
	{
	plik.read( bufor, 1024 ); //wczytuje tyle danych ile siê zmieœci do bufora

			unsigned char packet_request1[] = {
                    0x02, // 
                    0x0406, 
                    0x48, // 
					0x0403
					// )
            };

			len = sizeof(*packet_request1)+sizeof(*bufor);

			packet = new unsigned char[len];
			for (int i = 0; i< (int)strlen((const char*)packet_request1); i++)
				packet[i] = packet_request1[i];
			for (int j=0, i = (int)strlen((const char*)packet_request1); i< len; i++,j++)
				packet[i] = bufor[j];


            if(send(s,(const char*)packet,sizeof(*packet),0) == SOCKET_ERROR)
            {
                    std::cout << WSAGetLastError() << "packet\n";
                    return 1;
            }
			if(recv(s,(char*)rcvbuf,512,0) == SOCKET_ERROR)
            {
                    std::cout << WSAGetLastError() << "recv\n";
                    return 1;
            }

			if(rcvbuf[0] == 0x90) std::cout << "odebrano pakiet\n";
            else return 1;
			delete [] packet;
i++;
	}while(i!=2);

		plik.read( bufor, 1024 ); //wczytuje tyle danych ile siê zmieœci do bufora

			unsigned char packet_request2[] = {
                    0x82, // 
                    0x0406, 
                    0x49, // 
					0x0403
					// )
            };

			len = sizeof(*packet_request2)+sizeof(*bufor);

			packet = new unsigned char[len];
			for (int i = 0; i< (int)strlen((const char*)packet_request2); i++)
				packet[i] = packet_request2[i];
			for (int j=0, i = (int)strlen((const char*)packet_request2); i< len; i++,j++)
				packet[i] = bufor[j];


            if(send(s,(const char*)packet,sizeof(*packet),0) == SOCKET_ERROR)
            {
                    std::cout << WSAGetLastError() << "packet\n";
                    return 1;
            }
			if(recv(s,(char*)rcvbuf,512,0) == SOCKET_ERROR)
            {
                    std::cout << WSAGetLastError() << "recv\n";
                    return 1;
            }

			if(rcvbuf[0] == 0xa0) std::cout << "odebrano plik\n";
            else return 1;
			delete [] packet;
			/////////////////////////
            
            
     
            
     
            unsigned char disconnect_request[] = {
                    0x81, // opcode
                    0x00, 0x03 // packet length
            };
     
            if(send(s,(const char*)disconnect_request,3,0) == SOCKET_ERROR)
            {
                    std::cout << WSAGetLastError() << "send_dis\n";
                    return 1;
            }
     
            if(recv(s,(char*)rcvbuf,512,0) == SOCKET_ERROR)
            {
                    std::cout << WSAGetLastError() << "recv_dis\n";
                    return 1;
            }
     
            if(rcvbuf[0] == 0xa0 || rcvbuf[0] == 0xd3) std::cout << "dis ok\n";
     
            if(closesocket(s) != 0)
            {
                    std::cout << WSAGetLastError() << "closesocket\n";
                    return 1;
            }
     
            if(WSACleanup() != 0)
            {
                    std::cout << WSAGetLastError() << "WSACleanup\n";
                    return 1;
            }

            return 0;
    }
