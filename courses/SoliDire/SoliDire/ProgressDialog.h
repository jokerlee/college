#if !defined(AFX_PROGRESSDIALOG_H__B9EE0141_560D_4241_A3B8_3AEEB9DA6028__INCLUDED_)
#define AFX_PROGRESSDIALOG_H__B9EE0141_560D_4241_A3B8_3AEEB9DA6028__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressDialog.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// ProgressDialog dialog


#define WM_PG_STEP (WM_USER+100)
#define WM_PG_SET (WM_USER+102)
#define WM_PG_TEXT (WM_USER+103)

class ProgressDialog : public CDialog
{
private:
	CString m_Caption;
public:
	ProgressDialog(CWnd* pParent = NULL);   // standard constructor
	void SetCaption(CString);
	void OnCancel();
	BOOL OnInitDialog();

public:
	//CStatic m_Text;
// Dialog Data
	//{{AFX_DATA(ProgressDialog)
//	enum { IDD = IDD_STATUSDIALOG };
	CStatic	m_Text;
	CProgressCtrl	m_ProgressCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ProgressDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ProgressDialog)
		// NOTE: the ClassWizard will add member functions here
		afx_msg LRESULT OnStep(WPARAM wParam, LPARAM lParam);
		afx_msg LRESULT OnText(WPARAM wParam, LPARAM lParam);
		afx_msg LRESULT OnSet(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDIALOG_H__B9EE0141_560D_4241_A3B8_3AEEB9DA6028__INCLUDED_)

