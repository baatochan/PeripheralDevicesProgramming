#include <tchar.h>
#include <iostream>
#include <windows.h>
using namespace std;
BOOL modyfikacja(HANDLE hComPort);
HANDLE hSerial;

int _tmain(int argc, TCHAR *argv[], TCHAR *envp[])
{
	DWORD cBytes_out, cBytes_in;
	DWORD dwMask;
	char cBuffer_out[] = "";
	TCHAR cBuffer_in[80];

	cout << "Port szeregowy otwarty, nacisnij ctrl+c aby przerwac" << endl;
	hSerial = CreateFile(_T("COM9:"), GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, 0, NULL);
	// sprawdzenie wartosci uchwytu
	if (hSerial == INVALID_HANDLE_VALUE) {
		cout << "Blad otwarcia" << endl;
		system("pause");
		return 0;
	}
	// modyfikacja parametrów portu szeregowego
	if (!modyfikacja(hSerial)) {
		cout << "Bledy konfiguracji" << endl;
		system("pause");
		return 0;
	}

	// zapis do portu szeregowego
	if (!WriteFile(hSerial, cBuffer_out, strlen(cBuffer_out), &cBytes_out, NULL)) {
		cout << "Blad zapisu" << endl;
		system("pause");
		return 0;
	}

	SetCommMask(hSerial, EV_RXCHAR | EV_ERR);

	cBuffer_in[0] = 0;

	// dopoki ctrl+c nie jest wcisniety, rób!
	while (cBuffer_in[0] != 0x03) {
		cout << "P1" << endl;
		WaitCommEvent(hSerial, &dwMask, 0);
		cBytes_in = 1;
		cout << "P1_2" << endl;
		while (cBytes_in != 0) {
			// czyta dane z urzadzenia i wyswietla
			cout << "P2" << endl;
			if (ReadFile(hSerial, cBuffer_in, 79, &cBytes_in, NULL)) {
				if (cBytes_in == 0) break;
				printf("%s", cBuffer_in, cBytes_in);
				if (!WriteFile(hSerial, cBuffer_in, cBytes_in, &cBytes_out, NULL)) {
					cout << "Blad zapisu" << endl;
					system("pause");
					return 0;
				}
			}
		}
	}
	//zamkniêcie uchwytu
	CloseHandle(hSerial);
	return 1;
}

BOOL   modyfikacja(HANDLE hComPort)
{
	COMMTIMEOUTS ctos;
	DCB PortDCB; //struktura kontroluj¹ca ustawienia portu szeregowego 
	PortDCB.DCBlength = sizeof(DCB);
	// ustaw standardowe ustawienia dla portu szeregowego
	GetCommState(hSerial, &PortDCB);
	// zmiana ustawien portu szeregowego
	PortDCB.BaudRate = 9600;              // Current baud
	PortDCB.fBinary = TRUE;               // Binary mode; no EOF check
	PortDCB.fParity = TRUE;               // Enable parity checking
	PortDCB.fOutxCtsFlow = FALSE;         // No CTS output flow control
	PortDCB.fOutxDsrFlow = FALSE;         // No DSR output flow control
	PortDCB.fDtrControl = DTR_CONTROL_ENABLE; // DTR flow control type
	PortDCB.fDsrSensitivity = FALSE;      // DSR sensitivity
	PortDCB.fTXContinueOnXoff = TRUE;     // XOFF continues Tx
	PortDCB.fOutX = FALSE;                // No XON/XOFF out flow control
	PortDCB.fInX = FALSE;                 // No XON/XOFF in flow control
	PortDCB.fErrorChar = FALSE;           // Disable error replacement
	PortDCB.fNull = FALSE;                // Disable null stripping
	PortDCB.fRtsControl = RTS_CONTROL_ENABLE; // RTS flow control
	PortDCB.fAbortOnError = FALSE;        // Do not abort reads/writes on error
	PortDCB.ByteSize = 8;                 // Number of bits/byte, 4-8
	PortDCB.Parity = NOPARITY;            // 0-4=no,odd,even,mark,space
	PortDCB.StopBits = ONESTOPBIT;        // 0,1,2 = 1, 1.5, 2

	if (!SetCommState(hSerial, &PortDCB)) {
		cout << "Blad konfiguracji portu szeregowego" << endl;
		system("pause");
		return false;
	}
	// ustaw timeouty odczytu
	ctos.ReadIntervalTimeout = MAXDWORD; //maksymalne dopuszczalne przerwy pomiêdzy bajtami
	ctos.ReadTotalTimeoutMultiplier = MAXDWORD; //mno¿nik do wyliczenia okresu timeoutu
	ctos.ReadTotalTimeoutConstant = 1; //sta³a s³u¿¹ca do wyliczenia ca³ego okresu timeotu
	ctos.WriteTotalTimeoutMultiplier = 0;
	ctos.WriteTotalTimeoutConstant = 0;
	if (!SetCommTimeouts(hSerial, &ctos)) {
		cout << "Blad konfiguracji portu szeregowego" << endl;
		system("pause");
		return false;
	}
	return true;
}