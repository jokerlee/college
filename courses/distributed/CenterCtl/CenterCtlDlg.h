// CenterCtlDlg.h : 头文件
//

#pragma once

#include "afxcmn.h"
#include <map>

#include "CenterCtlDlg.h"
#include "ServerSocket.h"
#include "SlaveSocket.h"


// CCenterCtlDlg 对话框
class CCenterCtlDlg : public CDialog
{
public: 
    struct CSlaveState
    {
        CSlaveState();
        char speed;
        char mode;
        char id;
        int crntTemp;
        int trgtTemp;
        CTime enterTime;
        BOOL bTimmer;
    };

    // 构造
public:
	CCenterCtlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CENTERCTL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog( );
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint( );
	afx_msg HCURSOR OnQueryDragIcon( );
    afx_msg void OnTimer( UINT nIDEvent );
    afx_msg void OnClose( );
    afx_msg void ChangeWorkingState( );
	DECLARE_MESSAGE_MAP()

public:
    void OnSlaveConnect( CSlaveSocket * pSocket );
    void OnSlaveDisconnect( CSlaveSocket * pSocket );
    void ProcessMessage( CSlaveMessage msg, CSlaveSocket * pSocket );
    int GetTemperature( CSlaveState state );
    void InsertRow( const CSlaveState & state );
    void CCenterCtlDlg::UpdateUI();
    void AddLog( CString );
    UINT GetPort( );
    int GetInitTemp( );

private:
    CServerSocket * m_pSocket;
    std::map<CSlaveSocket *, CSlaveState> m_mapSlaves;
    CListCtrl m_refSlaveList;
    CListCtrl m_refLogList;
    BOOL m_bWorking;
    int m_iInitTemp;
    int m_mode;

private:
    static const int FREQ_CTRL = 5000;
    static const int FREQ_INFO = 5000;
    static const int FREQ_REFRESH = 2000;
};
