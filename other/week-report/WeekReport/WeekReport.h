
// WeekReport.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWeekReportApp:
// �йش����ʵ�֣������ WeekReport.cpp
//

class CWeekReportApp : public CWinAppEx
{
public:
	CWeekReportApp();
	~CWeekReportApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWeekReportApp theApp;