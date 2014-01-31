// SlaveSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SlaveCtl.h"
#include "SlaveSocket.h"
#include "SlaveCtlDlg.h"

// CSlaveSocket

CSlaveSocket::CSlaveSocket( CSlaveCtlDlg * pDlg )
    :m_pDlg( pDlg ), m_pFile( 0 ), m_pArchiveIn( 0 ), m_pArchiveOut( 0 )
{

}

CSlaveSocket::~CSlaveSocket()
{
    m_pDlg = NULL;
}

// CSlaveSocket Member Function

BOOL CSlaveSocket::ConnectServer( CString csIp, UINT uPort )
{
    if ( !this->Create( ) )
    {
        AfxMessageBox( L"�׽��ִ�������!" );
        return FALSE;
    }

    if( !this->Connect( csIp, uPort ) )
    {
        AfxMessageBox( L"�޷����ӷ���������!" );
        return FALSE;
    }

    m_pFile = new CSocketFile(this);
    m_pArchiveIn = new CArchive(m_pFile, CArchive::load);
    m_pArchiveOut = new CArchive(m_pFile, CArchive::store);

    return TRUE;
}


void CSlaveSocket::Destroy( ) 
{
    if ( m_pArchiveOut )
    {
        delete m_pArchiveOut;
        m_pArchiveOut = NULL;
    }
    if ( m_pArchiveOut )
    {
        delete m_pArchiveIn;
        m_pArchiveIn = NULL;
    }
    if ( m_pArchiveOut )
    {
        delete m_pFile;
        m_pFile = NULL;
    }

    this->Close();
}

void CSlaveSocket::OnClose( int nErrorCode )
{
    CSocket::OnClose( nErrorCode );
    m_pDlg->OnDisconnected( this );
}

void CSlaveSocket::OnReceive( int nErrorCode ) 
{
	CSocket::OnReceive( nErrorCode );
    CCenterMessage msg;
    TRY
    {
        do 
        {           
            msg.Serialize( * m_pArchiveIn );

            CString log;
            log.Format( L"Receive : %d %d %d %d", msg.type, msg.mode, msg.info, msg.optional );
            this->m_pDlg->AddLog( log );

            m_pDlg->ProcessMessage( msg );

            m_pArchiveIn->Flush( );
        }
        while ( !this->m_pArchiveIn->IsBufferEmpty( ) );
    }
    CATCH( CFileException, e )
    {
        AfxMessageBox( L"��������������!���ӹر�!" );
        m_pArchiveOut->Abort();
    }
    END_CATCH
}

void CSlaveSocket::Send( CSlaveMessage & msg )
{
    CString log;
    log.Format( L"Send : %d %d %d %d %d %d %d", msg.type, msg.mode, msg.id, msg.speed, msg.trgtTemp, msg.crntTemp, msg.optional );
    this->m_pDlg->AddLog( log );

    msg.Serialize( *m_pArchiveOut );
	m_pArchiveOut->Flush( );
}