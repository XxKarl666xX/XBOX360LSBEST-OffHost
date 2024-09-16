#include "stdafx.h"

DWORD SupportedVersion = 17559;
DWORD TitleID = 0x415608C3;
BOOL bInitOnce = FALSE;

detour<void> OriginalExTerminateTitleProcess;

void ExTerminateTitleProcessHook(int r3) {
	Global.UnloadEngine = TRUE;

	OriginalExTerminateTitleProcess.callOriginal(NULL);
}

void GameThread() {
	while (XamGetCurrentTitleId() != TitleID)
		Sleep(100);

	PLDR_DATA_TABLE_ENTRY entry;
	XexPcToFileHeader((PVOID)0x82000000, &entry);
	if (wcscmp(entry->BaseDllName.Buffer, L"default_mp.xex") == 0) {
		PBYTE buf = (PBYTE)XPhysicalAlloc(0x2000, MAXULONG_PTR, 128, MEM_LARGE_PAGES | PAGE_READWRITE);
		mManager = new MemoryManager((DWORD)buf, 0x2000);
		mManager->alloc(sizeof(cSecurity), &Security);

		Global.Initialize();

		while (!Global.g_killThread) {
			Sleep(1000);

			if (Security->bHasPatches) {
				if (!Global.g_Hooked) {
					Game::CacheSignInState();
					Hooking::LoadHooks();
					OriginalExTerminateTitleProcess.setupDetour((DWORD)Utilities::ResolveFunction(MODULE_KERNEL, 0x1A), (PVOID)ExTerminateTitleProcessHook);
					Global.g_Hooked = TRUE;



				}

				if (Global.UnloadEngine)
					Global.g_killThread = TRUE;

				for (int i = 0; i < 0x4; i++) {
					if (XamUserGetSigninState(i) != SigninState) {
						SigninState = XamUserGetSigninState(i);
						if (!freshSignedIn) {
							Game::FixGamertag();
							freshSignedIn = true;
						}
					}
				}

				



				
				if (!bInitOnce) {
					Sleep(2500);

					if (!bReadyToNotify) {
						bReadyToNotify = TRUE;
					}

					bInitOnce = TRUE;
				}
			}
			else {
				Security->SetAddresses();
			}
		}

		if (Global.g_Hooked) {
			Hooking::UnloadHooks();
			Global.g_Hooked = FALSE;
		}

		Sleep(500);
	}
	OriginalExTerminateTitleProcess.takeDownDetour();
	Global.g_MainLoopExited = true;

	if (Global.UnloadEngine) {
		*(WORD*)((DWORD)Global.hME + 64) = 1;
		DWORD exitCode;
		GetExitCodeThread(GetCurrentThread(), &exitCode);
		XexUnloadImageAndExitThread(Global.hME, (HANDLE)exitCode);
	}
}

DWORD flags = EX_CREATE_FLAG_SUSPENDED | EX_CREATE_FLAG_SYSTEM | EX_CREATE_FLAG_CORE2 | EX_CREATE_FLAG_PRIORITY1;
HRESULT InitializeEngine() {
	Global.hKernel = GetModuleHandle(MODULE_KERNEL);
	Global.hXam = GetModuleHandle(MODULE_XAM);

	if (Global.hME == NULL || Global.hKernel == NULL || Global.hXam == NULL)
		return E_FAIL;

	if (XboxKrnlVersion->Build != SupportedVersion)
		return E_FAIL;

	flags |= 0x18000424;

	HANDLE Handle;
	ExCreateThread(&Handle, 0, 0, XapiThreadStartup, (LPTHREAD_START_ROUTINE)GameThread, 0, flags);
	XSetThreadProcessor(Handle, 4);
	SetThreadPriority(Handle, THREAD_PRIORITY_ABOVE_NORMAL);
	ResumeThread(Handle);
	CloseHandle(Handle);

	srand((int)time(NULL));

	return ERROR_SUCCESS;
}

//#define OBFUSCATION


#ifdef OBFUSCATION
BYTE szObfuscationData[0x100] = { 'x', 'b', 'S', 'e', 'c', 'u', 'r', 'e' };

extern "C" BOOL WINAPI _CRT_INIT(HANDLE hModule, DWORD dwReason, LPVOID lpReserved);

#pragma code_seg(push, r1, ".ptext")
#pragma pack(push)
#pragma pack(1)

struct ObfuscationData {
	BYTE szRC4Key[0x20];
	DWORD rdataEnd;
	DWORD rdataStart;
	DWORD szXORValue;
	BYTE szRandom[0x27];
	DWORD textStart;
	DWORD textEnd;
};
#pragma pack(pop)

#pragma optimize( "", off)

BOOL APIENTRY SecureDllMain(HANDLE module, DWORD res, LPVOID lpR) {
	BOOL Result = TRUE;

	ObfuscationData* data = (ObfuscationData*)szObfuscationData;

	DWORD textSection, rdataSection;

	for (int i = 0; i < 0x20; i++) {
		data->szRC4Key[i] = (data->szRC4Key[i] ^ data->szXORValue);
	}

	if (res == DLL_PROCESS_ATTACH) {

		for (textSection = (data->textStart ^ data->szXORValue); textSection < (data->textEnd ^ data->szXORValue); textSection++) { //.text
			for (auto i = 0; i < 0x20; i++) {
				BYTE key_1 = (BYTE)(data->szRC4Key[i] << 2);
				BYTE key_2 = (BYTE)(key_1 + (textSection % 0x10));
				BYTE key_3 = (BYTE)(key_2 ^ key_1);
				BYTE key_4 = (BYTE)(key_3 * 0x4);
				BYTE key_5 = (BYTE)(((textSection % 0x10) >> 4) ^ data->szRC4Key[i]);
				BYTE key_6 = (BYTE)(key_5 | ((textSection % 0x10) ^ key_2) >> 7);

				BYTE finalKey = (((((key_6 ^ key_3) ^ key_4) ^ key_2) ^ key_5) ^ key_1);

				*(BYTE*)(textSection) ^= finalKey;
			}
		}

		for (rdataSection = (data->rdataStart ^ data->szXORValue); rdataSection < (data->rdataEnd ^ data->szXORValue); rdataSection++) { //.rdata
			for (auto i = 0; i < 0x20; i++) {
				BYTE key_1 = (BYTE)(data->szRC4Key[i] << 2);
				BYTE key_2 = (BYTE)(key_1 + (rdataSection % 0x10));
				BYTE key_3 = (BYTE)(key_2 ^ key_1);
				BYTE key_4 = (BYTE)(key_3 * 0x4);
				BYTE key_5 = (BYTE)(((rdataSection % 0x10) >> 4) ^ data->szRC4Key[i]);
				BYTE key_6 = (BYTE)(key_5 | ((rdataSection % 0x10) ^ key_2) >> 7);

				BYTE finalKey = (((((key_6 ^ key_3) ^ key_4) ^ key_2) ^ key_5) ^ key_1);

				*(BYTE*)(rdataSection) ^= finalKey;
			}
		}

		__dcbst(0, (void*)textSection);
		__dcbst(0, (void*)rdataSection);
		__sync();
		__isync();

		if (Result = _CRT_INIT(module, res, lpR)) {
			if (XamLoaderGetDvdTrayState() != DVD_TRAY_STATE_OPEN && XboxKrnlVersion->Build == 17559) {
				if (InitializeEngine() != ERROR_SUCCESS) {
					*(WORD*)((DWORD)module + 64) = 1;
					return false;
				}
			}
		}
	}
	return Result;
}

#pragma optimize( "", on)

#else

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		Global.hME = hModule;

		if (InitializeEngine() != ERROR_SUCCESS) {
			*(WORD*)((DWORD)hModule + 64) = 1;
			return FALSE;
		}
		break;
	case DLL_PROCESS_DETACH:
		Global.g_killThread = TRUE;
		while (!Global.g_MainLoopExited)
			Sleep(10);

		break;
	}
	return TRUE;
}

#endif