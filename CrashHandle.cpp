#define _WINSOCKAPI_
#include <metahook.h>
#include <assert.h>
#include <Dbghelp.h>
#include <stdio.h>
#include "Video.h"
#include "gamma.h"
#include "CSmtp.h"
#include "XorStr.h"
#include "Encode.h"
#include "configs.h"
#include "plugins.h"
#include "extdll.h"
#include "BugReport.h"
#include "minidump.h"

void V_FileBase(const char *in, char *out, int maxlen);

bool g_bSendBugReport = false;
bool g_bRestartGame = false;
bool g_bDeleteThisMDMP = false;
char g_szBugReportDesc[1024];
bool g_bIsUseCrashCmd = false;

void InternalWriteMiniDumpUsingExceptionInfo_BUGReport(unsigned int uStructuredExceptionCode, _EXCEPTION_POINTERS *pExceptionInfo)
{
	Gamma_Restore();
	ExtDLL_Release();

	if (CommandLine()->CheckParm("-nomdmp"))
		return;

	if (!VideoMode_IsWindowed())
		VID_SwitchFullScreen(false);

	VID_HideWindow();
	VID_CloseWindow();

	int iType = MiniDumpWithDataSegs | MiniDumpWithIndirectlyReferencedMemory;
	static char szFileName[32] = "";

	if (!WriteMiniDumpUsingExceptionInfo(uStructuredExceptionCode, pExceptionInfo, (MINIDUMP_TYPE)iType, szFileName))
	{
		iType = MiniDumpWithDataSegs;

		if (!WriteMiniDumpUsingExceptionInfo(uStructuredExceptionCode, pExceptionInfo, (MINIDUMP_TYPE)iType, szFileName))
			return;
	}

	if (BugReport_CreateWindow())
	{
	}

	DWORD dwFileSize = GetLastMiniDumpFileSize();

	char szFileBase[MAX_PATH];
	V_FileBase(szFileName, szFileBase, sizeof(szFileBase));

	if (g_bSendBugReport)
	{
		if (dwFileSize < (1024 * 1024 * 5))
		{
			CSmtp mail;
			bool isError = false;

			if (!g_bIsUseCrashCmd)
			{
				try
				{
					mail.SetSMTPServer(XorStr<0x13, 12, 0x139F41BA>("\x60\x79\x61\x66\x39\x69\x68\x34\x78\x73\x70" + 0x139F41BA).s, 25); // smtp.qq.com
					mail.SetSecurityType(NO_SECURITY);
					mail.SetLogin(XorStr<0xB3, 23, 0x6AF33DDC>("\xD0\xC7\xD7\xC2\xD2\xE7\xDB\xCF\xDC\xCF\xD8\xD0\xDB\xA5\xB3\x82\xB2\xB5\xEB\xA5\xA8\xA5" + 0x6AF33DDC).s); // csbte_bugsender@qq.com
					mail.SetPassword(XorStr<0xF6, 11, 0x7680F353>("\xB3\xB3\xCA\xC9\xCF\xC3\xB9\xBE\xCD\xBB" + 0x7680F353).s); // ED2058EC3D
					mail.SetSenderName(XorStr<0xBB, 16, 0xDB9F59C9>("\xD8\xCF\xDF\xCA\xDA\x9F\xA3\xB7\xA4\xB7\xA0\xA8\xA3\xAD\xBB" + 0xDB9F59C9).s); // csbte_bugsender
					mail.SetSenderMail(XorStr<0x8E, 23, 0x30E98F1A>("\xED\xFC\xF2\xE5\xF7\xCC\xF6\xE0\xF1\xE4\xFD\xF7\xFE\xFE\xEE\xDD\xEF\xEE\x8E\xC2\xCD\xCE" + 0x30E98F1A).s); // csbte_bugsender@qq.com
					mail.SetReplyTo(XorStr<0x33, 23, 0x2E1BA643>("\x50\x47\x57\x42\x52\x67\x5B\x4F\x5C\x4F\x58\x50\x5B\x25\x33\x02\x32\x35\x6B\x25\x28\x25" + 0x2E1BA643).s); // csbte_bugsender@qq.com
					mail.SetSubject(szFileBase);
					mail.AddRecipient(XorStr<0x23, 23, 0x0DA12156>("\x40\x57\x47\x52\x42\x77\x4B\x5F\x4C\x5E\x48\x5E\x40\x42\x45\x72\x42\x45\x1B\x55\x58\x55" + 0x0DA12156).s); // csbte_bugreport@qq.com
					mail.SetXPriority(XPRIORITY_HIGH);
					mail.SetXMailer(XorStr<0x4A, 30, 0xA907EBF5>("\x1E\x23\x29\x6D\x0C\x2E\x24\x70\x72\x7B\x22\x66\x78\x67\x6A\x70\x7A\x0B\x2E\x32\x38\x3A\x13\x12\x0B\x0C\x0A\x04\x0A" + 0xA907EBF5).s); // The Bat! (v3.02) Professional

					char msg[64];
					sprintf(msg, XorStr<0xDA, 34, 0xDD3D570D>("\x6E\x10\x68\x30\x10\x2C\x51\x49\x5A\x05\x2D\x1F\x55\x2E\x3B\x33\xCA\xA9\xB8\xA8\xCE\xA9\x9F\x83\xD2\xBD\x91\x82\xD6\xDF\xDD\x8A\xD3" + 0xDD3D570D).s, __DATE__); // 此错误报告生成于 BTE For New (%s)

					mail.AddMsgLine(msg);
					mail.AddMsgLine("");
					mail.AddMsgLine(g_szBugReportDesc);

					mail.AddAttachment(szFileName);
					mail.Send();
				}
				catch (ECSmtp e)
				{
					MessageBox(NULL, e.GetErrorText().c_str(), "Bug Report", MB_ICONERROR);
					isError = true;
				}
			}

			if (!isError)
			{
				MessageBox(NULL, "Thank you very much for your support, we will fix this problem as soon as possible!", "Bug Report", MB_ICONINFORMATION | MB_OK);
			}
		}
	}

	if (g_bDeleteThisMDMP)
	{
		DeleteFile(szFileName);
	}

	if (g_bRestartGame)
	{
		CommandLine()->AppendParm("-restart", NULL);

		STARTUPINFO SI;
		PROCESS_INFORMATION PI;
		memset(&SI, 0, sizeof(SI));
		memset(&PI, 0, sizeof(PI));
		SI.cb = sizeof(STARTUPINFO);

		if (!CreateProcess(NULL, (LPSTR)CommandLine()->GetCmdLine(), NULL, NULL, FALSE, CREATE_NEW_PROCESS_GROUP | NORMAL_PRIORITY_CLASS, NULL, NULL, &SI, &PI))
		{
			char szEXEPath[MAX_PATH];
			GetModuleFileName(GetModuleHandle(NULL), szEXEPath, sizeof(szEXEPath));
			SHELLEXECUTEINFO SEI;
			memset(&SEI, 0, sizeof(SEI));
			SEI.cbSize = sizeof(SHELLEXECUTEINFO);
			SEI.lpVerb = "runas";
			SEI.lpFile = szEXEPath;
			SEI.lpParameters = (LPSTR)CommandLine()->GetCmdLine();
			ShellExecuteEx(&SEI);
		}

		TerminateProcess(GetCurrentProcess(), 1);
	}
}

void CMD_Crash(void)
{
	g_bIsUseCrashCmd = true;

	void (*pfnCrash)(void) = NULL;
	pfnCrash();

	*(int *)0 = 0;

	g_bIsUseCrashCmd = false;
}

void InitCrashHandle(void)
{
	if (g_bIsUseSteam)
		return;

	if (!g_bIsDebuggerPresent)
	{
		SetupExceptionHandle();
		SetMiniDumpFunction(InternalWriteMiniDumpUsingExceptionInfo_BUGReport);
	}

	gEngfuncs.pfnAddCommand("crash", CMD_Crash);
}