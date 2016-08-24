
// SystemMoniter.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "SystemMoniter.h"
#include "SystemMoniterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSystemMoniterApp

BEGIN_MESSAGE_MAP(CSystemMoniterApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSystemMoniterApp ����

CSystemMoniterApp::CSystemMoniterApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CSystemMoniterApp ����

CSystemMoniterApp theApp;


// CSystemMoniterApp ��ʼ��

BOOL CSystemMoniterApp::InitInstance()
{
	CWinApp::InitInstance();


	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

    if (CSystemPerformanceCollecter::ERROR_CODE_SUCCESS 
        != CSystemPerformanceCollecter::Instance().Start(
        CSystemPerformanceCollecter::COLLECT_TYPE_PROC_IO
        | CSystemPerformanceCollecter::COLLECT_TYPE_PROC_ADVANCED
        | CSystemPerformanceCollecter::COLLECT_TYPE_PROC_MEMORY
        | CSystemPerformanceCollecter::COLLECT_TYPE_PROC_RESOURCE
        | CSystemPerformanceCollecter::COLLECT_TYPE_SYS_RESOURCE))
    {
        ::MessageBoxA(NULL, "����ϵͳ�����ռ���ʧ��", "��ʾ", MB_OK);

        return FALSE;
    }

	CSystemMoniterDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

