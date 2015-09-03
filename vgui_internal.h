#ifndef VGUI_INTERNAL_H
#define VGUI_INTERNAL_H

#ifdef _WIN32
#pragma once
#endif

#include <vgui/VGUI.h>
#include "interface.h"
#include "tier3/tier3.h"
#include <ICommandLine.h>
#include <cvardef.h>
#include "vgui_hook.h"

extern cvar_t *vgui_stencil_test;
extern cvar_t *vgui_message_dialog_modal;
extern cvar_t *vgui_emulatemouse;

namespace vgui
{
bool VGui_InternalLoadInterfaces(CreateInterfaceFn *factoryList, int numFactories);
bool VGui_LoadEngineInterfaces(CreateInterfaceFn vguiFactory, CreateInterfaceFn engineFactory);

extern class IInputInternal *g_pInput;
extern class ISchemeManager *g_pScheme;
extern class ISurface *g_pSurface;
extern class ISystem *g_pSystem;
extern class IVGui *g_pIVgui;
extern class IPanel *g_pIPanel;
}

extern struct cl_enginefuncs_s *engine;

extern class IEngineSurface *staticSurface;
extern class IEngineVGui *enginevguifuncs;
extern class IGameUIFuncs *gameuifuncs;
extern class vgui::ISurface *enginesurfacefuncs;
extern class IBaseUI *baseuifuncs;

#endif