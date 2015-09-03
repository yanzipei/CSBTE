#include <metahook.h>
#include <cvardef.h>
#include "buildnum.h"
#include "plugins.h"

cvar_t *g_pcvarGamma = NULL;
cvar_t *g_pcvarEnableConsole = NULL;
cvar_t *g_pcvarEnableBink = NULL;

void CVAR_Register(void)
{
	gEngfuncs.pfnRegisterVariable("bte_buildnum", build_number(), 0);

	g_pcvarGamma = gEngfuncs.pfnRegisterVariable("bte_monitorgamma", "2.2", FCVAR_ARCHIVE);
	g_pcvarEnableConsole = gEngfuncs.pfnRegisterVariable("bte_enable_console", "1", FCVAR_ARCHIVE);
	g_pcvarEnableBink = gEngfuncs.pfnRegisterVariable("bte_enable_bink", "1", FCVAR_ARCHIVE);
}

void CVAR_Reset(void)
{
	cvar_t *name = gEngfuncs.pfnGetCvarPointer("name");

	if (name)
		name->flags &= ~FCVAR_PRINTABLEONLY;
}

void CVAR_Init(void)
{
	CVAR_Register();
	CVAR_Reset();
}