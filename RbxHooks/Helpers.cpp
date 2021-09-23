#include "pch.h"
#include "Helpers.h"
#include "Hooks.h"

std::set<std::string> Helpers::TrustedSites = {
    "*.roblox.com",
    "roblox.com"
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

    // Hack
    if (url.at(0) == '*' || url.at(0) == '.')
    {
        return false;
    }

    // Wildcard subdomains
    // Breaks (on purpose!) for normal domains (unless a TLD is somehow trusted.) Does not work for subdomains that are >1 level
    if (url.find('.') != std::string::npos)
    {
        std::string slicedUrl = url.substr(url.find(".") + 1);
        if (TrustedSites.find("*." + slicedUrl) != TrustedSites.end())
        {
            return true;
        }
    }

    // Main check
    if (TrustedSites.find(url) != TrustedSites.end())
    {
        return true;
    }

    // Failed the trust check
    return false;
}

bool Helpers::IsExtranetIp(char* _ip)
{
    std::string ip = _ip;

    if (ip.substr(0, 7) == "192.168") return false;
    if (ip.substr(0, 5) == "127.0") return false;

    return true;
}