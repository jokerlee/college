// BuffonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Buffon.h"
#include "BuffonDlg.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuffonDlg dialog

CBuffonDlg::CBuffonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBuffonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBuffonDlg)
	m_nCount = 0;
	m_fInterval = 0.0;
	m_fLen = 0.0;
	m_nLines = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBuffonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuffonDlg)
	DDX_Text(pDX, IDC_EDIT_COUNT, m_nCount);
	DDV_MinMaxInt(pDX, m_nCount, 1, 10000000);
	DDX_Text(pDX, IDC_EDIT_INTERVAL, m_fInterval);
	DDX_Text(pDX, IDC_EDIT_LENGTH, m_fLen);
	DDX_Text(pDX, IDC_EDIT_LINES, m_nLines);
	DDV_MinMaxInt(pDX, m_nLines, 1, 100000);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBuffonDlg, CDialog)
	//{{AFX_MSG_MAP(CBuffonDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnStart)
	ON_BN_CLICKED(IDCANCEL, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuffonDlg message handlers

BOOL CBuffonDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBuffonDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBuffonDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

double CBuffonDlg::Rand(double f, double t)
{
	return ((double)rand()/RAND_MAX)*(t-f) + f;
}


void CBuffonDlg::OnStart() 
{	
	UpdateData(TRUE);
	srand(time(0));

	CRect rc;
	GetDlgItem(IDC_CANVAS)->GetWindowRect(&rc);
	double fHeight, fWidth;
	fHeight = rc.bottom - rc.top;
	fWidth = rc.right - rc.left;
	double len = m_fLen * (fHeight/(m_fInterval*(m_nLines-1)));

	// 生成针
	std::vector<CPoint> vNeedles;
	int i, j;
	const double pi = 3.1415926;
	for (i=0; i<m_nCount; ++i)
	{
		double x, y;
		// 生成起点
		x = Rand(m_fLen, (fWidth - m_fLen));
		y = Rand(0, fHeight);
		vNeedles.push_back(CPoint(x, y));

		//生成终点 循环保证生成的终点在画布范围内 不在范围内则重新生成
		double theta, xx, yy;
		do
		{
			theta = Rand(0, pi);
			xx = x + len * sin(theta);
			yy = y + len * cos(theta);
		}
		while (xx<0 || yy<0 || xx>fWidth || yy>fHeight);
		vNeedles.push_back(CPoint(xx, yy));
	}


	// 绘制平行线
	CClientDC dc(GetDlgItem(IDC_CANVAS));
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	dc.SelectObject(&pen);

	double hrzt = fHeight/(m_nLines-1); // 平行线的纵坐标
	for (i=0; i<m_nLines; i++)
	{
		dc.MoveTo(0, hrzt*i);;
		dc.LineTo(fWidth, hrzt*i);
	}

	// 绘制针
	for (i=0; i<vNeedles.size(); i+=2)
	{
		CPen pen(PS_SOLID, 1, RGB(Rand(0,255), Rand(0,255), Rand(0,255)));
		dc.SelectObject(&pen);
		dc.MoveTo(vNeedles[i]);
		dc.LineTo(vNeedles[i+1]);
		Sleep(20);
	}


	// 计算交点数
	int cnt = 0;
	double hrz = fHeight/(m_nLines-1); // 平行线的纵坐标
	for (i=0; i<m_nLines-2; i++)
		for (j=0; j<vNeedles.size(); j+=2)
		{
			if (vNeedles[j].y < vNeedles[j+1].y)
				if (vNeedles[j].y <= hrz*(i+1) && vNeedles[j+1].y >= hrz*(i+1)) 
					cnt ++;
			if (vNeedles[j].y >= vNeedles[j+1].y)
				if (vNeedles[j+1].y <= hrz*(i+1) && vNeedles[j].y >= hrz*(i+1)) 
					cnt ++;
			
		}

	double key = 2 * m_fLen/(m_fInterval*(double)cnt/m_nCount); //π=2*针长/(平行线间距*相交概率)
	CString csRes;
	csRes.Format(_T("相交次数%d, 相交概率%.2f, π的估算值为%f."), cnt, (double)cnt/m_nCount, key);
	this->GetDlgItem(IDC_STATIC_RESULT)->SetWindowText(csRes);
}

void CBuffonDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	PostQuitMessage(0); //退出程序
}
