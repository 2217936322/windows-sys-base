#include "DS_AppService.h"
#include "DS_Config.h"
#include "DS_Log.h"
#include "DS_StatisticsThread.h"
#include "DS_WorkThread.h"
#include "DS_NetServer.h"
#include "DS_ReloadThread.h"
#include "DS_ConfigMoniter.h"

namespace EM
{
    CAppService::CAppService()
    {
        CLogLoader::Init();
    }

    CAppService::~CAppService()
    {

    }

    bool CAppService::InitLib()
    {
        if (!CSocketLoader::InitSocket())
        {
            LOG_WRITE(LOG_KEY_SYSTEM, CLog::LOG_LEVEL_ERROR, "CAppService::InitLib init socket lib failed !");

            return false;
        }

        return true;
    }

    bool CAppService::LoadConfig()
    {
        if (!CConfig::Instance().Load())
        {
            LOG_WRITE(LOG_KEY_SYSTEM, CLog::LOG_LEVEL_ERROR, "CAppService::LoadConfig load config failed !");

            return false;
        }

        return true;
    }

    bool CAppService::InitAppConfig()
    {
        CLogLoader::ResetLogLevelFromConfig();

        return true;
    }

    bool CAppService::StartApp()
    {
        //////////////////////////////////////////////////////////////////////////
        //����ͳ���߳�

        if (!CStatisticsThread::Instance().Start())
        {
            LOG_WRITE(LOG_KEY_SYSTEM, CLog::LOG_LEVEL_ERROR, " CAppService::StartApp Start CStatisticsThread failed !");

            return false;
        }

        //////////////////////////////////////////////////////////////////////////
        //���������̣߳���ʱ����һЩ�������ݵȣ�

        if (!CReloadThread::Instance().Start())
        {
            LOG_WRITE(LOG_KEY_SYSTEM, CLog::LOG_LEVEL_ERROR, " CAppService::StartApp Start CReloadThread failed !");

            return false;
        }

        //////////////////////////////////////////////////////////////////////////
        //���������ļ����

        if (!CConfigMoniter::Instance().Start())
        {
            LOG_WRITE(LOG_KEY_SYSTEM, CLog::LOG_LEVEL_ERROR, " CAppService::StartApp Start CConfigMoniter failed !");

            return false;
        }

        //////////////////////////////////////////////////////////////////////////
        //���������߳�

        if (!CWorkThread::Instance().Start())
        {
            LOG_WRITE(LOG_KEY_SYSTEM, CLog::LOG_LEVEL_ERROR, " CAppService::StartApp Start CWorkThread failed !");

            return false;
        }

        //////////////////////////////////////////////////////////////////////////
        //�����շ�����ģ��

        if (!CNetServer::Instance().Start())
        {
            LOG_WRITE(LOG_KEY_SYSTEM, CLog::LOG_LEVEL_ERROR, " CAppService::StartApp Start CNetServer failed !");

            return false;
        }

        return true;
    }

    void CAppService::StopApp()
    {
        CNetServer::Instance().Stop();

        CWorkThread::Instance().Stop();

        CConfigMoniter::Instance().Stop();

        CReloadThread::Instance().Stop();

        CStatisticsThread::Instance().Stop();
    }

    bool CAppService::OnRun(int nArgc, char** argv)
    {
        //////////////////////////////////////////////////////////////////////////
        //��ʼ�����ÿ�

        if (!this->InitLib())
        {
            return false;
        }

        //////////////////////////////////////////////////////////////////////////
        //��������

        if (!this->LoadConfig())
        {
            return false;
        }

        //////////////////////////////////////////////////////////////////////////
        //APP ��ʼ�����ֲ�������

        if (!this->InitAppConfig())
        {
            return false;
        }

        //////////////////////////////////////////////////////////////////////////
        //APP ��������ģ��

        if (!this->StartApp())
        {
            return false;
        }

        return true;
    }

    void CAppService::OnStop()
    {
        this->StopApp();
    }
}