// ServerSocket.cpp : 实现文件
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


// CServerSocket 成员函数

void CServerSocket::StartListen( UINT nPort )
{
	if ( !this->Create( nPort ) )
	{
		AfxMessageBox( L"创建监听套接字错误" );
		return;
	}

	if ( !this->Listen( ) )
	{
		AfxMessageBox( L"启动监听错误" );
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