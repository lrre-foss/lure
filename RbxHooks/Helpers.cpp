#include "pch.h"
#include "Helpers.h"
#include "Hooks.h"

std::vector<std::string> TrustedSites = {
    "roblox.com",
    "www.roblox.com",
    "assetdelivery.roblox.com"
    // Add your custom domains here...
};

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

    // https://github.com/orcfoss/RbxHooks/issues/1
    // If there is a "/" left in the URL, treat it as a delimiter
    if (url.find('/') != std::string::npos)
    {
        url = url.substr(0, url.find("/", 0));
    }

    for (std::string site : TrustedSites)
    {
        if (url.substr(0, site.size()) == site) return true;
    }

    return false;
}

bool Helpers::IsExtranetIp(char* _ip)
{
    std::string ip = _ip;

    if (ip.substr(0, 7) == "192.168") return false;
    if (ip.substr(0, 5) == "127.0") return false;

    return true;
}