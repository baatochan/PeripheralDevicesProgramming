
// blutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "blut.h"
#include "blutDlg.h"



using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

wchar_t temp[500];


unsigned i = 0, N_FOUND_RADIOS = 0;
BT_RADIO* radios;
BLUETOOTH_DEVICE_INFO* devices;
HANDLE bt_selected_radio;


TCHAR *GetLastErrorMessage(DWORD last_error)
{
   static TCHAR errmsg[512];
   if (!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, last_error, 0, errmsg, 511, NULL))
   {	return (GetLastErrorMessage(GetLastError()));  
   }
  
   return errmsg;
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CblutDlg dialog




CblutDlg::CblutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CblutDlg::IDD, pParent)
  , m_t(_T(""))
  , adapter(0)
  , telefon(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CblutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CblutDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
  ON_BN_CLICKED(IDC_BUTTON1, &CblutDlg::OnBnClickedButton1)
  ON_BN_CLICKED(IDC_BUTTON2, &CblutDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CblutDlg message handlers

BOOL CblutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
UpdateData(FALSE);
radios= bt_find_radios (N_FOUND_RADIOS);
CString t;
swprintf(temp,500,L"Znalazlem %d adapterow BT: \r\n", N_FOUND_RADIOS);
t=(LPCWSTR)temp;
piszc(t);

	for (i = 0; i < N_FOUND_RADIOS; ++i)
	{	swprintf (temp,500,L"%d. %s\r\n", i, radios[i].info.szName);
  t=(LPCWSTR)temp;
piszc(t);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CblutDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CblutDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CblutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BLUETOOTH_DEVICE_INFO* CblutDlg::bt_find_devices (HANDLE* radio, unsigned& num_found)
{
	/* Parametry wyszukiwania */
	/*BLUETOOTH_DEVICE_SEARCH_PARAMS bt_search_params;
	bt_search_params.dwSize = sizeof (BLUETOOTH_DEVICE_SEARCH_PARAMS);
	bt_search_params.fReturnAuthenticated = true;
	bt_search_params.fReturnRemembered = true;
	bt_search_params.fReturnConnected = true;
	bt_search_params.fReturnUnknown = true;
	bt_search_params.fIssueInquiry = true;
	bt_search_params.hRadio = radio;*/

	BLUETOOTH_DEVICE_INFO* btdev_info = new BLUETOOTH_DEVICE_INFO[10];
	num_found = 0;
  btdev_info[num_found].dwSize = sizeof (BLUETOOTH_DEVICE_INFO);

	/* Szukamy pierwszego urzadzenia */
	HBLUETOOTH_DEVICE_FIND devresult;
//	devresult = BluetoothFindFirstDevice (&bt_search_params, &btdev_info[num_found]);


	HBLUETOOTH_DEVICE_FIND hFind;
	BLUETOOTH_DEVICE_SEARCH_PARAMS btsp = { sizeof(btsp) };
	BLUETOOTH_DEVICE_INFO btdi = { sizeof(btdi) };

	btsp.fReturnAuthenticated	= TRUE; //Zwróæ wszystkie interesuj¹ce nas urz¹dzenia
	btsp.fReturnRemembered		= TRUE;
	btsp.fReturnUnknown			= TRUE;

	hFind = BluetoothFindFirstDevice( &btsp, &btdi );
  btdev_info[num_found]=btdi;
  devresult=hFind;

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

BT_RADIO* CblutDlg::bt_find_radios (unsigned& num_found)
{
	/* Miejsce na wyniki, parametry wyszukiwania */
	BT_RADIO* rad = new BT_RADIO[10];
	num_found = 0;
	BLUETOOTH_FIND_RADIO_PARAMS bt_find_params;
	bt_find_params.dwSize = sizeof (BLUETOOTH_FIND_RADIO_PARAMS);

	/* Szukamy pierwsze radio w komputerze */
	HBLUETOOTH_RADIO_FIND result; 
	result = BluetoothFindFirstRadio (&bt_find_params, &(rad[num_found].handle));
	rad[num_found].info.dwSize = sizeof (BLUETOOTH_RADIO_INFO);

	/* Szukamy pozostale radia (jezeli pierwsze istnieje) */
	if (result)
	{
		do
		{
			/* Wpisujemy radio do tablicy wynikow */
			BluetoothGetRadioInfo (rad[num_found].handle, &(rad[num_found].info));
			rad[++num_found].info.dwSize = sizeof (BLUETOOTH_RADIO_INFO);
		} while (TRUE == BluetoothFindNextRadio (result, &(rad[num_found].handle)));
	}
	else
	{	return NULL;
	}

	/* Konczymy prace */
	BluetoothFindRadioClose (result);
	return rad;
}

BOOL bt_auth_func (LPVOID parametr, PBLUETOOTH_DEVICE_INFO dev)
{
	DWORD result = BluetoothSendAuthenticationResponse ((HANDLE)parametr, dev, L"1111");	
	if (ERROR_SUCCESS != result)
	{	return FALSE;
	}

	return TRUE;
}

int CblutDlg::wsa_cleanup (SOCKET& s, const char* msg)
{
  CString t;
  piszc(msg);
	closesocket (s);
	WSACleanup();
	return 1;
}

int CblutDlg::obex_send_file (SOCKET s, char* path)
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

	char send_date[] = "20101117T193000"; // tworzymy date

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

void CblutDlg::bt_connect (BLUETOOTH_DEVICE_INFO dev_info)
{
  CString t;
	WORD wVersionRequested = 0x202;
	WSADATA m_data;
  piszc("Wysy³amy\r\n");
	if (0 == ::WSAStartup(wVersionRequested, &m_data))
	{
		/* Tworzymy socket */
		SOCKET s = ::socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);

		if (INVALID_SOCKET == GetLastError())
		{
			swprintf (temp,500,L"Invalid socket!\n");
      t=(LPCWSTR)temp;
  piszc(t);
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
			swprintf (temp,500,L"Blad... [%d] %s\n", GetLastError(), GetLastErrorMessage (GetLastError()));
			closesocket (s);
      t=(LPCWSTR)temp;
  piszc(t);
			WSACleanup();
			return;
		}
		else
		{
			obex_send_file (s, "test.txt");
		}
	}
}


void CblutDlg::OnBnClickedButton1()
{
  // TODO: Add your control notification handler code here
  pisz(L"\r\n");
  CEdit* ed=(CEdit*)GetDlgItem(IDC_EDIT2);
  ed->GetWindowTextA(m_t);
  adapter=atoi(m_t);
  CString t;
  t.Format("Wybrany adapter: ");
  piszc(t);
  swprintf (temp,500,L"%d. %s\r\n", adapter, radios[adapter].info.szName);
  t=(LPCWSTR)temp;
  piszc(t);
  bt_selected_radio = radios[adapter].handle;
	BluetoothEnableDiscovery (bt_selected_radio, TRUE);
	BluetoothEnableIncomingConnections (bt_selected_radio, TRUE);
	/* Szukamy urzadzen BT */
	unsigned N_FOUND_DEVICES = 0;
	devices = bt_find_devices (&bt_selected_radio, N_FOUND_DEVICES);
	swprintf (temp,500,L"Znalazlem %d urzadzen: \r\n", N_FOUND_DEVICES);
  t=(LPCWSTR)temp;
  piszc(t);
	for (i = 0; i < N_FOUND_DEVICES; ++i)
	{	swprintf (temp,500,L"%d. %s\r\n", i, devices[i].szName);
  t=(LPCWSTR)temp;
  piszc(t);
	}
  
}

void CblutDlg::OnBnClickedButton2()
{
  pisz(L"\r\n");
  CEdit* ed=(CEdit*)GetDlgItem(IDC_EDIT3);
  ed->GetWindowTextA(m_t);
  telefon=atoi(m_t);
  CString t;
  t.Format("Wybrany telefon: ");
  piszc(t);
  swprintf (temp,500,L"%s %X:%X:%X:%X:%X:%X\r\n", devices[telefon].szName,
    devices[telefon].Address.rgBytes[5],
    devices[telefon].Address.rgBytes[4],
    devices[telefon].Address.rgBytes[3],
    devices[telefon].Address.rgBytes[2],
    devices[telefon].Address.rgBytes[1],
    devices[telefon].Address.rgBytes[0]);
  t=(LPCWSTR)temp;
  piszc(t);


  BLUETOOTH_DEVICE_INFO btdev_info = devices[telefon];
	HBLUETOOTH_AUTHENTICATION_REGISTRATION bt_reg_func_handle;
  //BluetoothRegisterForAuthentication(&btdev_info, &bt_reg_func_handle, bt_auth_func, bt_selected_radio);
  BluetoothAuthenticateDevice(NULL, radios[adapter].handle, &btdev_info, L"1235", 4);
	bt_connect (btdev_info);	
}

void CblutDlg::pisz(wchar_t* tekst)
{
  	CEdit* ed=(CEdit*)GetDlgItem(IDC_EDIT1);
	ed->GetWindowText(m_t);
	m_t.Append((char*)tekst);
	ed->SetWindowText(m_t);

}

void CblutDlg::piszc(CString tekst)
{
  CEdit* ed=(CEdit*)GetDlgItem(IDC_EDIT1);
	ed->GetWindowText(m_t);
	m_t.Append(tekst);
	ed->SetWindowText(m_t);
}




