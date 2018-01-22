#include <windows.h>
#include <iostream>
#include <string>
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
	char buffer[1024];
	std::string input;

	serialHandle = CreateFile(TEXT("\\\\.\\COM8"), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

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

	while (true)
	{
		ReadFile(serialHandle, buffer, sizeof(buffer), &read, NULL);

		for (int j = 0; j < sizeof(buffer); j++)
		{
			if (buffer[j] == -52)
				break;

			input += buffer[j];

			if (buffer[j] == 10)
			{
				if (input.size() > 2)
				{
					// Parsowanie
					std::string type = input.substr(0, 6);
					if (type == "$GPGGA")
					{
						if (input.size() > 47)
						{
							std::string allData[11];

							for (int k = 0; k < 11; k++)
							{
								std::size_t commaPos = input.find(",");
								input = input.substr(commaPos + 1);
								commaPos = input.find(",");
								std::string data = input.substr(0, commaPos);

								allData[k] = data;
							}

							// Pozycja
							// Lat
							std::string temp = allData[1].substr(0, 2);
							int degrees_lat = atoi(temp.c_str());

							temp = allData[1].substr(2, 2);
							int minutes_lat = atoi(temp.c_str());
							temp = allData[1].substr(5, 4);
							float sec_lat = atof(temp.c_str());
							sec_lat = 60 * sec_lat / 10000;

							std::cout << degrees_lat << "*" << minutes_lat << "'" << sec_lat << "''" << allData[2];

							//Lon
							temp = allData[3].substr(0, 3);
							int degrees_lon = atoi(temp.c_str());

							temp = allData[3].substr(3, 2);
							int minutes_lon = atoi(temp.c_str());
							temp = allData[3].substr(6, 4);
							float sec_lon = atof(temp.c_str());
							sec_lon = 60 * sec_lon / 10000;

							std::cout <<  " " << degrees_lon << "*" << minutes_lon << "'" << sec_lon << "''" << allData[4];

							//Altitude
							float altitude = atof(allData[8].c_str());
							float sealevel = atof(allData[10].c_str());
							altitude -= sealevel;
							std::cout << " " << altitude <<  "m n.p.m." << std::endl;
						}
					}






					//std::cout << input;
					input.clear();
				}
			}
		}
	}

	CloseHandle(serialHandle);

	return 0;
}