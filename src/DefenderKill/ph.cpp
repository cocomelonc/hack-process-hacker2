#include "ph.hpp"

namespace PH
{
	/*VOID PhInitializeKph(PVOID PhBase)
	{
		if (!PhBase)
		{
			return;
		}

#ifdef _AMD64_
		DWORD Offset = 0x22360;
#else
		DWORD Offset = 0x1A6D0;
#endif

		typedef VOID(__stdcall* xPhInitializeKph)();
		xPhInitializeKph pPhInitializeKph = (xPhInitializeKph)((PBYTE)PhBase + Offset);

		pPhInitializeKph();
	}*/

	/*
	
	� ������ �� ��� ������� ����� ��������� ������ __stdcall
	�� � ��������� ������� ������� � ������� ���������� ������� ����������, ��� ������������ fastcall (����� ����������� ������ �� �86, �� �64 ���� ��� �� ��� ��� ��� ��������� �� ��������� �����)
	������ ��� - ��, �� ������ �� �����
	
	*/

	NTSTATUS PhOpenProcess(PVOID PhBase, PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, HANDLE ProcessId)
	{
		if (!PhBase)
		{
			return 0;
		}
			 
#ifdef _AMD64_
		DWORD Offset = 0xB85F0;
#else
		DWORD Offset = 0x97A10;
#endif

		typedef NTSTATUS(__fastcall* xPhOpenProcess)(PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, HANDLE ProcessId);
		xPhOpenProcess pPhOpenProcess = (xPhOpenProcess)((PBYTE)PhBase + Offset);

		return pPhOpenProcess(ProcessHandle, DesiredAccess, ProcessId);
	}

	NTSTATUS PhOpenProcessToken(PVOID PhBase, HANDLE ProcessHandle, ACCESS_MASK DesiredAccess, PHANDLE TokenHandle)
	{
		if (!PhBase)
		{
			return 0;
		}

#ifdef _AMD64_
		DWORD Offset = 0xC03E0;
#else
		DWORD Offset = 0x9DD50;
#endif

		typedef NTSTATUS(__fastcall* xPhOpenProcessToken)(HANDLE ProcessHandle, ACCESS_MASK DesiredAccess, PHANDLE TokenHandle);
		xPhOpenProcessToken pPhOpenProcessToken = (xPhOpenProcessToken)((PBYTE)PhBase + Offset);

		return pPhOpenProcessToken(ProcessHandle, DesiredAccess, TokenHandle);
	}
}