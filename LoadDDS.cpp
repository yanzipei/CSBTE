#include <metahook.h>
#include "configs.h"
#include "qgl.h"
#include "LoadDDS.h"
#include "plugins.h"
#include "perf_counter.h"
#include "cvardef.h"
#include "tier0/dbg.h"

#define DDSD_CAPS 0x00000001
#define DDSD_PIXELFORMAT 0x00001000
#define DDPF_FOURCC 0x00000004

#define D3DFMT_DXT1 '1TXD'
#define D3DFMT_DXT5 '5TXD'

#pragma pack(push)
#pragma pack(1)

typedef struct dds_header_s
{
	char Signature[4];

	unsigned int Size1;
	unsigned int Flags1;
	unsigned int Height;
	unsigned int Width;
	unsigned int LinearSize;
	unsigned int Depth;
	unsigned int MipMapCount;
	unsigned int AlphaBitDepth;

	unsigned int NotUsed[10];

	unsigned int Size2;
	unsigned int Flags2;
	unsigned int FourCC;
	unsigned int RGBBitCount;
	unsigned int RBitMask;
	unsigned int GBitMask;
	unsigned int BBitMask;
	unsigned int RGBAlphaBitMask;

	unsigned int ddsCaps1, ddsCaps2, ddsCaps3, ddsCaps4;
	unsigned int TextureStage;
}
dds_header_t;

#pragma pack(pop)

bool LoadDDS(const char *szFilename, byte *buffer, int bufferSize, int *width, int *height)
{
	bool debugTime = (developer && (int)developer->value > 2);
	float startTime;

	if (debugTime)
		startTime = gPerformanceCounter.GetCurTime();

	FileHandle_t fp = g_pFileSystem->Open(szFilename, "rb");

	if (!fp)
		return FALSE;

	dds_header_t header;

	if (!g_pFileSystem->Read(&header, sizeof(header), fp))
	{
		*width = 0;
		*height = 0;

		g_pFileSystem->Close(fp);
		return FALSE;
	}

	unsigned int flags = header.Flags1;
	unsigned int FourCC = header.FourCC;
	unsigned int PFFlags = header.Flags2;
	unsigned int linearsize = header.LinearSize;

	if (strncmp(header.Signature, "DDS ", 4))
		return FALSE;

	if (!(flags & DDSD_PIXELFORMAT))
		return FALSE;

	if (!(flags & DDSD_CAPS))
		return FALSE;

	if (!(PFFlags & DDPF_FOURCC))
		return FALSE;

	if (FourCC != D3DFMT_DXT1 && FourCC != D3DFMT_DXT5)
		gEngfuncs.Con_Printf("LoadDDS: %s! Only DXT1 and DXT5 are supported!\n", szFilename);

	*width = header.Width;
	*height = header.Height;

	int size = g_pFileSystem->Size(fp) - sizeof(dds_header_t);

	if (size > bufferSize)
		return FALSE;

	int readcount = g_pFileSystem->Read(buffer, size, fp);
	g_pFileSystem->Close(fp);

	if (!readcount)
		return FALSE;

	Assert(0);

	if (debugTime)
	{
	}

	return TRUE;
}