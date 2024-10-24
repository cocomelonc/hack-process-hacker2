#include <Windows.h>

#ifndef _AMD64_
#pragma comment(linker,"/EXPORT:IsThemeActive=_IsThemeActive@0")
#pragma comment(linker,"/EXPORT:GetThemeInt=_GetThemeInt@20")
#pragma comment(linker,"/EXPORT:SetWindowTheme=_SetWindowTheme@12")
#pragma comment(linker,"/EXPORT:CloseThemeData=_CloseThemeData@4")
#pragma comment(linker,"/EXPORT:DrawThemeBackground=_DrawThemeBackground@24")
#pragma comment(linker,"/EXPORT:OpenThemeData=_OpenThemeData@8")
#pragma comment(linker,"/EXPORT:IsThemePartDefined=_IsThemePartDefined@12")
#pragma comment(linker,"/EXPORT:EnableThemeDialogTexture=_EnableThemeDialogTexture@8")
#define AVKILL_EXPORT
#else
#define AVKILL_EXPORT __declspec(dllexport)
#endif

namespace Exports
{
#define HTHEME HANDLE

	extern "C" AVKILL_EXPORT BOOL __stdcall IsThemeActive()
	{
		return 0;
	} 

	extern "C" AVKILL_EXPORT HRESULT __stdcall GetThemeInt(HTHEME hTheme, int iPartId, int iStateId, int iPropId, int* piVal)
	{
		return 0;
	}

	extern "C" AVKILL_EXPORT HRESULT __stdcall SetWindowTheme(HWND hwnd, LPCWSTR pszSubAppName, LPCWSTR pszSubIdList)
	{
		return 0;
	}

	extern "C" AVKILL_EXPORT HRESULT __stdcall CloseThemeData(HTHEME hTheme)
	{
		return 0;
	}

	extern "C" AVKILL_EXPORT HRESULT __stdcall DrawThemeBackground(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, LPCRECT pRect, LPCRECT pClipRect)
	{
		return 0;
	}

	extern "C" AVKILL_EXPORT HTHEME __stdcall OpenThemeData(HWND hwnd, LPCWSTR pszClassList)
	{
		return 0;
	}

	extern "C" AVKILL_EXPORT BOOL __stdcall IsThemePartDefined(HTHEME hTheme, int iPartId, int iStateId)
	{
		return 0;
	}

	extern "C" AVKILL_EXPORT BOOL __stdcall EnableThemeDialogTexture(HWND hwnd, DWORD dwFlags)
	{
		return 0;
	}
} 