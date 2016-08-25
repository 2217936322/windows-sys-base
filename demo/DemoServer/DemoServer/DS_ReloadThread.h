#pragma once

#include "DS_Common.h"

namespace EM
{
    class CReloadThread : public CSingletonT<CReloadThread>, public CCustomThread
    {
    public:

        CReloadThread();

        virtual ~CReloadThread();

        //���ܣ�����
        //����ֵ��TRUE �ɹ���FALSE ʧ��
        bool Start();

        //���ܣ�ֹͣ
        void Stop();

        //���ܣ���������
        void ReloadNow();

    protected:

        virtual void Proc();

    private:

        bool m_bStop;

        CEvent m_StopEvent;

        CAutoEvent m_ReLoadEvent;
    };
}
