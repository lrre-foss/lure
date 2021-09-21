#include "Helpers.h"
#include "Hooks.h"

char* Helpers::GetAppType(const char* AppVersion)
{
    if (strcmp(AppVersion, "0.22.13.13") == 0) return (char*)"August2010";
    else exit(EXIT_FAILURE);
}

char* Helpers::GetAppVersion()
{
    char ProcessPathBuffer[MAX_PATH];
    GetModuleFileNameA(NULL, ProcessPathBuffer, MAX_PATH);
    char* ProcessPath = ProcessPathBuffer;
    char* ProcessVersion = GetFileVersion(ProcessPath);

#if DEBUGLOGS
    std::cout << "[Helpers::GetAppInfo] App path is " << ProcessPath << std::endl;
    std::cout << "[Helpers::GetAppInfo] App version is " << ProcessVersion << std::endl;
#endif

    return ProcessVersion;
}

// https://stackoverflow.com/a/940743
char* Helpers::GetFileVersion(const char* filename)
{
    DWORD  verHandle = 0;
    UINT   size = 0;
    LPBYTE lpBuffer = NULL;
    DWORD  verSize = GetFileVersionInfoSizeA(filename, &verHandle);

    if (verSize != NULL)
    {
        LPSTR verData = new char[verSize];

        if (GetFileVersionInfoA(filename, verHandle, verSize, verData))
        {
            if (VerQueryValueA(verData, "\\", (VOID FAR * FAR*) & lpBuffer, &size))
            {
                if (size)
                {
                    VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
                    if (verInfo->dwSignature == 0xfeef04bd)
                    {
                        char buffer[2048];

                        sprintf_s(
                            buffer, sizeof(buffer), "%d.%d.%d.%d", 
                            (verInfo->dwFileVersionMS >> 16) & 0xffff,
                            (verInfo->dwFileVersionMS >> 0) & 0xffff,
                            (verInfo->dwFileVersionLS >> 16) & 0xffff,
                            (verInfo->dwFileVersionLS >> 0) & 0xffff
                        );

                        char* version = buffer;
                        delete[] verData;
                        return version;
                    }
                }
            }
        }

        delete[] verData;
    }

    return (char*)"";
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