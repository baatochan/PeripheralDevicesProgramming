
// GPS3Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "explorer1.h"


// CGPS3Dlg dialog
class CGPS3Dlg : public CDialog
{
// Construction
public:
	CGPS3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GPS3_DIALOG };
#endif

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
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton2();
	CEdit szerokosc;
	CExplorer1 firefox;
	afx_msg void OnBnClickedButton3();
	CEdit porcik;
	CEdit kontrola;
	CEdit dlugosc;
};
