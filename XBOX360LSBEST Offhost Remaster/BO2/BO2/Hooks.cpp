#include "stdafx.h"

detour<void>* SND_EndFrameDetour;
detour<int>* XamInputGetStateDetour;
detour<void>* CL_CreateNewCommandsDetour;
detour<void>* CL_SendCommandDetour;




void SND_EndFrameHook() {
	if (Global.g_killThread) {
		SND_EndFrameDetour->callOriginal(NULL);
		return;
	}

	if (!Global.MenuReady) {
		Render::Initialize();
	}
	else {
		bool bInGame = Game::CheckInGame();
		if (bInGame) {
			DWORD cgs_t = *(DWORD*)0x82BBAE44;
			if (cgs_t) {
				CG::bInGameCached = bInGame && *(DWORD*)(cgs_t + 0x1660) != 0;
			}
			else {
				CG::bInGameCached = false;
			}
		}
		else {
			CG::bInGameCached = bInGame;
		}

		if (CG::bInGameCached && !CG::bLobbyInitialized) {
			CG::bLobbyInitialized = TRUE;
		}
		else if (!CG::bInGameCached && CG::bLobbyInitialized) {
			CG::bLobbyInitialized = FALSE;
		}

		
		Menu::Update();
		Visuals::HandleVisuals();
	}

	SND_EndFrameDetour->callOriginal(NULL);
}

int XamInputGetStateHook(int dwUserIndex, PXINPUT_STATE pState) {
	int result = XamInputGetStateDetour->callOriginal(dwUserIndex, pState);

	if (dwUserIndex != 0 || FAILED(result) || !pState || Global.g_killThread)
		return result;

	if (UIItems.submenu != CLOSED) {
		pState->Gamepad.wButtons &= ~(XINPUT_GAMEPAD_DPAD_UP | XINPUT_GAMEPAD_DPAD_DOWN | XINPUT_GAMEPAD_DPAD_LEFT | XINPUT_GAMEPAD_DPAD_RIGHT | XINPUT_GAMEPAD_A | XINPUT_GAMEPAD_B | XINPUT_GAMEPAD_X | XINPUT_GAMEPAD_Y | XINPUT_GAMEPAD_LEFT_SHOULDER | XINPUT_GAMEPAD_RIGHT_SHOULDER);
	}

	return result;
}

void CL_CreateNewCommandsHook(int localClientNum) {
	if (Global.g_killThread) {
		CL_CreateNewCommandsDetour->callOriginal(localClientNum);
		return;
	}

	CL_CreateNewCommandsDetour->callOriginal(localClientNum);

	if (Game::UserInGame()) {
		Structs::UpdateStructures();

		usercmd_s* oldCmd = clientActive->getCmd(clientActive->cmdNumber - 1);
		usercmd_s* currentCmd = clientActive->getCmd(clientActive->cmdNumber);
		usercmd_s* nextCmd = clientActive->getCmd(clientActive->cmdNumber + 1);
		*nextCmd = *currentCmd;
		clientActive->cmdNumber += 1;
		currentCmd->serverTime = oldCmd->serverTime + 2;

		Aimbot::HandleAimbot(currentCmd, nextCmd);
	}
}

void CL_SendCommandHook(int localClientNum) {
	if (Global.g_killThread) {
		CL_SendCommandDetour->callOriginal(localClientNum);
		return;
	}

	static int fakeLagCount = 0;

	if (Game::UserInGame()) {
		Structs::UpdateStructures();//dev___1_

		usercmd_s *cmd = clientActive->getCmd(clientActive->cmdNumber + 1);
		usercmd_s *oldCmd = clientActive->getCmd(clientActive->cmdNumber);

		clientActive->cmdNumber++;
		*cmd = *oldCmd;
		cmd->serverTime += 1;

		Spinbot::HandleSpinbot(cmd);
	}

	CL_SendCommandDetour->callOriginal(localClientNum);
}

void Hooking::LoadHooks() {
	SND_EndFrameDetour = new detour<void>;
	XamInputGetStateDetour = new detour<int>;
	CL_CreateNewCommandsDetour = new detour<void>;
	CL_SendCommandDetour = new detour<void>;

	Definitions::Initialize();

	*(int*)(Security->addrs.CrashFix) = 0x60000000;

	BYTE EmptyMemory[0x20] = { 0x7C, 0x83, 0x23, 0x78, 0x3D, 0x60, 0x82, 0xC5, 0x38, 0x8B, 0x5D, 0x60, 0x3D, 0x60, 0x82, 0x4A, 0x39, 0x6B, 0xDC, 0xA0, 0x38, 0xA0, 0x00, 0x20, 0x7D, 0x69, 0x03, 0xA6, 0x4E, 0x80, 0x04, 0x20 };
	BYTE XamGetUserName[0x10] = { 0x3D, 0x60, 0x82, 0xC5, 0x39, 0x6B, 0x5D, 0x00, 0x7D, 0x69, 0x03, 0xA6, 0x4E, 0x80, 0x04, 0x20 };
	BYTE GT_Patch1[1] = { 0x00 };
	BYTE GT_Patch2[1] = { 0x40 };

	memcpy((PVOID)Security->addrs.EmptyMemory, EmptyMemory, 0x20);
	memcpy((PVOID)Security->addrs.XamGetUserName, XamGetUserName, 0x10);
	memcpy((PVOID)Security->addrs.ErrorPatch[0], GT_Patch1, 0x1);
	memcpy((PVOID)Security->addrs.ErrorPatch[1], GT_Patch2, 0x1);



	SND_EndFrameDetour->setupDetour(Security->addrs.SND_EndFrameHook, (PVOID)SND_EndFrameHook);
	XamInputGetStateDetour->setupDetour(Security->addrs.XamInputGetStateHook, (PVOID)XamInputGetStateHook);
	CL_CreateNewCommandsDetour->setupDetour(Security->addrs.CL_CreateNewCommandsHook, (PVOID)CL_CreateNewCommandsHook);
	CL_SendCommandDetour->setupDetour(Security->addrs.CL_SendCommandHook, (PVOID)CL_SendCommandHook);
}

void Hooking::UnloadHooks() {
	if (SND_EndFrameDetour->IsValid())
		SND_EndFrameDetour->takeDownDetour();

	if (XamInputGetStateDetour->IsValid())
		XamInputGetStateDetour->takeDownDetour();

	if (CL_CreateNewCommandsDetour->IsValid())
		CL_CreateNewCommandsDetour->takeDownDetour();

	if (CL_SendCommandDetour->IsValid())
		CL_SendCommandDetour->takeDownDetour();

	delete SND_EndFrameDetour;
	delete XamInputGetStateDetour;
	delete CL_CreateNewCommandsDetour;
	delete CL_SendCommandDetour;
}