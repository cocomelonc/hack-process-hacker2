#include "memory.hpp"

#pragma function (memset)
void* memset(void* _Dst, int _Val, size_t _Size)
{
	byte* x = (byte*)_Dst;

	while (_Size--)
	{
		*x++ = _Val;
	}

	return _Dst;
}

namespace Memory
{
	HANDLE HeapHandle = NULL;

	BOOL Init()
	{
		return (HeapHandle = GetProcessHeap()) ? true : false;
	}

	PVOID Alloc(DWORD Size)
	{
		return HeapAlloc(HeapHandle, HEAP_ZERO_MEMORY, Size);
	}

	PVOID ReAlloc(PVOID MemPtr, DWORD Size)
	{
		return HeapReAlloc(HeapHandle, HEAP_ZERO_MEMORY, MemPtr, Size);
	}

	BOOL Free(PVOID MemPtr)
	{
		return HeapFree(HeapHandle, 0, MemPtr);
	}
}