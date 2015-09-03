#include "tier0/minidump.h"

DWORD GetLastMiniDumpFileSize(void);
FnMiniDump SetMiniDumpFunction(FnMiniDump pfn);
void SetupExceptionHandle(void);