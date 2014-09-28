// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#include <libtcc.h>

#define GetFuncPointer(F) (Marshal::GetFunctionPointerForDelegate((F)).ToPointer())
#define GetFuncPointerA(F) (Marshal::GetFunctionPointerForDelegate((F)))
#define CreateStr(M) ((const char*)Marshal::StringToHGlobalAnsi((M)).ToPointer())
#define FreeStr(N) Marshal::FreeHGlobal(IntPtr((void*)(N)))

#pragma comment(lib, "libtcc.lib")