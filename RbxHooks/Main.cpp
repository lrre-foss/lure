#include "pch.h"
#include "Main.h"
#include "Helpers.h"
#include "Hooks.h"

bool AttachHook(void* Function, void* HookAddress, int Length)
{
    if (Length < 5) return false;

    DWORD CurrentProtection;
    VirtualProtect(HookAddress, Length, PAGE_EXECUTE_READWRITE, &CurrentProtection);

    memset(HookAddress, 0x90, Length);

    DWORD relativeAddress = ((DWORD)Function - (DWORD)HookAddress) - 5;

    *(BYTE*)HookAddress = 0xE9;
    *(DWORD*)((DWORD)HookAddress + 1) = relativeAddress;

    DWORD temp;
    VirtualProtect(HookAddress, Length, CurrentProtection, &temp);

    return true;
}

int length;
DWORD hookAddress;
char* AppVersion;
char* AppType;

extern DWORD SwapAssetUrlReturnAddress;

template <typename Hook>
void CreateHook(int HookAddress)
{
    if (HookAddress == 0x0)
    {
#if DEBUGLOGS
        std::cout << "[CreateHook] " << typeid(Hook).name() << " does not have a hook address for this client version, aborting hook" << std::endl;
#endif
        return;
    }

    Hook::HookAddress = HookAddress;
    Hook::ReturnAddress = HookAddress + Hook::Length;
    AttachHook(Hook::Detour, (void*)HookAddress, Hook::Length);
}

template <typename Hook>
void CreateHook()
{
#if DEBUGLOGS
    std::cout << "[CreateHook] Creating hook for " << typeid(Hook).name() << std::endl;
#endif

    if (strcmp(AppVersion, "0.22.13.13") == 0) CreateHook<Hook>(Hook::Addresses::August2010);
}

void HookMain()
{
#if DEBUGLOGS
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    // freopen_s((FILE**)stdout, "ConsoleOutput.txt", "w", stdout);

    std::cout << "[HookMain] HookManager has started up" << std::endl;
#endif

    AppVersion = (char*)"0";
    AppType = Helpers::GetAppType(AppVersion);

#if DEBUGLOGS
    std::cout << "[HookMain] App type has been detected as " << AppType << std::endl;
#endif

    CreateHook<Hooks::TrustCheck>();
    CreateHook<Hooks::SwapIp>();
}