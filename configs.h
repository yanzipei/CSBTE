typedef struct config_s
{
	bool bInitialied;

	char szLanguage[128];
	char szGameDir[MAX_PATH];
	char szGameLangDir[MAX_PATH];
	char szFallbackDir[MAX_PATH];
	char szGameVersion[12];
	char szDownloadURL[256];
	char szGameName[128];
	char szUIScheme[32];

	bool bEnableCSOModelLoad;
	bool bEnableFMOD;
}
config_t;

extern char g_szLanguage[128];
extern config_t gConfigs;

void Config_Init(void);