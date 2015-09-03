#include <metahook.h>
#include "plugins.h"
#include "master.h"

int (*g_pfnCOM_CheckParm)(char *parm);

int COM_CheckParm(char *parm)
{
	if (!strcmp(parm, "-nomaster"))
		return TRUE;

	return g_pfnCOM_CheckParm(parm);
}

void Master_Init(void)
{
	if (g_dwEngineBuildnum >= 5971)
		return;

	g_pMetaHookAPI->GetNextCallAddr(g_pMetaSave->pEngineFuncs->CheckParm, 0x20);
	g_pfnCOM_CheckParm = (int (*)(char *))g_pMetaHookAPI->GetNextCallAddr(NULL, 0x20);

	if (g_pfnCOM_CheckParm)
		g_pMetaHookAPI->InlineHook(g_pfnCOM_CheckParm, COM_CheckParm, (void *&)g_pfnCOM_CheckParm);
}