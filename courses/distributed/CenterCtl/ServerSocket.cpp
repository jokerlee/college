// ServerSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"

#include "CenterCtl.h"
#include "ServerSocket.h"
#include "CenterCtlDlg.h"

// CServerSocket

CServerSocket::CServerSocket( CCenterCtlDlg * pDlg )
    : m_pDlg( pDlg )
{

}

CServerSocket::~CServerSocket()
{
    m_pDlg = NULL;
}


// CServerSocket ��Ա����

void CServerSocket::StartListen( UINT nPort )
{
	if ( !this->Create( nPort ) )
	{
		AfxMessageBox( L"���������׽��ִ���" );
		return;
	}

	if ( !this->Listen( ) )
	{
		AfxMessageBox( L"������������" );
		return;
	}
    
    return;
}


void CServerSocket::OnAccept( int nErrorCode ) 
{	
	CSocket::OnAccept( nErrorCode );
   
    CSlaveSocket * pSocket = new CSlaveSocket( this->m_pDlg );

    if( this->Accept( *pSocket ) )
    {
        pSocket->Initialize( );
	    m_pDlg->OnSlaveConnect( pSocket );
    }
    else
    {
        delete pSocket;
    }
}