
// GPS3.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CGPS3App:
// See GPS3.cpp for the implementation of this class
//

class CGPS3App : public CWinApp
{
public:
	CGPS3App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CGPS3App theApp;
