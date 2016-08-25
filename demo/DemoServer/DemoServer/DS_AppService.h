#pragma once

#include "DS_Common.h"

namespace EM
{
    class CAppService : public SysBase::IServiceHandler
    {
    public:

        CAppService();

        virtual ~CAppService();

    protected:

        bool InitLib();

        bool LoadConfig();

        bool InitAppConfig();

        bool StartApp();

        void StopApp();

        //�¼�:������������������Ӧ��ҵ���߼��̣߳���Ҫ�ڸ��¼���ʹ��ѭ���ȴ���Ϣ��
        //����ֵ: TRUE ������Ϣ�ȴ� FALSE �˳�
        virtual bool OnRun(int nArgc, char** argv);

        //�¼�: ���յ�����ֹͣ��
        virtual void OnStop();
    };
}