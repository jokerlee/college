// ConnThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CenterCtl.h"
#include "ConnThread.h"


// CConnThread

IMPLEMENT_DYNCREATE(CConnThread, CWinThread)

CConnThread::CConnThread()
{
}

CConnThread::~CConnThread()
{
}

BOOL CConnThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CConnThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CConnThread, CWinThread)
END_MESSAGE_MAP()


// CConnThread ��Ϣ�������
