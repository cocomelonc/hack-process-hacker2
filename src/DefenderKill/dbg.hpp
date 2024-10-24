#pragma once

#include <Windows.h>

#define DEBUG_OUTPUT_MODE_CONSOLE 1
#define DEBUG_OUTPUT_MODE_FILE 2

namespace Debug
{
	BOOL Init(DWORD NewOutputMode);

	VOID DbgOutW(LPCWSTR DebugString, ...);
}