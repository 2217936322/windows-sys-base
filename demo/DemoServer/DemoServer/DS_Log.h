#pragma once

#include "DS_Common.h"

namespace EM
{
    class CLogLoader
    {
    public:

        CLogLoader();

        virtual ~CLogLoader();

        static void Init();

        //���������ü��غ����
        static void ResetLogLevelFromConfig();
    };
}