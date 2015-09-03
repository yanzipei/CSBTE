#include <windows.h>

HMODULE g_hSteamClient;

void SteamClient_LoadLibray(HMODULE hModule)
{
	g_hSteamClient = hModule;
}