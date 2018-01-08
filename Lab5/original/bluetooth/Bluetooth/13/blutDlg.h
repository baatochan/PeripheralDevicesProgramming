
// blutDlg.h : header file
//

#pragma once

#include <winsock2.h>
#include <Ws2bth.h>
#include <BluetoothAPIs.h>
#include <stdio.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Irprops.lib")
using namespace std;

  typedef struct
{
	HANDLE handle;
	BLUETOOTH_RADIO_INFO info;
} BT_RADIO;
// CblutDlg dialog
class CblutDlg : public CDialog
{
// Construction
public:
	CblutDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BLUT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

  CString m_t;
  afx_msg void OnBnClickedButton1();
  void pisz(wchar_t* tekst);
  void piszc(CString tekst);
  int adapter;
  int telefon;
  BT_RADIO* bt_find_radios (unsigned& num_found);
  BLUETOOTH_DEVICE_INFO* bt_find_devices (HANDLE* radio, unsigned& num_found);
  void bt_connect (BLUETOOTH_DEVICE_INFO dev_info);
int wsa_cleanup (SOCKET& s, const char* msg);
int obex_send_file (SOCKET s, char* path);
  afx_msg void OnBnClickedButton2();
};
