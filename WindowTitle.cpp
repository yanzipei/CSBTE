#include "metahook.h"
#include "Video.h"
#include "plugins.h"
#include "configs.h"

char g_szSaveTitle[128];

void WindowTitle_Init(void)
{
	GetWindowText(g_hMainWnd, g_szSaveTitle, sizeof(g_szSaveTitle) - 1);
}

void WindowTitle_Reset(void)
{
	SetWindowText(g_hMainWnd, g_szSaveTitle);
}

void WindowTitle_SetTAG(char *format, ...)
{
	static char fullTitle[256];
	sprintf(fullTitle, "%s - %s", g_szSaveTitle, gConfigs.szGameVersion);
	SetWindowText(g_hMainWnd, fullTitle);
}