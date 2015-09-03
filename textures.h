#define GL_LOADTEXTURE_SIG "\xA1\x2A\x2A\x2A\x2A\x8B\x4C\x24\x20\x8B\x54\x24\x1C\x50\x8B\x44\x24\x1C\x51\x8B\x4C\x24\x1C\x52\x8B\x54\x24\x1C\x50\x8B\x44\x24\x1C"
#define GL_LOADTEXTURE_SIG_NEW "\x55\x8B\xEC\xA1\x2A\x2A\x2A\x2A\x8B\x4D\x24\x8B\x55\x20\x50\x8B\x45\x1C\x51\x8B\x4D\x18\x52\x8B\x55\x14\x50\x8B\x45\x10\x51"
#define GL_LOADTEXTURE2_SIG "\xB8\x0C\x40\x00\x00\xE8\x2A\x2A\x2A\x2A\x53\x8B\x9C\x24\x14\x40\x00\x00\x55\x56\x8A\x03\x33\xF6"
#define GL_LOADTEXTURE2_SIG2 "\xB8\x0C\x40\x00\x00\xE8\x2A\x2A\x2A\x2A\x8B\x84\x24\x10\x40\x00\x00\x53\x55\x33\xDB\x8A\x08\x56\x84\xC9\x57\x89\x5C\x24\x14"
#define GL_LOADTEXTURE2_SIG_NEW "\x55\x8B\xEC\xB8\x0C\x40\x00\x00\xE8\x2A\x2A\x2A\x2A\x8B\x45\x08\x53\x33\xDB\x56\x8A\x08\x57\x84\xC9\x89\x5D\xF4\x74\x2A\x33\xF6"

extern int (*g_pfnGL_LoadTexture)(char *identifier, int textureType, int width, int height, byte *data, qboolean mipmap, int iType, byte *pPa);
extern hook_t *g_phGL_LoadTexture;
extern int (*g_pfnGL_LoadTexture2)(char *identifier, int textureType, int width, int height, byte *data, qboolean mipmap, int iType, byte *pPal, int filter);
extern struct hook_s *g_phGL_LoadTexture2;

#define MAX_GLTEXTURES 4800

typedef struct
{
	int texnum;
	int servercount;
	int paletteIndex;
	int width;
	int height;
	qboolean mipmap;
	char identifier[64];
}
gltexture_t;

typedef enum
{
	GLT_SYSTEM,
	GLT_DECAL,
	GLT_HUDSPRITE,
	GLT_STUDIO,
	GLT_WORLD,
	GLT_SPRITE
}
GL_TEXTURETYPE;

int GL_LoadTexture(char *identifier, GL_TEXTURETYPE textureType, int width, int height, byte *data, qboolean mipmap, int iType, byte *pPal);
int GL_LoadTexture2(char *identifier, GL_TEXTURETYPE textureType, int width, int height, byte *data, qboolean mipmap, int iType, byte *pPal, int filter);