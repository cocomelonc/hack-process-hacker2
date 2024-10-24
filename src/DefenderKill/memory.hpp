#pragma once

#include <Windows.h>

namespace Memory
{
	BOOL Init();

	PVOID Alloc(DWORD Size);

	PVOID ReAlloc(PVOID MemPtr, DWORD Size);

	BOOL Free(PVOID MemPtr);
}