// ConnThread.cpp : 实现文件
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
	// TODO: 在此执行任意逐线程初始化
	return TRUE;
}

int CConnThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CConnThread, CWinThread)
END_MESSAGE_MAP()


// CConnThread 消息处理程序
