
// SystemMoniter.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

using namespace SysBase;

// CSystemMoniterApp:
// �йش����ʵ�֣������ SystemMoniter.cpp
//

class CSystemMoniterApp : public CWinApp
{
public:
	CSystemMoniterApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSystemMoniterApp theApp;