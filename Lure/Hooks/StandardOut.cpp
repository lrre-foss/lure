#include "pch.h"

#include "Hooks/StandardOut.h"

#ifdef _DEBUG

HANDLE console;

void InitializeConsole()
{
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    console = CreateFileA("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetStdHandle(STD_OUTPUT_HANDLE, console);
}

StandardOut__print_t StandardOut__print = (StandardOut__print_t)ADDRESS_STANDARDOUT__PRINT;

void __fastcall StandardOut__print_hook(int _this, void*, int type, std::string* message)
{
    StandardOut__print(_this, type, message);

#ifndef _DEBUG
    // Message pointer is offset 4 bytes when the DLL is compiled as release
    message = reinterpret_cast<std::string*>((int)message + 4);
#endif

    switch (type)
    {
    case RBX__MESSAGE_OUTPUT:
        SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        break;
    case RBX__MESSAGE_INFO:
        SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    case RBX__MESSAGE_WARNING:
        SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN);
        break;
    case RBX__MESSAGE_ERROR:
        SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;
    }

    printf("%s\n", message->c_str());
    SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void CleanupConsole()
{
    CloseHandle(console);
}

#endif