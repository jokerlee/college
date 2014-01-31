// SlaveSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "CenterCtl.h"
#include "SlaveSocket.h"
#include "CenterCtlDlg.h"

// CSlaveSocket

CSlaveSocket::CSlaveSocket( CCenterCtlDlg * pDlg )
    :m_pDlg( pDlg ), m_pFile( NULL ), m_pArchiveIn( NULL ), m_pArchiveOut( NULL )
{

}

CSlaveSocket::~CSlaveSocket()
{
    m_pDlg = NULL;
	if ( m_pArchiveOut != NULL ) delete m_pArchiveOut;
	if ( m_pArchiveIn != NULL ) delete m_pArchiveIn;
	if ( m_pFile != NULL ) delete m_pFile;
}

// CSlaveSocket Member Function

void CSlaveSocket::OnReceive( int nErrorCode ) 
{
	CSocket::OnReceive( nErrorCode );

    CSlaveMessage msg;
    TRY
    {
        do 
        {
            msg.Serialize( *m_pArchiveIn );

            CString log;
            log.Format( _T("Receive : %d %d %d %d %d %d %d"), 
                msg.type, msg.mode, msg.id, msg.speed, msg.trgtTemp, msg.crntTemp, msg.optional );
            this->m_pDlg->AddLog( log );

	        m_pDlg->ProcessMessage( msg, this );
        }
        while ( !this->m_pArchiveIn->IsBufferEmpty() );     
    }
    CATCH( CFileException, e )
    {
        AfxMessageBox( L"服务器重置连接!连接关闭!" );
        m_pArchiveOut->Abort();
    }
    END_CATCH
}

void CSlaveSocket::OnClose( int nErrorCode ) 
{
	CSocket::OnClose( nErrorCode );
	m_pDlg->OnSlaveDisconnect( this );
}

void CSlaveSocket::Initialize()
{
	m_pFile = new CSocketFile( this, TRUE );
	m_pArchiveIn = new CArchive( m_pFile, CArchive::load );
	m_pArchiveOut = new CArchive( m_pFile, CArchive::store );
}

void CSlaveSocket::Send( CCenterMessage & msg )
{
	if ( m_pArchiveOut != NULL )
	{
        CString log;
        log.Format( L"Send : %d %d %d %d", 
            msg.type, msg.mode, msg.info, msg.optional );
        this->m_pDlg->AddLog( log );
        
        msg.Serialize( *m_pArchiveOut );
		m_pArchiveOut->Flush( );
	}
}

CArchive * CSlaveSocket::GetArchiveIn( )
{
    return m_pArchiveIn;
}

CArchive * CSlaveSocket::GetArchiveOut( )
{
    return m_pArchiveOut;
}