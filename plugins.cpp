#include <metahook.h>
#include "exportfuncs.h"
#include "model.h"
#include "textures.h"
#include "client.h"
#include "LoadTGA.h"
#include "BaseUI.h"
#include "configs.h"
#include "info.h"
#include "demo.h"
#include "vgui_internal.h"
#include "Modules.h"
#include "Video.h"
#include "gamma.h"
#include "CrashHandle.h"
#include "mempatchs.h"
#include "perf_counter.h"
#include "WindowTitle.h"
#include "NewRegistry.h"
#include "SteamAPI.h"
#include "Renderer.h"
#include "extdll.h"
#include "sys.h"
#include "inputw32.h"
#include "view.h"
#include "camera.h"
#include "zone.h"
#include "SecureClient.h"
#include "kbutton.h"
#include "tier0\memalloc.h"

cl_exportfuncs_t gExportfuncs;
mh_interface_t *g_pInterface;
metahook_api_t *g_pMetaHookAPI;
mh_enginesave_t *g_pMetaSave;

HINSTANCE g_hInstance, g_hThisModule, g_hEngineModule;
DWORD g_dwEngineBase, g_dwEngineSize;
DWORD g_dwEngineBuildnum;
DWORD g_iVideoMode;
int g_iVideoWidth, g_iVideoHeight, g_iBPP;
bool g_bWindowed;
bool g_bIsNewEngine;
bool g_bIsUseSteam;
bool g_bIsRunningSteam;
bool g_bIsDebuggerPresent;
IFileSystem *g_pFileSystem;

cvar_t *developer;

void (*g_pfnHUD_VoiceStatus)(int entindex, qboolean bTalking);

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	g_hThisModule = hinstDLL;

	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
#ifdef _CRTDBG_MAP_ALLOC
			_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
#endif
			break;
		}

		case DLL_PROCESS_DETACH:
		{
#ifdef _DEBUG
			g_pMemAlloc->DumpStats();
#endif
			break;
		}
	}

	return TRUE;
}

void IPlugins::Init(metahook_api_t *pAPI, mh_interface_t *pInterface, mh_enginesave_t *pSave)
{
	BOOL (*IsDebuggerPresent)(void) = (BOOL (*)(void))GetProcAddress(GetModuleHandle("kernel32.dll"), "IsDebuggerPresent");

	g_pInterface = pInterface;
	g_pMetaHookAPI = pAPI;
	g_pMetaSave = pSave;
	g_hInstance = GetModuleHandle(NULL);
	g_bIsUseSteam = false;
	g_bIsRunningSteam = false;
	g_bIsDebuggerPresent = IsDebuggerPresent() != FALSE;

	NewReg_Init();
	Config_Init();
	Renderer_Init();

	gPerformanceCounter.InitializePerformanceCounter();

	if (g_pRenderer)
		g_pRenderer->Init(pAPI, pInterface, pSave);
}

void IPlugins::Shutdown(void)
{
	if (g_pRenderer)
		g_pRenderer->Shutdown();

	Module_Shutdown();
	Renderer_Shutdown();
}

void IPlugins::LoadEngine(void)
{
	g_pFileSystem = g_pInterface->FileSystem;
	g_iVideoMode = g_pMetaHookAPI->GetVideoMode(&g_iVideoWidth, &g_iVideoHeight, &g_iBPP, &g_bWindowed);
	g_dwEngineBuildnum = g_pMetaHookAPI->GetEngineBuildnum();
	g_iBPP = 32;

	if (g_iVideoMode == VIDEOMODE_SOFTWARE)
		return;

	float flStartTime = gPerformanceCounter.GetCurTime();

	g_hEngineModule = g_pMetaHookAPI->GetEngineModule();
	g_dwEngineBase = g_pMetaHookAPI->GetEngineBase();
	g_dwEngineSize = g_pMetaHookAPI->GetEngineSize();

	g_pfnGL_LoadTexture = (int (*)(char *, int, int, int, byte *, qboolean, int, byte *))g_pMetaHookAPI->SearchPattern((void *)g_dwEngineBase, g_dwEngineSize, GL_LOADTEXTURE_SIG, sizeof(GL_LOADTEXTURE_SIG) - 1);
	g_pfnLoadTGA = (int (*)(const char *, byte *, int, int *, int *))g_pMetaHookAPI->SearchPattern((void *)g_dwEngineBase, g_dwEngineSize, LOADTGA_SIG, sizeof(LOADTGA_SIG) - 1);
	g_pfnInfo_SetValueForKey = (void (*)(char *, char *, char *, int))g_pMetaHookAPI->SearchPattern((void *)g_dwEngineBase, g_dwEngineSize, INFO_SETVALUEFORKEY_SIG, sizeof(INFO_SETVALUEFORKEY_SIG) - 1);
	g_pfnVideoMode_Create = (CVideoMode_Common *(*)(void))g_pMetaHookAPI->SearchPattern((void *)g_dwEngineBase, g_dwEngineSize, VIDEOMODE_CREATE_SIG, sizeof(VIDEOMODE_CREATE_SIG) - 1);
	g_pVID_EnumDisplayModesProc = (HRESULT (CALLBACK *)(void *, DWORD *))g_pMetaHookAPI->SearchPattern((void *)g_dwEngineBase, g_dwEngineSize, VID_ENUMDISPLAYMODESPROC_SIG, sizeof(VID_ENUMDISPLAYMODESPROC_SIG) - 1);

	g_phLoadTGA = g_pMetaHookAPI->InlineHook(g_pfnLoadTGA, LoadTGA, (void *&)g_pfnLoadTGA);
	g_phInfo_SetValueForKey = g_pMetaHookAPI->InlineHook(g_pfnInfo_SetValueForKey, Info_SetValueForKey, (void *&)g_pfnInfo_SetValueForKey);
	g_phVideoMode_Create = g_pMetaHookAPI->InlineHook(g_pfnVideoMode_Create, VideoMode_Create, (void *&)g_pfnVideoMode_Create);
	g_phVID_EnumDisplayModesProc = g_pMetaHookAPI->InlineHook(g_pVID_EnumDisplayModesProc, VID_EnumDisplayModesProc, (void *&)g_pVID_EnumDisplayModesProc);

	SteamAPI_InstallHook();
	BaseUI_InstallHook();
	Module_InstallHook();

	if (g_pRenderer)
		g_pRenderer->LoadEngine();
}

void IPlugins::LoadClient(cl_exportfuncs_t *pExportFunc)
{
	if (g_iVideoMode == VIDEOMODE_SOFTWARE)
		return;

	memcpy(&gExportfuncs, pExportFunc, sizeof(gExportfuncs));

	pExportFunc->Initialize = Initialize;
	pExportFunc->ClientFactory = ClientFactory;

	pExportFunc->HUD_Init = HUD_Init;
	pExportFunc->HUD_VidInit = HUD_VidInit;
	pExportFunc->HUD_Redraw = HUD_Redraw;
	pExportFunc->HUD_GetStudioModelInterface = HUD_GetStudioModelInterface;
	pExportFunc->HUD_ProcessPlayerState = HUD_ProcessPlayerState;
	pExportFunc->HUD_TxferLocalOverrides = HUD_TxferLocalOverrides;
	pExportFunc->HUD_PostRunCmd = HUD_PostRunCmd;
	pExportFunc->HUD_TxferPredictionData = HUD_TxferPredictionData;
	pExportFunc->HUD_DrawNormalTriangles = HUD_DrawNormalTriangles;
	pExportFunc->HUD_DrawTransparentTriangles = HUD_DrawTransparentTriangles;
	pExportFunc->HUD_UpdateClientData = HUD_UpdateClientData;
	//pExportFunc->HUD_StudioEvent = HUD_StudioEvent;
	pExportFunc->HUD_Frame = HUD_Frame;
	pExportFunc->HUD_PlayerMove = HUD_PlayerMove;
	pExportFunc->HUD_Shutdown = HUD_Shutdown;
	pExportFunc->HUD_TempEntUpdate = HUD_TempEntUpdate;
	pExportFunc->HUD_CreateEntities = HUD_CreateEntities;
	pExportFunc->HUD_PlayerMoveInit = HUD_PlayerMoveInit;
	pExportFunc->HUD_AddEntity = HUD_AddEntity;
	pExportFunc->HUD_ConnectionlessPacket = HUD_ConnectionlessPacket;
	pExportFunc->HUD_Key_Event = HUD_Key_Event;
	pExportFunc->HUD_DirectorMessage = HUD_DirectorMessage;

	pExportFunc->CL_CreateMove = CL_CreateMove;
	pExportFunc->CL_IsThirdPerson = CL_IsThirdPerson;

	pExportFunc->IN_ActivateMouse = IN_ActivateMouse;
	pExportFunc->IN_DeactivateMouse = IN_DeactivateMouse;
	pExportFunc->IN_MouseEvent = IN_MouseEvent;
	pExportFunc->IN_Accumulate = IN_Accumulate;
	pExportFunc->IN_ClearStates = IN_ClearStates;

	pExportFunc->CAM_Think = CAM_Think;
	pExportFunc->V_CalcRefdef = V_CalcRefdef;
	pExportFunc->Demo_ReadBuffer = Demo_ReadBuffer;
	pExportFunc->KB_Find = KB_Find;

	g_pMetaHookAPI->InlineHook(gExportfuncs.HUD_VoiceStatus, HUD_VoiceStatus, (void *&)g_pfnHUD_VoiceStatus);

	VID_Init();

	WindowTitle_Init();
	WindowTitle_SetTAG("Loading...");

	if (g_pRenderer)
		g_pRenderer->LoadClient(pExportFunc);
}

void IPlugins::ExitGame(int iResult)
{
	NewReg_Shutdown();
	VID_Shutdown();
	Gamma_Shutdown();
	ExtDLL_Release();

	if (g_pRenderer)
		g_pRenderer->ExitGame(iResult);
}

EXPOSE_SINGLE_INTERFACE(IPlugins, IPlugins, METAHOOK_PLUGIN_API_VERSION);