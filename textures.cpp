#include <metahook.h>
#include "textures.h"
#include "configs.h"
#include "perf_counter.h"
#include "cvardef.h"
#include "plugins.h"

int (*g_pfnGL_LoadTexture)(char *identifier, int textureType, int width, int height, byte *data, qboolean mipmap, int iType, byte *pPa);
hook_t *g_phGL_LoadTexture;
int (*g_pfnGL_LoadTexture2)(char *identifier, int textureType, int width, int height, byte *data, qboolean mipmap, int iType, byte *pPal, int filter);
hook_t *g_phGL_LoadTexture2;

void (*g_pfnGL_Bind)(int texnum);
hook_t *g_phGL_Bind;

gltexture_t gltextures[MAX_GLTEXTURES];
int numgltextures;

int GL_LoadTexture(char *identifier, GL_TEXTURETYPE textureType, int width, int height, byte *data, qboolean mipmap, int iType, byte *pPal)
{
	if (!gConfigs.bEnableCSOModelLoad)
		return g_pfnGL_LoadTexture(identifier, textureType, width, height, data, mipmap, iType, pPal);

	if (textureType != GLT_STUDIO)
		return g_pfnGL_LoadTexture(identifier, textureType, width, height, data, mipmap, iType, pPal);

	size_t len = strlen(identifier);
	char *n_identifier = strstr(identifier, ".mdl");
	bool debugTime = (developer && (int)developer->value > 2);
	float startTime;

	if (n_identifier)
	{
		n_identifier += 4;

		if (n_identifier[0] == '#')
		{
			char *check = &n_identifier[7];

			if (!strncmp(&n_identifier[7], "pw_", 3))
				check += 3;

			for (int i = 0; i < numgltextures; i++)
			{
				if (!strcmp(gltextures[i].identifier, check))
					return gltextures[i].texnum;
			}

			char models[32];
			size_t mlen = n_identifier - identifier;
			strncpy(models, identifier, mlen);
			models[mlen] = 0;
			gEngfuncs.Con_DPrintf("GL_LoadTexture: texture %s missing from %s\n", n_identifier, models);
			return 0;
		}
	}
	else
		n_identifier = identifier;

	if (debugTime)
		startTime = gPerformanceCounter.GetCurTime();

	int result = g_pfnGL_LoadTexture(identifier, textureType, width, height, data, mipmap, iType, pPal);
	strcpy(gltextures[result].identifier, n_identifier);
	gltextures[result].width = width;
	gltextures[result].height = height;
	gltextures[result].texnum = result;
	numgltextures = result + 1;

	if (debugTime)
		gEngfuncs.Con_Printf("GL_LoadTexture: load %s take %.4f sec.\n", identifier ? identifier : "*", gPerformanceCounter.GetCurTime() - startTime);

	return result;
}