#include <metahook.h>
#include "CVARs.h"
#include "Renderer.h"
#include "configs.h"
#include "plugins.h"
#include "interface.h"

IRenderer *g_pRenderer = NULL;
HINTERFACEMODULE g_hRenderer;

void Renderer_Init(void)
{
	char filepath[MAX_PATH];
	sprintf(filepath, "%s/cl_dlls/renderer.dll", gConfigs.szGameDir);

	g_hRenderer = Sys_LoadModule(filepath);

	if (!g_hRenderer)
		return;

	g_pRenderer = (IRenderer *)((CreateInterfaceFn)Sys_GetFactory(g_hRenderer))(RENDERER_API_VERSION, NULL);
}

void Renderer_Shutdown(void)
{
	if (g_pRenderer)
		Sys_FreeModule(g_hRenderer);
}