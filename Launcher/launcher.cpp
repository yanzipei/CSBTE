#include "metahook.h"
#include <IEngine.h>
#include "LoadBlob.h"
#include "ExceptHandle.h"
#include "sys.h"

#pragma warning(disable : 4733)
#pragma comment(lib, "ws2_32.lib")

IFileSystem *g_pFileSystem;

HINTERFACEMODULE LoadFilesystemModule(void)
{
    HINTERFACEMODULE hModule = Sys_LoadModule("filesystem_stdio.dll");

    if (!hModule)
    {
        MessageBox(NULL, "Could not load filesystem dll.\nFileSystem crashed during construction.", "Fatal Error", MB_ICONERROR);
        return NULL;
    }

    return hModule;
}

void SetEngineDLL(const char *&pszEngineDLL)
{
    pszEngineDLL = "hw.dll";
}

BOOL OnVideoModeFailed(void)
{
    registry->WriteInt("ScreenWidth", 640);
    registry->WriteInt("ScreenHeight", 480);
    registry->WriteInt("ScreenBPP", 16);

    if (!registry->ReadInt("EngineD3D", FALSE))
    {
        registry->WriteInt("EngineD3D", TRUE);
        return (MessageBox(NULL, "The specified video mode is not supported.\nThe game will now run in D3D mode.", "Video mode change failure", MB_OKCANCEL | MB_ICONWARNING) == IDOK);
    }
    else
    {
        registry->WriteInt("EngineD3D", FALSE);
        return (MessageBox(NULL, "The specified video mode is not supported.\nThe game will now run in openGL mode.", "Video mode change failure", MB_OKCANCEL | MB_ICONWARNING) == IDOK);
    }
}

BlobFootprint_t g_blobfootprintClient;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    CommandLine()->CreateCmdLine(GetCommandLine());
    CommandLine()->AppendParm("-game", "cstrike");

    HANDLE hObject = NULL;
    BOOL (*IsDebuggerPresent)(void) = (BOOL (*)(void))GetProcAddress(GetModuleHandle("kernel32.dll"), "IsDebuggerPresent");

#ifndef _DEBUG
    if (!IsDebuggerPresent() && (!CommandLine()->CheckParm("-nomutex") == NULL && !CommandLine()->CheckParm("-restart")))
    {
        hObject = CreateMutex(NULL, FALSE, "ValveHalfLifeLauncherMutex");

        DWORD dwStatus = WaitForSingleObject(hObject, NULL);

        if (dwStatus && dwStatus != WAIT_ABANDONED)
        {
            MessageBox(NULL, "Could not launch game.\nOnly one instance of this game can be run at a time.", "Error", MB_ICONERROR);
            return FALSE;
        }
    }
#endif

    WSAData WSAData;
    WSAStartup(2, &WSAData);

    registry->Init();

    if (registry->ReadInt("CrashInitializingVideoMode", FALSE))
    {
        registry->WriteInt("CrashInitializingVideoMode", FALSE);

        if (registry->ReadInt("EngineD3D", FALSE))
        {
            registry->WriteInt("EngineD3D", FALSE);

            if (MessageBox(NULL, "The game has detected that the previous attempt to start in D3D video mode failed.\nThe game will now run attempt to run in openGL mode.", "Video mode change failure", MB_OKCANCEL | MB_ICONWARNING) != IDOK)
                return FALSE;
        }
        else
        {
            registry->WriteString("EngineDLL", "sw.dll");

            if (MessageBox(NULL, "The game has detected that the previous attempt to start in openGL video mode failed.\nThe game will now run in software mode.", "Video mode change failure", MB_OKCANCEL | MB_ICONWARNING) != IDOK)
                return FALSE;
        }

        registry->WriteInt("ScreenWidth", 640);
        registry->WriteInt("ScreenHeight", 480);
        registry->WriteInt("ScreenBPP", 16);
    }

    while (TRUE)
    {
        HINTERFACEMODULE hFileSystem = LoadFilesystemModule();

        if (!hFileSystem)
            break;

        char szDLLPath[MAX_PATH];
        sprintf(szDLLPath, "metahook.dll");

        MH_LoadLibrary(szDLLPath);
        MH_Setup(NULL, CommandLine(), registry);
        MH_Init("cstrike");

        CreateInterfaceFn fsCreateInterface = (CreateInterfaceFn)Sys_GetFactory(hFileSystem);
        g_pFileSystem = (IFileSystem *)fsCreateInterface(FILESYSTEM_INTERFACE_VERSION, NULL);
        g_pFileSystem->Mount();
        g_pFileSystem->AddSearchPath(Sys_GetLongPathName(), "ROOT");
        MH_Setup(g_pFileSystem, CommandLine(), registry);

        static char szNewCommandParams[2048];
        const char *pszEngineDLL;
        int iResult = ENGINE_RESULT_NONE;

        SetEngineDLL(pszEngineDLL);

        szNewCommandParams[0] = NULL;
        g_blobfootprintClient.m_hDll = NULL;

        IEngine *engineAPI = NULL;
        HINTERFACEMODULE hEngine;
        bool bUseBlobDLL = false;

        if (FIsBlob(pszEngineDLL))
        {
            Sys_CloseDEP();
            SetupExceptHandler3();
            NLoadBlobFile(pszEngineDLL, &g_blobfootprintClient, (void **)&engineAPI);
            MH_SetBlobHeader(GetBlobHeader());
            bUseBlobDLL = true;
        }
        else
        {
            hEngine = Sys_LoadModule(pszEngineDLL);

            if (!hEngine)
            {
                static char msg[512];
                wsprintf(msg, "Could not load %s.\nPlease try again at a later time.", pszEngineDLL);
                MessageBox(NULL, msg, "Fatal Error", MB_ICONERROR);
                break;
            }

            CreateInterfaceFn engineCreateInterface = (CreateInterfaceFn)Sys_GetFactory(hEngine);
            engineAPI = (IEngine *)engineCreateInterface(VENGINE_LAUNCHER_API_VERSION, NULL);

            if (!engineCreateInterface || !engineAPI)
                Sys_FreeModule(hEngine);
        }

        if (engineAPI)
        {
            MH_LoadEngine(bUseBlobDLL ? NULL : (HMODULE)hEngine);
            iResult = engineAPI->Run(hInstance, Sys_GetLongPathName(), CommandLine()->GetCmdLine(), szNewCommandParams, Sys_GetFactoryThis(), Sys_GetFactory(hFileSystem));
            MH_ExitGame(iResult);

            if (bUseBlobDLL)
                FreeBlob(&g_blobfootprintClient);
            else
                Sys_FreeModule(hEngine);
        }

        if (iResult == ENGINE_RESULT_NONE || iResult > ENGINE_RESULT_UNSUPPORTEDVIDEO)
            break;

        bool bContinue;

        switch (iResult)
        {
            case ENGINE_RESULT_RESTART:
            {
                bContinue = true;
                break;
            }

            case ENGINE_RESULT_UNSUPPORTEDVIDEO:
            {
                bContinue = OnVideoModeFailed();
                break;
            }
        }

        CommandLine()->RemoveParm("-sw");
        CommandLine()->RemoveParm("-startwindowed");
        CommandLine()->RemoveParm("-windowed");
        CommandLine()->RemoveParm("-window");
        CommandLine()->RemoveParm("-full");
        CommandLine()->RemoveParm("-fullscreen");
        CommandLine()->RemoveParm("-soft");
        CommandLine()->RemoveParm("-software");
        CommandLine()->RemoveParm("-gl");
        CommandLine()->RemoveParm("-d3d");
        CommandLine()->RemoveParm("-w");
        CommandLine()->RemoveParm("-width");
        CommandLine()->RemoveParm("-h");
        CommandLine()->RemoveParm("-height");
        CommandLine()->RemoveParm("-novid");

        if (strstr(szNewCommandParams, "-game"))
            CommandLine()->RemoveParm("-game");

        if (strstr(szNewCommandParams, "+load"))
            CommandLine()->RemoveParm("+load");

        CommandLine()->AppendParm(szNewCommandParams, NULL);
        CommandLine()->AppendParm("-restart", NULL);

        g_pFileSystem->Unmount();
        Sys_FreeModule(hFileSystem);
        MH_Shutdown();
        MH_FreeLibrary();

        if (!bContinue)
            break;
    }

    registry->Shutdown();

    if (hObject)
    {
        ReleaseMutex(hObject);
        CloseHandle(hObject);
    }

    WSACleanup();
    MH_Shutdown();
    MH_FreeLibrary();
    TerminateProcess(GetCurrentProcess(), TRUE);

    return TRUE;
}