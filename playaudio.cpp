#include <metahook.h>
#include "fmod.h"
#include "cmd.h"
#include <cvardef.h>
#include "plugins.h"
#include "configs.h"

HMODULE g_hFMOD;

cmd_function_t *cmd_play = NULL;
cmd_function_t *cmd_stopsound = NULL;
cmd_function_t *cmd_fmod = NULL;

cvar_t *MP3Volume = NULL;

typedef struct
{
	bool initialied;
	float curvolume;

	FMOD_SYSTEM *system;
	FMOD_SOUND *sound;
	FMOD_CHANNEL *channel;
}
fmod_t;

fmod_t fmod;

FMOD_RESULT (F_API *g_pfnFMOD_System_Create)(FMOD_SYSTEM **system);
FMOD_RESULT (F_API *g_pfnFMOD_System_Release)(FMOD_SYSTEM *system);
FMOD_RESULT (F_API *g_pfnFMOD_System_PlaySound)(FMOD_SYSTEM *system, FMOD_CHANNELINDEX channelid, FMOD_SOUND *sound, FMOD_BOOL paused, FMOD_CHANNEL **channel);
FMOD_RESULT (F_API *g_pfnFMOD_Sound_SetMode)(FMOD_SOUND *sound, FMOD_MODE mode);
FMOD_RESULT (F_API *g_pfnFMOD_System_CreateSound)(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound);
FMOD_RESULT (F_API *g_pfnFMOD_Sound_Release)(FMOD_SOUND *sound);
FMOD_RESULT (F_API *g_pfnFMOD_System_GetChannelsPlaying)(FMOD_SYSTEM *system, int *channels);
FMOD_RESULT (F_API *g_pfnFMOD_System_Init)(FMOD_SYSTEM *system, int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata);
FMOD_RESULT (F_API *g_pfnFMOD_System_Close)(FMOD_SYSTEM *system);
FMOD_RESULT (F_API *g_pfnFMOD_System_Update)(FMOD_SYSTEM *system);
FMOD_RESULT (F_API *g_pfnFMOD_Channel_GetVolume)(FMOD_CHANNEL *channel, float *volume);
FMOD_RESULT (F_API *g_pfnFMOD_Channel_SetVolume)(FMOD_CHANNEL *channel, float volume);

FMOD_RESULT F_API FMOD_System_Create(FMOD_SYSTEM **system)
{
	return g_pfnFMOD_System_Create(system);
}

FMOD_RESULT F_API FMOD_System_Release(FMOD_SYSTEM *system)
{
	return g_pfnFMOD_System_Release(system);
}

FMOD_RESULT F_API FMOD_System_PlaySound(FMOD_SYSTEM *system, FMOD_CHANNELINDEX channelid, FMOD_SOUND *sound, FMOD_BOOL paused, FMOD_CHANNEL **channel)
{
	return g_pfnFMOD_System_PlaySound(system, channelid, sound, paused, channel);
}

FMOD_RESULT F_API FMOD_Sound_SetMode(FMOD_SOUND *sound, FMOD_MODE mode)
{
	return g_pfnFMOD_Sound_SetMode(sound, mode);
}

FMOD_RESULT F_API FMOD_System_CreateSound(FMOD_SYSTEM *system, const char *name_or_data, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo, FMOD_SOUND **sound)
{
	return g_pfnFMOD_System_CreateSound(system, name_or_data, mode, exinfo, sound);
}

FMOD_RESULT F_API FMOD_Sound_Release(FMOD_SOUND *sound)
{
	return g_pfnFMOD_Sound_Release(sound);
}

FMOD_RESULT F_API FMOD_System_GetChannelsPlaying(FMOD_SYSTEM *system, int *channels)
{
	return g_pfnFMOD_System_GetChannelsPlaying(system, channels);
}

FMOD_RESULT F_API FMOD_System_Init(FMOD_SYSTEM *system, int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata)
{
	return g_pfnFMOD_System_Init(system, maxchannels, flags, extradriverdata);
}

FMOD_RESULT F_API FMOD_System_Close(FMOD_SYSTEM *system)
{
	return g_pfnFMOD_System_Close(system);
}

FMOD_RESULT F_API FMOD_System_Update(FMOD_SYSTEM *system)
{
	return g_pfnFMOD_System_Update(system);
}

FMOD_RESULT F_API FMOD_Channel_GetVolume(FMOD_CHANNEL *channel, float *volume)
{
	return g_pfnFMOD_Channel_GetVolume(channel, volume);
}

FMOD_RESULT F_API FMOD_Channel_SetVolume(FMOD_CHANNEL *channel, float volume)
{
	return g_pfnFMOD_Channel_SetVolume(channel, volume);
}

void FMOD_f(void)
{
	if (!fmod.initialied)
	{
		if (gConfigs.bEnableFMOD || developer->value > 1)
			gEngfuncs.Con_DPrintf("fmod call fails, use mp3\n");

		if (!cmd_fmod)
			cmd_fmod = Cmd_FindCmd("mp3");

		cmd_fmod->function();
		return;
	}

	bool loop = false;

	for (int i = 1; i < gEngfuncs.Cmd_Argc(); i++)
	{
		char *params = gEngfuncs.Cmd_Argv(i);

		if (!stricmp(params, "loop"))
		{
			loop = true;
		}
		else if (!stricmp(params, "stop"))
		{
			int playing = 0;
			FMOD_System_GetChannelsPlaying(fmod.system, &playing);

			if (playing)
			{
				FMOD_Sound_Release(fmod.sound);
				fmod.sound = NULL;
			}
		}
		else
		{
			if (strlen(params) > 0)
			{
				int playing = 0;
				FMOD_System_GetChannelsPlaying(fmod.system, &playing);

				if (playing)
					FMOD_Sound_Release(fmod.sound);

				char fullPath[MAX_PATH];
				char *sound = params;
				g_pFileSystem->GetLocalPath(sound, fullPath, sizeof(fullPath));

				if (FMOD_System_CreateSound(fmod.system, fullPath, FMOD_HARDWARE, 0, &fmod.sound) != FMOD_OK)
				{
					gEngfuncs.Con_Printf("FMOD_f: Could not load %s\n", sound);
					return;
				}

				FMOD_Sound_SetMode(fmod.sound, loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);

				if (FMOD_System_PlaySound(fmod.system, FMOD_CHANNEL_FREE, fmod.sound, 0, &fmod.channel) != FMOD_OK)
				{
					gEngfuncs.Con_Printf("FMOD_f: Could not play %s\n", sound);
					return;
				}

				FMOD_Channel_SetVolume(fmod.channel, 0);
			}
		}
	}
}

void PlayAudio_f(void)
{
	if (!fmod.initialied)
	{
		if (gConfigs.bEnableFMOD || developer->value > 1)
			gEngfuncs.Con_DPrintf("playaudio call fails, use play\n");

		if (!cmd_play)
			cmd_play = Cmd_FindCmd("play");

		cmd_play->function();
		return;
	}

	if (gEngfuncs.Cmd_Argc() <= 1)
		return;

	int playing = FALSE;
	FMOD_System_GetChannelsPlaying(fmod.system, &playing);

	if (playing)
		FMOD_Sound_Release(fmod.sound);

	char *sound = gEngfuncs.Cmd_Argv(1);
	char fullPath[MAX_PATH];
	g_pFileSystem->GetLocalPath(sound, fullPath, sizeof(fullPath));

	if (FMOD_System_CreateSound(fmod.system, fullPath, FMOD_HARDWARE, 0, &fmod.sound) != FMOD_OK)
	{
		gEngfuncs.Con_Printf("PlayAudio_f: Could not load %s\n", sound);
		return;
	}

	FMOD_Sound_SetMode(fmod.sound, FMOD_LOOP_OFF);

	if (FMOD_System_PlaySound(fmod.system, FMOD_CHANNEL_FREE, fmod.sound, 0, &fmod.channel) != FMOD_OK)
	{
		gEngfuncs.Con_Printf("PlayAudio_f: Could not play %s\n", sound);
		return;
	}

	FMOD_Channel_SetVolume(fmod.channel, 0);
}

void StopAudio_f(void)
{
	if (!fmod.initialied)
	{
		if (gConfigs.bEnableFMOD || developer->value > 1)
			gEngfuncs.Con_DPrintf("stopaudio call fails, use stopsound\n");

		if (!cmd_stopsound)
			cmd_stopsound = Cmd_FindCmd("stopsound");

		cmd_stopsound->function();
		return;
	}

	int playing = FALSE;
	FMOD_System_GetChannelsPlaying(fmod.system, &playing);

	if (playing)
	{
		FMOD_Sound_Release(fmod.sound);
		fmod.sound = NULL;
	}
}

void PlayAudio_Init(void)
{
	memset(&fmod, NULL, sizeof(fmod));

	gEngfuncs.pfnAddCommand("fmod", FMOD_f);
	gEngfuncs.pfnAddCommand("playaudio", PlayAudio_f);
	gEngfuncs.pfnAddCommand("stopaudio", StopAudio_f);

	if (gConfigs.bEnableFMOD)
	{
		char fullPath[MAX_PATH];
		g_pFileSystem->GetLocalPath("cl_dlls/fmodex.dll", fullPath, sizeof(fullPath));
		g_hFMOD = LoadLibrary(fullPath);
	}
	else
		g_hFMOD = NULL;

	if (!g_hFMOD)
		return;

	g_pfnFMOD_System_Create = (FMOD_RESULT (F_API *)(FMOD_SYSTEM **))GetProcAddress(g_hFMOD, "FMOD_System_Create");
	g_pfnFMOD_System_Release = (FMOD_RESULT (F_API *)(FMOD_SYSTEM *))GetProcAddress(g_hFMOD, "FMOD_System_Release");
	g_pfnFMOD_System_PlaySound = (FMOD_RESULT (F_API *)(FMOD_SYSTEM *, FMOD_CHANNELINDEX, FMOD_SOUND *, FMOD_BOOL, FMOD_CHANNEL **))GetProcAddress(g_hFMOD, "FMOD_System_PlaySound");
	g_pfnFMOD_Sound_SetMode = (FMOD_RESULT (F_API *)(FMOD_SOUND *, FMOD_MODE))GetProcAddress(g_hFMOD, "FMOD_Sound_SetMode");
	g_pfnFMOD_System_CreateSound = (FMOD_RESULT (F_API *)(FMOD_SYSTEM *, const char *, FMOD_MODE, FMOD_CREATESOUNDEXINFO *, FMOD_SOUND **))GetProcAddress(g_hFMOD, "FMOD_System_CreateSound");
	g_pfnFMOD_Sound_Release = (FMOD_RESULT (F_API *)(FMOD_SOUND *))GetProcAddress(g_hFMOD, "FMOD_Sound_Release");
	g_pfnFMOD_System_GetChannelsPlaying = (FMOD_RESULT (F_API *)(FMOD_SYSTEM *, int *))GetProcAddress(g_hFMOD, "FMOD_System_GetChannelsPlaying");
	g_pfnFMOD_System_Init = (FMOD_RESULT (F_API *)(FMOD_SYSTEM *, int, FMOD_INITFLAGS, void *))GetProcAddress(g_hFMOD, "FMOD_System_Init");
	g_pfnFMOD_System_Close = (FMOD_RESULT (F_API *)(FMOD_SYSTEM *))GetProcAddress(g_hFMOD, "FMOD_System_Close");
	g_pfnFMOD_System_Update = (FMOD_RESULT (F_API *)(FMOD_SYSTEM *))GetProcAddress(g_hFMOD, "FMOD_System_Update");
	g_pfnFMOD_Channel_SetVolume = (FMOD_RESULT (F_API *)(FMOD_CHANNEL *, float))GetProcAddress(g_hFMOD, "FMOD_Channel_SetVolume");
	g_pfnFMOD_Channel_GetVolume = (FMOD_RESULT (F_API *)(FMOD_CHANNEL *, float *))GetProcAddress(g_hFMOD, "FMOD_Channel_SetVolume");

	if (FMOD_System_Create(&fmod.system) != FMOD_OK)
		return;

	if (FMOD_System_Init(fmod.system, 1, FMOD_INIT_NORMAL, NULL) != FMOD_OK)
		return;

	fmod.initialied = true;
}

void PlayAudio_Shutdown(void)
{
	if (fmod.initialied)
	{
		FMOD_System_Close(fmod.system);
		FMOD_System_Release(fmod.system);
	}

	if (g_hFMOD)
		FreeLibrary(g_hFMOD);
}

void PlayAudio_Frame(void)
{
	if (!fmod.initialied)
		return;

	if (!fmod.sound)
		return;

	if (!MP3Volume)
		MP3Volume = gEngfuncs.pfnGetCvarPointer("MP3Volume");

	float volume = 0.0;
	FMOD_Channel_GetVolume(fmod.channel, &volume);

	if (volume != MP3Volume->value)
		FMOD_Channel_SetVolume(fmod.channel, max(0, MP3Volume->value));

	FMOD_System_Update(fmod.system);
}