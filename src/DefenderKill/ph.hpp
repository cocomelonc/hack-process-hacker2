#pragma once

#include <Windows.h>

#define PH_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

namespace PH
{
	//VOID PhInitializeKph(PVOID PhBase);

	NTSTATUS PhOpenProcess(PVOID PhBase, PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, HANDLE ProcessId);

	NTSTATUS PhOpenProcessToken(PVOID PhBase, HANDLE ProcessHandle, ACCESS_MASK DesiredAccess, PHANDLE TokenHandle);
}