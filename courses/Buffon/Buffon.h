// Buffon.h : main header file for the BUFFON application
//

#if !defined(AFX_BUFFON_H__76A8B778_3C6C_427A_B0BD_0363FCAD8062__INCLUDED_)
#define AFX_BUFFON_H__76A8B778_3C6C_427A_B0BD_0363FCAD8062__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBuffonApp:
// See Buffon.cpp for the implementation of this class
//

class CBuffonApp : public CWinApp
{
public:
	CBuffonApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuffonApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBuffonApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUFFON_H__76A8B778_3C6C_427A_B0BD_0363FCAD8062__INCLUDED_)
