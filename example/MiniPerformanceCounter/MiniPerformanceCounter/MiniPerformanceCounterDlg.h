
// MiniPerformanceCounterDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMiniPerformanceCounterDlg �Ի���
class CMiniPerformanceCounterDlg : public CDialogEx
{
// ����
public:
	CMiniPerformanceCounterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MINIPERFORMANCECOUNTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

    virtual void OnOK(){};

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
    CListBox m_LB_Object;
    CListBox m_LB_ObjectItem;
    CListBox m_LB_ItemInstance;

    afx_msg void OnBnClickedButton1();
    afx_msg void OnLbnSelchangeList2();

    CEdit m_EditCounterPath;

    afx_msg void OnLbnSelchangeList1();

    void ShowCounterPath();

    afx_msg void OnLbnSelchangeList3();
    afx_msg void OnBnClickedButton2();
    CListCtrl m_ListShow;

    afx_msg void OnClose();

    afx_msg void OnTimer(UINT_PTR nIDEvent);
};
