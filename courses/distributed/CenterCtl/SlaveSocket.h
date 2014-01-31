#pragma once

// CSlaveSocket ÃüÁîÄ¿±ê

#include "Message.h"

class CCenterCtlDlg;

class CSlaveSocket : public CSocket
{
public:
	CSlaveSocket( CCenterCtlDlg * pDlg );
	virtual ~CSlaveSocket();


public:
    void Initialize();

    CArchive * GetArchiveIn( );
    CArchive * GetArchiveOut( );

public:
    void Send( CCenterMessage & pMsg );
	virtual void OnReceive( int nErrorCode );
    virtual void OnClose( int nErrorCode );

private:
    CCenterCtlDlg * m_pDlg;
	CSocketFile * m_pFile;
	CArchive * m_pArchiveIn;
	CArchive * m_pArchiveOut;
};


