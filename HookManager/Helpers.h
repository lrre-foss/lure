#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>

struct Helpers
{
	static char* GetAppVersion();
	static char* GetAppType(const char* AppVersion);
	static char* GetFileVersion(const char* filename);
	static bool IsTrustedSite(char* _url);
	static bool IsExtranetIp(char* _ip);
};

#define DEBUGLOGS true