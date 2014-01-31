// ProgressDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SoliDire.h"
#include "ProgressDialog.h"
#include <afxmt.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ProgressDialog dialog


ProgressDialog::ProgressDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_STATUSDIALOG)
{	
	//{{AFX_DATA_INIT(ProgressDialog)
	//}}AFX_DATA_INIT
}

void ProgressDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ProgressDialog)
	DDX_Control(pDX, IDC_TEXT, m_Text);
	DDX_Control(pDX, IDC_PROGRESS, m_ProgressCtrl);
	//}}AFX_DATA_MAP
	//DDX_Control(pDX, IDC_STATIC, m_Text);
}

void ProgressDialog::OnCancel()
{
	CDialog::OnCancel();
}

BOOL ProgressDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	this->SetWindowText(m_Caption);
	return TRUE;
}

void ProgressDialog::SetCaption(CString caption)
{
	m_Caption = caption;
}


afx_msg LRESULT ProgressDialog::OnStep(WPARAM wParam, LPARAM lParam)
{
	m_ProgressCtrl.StepIt();	
	return 0;
}


afx_msg LRESULT ProgressDialog::OnText(WPARAM wParam, LPARAM lParam)
{
	m_Text.SetWindowText((char*)wParam);
	return 0;
}


afx_msg LRESULT ProgressDialog::OnSet(WPARAM wParam, LPARAM lParam)
{
	m_ProgressCtrl.SetPos(*(int*)wParam);
	return 0;
}

BEGIN_MESSAGE_MAP(ProgressDialog, CDialog)
	//{{AFX_MSG_MAP(ProgressDialog)
		// NOTE: the ClassWizard will add message map macros here
		#define WM_PG_STEP (WM_USER+100)
		#define WM_PG_RESET (WM_USER+101)
		#define WM_PG_SET (WM_USER+102)
		#define WM_PG_TEXT (WM_USER+103)
		#define WM_PG_TITLE (WM_USER+104)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// ProgressDialog message handlers
