#include <metahook.h>
#include "configs.h"
#include "plugins.h"

HKEY g_hCurrentKey = NULL;

LONG (APIENTRY *g_pfnRegCreateKeyExA)(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved, LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition);
LONG (APIENTRY *g_pfnRegCloseKey)(HKEY hKey);
LONG (APIENTRY *g_pfnRegSetValueExA)(HKEY hKey, LPCSTR lpValueName, DWORD Reserved, DWORD dwType, CONST BYTE *lpData, DWORD cbData);
LONG (APIENTRY *g_pfnRegQueryValueExA)(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);

hook_t *g_phRegCreateKeyExA = NULL;
hook_t *g_phRegCloseKey = NULL;
hook_t *g_phRegSetValueExA = NULL;
hook_t *g_phRegQueryValueExA = NULL;

const char *g_pszNewUseKeyName[] =
{
	"Language",
	"CrashInitializingVideoMode",
	"EngineD3D",
	"EngineDLL",
	"ScreenHeight",
	"ScreenWidth",
	"ScreenWindowed"
};

bool NewReg_CheckIsNewKey(LPCSTR lpValueName)
{
	for (int i = 0; i < _ARRAYSIZE(g_pszNewUseKeyName); i++)
	{
		if (!strcmp(lpValueName, g_pszNewUseKeyName[i]))
			return true;
	}

	return false;
}

LONG APIENTRY NewReg_RegCreateKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved, LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition)
{
	LONG res = g_pfnRegCreateKeyExA(hKey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition);

	if (!strcmp(lpSubKey, "Software\\Valve\\Steam"))
	{
		g_hCurrentKey = *phkResult;
	}
	else
		g_hCurrentKey = NULL;

	return res;
}

LONG APIENTRY NewReg_RegCloseKey(HKEY hKey)
{
	LONG res = g_pfnRegCloseKey(hKey);

	if (hKey == g_hCurrentKey)
		g_hCurrentKey = NULL;

	return res;
}

LONG APIENTRY NewReg_RegSetValueExA(HKEY hKey, LPCSTR lpValueName, DWORD Reserved, DWORD dwType, CONST BYTE *lpData, DWORD cbData)
{
	if (NewReg_CheckIsNewKey(lpValueName))
	{
		LONG lResult;
		HKEY hKey2;
		DWORD dwDisposition;

		char szKey[128];
		sprintf(szKey, "Software\\Valve\\Half-Life\\CSBTE\\Settings");

		lResult = g_pfnRegCreateKeyExA(HKEY_CURRENT_USER, szKey, 0, "String", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey2, &dwDisposition);

		if (lResult == ERROR_SUCCESS)
		{
			lResult = g_pfnRegSetValueExA(hKey2, lpValueName, Reserved, dwType, lpData, cbData);

			g_pfnRegCloseKey(hKey2);
			return lResult;
		}
		else
			g_pfnRegCloseKey(hKey2);
	}

	return g_pfnRegSetValueExA(hKey, lpValueName, Reserved, dwType, lpData, cbData);;
}

LONG APIENTRY NewReg_RegQueryValueExA(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
	if (lpValueName)
	{
		if (!strcmp(lpValueName, "ScreenBPP"))
		{
			*lpType = REG_DWORD;
			*lpData = 32;
			*lpcbData = 4;

			return ERROR_SUCCESS;
		}

		if (NewReg_CheckIsNewKey(lpValueName))
		{
			LONG lResult;
			HKEY hKey2;
			DWORD dwDisposition;

			char szKey[128];
			sprintf(szKey, "Software\\Valve\\Half-Life\\CSBTE\\Settings");

			lResult = g_pfnRegCreateKeyExA(HKEY_CURRENT_USER, szKey, 0, "String", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey2, &dwDisposition);

			if (lResult == ERROR_SUCCESS)
			{
				lResult = g_pfnRegQueryValueExA(hKey2, lpValueName, lpReserved, lpType, lpData, lpcbData);

				if (lResult == ERROR_SUCCESS)
				{
					g_pfnRegCloseKey(hKey2);
					return lResult;
				}
			}
			else
				g_pfnRegCloseKey(hKey2);
		}
	}

	return g_pfnRegQueryValueExA(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
}

void NewReg_Init(void)
{
	g_pfnRegCreateKeyExA = RegCreateKeyExA;
	g_pfnRegCloseKey = RegCloseKey;
	g_phRegSetValueExA = g_pMetaHookAPI->InlineHook((void *)RegSetValueExA, NewReg_RegSetValueExA, (void *&)g_pfnRegSetValueExA);
	g_phRegQueryValueExA = g_pMetaHookAPI->InlineHook((void *)RegQueryValueExA, NewReg_RegQueryValueExA, (void *&)g_pfnRegQueryValueExA);
}

void NewReg_Shutdown(void)
{
	if (g_phRegCreateKeyExA)
		g_pMetaHookAPI->UnHook(g_phRegCreateKeyExA);

	if (g_phRegCloseKey)
		g_pMetaHookAPI->UnHook(g_phRegCloseKey);

	if (g_phRegSetValueExA)
		g_pMetaHookAPI->UnHook(g_phRegSetValueExA);

	if (g_phRegQueryValueExA)
		g_pMetaHookAPI->UnHook(g_phRegQueryValueExA);
}