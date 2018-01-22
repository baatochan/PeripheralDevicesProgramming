#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>

static DCB dcb;
static HANDLE hPort;
static char lpBuffor_read[33], lpBuffor_write[33];
static DWORD RS_ile;

using namespace std;

int main(){

	/*LPCWSTR portName;
	cout << "Podaj nazwe portu:  ";
	cin >> portName;*/
	LPCWSTR portName = L"\\\\.\\COM18";
	hPort = CreateFile(portName, GENERIC_WRITE |
		GENERIC_READ, 0, NULL,
		OPEN_EXISTING, 0, NULL);

	dcb.DCBlength = sizeof(dcb);

	dcb.BaudRate = CBR_4800;
	dcb.fParity = TRUE;
	dcb.Parity = EVENPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.ByteSize = 7;

	dcb.fDtrControl = DTR_CONTROL_ENABLE;
	dcb.fRtsControl = RTS_CONTROL_ENABLE;

	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fDsrSensitivity = FALSE;
	dcb.fAbortOnError = FALSE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;
	dcb.fErrorChar = FALSE;
	dcb.fNull = FALSE;

	char data[512];
	char szer[9];
	char wid, len;
	char dl[9];
	for (int i = 0; i < 9; i++){
		szer[i] = 0;
		dl[i] = 0;
	}
	string url = "https://google.com/maps/place/";
	string http;
	fstream plik;
	plik.open("Adres.txt", std::ios::in | std::ios::out);

	if (SetCommState(hPort, &dcb)){
		cout << "Udalo sie polaczyc z portem\n";
		while (true){
			ReadFile(hPort, data, 512, &RS_ile, NULL);
			//cout << data << "\n";
			for (int i = 0; i < 512; i++){
				if (data[i] == 'G' && data[i + 1] == 'G' && data[i + 2] == 'A'){
					i += 15;
					for (int j = 0; data[i] != ','; j++, i++){
						szer[j] = data[i];
						cout << szer[j];
					}
					i++;
					wid = data[i];
					cout << " " << wid << " ";
					i += 3;
					for (int j = 0; data[i] != ','; j++, i++){
						dl[j] = data[i];
						cout << dl[j];
					}
					i++;

					float d;
					//cout << (float)szer[5] << "  " <<(float)szer[6] << "\n";
					szer[5] -= 48;
					
					szer[6] -= 48;
					
					szer[7] -= 48;
					
					szer[8] -= 48;
					d = (float)szer[5] * 1000.0 + (float)szer[6]*100.0 + (float)szer[7]*10.0 + (float)szer[8];
					
					d *= (6.0 / 1000.0);
				
					float d2;
					dl[5] -= 48;
					
					dl[6] -= 48;
					
					dl[7] -= 48;
					
					dl[8] -= 48;
					d2 = (float)dl[5]*1000.0 + (float)dl[6]*100.0 + (float)dl[7]*10.0 + dl[8];
					d2 *= (6.0 / 1000.0);

					
					len = data[i];
					cout << " " << len << "\n";
					http = url + szer[0] + szer[1] + "°" + szer[2] + szer[3] + "'" + to_string(d) + "\"" + wid + "+"
						+ dl[0] + dl[1] + "°" + dl[2] + dl[3] + "'" + to_string(d2) + "\"" + len;
					ShellExecute(NULL, L"open", http, L"", L"", SW_SHOWNORMAL);
					plik << url << szer[0] << szer[1] << "°" << szer[2] << szer[3] << "'" << d  <<  "\"" << wid << "+"
						<< dl[0] << dl[1] << "°" << dl[2] << dl[3] << "'" << d2 <<  "\"" << len;
					plik.close();
				}
			}
			//break;
		}
		CloseHandle(hPort);
	}
	else
	{
		cout << "Nie polaczono sie z portem\n";
	}

	cin.get();
}
