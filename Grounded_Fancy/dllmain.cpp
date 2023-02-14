#include "pch.h"
DWORD WINAPI startupThread(LPVOID lpvoid, HMODULE hmodule)
{
    AllocConsole();
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole, 1);
    FILE* consoleout;
    freopen_s(&consoleout, "CONOUT$", "w", stdout);  // NOLINT(cert-err33-c)
    SetConsoleTextAttribute(hconsole, 4);
    LOG("Starting up...");  // NOLINT(clang-diagnostic-gnu-zero-variadic-macro-arguments)
    return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if(ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)startupThread, hModule, 0, 0);
    }
    else if(ul_reason_for_call == DLL_PROCESS_DETACH)
    {
        
    }
    return TRUE;
}

