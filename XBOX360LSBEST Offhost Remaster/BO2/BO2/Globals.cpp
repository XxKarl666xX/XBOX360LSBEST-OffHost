#include "stdafx.h"

BOOL bReadyToNotify = FALSE;

DWORD CG::dwWhite = NULL;
DWORD CG::dwSmallFont = NULL;

BOOL CG::bInGameCached = FALSE;
BOOL CG::bConnected = FALSE;
BOOL CG::bLobbyInitialized = FALSE;
BOOL CG::bQuittingGame = FALSE;

BOOL CG::NoRecoil = TRUE;
BOOL CG::NoSway = TRUE;
BOOL CG::NoSpread = TRUE;
BOOL CG::VSAT = TRUE;
BOOL CG::ThirdPerson = FALSE;
FLOAT CG::fFovValue = 90.0f;

BOOL CG::bLaunchCustomGTEntry = FALSE;
BOOL CG::dwRainbowGT = FALSE;
FLOAT CG::dwRainbowDelay = 500.0f;

BOOL CG::dwAimbot = TRUE;
BOOL CG::customToggleOption = TRUE; //my custom toggle option
DWORD CG::dwAimbotType = 1;
DWORD CG::dwTargetType = 1;
DWORD CG::dwAimTag = 1;
BOOL CG::dwAutoShoot = TRUE;
BOOL CG::dwAntiAim = FALSE;
DWORD CG::dwAntiAimPitch = 0;
DWORD CG::dwAntiAimYaw = 0;

BOOL CG::dwESPDrawAllies = TRUE;
BOOL CG::dwESPDrawAxis = TRUE;
DWORD CG::dwESPBoxType = BOX_TYPE_2D;
BOOL CG::dwESPName = FALSE;
BOOL CG::dwESPBones = TRUE;
BOOL CG::dwESPDistance = FALSE;
BOOL CG::dwESPWeapon = TRUE;
BOOL CG::dwSnaplines = TRUE;
BOOL CG::dwESPDrawCrosshair = TRUE;


Globals Global;

void Globals::Initialize() {
	UnloadEngine = FALSE;
	MenuReady = FALSE;

	aimbotClient = -1;
}