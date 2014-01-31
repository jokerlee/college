// SlaveCtlDlg.h : 头文件
//

#pragma once

#include "SlaveSocket.h"
#include "afxwin.h"
#include "afxcmn.h"

// CSlaveCtlDlg 对话框
class CSlaveCtlDlg : public CDialog
{
public:
    struct CSlaveState
    {
        CSlaveState();

        char id;
        char mode;
        char speed;
        double crntTemp;
        int trgtTemp;
        BOOL bTimmer;
    };
    // 构造
public:
	CSlaveCtlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SLAVECTL_DIALOG };

	protected:
	virtual void DoDataExchange( CDataExchange * pDX );	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog( );
	afx_msg void OnSysCommand( UINT nID, LPARAM lParam );
	afx_msg void OnPaint( );
	afx_msg HCURSOR OnQueryDragIcon( );
    afx_msg void OnDestroy( );
    afx_msg void OnBnClickedButton1( );
    afx_msg void OnBnClickedON( );
    afx_msg void OnBnClickedOFF( );
    afx_msg void OnTimer( UINT nIDEvent );
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedDown();
    afx_msg void OnBnClickedSpeedOne();
    afx_msg void OnBnClickedSpeedTwo();
    afx_msg void OnBnClickedSpeedThree();
	DECLARE_MESSAGE_MAP()

public:
    static const int FREQ_CHANGE = 2000;    
    static enum mode_t { MODE_FIRST, MODE_WORKING, MODE_STABLE };

public:
    void UpdateUI( );
    void ProcessMessage( const CCenterMessage & );
    void CheckState( CSlaveCtlDlg::mode_t );
    void OnUserRequest( int tgrt_temp, int speed );
    void Destroy( );
    void OnDisconnected( CSlaveSocket * pSocket );
    void ChangeWorkingState( );


public:
    CString GetIP( );
    UINT GetPort( );
    void AddLog( CString );


private:
    CSlaveSocket * m_pSocket;
    CSlaveState m_state;
    CSlaveState m_laststate;
    CListCtrl m_refLogList;
    CFont m_fontBig;
    int m_iInitTemp;
    BOOL m_bWorking;
};
