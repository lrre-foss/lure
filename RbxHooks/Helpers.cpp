#include "pch.h"
#include "Helpers.h"
#include "Hooks.h"

char* Helpers::GetAppType(const char* AppVersion)
{
    if (strcmp(AppVersion, "0.22.13.13") == 0) return (char*)"August2010";
    else exit(EXIT_FAILURE);
}

bool Helpers::IsTrustedSite(char* _url)
{
    std::string url = _url;

    if (url.substr(0, 7) == "http://") url.erase(0, 7);
    else if (url.substr(0, 8) == "https://") url.erase(0, 8);

    if (url.substr(0, 10) == "roblox.com") return true;
    if (url.substr(0, 14) == "www.roblox.com") return true;
    if (url.substr(0, 24) == "assetdelivery.roblox.com") return true;

    if (url.substr(0, 11) == "example.com") return true;

    return false;
}

bool Helpers::IsExtranetIp(char* _ip)
{
    std::string ip = _ip;

    if (ip.substr(0, 7) == "192.168") return false;
    if (ip.substr(0, 5) == "127.0") return false;

    return true;
}