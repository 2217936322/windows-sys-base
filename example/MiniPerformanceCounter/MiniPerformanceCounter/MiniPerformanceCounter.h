
// MiniPerformanceCounter.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
using namespace SysBase;

// CMiniPerformanceCounterApp:
// �йش����ʵ�֣������ MiniPerformanceCounter.cpp
//

class CMiniPerformanceCounterApp : public CWinApp
{
public:
	CMiniPerformanceCounterApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMiniPerformanceCounterApp theApp;