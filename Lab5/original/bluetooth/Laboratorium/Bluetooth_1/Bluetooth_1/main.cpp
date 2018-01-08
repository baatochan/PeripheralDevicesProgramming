#include "Bluetooth.h"

/*
#include <process.h>

bool listen_v = false;

void handleSocket(void *sock)
{
	SOCKET* Socket = (SOCKET*)sock;
	char head[3];
	while(listen_v)
	{
		recv(*Socket,(char*)head,3,0);
		int size = head[1]>>8; size+=head[2];
		std::cout << std::hex << "Got packet. Type:" << (int)head[0] << ", Size = " << head[1] << std::endl;
		if(size>0)
		{
			char *data = new char[size];
			recv(*Socket,data,size,0);
			delete[] data;
		}
		head[0] = 0; head[1] = 0; head[2] = 0;
	}
	_endthread();
}


void startListening(void *sock)
{
	SOCKET *lst = (SOCKET*)sock;
	while(listen_v)
	{
		SOCKET *Socket = new SOCKET;
		*Socket = accept(*lst,0,0);
		std::cout << std::endl << "Accepted new connection." << std::endl;
		_beginthread(handleSocket,0,(void*)Socket);
		Sleep(100);
	}
	_endthread();
}
*/
int main()
{
    Bluetooth bt;
    bt.FindAdapters(true);
    bt.Look_For_Devices(true);
    int tmp;
    while(bt.selected_device == NULL)
    {
        std::cout << "Select Device: "; std::cin >> tmp; std::cout << std::endl;
        bt.select_device(tmp);
        if(bt.selected_device != NULL)
        {
            std::cout << "Wybrano urzadzenie: ";
            bt.show_device_details(bt.selected_device);
            break;		
        }
        else
            std::cout << "Podano zly nr urzadzenia. Try Again. " << std::endl;

    }
    std::cout << "Autoryzowanie urzadzenia... ";
    if(!bt.authenticate_selected_device())
    {
        std::cout << "Nie mozna bylo dokonac autoryzacji urzadzenia!" << std::endl;
        return 0;
    }
	/*
	char acc;
	std::cout << "Bind Listening? (y/n): ";
	std::cin >> acc; std::cout << std::endl;
	if(acc == 'y' || acc == 'Y')
	{
		listen_v = true;
		WSADATA wsaData;
		int result = WSAStartup(MAKEWORD(2,2), &wsaData);
		if (result != NO_ERROR) {
			std::cout << "Blad WSAStartup: " << result;
		}
		else
		{
			SOCKET *Socket = new SOCKET;
			*Socket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
     
			if (*Socket == INVALID_SOCKET) 
			{
				std::cout << "Nieprawidlowe gniazdo. ErrId: " << GetLastError() << std::endl;
			} 
			else 
			{
				SOCKADDR_BTH sockAddr;
				memset (&sockAddr, 0, sizeof(sockAddr));

				sockAddr.addressFamily = AF_BTH;
				sockAddr.port = (ULONG)BT_PORT_ANY;

				if (bind(*Socket,(struct sockaddr *) &sockAddr,sizeof(SOCKADDR_BTH))) 
				{
					std::cout << "Unable to bind. Err:" << GetLastError() << std::endl;
					closesocket(*Socket);
					WSACleanup();
				}
				else
				{
					if (listen(*Socket, SOMAXCONN) ==  SOCKET_ERROR) 
					{
						std::cout << "Unable to listen. Err:" << GetLastError() << std::endl;
						closesocket(*Socket);
							WSACleanup();
					}
					_beginthread(startListening, 0, (void*)Socket);
				}
			}
		}
	}
	while(listen_v)
	{
		int tmp = 0;
		std::cin >> tmp;
		if(tmp == 0)
		{
			listen_v = false;
			break;
		}
		Sleep(2000);
	}*/
    std::cout << "OK!" << std::endl;
    std::cout << "Wysylanie pliku... ";
    bt.send_file("1.txt");
	system("PAUSE");
    return 0;
}