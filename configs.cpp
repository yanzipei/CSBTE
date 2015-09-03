#include <metahook.h>
#include "sys.h"
#include "Configs.h"
#include "plugins.h"
#include "common.h"
#include "SteamAPI.h"

config_t gConfigs = { 0 };
char g_szLanguage[128];

void Config_Init(void)
{
	char configPath[MAX_PATH], value[1024];

	strcpy(gConfigs.szGameName, "Counter-Strike: BreakThrough Edition 1");
	strcpy(gConfigs.szGameDir, "cstrike");
	strcpy(gConfigs.szGameVersion, "1.10");
	strcpy(gConfigs.szDownloadURL, "");
	strcpy(gConfigs.szFallbackDir, "CSBTE");

	gConfigs.bEnableCSOModelLoad = false;
	gConfigs.bEnableFMOD = true;

	if (g_bIsUseSteam)
	{
		ISteamApps *pSteamApps = SteamApps();

		if (!pSteamApps)
		{
			if (SteamAPI_InitSteamApps())
				pSteamApps = SteamApps();
		}

		if (pSteamApps)
		{
			const char *pszLanguage = pSteamApps->GetCurrentGameLanguage();

			if (pszLanguage)
				strcpy(g_szLanguage, pszLanguage);
		}
		else
			return;
	}
	else
		Sys_GetRegKeyValueUnderRoot("Software\\Valve\\Steam", "Language", g_szLanguage, sizeof(g_szLanguage), "english");

	if (stricmp(g_szLanguage, "english"))
		sprintf(gConfigs.szGameLangDir, "cstrike_%s", g_szLanguage);
	else
		strcpy(gConfigs.szGameLangDir, "cstrike");

	strcpy(gConfigs.szLanguage, g_szLanguage);

	FILE *fp;
	char line[128], key[64];
	const char *data;

	sprintf(configPath, "%s/configs.ini", gConfigs.szGameLangDir);

	fp = fopen(configPath, "r");

	if (!fp)
	{
		char configPath2[MAX_PATH];
		sprintf(configPath2, "%s/configs.ini", gConfigs.szGameDir);
		CreateDirectory(gConfigs.szGameLangDir, NULL);
		CopyFile(configPath2, configPath, TRUE);

		fp = fopen(configPath2, "r");
	}

	if (fp)
	{
		while (!feof(fp))
		{
			fgets(line, sizeof(line), fp);

			data = COM_Parse(line);
			strcpy(key, COM_GetToken());
			data = COM_Parse(data);
			strcpy(value, COM_GetToken());

			if (!strcmp(key, "UIScheme"))
			{
				strcpy(gConfigs.szUIScheme, value);
			}
		}

		fclose(fp);
	}

	gConfigs.bInitialied = true;
}