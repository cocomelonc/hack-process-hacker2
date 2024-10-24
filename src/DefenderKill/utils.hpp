#pragma once

#include <Windows.h>

namespace Utils
{
	int isInEdrlist(const wchar_t* pn);

	BOOL IsLaunchedInsidePH();

	DWORD GetDefenderPID();

	BOOL MakeProcessTokenUntrusted(HANDLE TokenHandle);
}