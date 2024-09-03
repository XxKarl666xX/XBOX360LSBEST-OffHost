#pragma once

extern BOOL bReadyToNotify;

namespace CG {
	extern DWORD dwWhite;
	extern DWORD dwSmallFont;

	extern BOOL bInGameCached;
	extern BOOL bConnected;
	extern BOOL bLobbyInitialized;
	extern BOOL bQuittingGame;

	extern BOOL NoRecoil;
	extern BOOL NoSway;
	extern BOOL NoSpread;
	extern BOOL VSAT;
	extern BOOL ThirdPerson;
	extern FLOAT fFovValue;

	extern BOOL bLaunchCustomGTEntry;
	extern BOOL dwRainbowGT;
	extern FLOAT dwRainbowDelay;

	extern BOOL dwAimbot;
	extern BOOL customToggleOption;//my cusotm toggle option
	extern DWORD dwAimbotType;
	extern DWORD dwTargetType;
	extern DWORD dwAimTag;
	extern BOOL dwAutoShoot;
	extern BOOL dwAntiAim;
	extern DWORD dwAntiAimPitch;
	extern DWORD dwAntiAimYaw;

	extern BOOL dwESPDrawAllies;
	extern BOOL dwESPDrawAxis;
	extern DWORD dwESPBoxType;
	extern BOOL dwESPName;
	extern BOOL dwESPBones;
	extern BOOL dwESPDistance;
	extern BOOL dwESPWeapon;
	extern BOOL dwSnaplines;
	extern BOOL dwESPDrawCrosshair;
	
}

class Globals {
public:

	XINPUT_STATE state;

	BOOL g_killThread;
	BOOL g_Hooked;
	BOOL g_MainLoopExited;

	BOOL UnloadEngine;
	BOOL SaveINI;
	BOOL LoadINI;
	BOOL MenuReady;

	HANDLE hME;
	HANDLE hKernel;
	HANDLE hXam;

	void Initialize();
};

extern Globals Global;