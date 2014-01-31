// SoliDire.h : main header file for the SOLIDIRE application
//

#if !defined(AFX_SOLIDIRE_H__0364D2C1_217B_41C3_B86E_8E2A0FC7865B__INCLUDED_)
#define AFX_SOLIDIRE_H__0364D2C1_217B_41C3_B86E_8E2A0FC7865B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSoliDireApp:
// See SoliDire.cpp for the implementation of this class
//

class CSoliDireApp : public CWinApp
{
public:
	CSoliDireApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoliDireApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSoliDireApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOLIDIRE_H__0364D2C1_217B_41C3_B86E_8E2A0FC7865B__INCLUDED_)
