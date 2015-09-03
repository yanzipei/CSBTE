#include <metahook.h>
#include "Bink.h"
#include "CVARs.h"
#include "plugins.h"

HMODULE g_hBink;

S32 (RADEXPLINK *g_pfnBinkCopyToBuffer)(HBINK bnk, void *dest, S32 destpitch, U32 destheight, U32 destx, U32 desty, U32 flags);
S32 (RADEXPLINK *g_pfnBinkDoFrame)(HBINK bnk);
void (RADEXPLINK *g_pfnBinkGoto)(HBINK bnk, U32 frame, S32 flags);
S32 (RADEXPLINK *g_pfnBinkSetSoundOnOff)(HBINK bnk, S32 onoff);
HBINK (RADEXPLINK *g_pfnBinkOpen)(const char PTR4 *name, U32 flags);
void (RADEXPLINK *g_pfnBinkClose)(HBINK bnk);
HBINKBUFFER (RADEXPLINK *g_pfnBinkBufferOpen)(void *wnd, U32 width, U32 height, U32 bufferflags);
void (RADEXPLINK *g_pfnBinkBufferClose)(HBINKBUFFER buf);

S32 RADEXPLINK BinkCopyToBuffer(HBINK bnk, void *dest, S32 destpitch, U32 destheight, U32 destx, U32 desty, U32 flags)
{
	return g_pfnBinkCopyToBuffer(bnk, dest, destpitch, destheight, destx, desty, flags);
}

S32 RADEXPLINK BinkDoFrame(HBINK bnk)
{
	return g_pfnBinkDoFrame(bnk);
}

void RADEXPLINK BinkGoto(HBINK bnk, U32 frame, S32 flags)
{
	return g_pfnBinkGoto(bnk, frame, flags);
}

S32 RADEXPLINK BinkSetSoundOnOff(HBINK bnk, S32 onoff)
{
	return g_pfnBinkSetSoundOnOff(bnk, onoff);
}

HBINK RADEXPLINK BinkOpen(const char PTR4 *name, U32 flags)
{
	if (!g_hBink)
		return NULL;

	return g_pfnBinkOpen(name, flags);
}

void RADEXPLINK BinkClose(HBINK bnk)
{
	return g_pfnBinkClose(bnk);
}

HBINKBUFFER RADEXPLINK BinkBufferOpen(void *wnd, U32 width, U32 height, U32 bufferflags)
{
	return g_pfnBinkBufferOpen(wnd, width, height, bufferflags);
}

void RADEXPLINK BinkBufferClose(HBINKBUFFER buf)
{
	g_pfnBinkBufferClose(buf);
}

void Bink_Init(void)
{
	char fullPath[MAX_PATH];
	g_pFileSystem->GetLocalPath("cl_dlls/binkw32.dll", fullPath, sizeof(fullPath));
	g_hBink = LoadLibrary(fullPath);

	if (!g_hBink)
		return;

	g_pfnBinkCopyToBuffer = (S32 (RADEXPLINK *)(HBINK, void *, S32, U32, U32, U32, U32))GetProcAddress(g_hBink, "_BinkCopyToBuffer@28");
	g_pfnBinkDoFrame = (S32 (RADEXPLINK *)(HBINK))GetProcAddress(g_hBink, "_BinkDoFrame@4");
	g_pfnBinkGoto = (void (RADEXPLINK *)(HBINK, U32, S32))GetProcAddress(g_hBink, "_BinkGoto@12");
	g_pfnBinkSetSoundOnOff = (S32 (RADEXPLINK *)(HBINK, S32))GetProcAddress(g_hBink, "_BinkSetSoundOnOff@8");
	g_pfnBinkOpen = (HBINK (RADEXPLINK *)(const char PTR4 *, U32))GetProcAddress(g_hBink, "_BinkOpen@8");
	g_pfnBinkClose = (void (RADEXPLINK *)(HBINK))GetProcAddress(g_hBink, "_BinkClose@4");
	g_pfnBinkBufferOpen = (HBINKBUFFER (RADEXPLINK *)(void *, U32, U32, U32))GetProcAddress(g_hBink, "_BinkBufferOpen@16");
	g_pfnBinkBufferClose = (void (RADEXPLINK *)(HBINKBUFFER))GetProcAddress(g_hBink, "_BinkBufferClose@4");
}

void Bink_Shutdown(void)
{
	if (!g_hBink)
		return;

	FreeLibrary(g_hBink);
}