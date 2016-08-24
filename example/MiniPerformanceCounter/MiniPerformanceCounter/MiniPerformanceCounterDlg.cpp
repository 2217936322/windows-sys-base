
// MiniPerformanceCounterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MiniPerformanceCounter.h"
#include "MiniPerformanceCounterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMiniPerformanceCounterDlg �Ի���

#define DLG_TIMER_ID 1001

#define PROC_COLUMN_INDEX_NAME 0
#define PROC_COLUMN_INDEX_VALUE 1

static int s_nIndex = 1;

typedef map<string, int> CounterMap;

CounterMap s_CounterMap;

CMiniPerformanceCounterDlg::CMiniPerformanceCounterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMiniPerformanceCounterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMiniPerformanceCounterDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_LB_Object);
    DDX_Control(pDX, IDC_LIST2, m_LB_ObjectItem);
    DDX_Control(pDX, IDC_LIST3, m_LB_ItemInstance);
    DDX_Control(pDX, IDC_EDIT1, m_EditCounterPath);
    DDX_Control(pDX, IDC_LIST_SHOW, m_ListShow);
}

BEGIN_MESSAGE_MAP(CMiniPerformanceCounterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &CMiniPerformanceCounterDlg::OnBnClickedButton1)
    ON_LBN_SELCHANGE(IDC_LIST2, &CMiniPerformanceCounterDlg::OnLbnSelchangeList2)
    ON_LBN_SELCHANGE(IDC_LIST1, &CMiniPerformanceCounterDlg::OnLbnSelchangeList1)
    ON_LBN_SELCHANGE(IDC_LIST3, &CMiniPerformanceCounterDlg::OnLbnSelchangeList3)
    ON_BN_CLICKED(IDC_BUTTON2, &CMiniPerformanceCounterDlg::OnBnClickedButton2)
    ON_WM_CLOSE()
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CMiniPerformanceCounterDlg ��Ϣ�������

BOOL CMiniPerformanceCounterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

    list<string> objectList;

	SysBase::CPerformanceCounter::GetCounterObjectList(objectList);
    
    list<string>::iterator entity = objectList.begin();
    list<string>::iterator endEntity = objectList.end();

    for (; entity != endEntity; ++entity)
    {
        m_LB_Object.AddString(entity->c_str());
    }
    
    //////////////////////////////////////////////////////////////////////////

    DWORD dwStyle = m_ListShow.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
    dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
    dwStyle |= LVS_EX_DOUBLEBUFFER;
    m_ListShow.SetExtendedStyle(dwStyle); //������չ���

    m_ListShow.InsertColumn(PROC_COLUMN_INDEX_NAME, "������", 0, 500);
    m_ListShow.InsertColumn(PROC_COLUMN_INDEX_VALUE, "��ֵ", 0, 120);

    // TODO: �ڴ���Ӷ���ĳ�ʼ������
    SetTimer(DLG_TIMER_ID, 1000, NULL);

    CPerformanceCounterMonitor::Instance().Start();

    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMiniPerformanceCounterDlg::OnClose()
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

    KillTimer(DLG_TIMER_ID);

    CPerformanceCounterMonitor::Instance().Stop();

    CDialogEx::OnClose();
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMiniPerformanceCounterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMiniPerformanceCounterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//�������б�ѡ���
void CMiniPerformanceCounterDlg::OnLbnSelchangeList2()
{
    this->ShowCounterPath();
}

//�����б�ѡ���
void CMiniPerformanceCounterDlg::OnLbnSelchangeList1()
{
    m_LB_ObjectItem.ResetContent();
    m_LB_ItemInstance.ResetContent();

    char szText[1024] = {0};
    m_LB_Object.GetText(m_LB_Object.GetCurSel(), szText);

    list<string> counterObjectItemListOut;
    list<string> counterInstanceListOut;

    SysBase::CPerformanceCounter::GetCounterObjectItemList(
        counterObjectItemListOut, 
        counterInstanceListOut, 
        szText);

    {
        list<string>::iterator entity = counterObjectItemListOut.begin();
        list<string>::iterator endEntity = counterObjectItemListOut.end();

        for (; entity != endEntity; ++entity)
        {
            m_LB_ObjectItem.AddString(entity->c_str());
        }
    }

    {
        list<string>::iterator entity = counterInstanceListOut.begin();
        list<string>::iterator endEntity = counterInstanceListOut.end();

        for (; entity != endEntity; ++entity)
        {
            m_LB_ItemInstance.AddString(entity->c_str());
        }
    }

    //////////////////////////////////////////////////////////////////////////

    if (m_LB_ObjectItem.GetCount() > 0)
    {
        m_LB_ObjectItem.SetCurSel(0);
    }

    if (m_LB_ItemInstance.GetCount() > 0)
    {
        m_LB_ItemInstance.SetCurSel(0);
    }

    //////////////////////////////////////////////////////////////////////////

    this->ShowCounterPath();
}

void CMiniPerformanceCounterDlg::ShowCounterPath()
{
    char szObject[1024] = {0};
    char szObjectItem[1024] = {0};
    char szInstance[1024] = {0};
    char szCounterPath[1024] = {0};

    if (m_LB_Object.GetCount() > 0)
    {
        m_LB_Object.GetText(m_LB_Object.GetCurSel(), szObject);
    }

    if (m_LB_ObjectItem.GetCount() > 0)
    {
        m_LB_ObjectItem.GetText(m_LB_ObjectItem.GetCurSel(), szObjectItem);
    }

    if (m_LB_ItemInstance.GetCount() > 0)
    {
        m_LB_ItemInstance.GetText(m_LB_ItemInstance.GetCurSel(), szInstance);
    }

    CPerformanceCounter::BuildCounterPath(szObject, szInstance, szObjectItem, szCounterPath, 1024);

    m_EditCounterPath.SetWindowTextA(szCounterPath);
}


void CMiniPerformanceCounterDlg::OnLbnSelchangeList3()
{
    this->ShowCounterPath();
}

//���
void CMiniPerformanceCounterDlg::OnBnClickedButton1()
{
    char szCounterPath[1024] = {0};
    m_EditCounterPath.GetWindowTextA(szCounterPath, 1023);

    if (!CPerformanceCounter::IsCounterPathValid(szCounterPath))
    {
        return;
    }

    CounterMap::iterator entity = s_CounterMap.find(szCounterPath);

    if (entity != s_CounterMap.end())
    {
        return;
    }

    s_CounterMap[szCounterPath] = s_nIndex++;

    char szTemp[1024] = {0};

    LVITEMA aLvItem = {0};
    aLvItem.mask = LVIF_TEXT | LVIF_PARAM;
    aLvItem.lParam = s_CounterMap[szCounterPath];
    aLvItem.pszText = szCounterPath;
    aLvItem.iItem = m_ListShow.GetItemCount();
    m_ListShow.InsertItem(&aLvItem);

    sprintf_s(szTemp, 1023, "0.00");
    aLvItem.pszText = szTemp;
    aLvItem.iSubItem = PROC_COLUMN_INDEX_VALUE;
    m_ListShow.SetItem(&aLvItem);

    CPerformanceCounterMonitor::Instance().AddCounter(szCounterPath);
}

//�Ƴ�
void CMiniPerformanceCounterDlg::OnBnClickedButton2()
{
    int nIndex = m_ListShow.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);

    if (nIndex >= 0)
    {
        char szText[1024] = {0};

        m_ListShow.GetItemText(nIndex, PROC_COLUMN_INDEX_NAME, szText, 1023);

        s_CounterMap.erase(szText);

        m_ListShow.DeleteItem(nIndex);
    }
}

void CMiniPerformanceCounterDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

    if (DLG_TIMER_ID == nIDEvent)
    {
        map<string, double> counterValueMap;

        CPerformanceCounterMonitor::Instance().GetCounterValue(counterValueMap);

        if (0 == counterValueMap.size())
        {
            return;
        }

        if (0 == s_CounterMap.size())
        {
            return;
        }

        //////////////////////////////////////////////////////////////////////////
        //����ListView������Ϣ

        map<string, double>::iterator valueEntity = counterValueMap.begin();
        map<string, double>::iterator valueEndEntity = counterValueMap.end();

        m_ListShow.SetRedraw(FALSE);

        for (; valueEntity != valueEndEntity; ++valueEntity)
        {
            CounterMap::iterator entity = s_CounterMap.find(valueEntity->first);

            if (entity == s_CounterMap.end())
            {
                continue;
            }
            else
            {
                //�����б���½�����Ϣ

                LVFINDINFOA aLVFINDINFO = {0};
                aLVFINDINFO.flags = LVFI_PARAM;
                aLVFINDINFO.lParam = entity->second;
                int nIndex = m_ListShow.FindItem(&aLVFINDINFO);

                if (nIndex >= 0)
                {
                    char szTemp[1024] = {0};
                    sprintf_s(szTemp, 1023, "%f", valueEntity->second);
                    m_ListShow.SetItemText(nIndex, PROC_COLUMN_INDEX_VALUE, szTemp);
                }
            }
        }

        m_ListShow.SetRedraw(TRUE);
        m_ListShow.Invalidate();
        m_ListShow.UpdateWindow();
    }

    //////////////////////////////////////////////////////////////////////////

    CDialogEx::OnTimer(nIDEvent);
}
