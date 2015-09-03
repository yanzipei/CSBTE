#include <metahook.h>
#include "Bink.h"
#include "playaudio.h"

bool g_extdll_inited = false;

void ExtDLL_Init(void)
{
	Bink_Init();
	PlayAudio_Init();

	g_extdll_inited = true;
}

void ExtDLL_Release(void)
{
	if (!g_extdll_inited)
		return;

	g_extdll_inited = false;

	Bink_Shutdown();
	PlayAudio_Shutdown();
}

void ExtDLL_Frame(void)
{
	if (!g_extdll_inited)
		return;

	PlayAudio_Frame();
}