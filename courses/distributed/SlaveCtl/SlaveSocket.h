#pragma once

// CSlaveSocket ÃüÁîÄ¿±ê

#include "Message.h"

class CSlaveCtlDlg;

class CSlaveSocket : public CSocket
{
public:
	CSlaveSocket( CSlaveCtlDlg * pDlg );
	virtual ~CSlaveSocket();
    BOOL ConnectServer( CString csIp, UINT uPort );
    void Destroy( );
    void Send( CSlaveMessage & );

public:
	virtual void OnReceive( int nErrorCode );
    virtual void OnClose( int nErrorCode );

private:
    CSlaveCtlDlg * m_pDlg;
    CSocketFile * m_pFile;
    CArchive * m_pArchiveIn;
    CArchive * m_pArchiveOut;
};


