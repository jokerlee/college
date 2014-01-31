// BuffonDlg.h : header file
//

#if !defined(AFX_BUFFONDLG_H__E0E965BC_BB04_44E8_8FF8_2B4C52A0F181__INCLUDED_)
#define AFX_BUFFONDLG_H__E0E965BC_BB04_44E8_8FF8_2B4C52A0F181__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBuffonDlg dialog

class CBuffonDlg : public CDialog
{
// Construction
public:
	CBuffonDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBuffonDlg)
	enum { IDD = IDD_BUFFON_DIALOG };
	int		m_nCount;
	double	m_fInterval;
	double	m_fLen;
	int		m_nLines;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuffonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBuffonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	double Rand(double f, double t);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUFFONDLG_H__E0E965BC_BB04_44E8_8FF8_2B4C52A0F181__INCLUDED_)
