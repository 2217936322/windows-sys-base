
// SystemMoniterDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CSystemMoniterDlg �Ի���
class CSystemMoniterDlg : public CDialogEx
{
// ����
public:
	CSystemMoniterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SYSTEMMONITER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

    void OnOK(){};

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:

    BYTE m_SystemCpuUsage;
    BYTE m_SystemCpuIdle;

    ULONGLONG m_SystemCommitTotal;
    ULONGLONG m_SystemCommitLimit;
    ULONGLONG m_SystemCommitPeak;

    ULONGLONG m_PhcTotal;
    ULONGLONG m_PhcAVB;
    ULONGLONG m_SystemCache;

    ULONGLONG m_KernelTotal;
    ULONGLONG m_KernelPaged;
    ULONGLONG m_KernelNonpaged;
    ULONGLONG m_PageSize;

    DWORD m_HandleCount;
    DWORD m_ProcCount;
    DWORD m_ThreadCount;

public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnClose();
private:
    CListCtrl m_ProcListCtl;
};
