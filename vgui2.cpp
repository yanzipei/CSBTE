#include <metahook.h>
#include <VGUI/KeyCode.h>
#include <IEngineSurface.h>
#include <IEngineVGui.h>
#include <IGameUIFuncs.h>
#include <IBaseUI.h>
#include "vgui_internal.h"
#include <vstdlib/IKeyValuesSystem.h>
#include <VGUI/ISystem.h>
#include <VGUI/IPanel.h>
#include <VGUI/ISurface.h>
#include "FileSystem.h"
#include "KeyValues.h"
#include <cvardef.h>
#include "plugins.h"

cl_enginefuncs_s *engine;

IEngineSurface *staticSurface;
IEngineVGui *enginevguifuncs;
IGameUIFuncs *gameuifuncs;
vgui::ISurface *enginesurfacefuncs;
IBaseUI *baseuifuncs;

namespace vgui
{
class IInputInternal *g_pInput;
class ISchemeManager *g_pScheme;
class ISurface *g_pSurface;
class ISystem *g_pSystem;
class IVGui *g_pIVgui;
class IPanel *g_pIPanel;
}

IKeyValuesSystem *g_pKeyValuesSystem;
IFileSystem *g_pFullFileSystem;

IKeyValuesSystem *KeyValuesSystem(void)
{
	return g_pKeyValuesSystem;
}

ICommandLine *CommandLine(void)
{
	return g_pInterface->CommandLine;
}

bool vgui::VGui_LoadEngineInterfaces(CreateInterfaceFn vguiFactory, CreateInterfaceFn engineFactory)
{
	staticSurface = (IEngineSurface *)engineFactory(ENGINE_SURFACE_VERSION, NULL);
	enginevguifuncs = (IEngineVGui *)engineFactory(VENGINE_VGUI_VERSION, NULL);
	enginesurfacefuncs = (vgui::ISurface *)engineFactory(VGUI_SURFACE_INTERFACE_VERSION, NULL);
	gameuifuncs = (IGameUIFuncs *)engineFactory(VENGINE_GAMEUIFUNCS_VERSION, NULL);
	baseuifuncs = (IBaseUI *)engineFactory(BASEUI_INTERFACE_VERSION, NULL);

	g_pKeyValuesSystem = (IKeyValuesSystem *)vguiFactory(KEYVALUESSYSTEM_INTERFACE_VERSION, NULL);
	g_pSystem = (ISystem *)vguiFactory(VGUI_SYSTEM_INTERFACE_VERSION, NULL);
	g_pFullFileSystem = g_pFileSystem;
	g_pIPanel = (IPanel *)vguiFactory(VGUI_PANEL_INTERFACE_VERSION, NULL);
	g_pVGui = (IVGui *)vguiFactory(VGUI_PANEL_INTERFACE_VERSION, NULL);
	g_pKeyValuesSystem->RegisterSizeofKeyValues(sizeof(KeyValues));
	return true;
}