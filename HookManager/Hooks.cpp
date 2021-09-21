#include "Hooks.h"
#include "Helpers.h"

int ValidDomain;
void* Url;
int Hooks::TrustCheck::Length = 5;
DWORD Hooks::TrustCheck::HookAddress;
DWORD Hooks::TrustCheck::ReturnAddress;
void __declspec(naked) Hooks::TrustCheck::Detour()
{
    __asm
    {
        mov Url, eax
    }

    ValidDomain = (int) Helpers::IsTrustedSite((char*) Url);

#if DEBUGLOGS
    if (ValidDomain == 1)
        std::cout << "[Hooks::TrustCheck] " << (char*) Url << " passes trust check" << std::endl;
    else
        std::cout << "[Hooks::TrustCheck] " << (char*) Url << " does not pass trust check" << std::endl;
#endif

    __asm
    {
        mov eax, ValidDomain
        jmp ReturnAddress
    }
}

void* IpAddress;
int Hooks::SwapIp::Length = 5;
DWORD Hooks::SwapIp::HookAddress;
DWORD Hooks::SwapIp::ReturnAddress;
void __declspec(naked) Hooks::SwapIp::Detour()
{
    __asm
    {
        lea eax, dword ptr ss:[esp+8]
        mov IpAddress, eax
    }

    if (Helpers::IsExtranetIp((char*) IpAddress))
        IpAddress = (char*) "RakPeer";

    __asm
    {
        mov eax, IpAddress
        push eax
        jmp ReturnAddress
    }
}