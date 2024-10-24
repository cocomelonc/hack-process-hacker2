#include "dbg.hpp"
#include <Shlwapi.h>

namespace Debug
{
	CRITICAL_SECTION DebugFileSection = { 0 };
	HANDLE DebugFileHandle = NULL;
	DWORD OutputMode = 0;

	VOID WriteDebugLogToDebugConsoleW(LPCWSTR DebugString, va_list ArgList)
	{
		if (!DebugString)
		{
			return;
		}

		do
		{
			WCHAR FormattedString[4096];

			if (!wvnsprintfW(FormattedString, 4095, DebugString, ArgList))
			{
				break;
			}

			OutputDebugStringW(FormattedString);
		} while (false);
	}

	VOID WriteDebugLogToFileW(LPCWSTR DebugString, va_list ArgList)
	{
		if (!DebugString || !ArgList)
		{
			return;
		}

		EnterCriticalSection(&DebugFileSection);

		do
		{
			WCHAR FormattedString[4096] = { 0 };
	
			int Length = wvnsprintfW(FormattedString, 4095, DebugString, ArgList);

			if (!Length)
			{
				break;
			}

			DWORD Written = 0;

			if (!WriteFile(DebugFileHandle, FormattedString, Length * 2, &Written, nullptr))
			{
				break;
			}
		} while (false);

		LeaveCriticalSection(&DebugFileSection);
	}

	VOID DbgOutW(LPCWSTR DebugString, ...)
	{
		if (!DebugString)
		{
			return;
		}

		va_list ArgList = nullptr;
		va_start(ArgList, DebugString);

		if (OutputMode == DEBUG_OUTPUT_MODE_FILE && DebugFileHandle)
		{
			WriteDebugLogToFileW(DebugString, ArgList);
		}
		else
		{
			WriteDebugLogToDebugConsoleW(DebugString, ArgList);
		}

		va_end(ArgList);
	}

	BOOL InitFileOutput()
	{
		BOOL Result = false;

		do
		{
			WCHAR ProgramDataPath[1025] = { 0 };
			SYSTEMTIME SystemTime = { 0 };
			WCHAR LogPath[1025] = { 0 };

			if (!GetEnvironmentVariableW(L"PROGRAMDATA", ProgramDataPath, 1024))
			{
				break;
			}

			GetSystemTime(&SystemTime);

			if (!wsprintfW(LogPath, L"%s\\DefenderKillLog-%02d-%02d-%02d-%02d-%02d-%02d.log", ProgramDataPath, SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay, SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond))
			{
				break;
			}

			DebugFileHandle = CreateFileW(LogPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

			if (DebugFileHandle == INVALID_HANDLE_VALUE)
			{
				break;
			}

			InitializeCriticalSection(&DebugFileSection);

			Result = true;
		} while (false);

		return Result;
	}

	BOOL Init(DWORD NewOutputMode)
	{
		if (!NewOutputMode || NewOutputMode != DEBUG_OUTPUT_MODE_CONSOLE && NewOutputMode != DEBUG_OUTPUT_MODE_FILE)
		{
			return FALSE;
		}

		OutputMode = NewOutputMode;

		if (OutputMode == DEBUG_OUTPUT_MODE_FILE)
		{
			return InitFileOutput();
		}

		return TRUE;
	}
}