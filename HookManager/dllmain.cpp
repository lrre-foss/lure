#include "Main.h"

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
        HookMain();

    return TRUE;
}

void __declspec(dllexport) HookManager() {}