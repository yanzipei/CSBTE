#include <metahook.h>
#include <r_studioint.h>
#include <r_efx.h>
#include <ref_params.h>
#include <cl_entity.h>
#include <studio.h>
#include <cvardef.h>
#include <usercmd.h>
#include "engfuncs.h"
#include "qgl.h"
#include "r.h"
#include "hud.h"
#include "svchook.h"
#include "msghook.h"
#include "cmd.h"
#include "BaseUI.h"
#include "CVARs.h"
#include "gamma.h"
#include "mempatchs.h"
#include "common.h"
#include "configs.h"
#include "CrashHandle.h"
#include "events.h"
#include "client.h"
#include "player.h"
#include "weapons.h"
#include "eventscripts.h"
#include <pm_defs.h>
#include <event_api.h>
#include "WindowTitle.h"
#include "eventapi.h"
#include "extdll.h"
#include "Video.h"
#include "Renderer.h"
#include "plugins.h"
#include "r.h"
#include "modules.h"
#include "inputw32.h"
#include "entity_types.h"
#include "master.h"
#include "game_shared/voice_status.h"

extern "C"
{
#include "pm_shared.h"
}

cl_enginefunc_t gEngfuncs;

int Initialize(struct cl_enginefuncs_s *pEnginefuncs, int iVersion)
{
	engine = pEnginefuncs;
	memcpy(&gEngfuncs, pEnginefuncs, sizeof(gEngfuncs));

	pEnginefuncs->LoadMapSprite = LoadMapSprite;
	pEnginefuncs->pfnGetPlayerInfo = GetPlayerInfo;
	pEnginefuncs->CheckParm = CheckParm;
	pEnginefuncs->pfnGetPlayerInfo = GetPlayerInfo;
	pEnginefuncs->pfnGetScreenInfo = GetScreenInfo;
	pEnginefuncs->pfnSetCrosshair = SetCrosshair;

	COM_Init();
	QGL_Init();
	CVAR_Init();
	MSG_Init();
	ExtDLL_Init();

	int result = gExportfuncs.Initialize(pEnginefuncs, iVersion);

	if (result)
		IN_InstallHook();

	return result;
}

void *ClientFactory(void)
{
	return Sys_GetFactoryThis();
}

void InitInput(void);
void ShutdownInput(void);

void HUD_Init(void)
{
	gExportfuncs.HUD_Init();

	InitInput();
	gHUD.Init();

	developer = gEngfuncs.pfnGetCvarPointer("developer");

#ifdef _DEBUG
	WindowTitle_SetTAG("%s (debug)", __DATE__);
#else
	if (developer->value)
		WindowTitle_SetTAG("%s (dev)", __DATE__);
	else
		WindowTitle_SetTAG("%s", __DATE__);
#endif
}

int HUD_VidInit(void)
{
	int result = gExportfuncs.HUD_VidInit();

	VID_VidInit();
	gHUD.VidInit();

	return result;
}

int HUD_Redraw(float time, int intermission)
{
	int result = gExportfuncs.HUD_Redraw(time, intermission);

	gHUD.Redraw(time, intermission);
	return result;
}

int HUD_UpdateClientData(client_data_t *pcldata, float flTime)
{
	IN_Commands();

	gHUD.UpdateClientData(pcldata, flTime);
	return gExportfuncs.HUD_UpdateClientData(pcldata, flTime);
}

void HUD_PlayerMove(struct playermove_s *ppmove, int server)
{
	gEngfuncs.pEventAPI->EV_LocalPlayerViewheight(g_vecEyePos);

	g_vecEyePos[0] += ppmove->origin[0];
	g_vecEyePos[1] += ppmove->origin[1];
	g_vecEyePos[2] += ppmove->origin[2];

	return gExportfuncs.HUD_PlayerMove(ppmove, server);
}

void HUD_Frame(double time)
{
	Gamma_Check();
	ExtDLL_Frame();

	GetClientVoice()->Frame(time);
}

void HUD_Shutdown(void)
{
	ShutdownInput();
	ExtDLL_Release();

	return gExportfuncs.HUD_Shutdown();
}

void HUD_TempEntUpdate(double frametime, double client_time, double cl_gravity, struct tempent_s **ppTempEntFree, struct tempent_s **ppTempEntActive, int (*Callback_AddVisibleEntity)(struct cl_entity_s *pEntity), void (*Callback_TempEntPlaySound)(struct tempent_s *pTemp, float damp))
{
	gExportfuncs.HUD_TempEntUpdate(frametime, client_time, cl_gravity, ppTempEntFree, ppTempEntActive, Callback_AddVisibleEntity, Callback_TempEntPlaySound);
}

void HUD_PlayerMoveInit(struct playermove_s *ppmove)
{
	PM_Init(ppmove);

	gExportfuncs.HUD_PlayerMoveInit(ppmove);
}

int HUD_ConnectionlessPacket(const struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size)
{
	return CL_ConnectionlessPacket(net_from, args, response_buffer, response_buffer_size);
}