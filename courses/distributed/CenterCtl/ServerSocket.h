#pragma once

// CServerSocket ����Ŀ��

class CCenterCtlDlg;

class CServerSocket : public CSocket
{
public:
    CServerSocket( CCenterCtlDlg * pDlg );
	virtual ~CServerSocket();
    void StartListen( UINT nPort );

public:
    void OnAccept( int nErrorCode );

private:
    CCenterCtlDlg * m_pDlg;
};


