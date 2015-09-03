#include <metahook.h>
#include <com_model.h>
#include "configs.h"
#include "ViewPort.h"
#include "plugins.h"

model_t *g_MapSprite;

struct model_s *LoadMapSprite(const char *filename)
{
	static char lastname[MAX_PATH];

	if (g_MapSprite && !strcmp(lastname, filename))
		return g_MapSprite;

	g_MapSprite = gEngfuncs.LoadMapSprite(filename);

	g_pViewPort->UpdateMapSprite();

	strcpy(lastname, filename);
	return g_MapSprite;
}

int GetScreenInfo(SCREENINFO *pscrinfo)
{
	static bool initialize = false;
	static SCREENINFO scrinfo;

	if (!initialize)
	{
		memset(&scrinfo, 0, sizeof(scrinfo));
		scrinfo.iSize = sizeof(SCREENINFO);

		if (g_pMetaSave->pEngineFuncs->pfnGetScreenInfo(&scrinfo))
		{
			initialize = true;
		}
	}

	if (pscrinfo->iSize == sizeof(SCREENINFO))
	{
		pscrinfo->iFlags = scrinfo.iFlags;
		pscrinfo->iCharHeight = scrinfo.iCharHeight;
		pscrinfo->iWidth = g_iVideoWidth;
		pscrinfo->iHeight = g_iVideoHeight;
		return 1;
	}

	return 0;
}

void HookEvent(char *name, void (*pfnEvent)(struct event_args_s *args))
{
}

void Con_Printf(char *fmt, ...)
{
}

int CheckParm(char *parm, char **ppnext)
{
	if (ppnext == NULL && (!strcmp(parm, "-nomouse") || !strcmp(parm, "-nojoy")))
		return 1;

	return gEngfuncs.CheckParm(parm, ppnext);
}

void GetPlayerInfo(int ent_num, hud_player_info_t *pinfo)
{
	static hud_player_info_t info;
	g_pMetaSave->pEngineFuncs->pfnGetPlayerInfo(ent_num, &info);

	pinfo->name = info.name;
	pinfo->ping = info.ping;
	pinfo->thisplayer = info.thisplayer;
	pinfo->spectator = info.spectator;
	pinfo->packetloss = info.packetloss;
	pinfo->model = info.model;
	pinfo->topcolor = info.topcolor;
	pinfo->bottomcolor = info.bottomcolor;

	if (g_dwEngineBuildnum >= 5953)
		pinfo->m_nSteamID = info.m_nSteamID;
}

void SetCrosshair(HSPRITE hspr, wrect_t rc, int r, int g, int b)
{
}