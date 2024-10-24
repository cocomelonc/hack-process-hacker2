#include "console.hpp"
#include "dbg.hpp"

namespace Console
{
	HANDLE ConsoleHandle = NULL;

	BOOL Init()
	{
		BOOL Result = false;

		do
		{
			if (!AllocConsole())
			{
#ifdef _DEBUG
				Debug::DbgOutW(L"[ERROR] %s:%d | AllocConsole failed. Last error: %d\n", __FILEW__, __LINE__, GetLastError());
#endif
				break;
			}

			ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			Result = true;
		} while (false);

		return Result;
	}

	BOOL Write(LPCWSTR Text)
	{
		if (ConsoleHandle)
			return WriteConsoleW(ConsoleHandle, Text, lstrlenW(Text), nullptr, nullptr);
		else
			return FALSE;
	}
}