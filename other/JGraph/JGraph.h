// JGraph.h : JGraph Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CJGraphApp:
// �йش����ʵ�֣������ JGraph.cpp
//

class CJGraphApp : public CWinApp
{
public:
	CJGraphApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CJGraphApp theApp;