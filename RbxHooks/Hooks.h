#pragma once

#include <Windows.h>
#include <WinInet.h>

struct Hooks
{
	struct TrustCheck
	{
		enum Addresses
		{
			August2010 = 0x67ED15
		};

		static int Length;
		static DWORD HookAddress;
		static DWORD ReturnAddress;
		static void Detour();
	};

	struct SwapIp
	{
		enum Addresses
		{
			August2010 = 0x4C23AF
		};

		static int Length;
		static DWORD HookAddress;
		static DWORD ReturnAddress;
		static void Detour();
	};
};