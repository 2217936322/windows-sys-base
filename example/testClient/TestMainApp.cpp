#define _WIN32_WINNT 0x0502

#include <iostream>
#include "SnmpThread.h"

static bool bExit = false;

/************************************************************************/
/* ���Գ��򣺽���30000�����ݺ�ط�30000����,֮��ر�����,��ϵͳ����   */
/************************************************************************/


#define TEST_DATA_SIZE 1024

typedef struct MSG_HEAD 
{
    DWORD dwSize;
}*PMSG_HEAD;

typedef struct MSG_BODY
{
    char szTest[100];
}*PMSG_BODY;

static LONG nCount = 0;

SysBase::CTcpClient g_CTcpClient;

//////////////////////////////////////////////////////////////////////////

class CMyTcpClientHandler : public SysBase::ITcpClientHandler
{
public:

    virtual UINT32 GetHeadSize()
    {
        return sizeof(MSG_HEAD);
    }

	virtual UINT32 GetMsgSize(const char* pData, UINT32 nDataSize)
    {
        MSG_HEAD *pHead = (MSG_HEAD *)pData;

        return pHead->dwSize;
    }

	virtual void OnReceived(CTcpClient* pCTcpClient, const char* pData, UINT32 nSize)
    {
		CSnmpThread::Instance().Add(CSnmpThread::SNMP_TYPE_RECV);
    }
    
	virtual bool OnConnecting(CTcpClient* pCTcpClient, UINT32& nIP, UINT16& nPort)
	{
		nIP = SysBase::CSocketAddr::ToDwordIP("127.0.0.1");
		nPort = 6543;

		return true;
	}

	virtual void OnConnected(CTcpClient* pCTcpClient, UINT32 nIP, UINT16 nPort)
    {
		cout << "���Ը���:" << ++nCount << "���ӷ������ɹ�" << endl;

		char szBuffer[TEST_DATA_SIZE] = { 0 };

		MSG_HEAD *pSendHead = (MSG_HEAD *)szBuffer;

		pSendHead->dwSize = sizeof(MSG_HEAD) + sizeof(MSG_BODY);

		MSG_BODY *pSendBody = (MSG_BODY *)(szBuffer + sizeof(MSG_HEAD));

		strcpy(pSendBody->szTest, "�ͻ��˵�������Ϣ");

		g_CTcpClient.Send(szBuffer, pSendHead->dwSize);
    }

	virtual void OnConnectFailed(CTcpClient* pCTcpClient, UINT32 nIP, UINT16 nPort)
	{
		cout << "���Ը���:" << ++nCount << "���ӷ�����ʧ��" << endl;
	}

	virtual void OnClosed(CTcpClient* pCTcpClient, ERROR_CODE errorCode)
    {
        cout << "���Ը���:" << ++nCount << "Զ�����ӹر�" << endl;
    }

	virtual void OnTime(CTcpClient* pCTcpClient)
	{
		cout << "���ݼ��" << endl;
	}
};

CMyTcpClientHandler g_CMyTcpClientHandler;

class CSendThread : public SysBase::CCustomThread, public SysBase::CSingletonT<CSendThread>
{
public:

	virtual ~CSendThread(){};
	friend class SysBase::CSingletonT<CSendThread>;

protected:

	virtual void Proc()
	{
		int nCount = 2000;
		int nSleep = 1;
		char pBuffer[1024] = {0};
		
		MSG_HEAD *pSendHead = (MSG_HEAD *)pBuffer;
		pSendHead->dwSize = sizeof(MSG_HEAD) + sizeof(MSG_BODY);

		MSG_BODY *pSendBody = (MSG_BODY *)(pBuffer + sizeof(MSG_HEAD));
		
		while (TRUE)
		{
			for (int nIndex = 0; nIndex < nCount; ++nIndex)
			{
				g_CTcpClient.Send(pBuffer, pSendHead->dwSize);

				CSnmpThread::Instance().Add(CSnmpThread::SNMP_TYPE_SEND);
			}

			Sleep(nSleep);
		}
	}

private:

	CSendThread(){};
};

void main()
{ 
	SysBase::CSocketLoader::InitSocket();

	CSnmpThread::Instance().Start();

    g_CTcpClient.Start(
        &g_CMyTcpClientHandler,
        TEST_DATA_SIZE,
        TEST_DATA_SIZE,
		1000,
		1000,
		true, 
		30 * 1000);

	Sleep(3000);
	
	CSendThread::Instance().Start();

	while (1)
	{
		Sleep(5 * 1000);

		//g_CTcpClient.PostClose();
	}

    

    g_CTcpClient.Stop();
}