#include "DS_AppService.h"

int _tmain(int argc, char** argv)
{
    CAppInfo appInfo;
    CDump::Instance().Init(appInfo.GetAppDirectory(), appInfo.GetAppFileName());

    EM::CAppService appService;
    CService aCService;
    int ret = aCService.Start(&appService, "DemoServer", "DemoServer", "SysBase ʾ������������", argc, argv, false);

    return 0;
}

