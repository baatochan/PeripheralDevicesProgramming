#include <windows.h>
#include <iostream>
//#include <fstream>

int main()
{
	//    std::ifstream gpsPort;
	//
	//    std::cout << "GPS test" << std::endl;
	//
	//    gpsPort.open("COM9");
	//
	//    for(int i = 0; i < 10; i++)
	//    {
	//        std::string input;
	//
	//        gpsPort >> input;
	//        std::cout << input << std::endl;
	//    }
	//
	//    gpsPort.close();

	// Open serial port
	HANDLE serialHandle;
	char buffer[256];

	serialHandle = CreateFile((LPCWSTR)"\\\\.\\COM9", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	// Do some basic settings
	DCB serialParams = { 0 };
	DWORD read;
	serialParams.DCBlength = sizeof(serialParams);

	GetCommState(serialHandle, &serialParams);
	serialParams.BaudRate = CBR_4800;
	serialParams.ByteSize = 8;
	serialParams.StopBits = ONESTOPBIT;
	serialParams.Parity = NOPARITY;
	SetCommState(serialHandle, &serialParams);

	// Set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 50;
	timeout.ReadTotalTimeoutConstant = 50;
	timeout.ReadTotalTimeoutMultiplier = 50;
	timeout.WriteTotalTimeoutConstant = 50;
	timeout.WriteTotalTimeoutMultiplier = 10;

	SetCommTimeouts(serialHandle, &timeout);

	for (int i = 0; i < 10; i++)
	{
		ReadFile(serialHandle, buffer, sizeof(buffer), &read, NULL);
		std::cout << buffer << std::endl;
	}

	CloseHandle(serialHandle);

	return 0;
}
