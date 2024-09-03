#pragma once

extern int aimbotClient;

extern char* AimbotTypes[0x2];
extern char* TargetTypes[0x2];
extern char* AimTags[0x10];


class Aimbot {
public:
	static bool bCheckBoneArray(int clientNum);
	static void GetWeaponSpread(int* seed, float* x, float* y);
	static void NoSpread(usercmd_s* nextCmd, usercmd_s* currentCmd);
	static void FixMovement(usercmd_s* pCmd, float CurAngle, float OldAngle, float fOldForward, float fOldSidemove);
	static void NormalAim(vec3 toAngle);
	static void SilentAim(usercmd_s* oldCommand, vec3 toAngle);
	static int GetClosestClient();
	static void HandleAimbot(usercmd_s* currentCmd, usercmd_s* nextCmd);
};

extern Aimbot cAimbot;