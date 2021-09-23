#pragma once

#include <Windows.h>
#include <iostream>
#include <set>

struct Helpers
{
	static char* GetAppType(const char* AppVersion);
	static bool IsTrustedSite(char* _url);
	static bool IsExtranetIp(char* _ip);
	static std::set<std::string> TrustedSites;
};

#define DEBUGLOGS true