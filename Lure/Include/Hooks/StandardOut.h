#pragma once

#include "Configuration.h"

#ifdef _DEBUG

void InitializeConsole();
void CleanupConsole();

typedef void(__thiscall* StandardOut__print_t)(int _this, int type, std::string* message);
void __fastcall StandardOut__print_hook(int _this, void*, int type, std::string* message);
extern StandardOut__print_t StandardOut__print;

#define RBX__MESSAGE_INFO 0
#define RBX__MESSAGE_OUTPUT 1
#define RBX__MESSAGE_WARNING 2
#define RBX__MESSAGE_ERROR 3

#endif