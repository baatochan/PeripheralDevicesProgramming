#include <iostream>
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "Serial.h"
#include <tchar.h>
using namespace std;

#define RX_BUFFSIZE 512

int i;
void kopiuj(char* tabl, char* zmienn);
string doubl2str(double i);
const char* comName = "COM4";

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		cout << "Otwieram port..." << endl;
		Serial serial(9600);
		cout << "Polaczono" << endl;
		char tablica[RX_BUFFSIZE];
		cout << "Odczytywanie danych z portu: \n";
		for (int a = 0; a < 5; a++)
		{
			int charsRead = serial.read(tablica, RX_BUFFSIZE);
			Sleep(3000);
		}
		cout << tablica;
		bool koniec = false;

		char tmp[RX_BUFFSIZE];
		int iter = 0;
		do
		{
			serial.read(tmp, RX_BUFFSIZE);
			if (tmp[iter] == 'G' && tmp[iter + 1] == 'G' && tmp[iter + 2] == 'A')
			{
				serial.read(tablica, 82);
			}
				



			iter++;

		} while (!koniec);

		char czas[20], szerokosc[20], dlugosc[20], liczbaSatelitow[4];
		char fi[2], lambda[2], status[2], wspolczynnik[5], wysokosc[8];
		//int j = 0;

		for (int i = 0; i < 100; i++)
		{
			if (tablica[i] == 'G' && tablica[i + 1] == 'G' && tablica[i + 2] == 'A')	//naglowek protokolu
			{
				i += 3;
				kopiuj(tablica, czas);//kopiowanie kolejnych wartości do tablic
				kopiuj(tablica, szerokosc);
				kopiuj(tablica, fi);
				kopiuj(tablica, dlugosc);
				kopiuj(tablica, lambda);
				kopiuj(tablica, status);
				//kopiuj(tablica, liczbaSatelitow);
				//kopiuj(tablica, wspolczynnik);
				//kopiuj(tablica, wysokosc);
				break;
			}
		}
			
		cout << endl;
		cout << "czas = " << czas << endl;
		cout << "szerokosc = " << szerokosc << endl;
		cout << fi << endl;
		cout << dlugosc << endl;
		cout << lambda << endl;
		cout << status << endl;
	}

	catch (const char *msg)
	{
		cout << msg << endl;
	}

	
	cout << endl << "Nacisnij ENTER..." << endl;
	cin.get();

	return 0;
}

void kopiuj(char* tabl, char* zmienn)	//funkcja kopiująca z tablica do mniejszych tablic do przecinka  
{
	i++;
	int j = 0;
	for (; *(tabl + i) != ','; i++)
		zmienn[j++] = tabl[i];
	zmienn[j] = 0;					//znak null na końcu C-stringa
}

string doubl2str(double i)	// funkcja konwertująca liczbę double do typu string
{
	stringstream ss;
	string temp;
	ss << i;
	ss >> temp;
	return temp;
}
