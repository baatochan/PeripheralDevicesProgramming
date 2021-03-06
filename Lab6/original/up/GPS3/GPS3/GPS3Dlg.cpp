
// GPS3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "GPS3.h"
#include "GPS3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BOOL modyfikacja(HANDLE hComPort);
HANDLE hSerial;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGPS3Dlg dialog



CGPS3Dlg::CGPS3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_GPS3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGPS3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, szerokosc);
	DDX_Control(pDX, IDC_EXPLORER1, firefox);
	DDX_Control(pDX, IDC_EDIT3, porcik);
	DDX_Control(pDX, IDC_EDIT4, kontrola);
	DDX_Control(pDX, IDC_EDIT2, dlugosc);
}

BEGIN_MESSAGE_MAP(CGPS3Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CGPS3Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGPS3Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CGPS3Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CGPS3Dlg message handlers

BOOL CGPS3Dlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGPS3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGPS3Dlg::OnPaint()
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
HCURSOR CGPS3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGPS3Dlg::OnEnChangeEdit1()
{
	// TODO:  Jeżeli to jest kontrolka RICHEDIT, to kontrolka nie będzie
	// wyślij to powiadomienie, chyba że przesłonisz element CDialog::OnInitDialog()
	// funkcja i wywołanie CRichEditCtrl().SetEventMask()
	// z flagą ENM_CHANGE zsumowaną logicznie z maską.

	// TODO:  Dodaj tutaj swój kod procedury obsługi powiadamiania kontrolki
}


void CGPS3Dlg::OnBnClickedButton2()
{
	// TODO: Dodaj tutaj swój kod procedury obsługi powiadamiania kontrolki


	//POKA MAPE
	CString szer, dlug, adres;
	szerokosc.GetWindowTextW(szer);
	dlugosc.GetWindowTextW(dlug);
	adres = _T("http://google.com/maps/place/") + szer + "," + dlug;
	firefox.Navigate(adres, NULL, NULL, NULL, NULL);




}


void CGPS3Dlg::OnBnClickedButton3()
{
	// TODO: Dodaj tutaj swój kod procedury obsługi powiadamiania kontrolki

	DWORD cBytes_out, cBytes_in;
	DWORD dwMask;
	char cBuffer_out[] = "";
	TCHAR cBuffer_in[80];

	CString dupa;
	porcik.GetWindowTextW(dupa);

	// tak mialem wczesniej
	//hSerial = CreateFile(_T("COM3"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	hSerial = CreateFile(dupa, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);



	if (hSerial == INVALID_HANDLE_VALUE) {
		kontrola.SetWindowTextW(_T("dupa1"));
	}


	if (!modyfikacja(hSerial)) {
		kontrola.SetWindowTextW(_T("dupa modyfikancja"));
	}

	if (!WriteFile(hSerial, cBuffer_out, strlen(cBuffer_out), &cBytes_out, NULL)) {
		kontrola.SetWindowTextW(_T("dupa2"));
	}

	SetCommMask(hSerial, EV_RXCHAR | EV_ERR);

	cBuffer_in[0] = 0;
	// dopoki ctrl+c nie jest wcisniety, rób!
	while (cBuffer_in[0] != 0x03) {

		WaitCommEvent(hSerial, &dwMask, 0);
		cBytes_in = 1;

		while (cBytes_in != 0) {
			// czyta dane z urzadzenia i wyswietla
			if (ReadFile(hSerial, cBuffer_in, 79, &cBytes_in, NULL)) {
				if (cBytes_in == 0) break;
				//printf("%s", cBuffer_in, cBytes_in);
				if (!WriteFile(hSerial, cBuffer_in, cBytes_in, &cBytes_out, NULL)) {
					kontrola.SetWindowTextW(_T("dupa3"));
					return;
				}
			}
		} return;
	}
	CloseHandle(hSerial);

}



BOOL   modyfikacja(HANDLE hComPort)
{
	COMMTIMEOUTS ctos;
	DCB PortDCB; //struktura kontrolująca ustawienia portu szeregowego 
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
		//cout << "Blad konfiguracji portu szeregowego" << endl;
		system("pause");
		return false;
	}
	// ustaw timeouty odczytu
	ctos.ReadIntervalTimeout = MAXDWORD; //maksymalne dopuszczalne przerwy pomiędzy bajtami
	ctos.ReadTotalTimeoutMultiplier = MAXDWORD; //mnożnik do wyliczenia okresu timeoutu
	ctos.ReadTotalTimeoutConstant = 1; //stała służąca do wyliczenia całego okresu timeotu
	ctos.WriteTotalTimeoutMultiplier = 0;
	ctos.WriteTotalTimeoutConstant = 0;
	if (!SetCommTimeouts(hSerial, &ctos)) {
		//cout << "Blad konfiguracji portu szeregowego" << endl;
		system("pause");
		return false;
	}
	return true;
}


	