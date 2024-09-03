#include "stdafx.h"

Aimbot cAimbot;

int aimbotClient = -1;

char* AimbotTypes[0x2] = { "Visible", "Autowall" };
char* TargetTypes[0x2] = { "Snap", "Silent" };
char* AimTags[0x10] = { "j_helmet", "j_head", "j_neck", "j_shoulder_le", "j_shoulder_ri", "j_mainroot", "j_elbow_le", "j_elbow_ri", "j_wrist_le", "j_wrist_ri", "j_spineupper", "j_spinelower", "j_knee_le", "j_knee_ri", "j_ankle_le", "j_ankle_ri" };

bool Aimbot::bCheckBoneArray(int clientNum) {
	for (int i = 0; i < ARRAYSIZE(AimTags); i++) {
		if (!Autowall::IsPlayerPenetrable(clientNum, SL_GetString(AimTags[i], 0)))
			continue;

		pInfo[clientNum].Bone = AimTags[i];

		return true;
	}

	return false;
}

double Radians(float Degrees) {
	return  0.01745329238474369 * Degrees;
}

void Aimbot::GetWeaponSpread(int* seed, float* x, float* y) {
	float min, max, spread, fx, fy;
	int randSeed = *seed;
	BG_GetSpreadForWeapon((playerState_s*)((DWORD)cg + 0x480A8), centity[cg->clientNumber].weaponNum, &min, &max);
	spread = (max - min) * (cg->SpreadScale * 0.00392156862) + min;
	fx = Radians(RandomBulletDir(&randSeed) * 360);
	sub_82697FC0(&randSeed);
	fy = RandomBulletDir(&randSeed);
	*x = cos(fx) * fy * spread;
	*y = sin(fx) * fy * spread;
}

void Aimbot::NoSpread(usercmd_s* nextCmd, usercmd_s* currentCmd) {
	vec3 SpreadAngles = vec3();

	int Seed = nextCmd->serverTime;

	TransformSeed(&Seed);

	GetWeaponSpread(&Seed, &SpreadAngles.x, &SpreadAngles.y);

	currentCmd->ViewAngles[0] -= ANGLE2SHORT(-SpreadAngles.y);
	currentCmd->ViewAngles[1] -= ANGLE2SHORT(-SpreadAngles.x);
}

void Aimbot::FixMovement(usercmd_s* pCmd, float CurAngle, float OldAngle, float fOldForward, float fOldSidemove) {
	float deltaView = CurAngle - OldAngle;
	int forward = (int)(cos(deltaView * (PI / 180.0f)) * fOldForward + cos((deltaView + 90.f) * (PI / 180.0f)) * fOldSidemove);
	int right = (int)(sin(deltaView * (PI / 180.0f)) * fOldForward + sin((deltaView + 90.f) * (PI / 180.0f)) * fOldSidemove);

	if (forward < -128) forward = -128;
	else if (forward > 127) forward = 127;
	if (right < -128) right = -128;
	else if (right > 127) right = 127;

	pCmd->forwardmove = (char)forward;
	pCmd->sidemove = (char)right;
}

void Aimbot::NormalAim(vec3 toAngle) {
	auto ca = clientActive;
	if (ca) {
		ca->viewAngles.x = toAngle.x - ca->spawnAngles.x;
		ca->viewAngles.y = toAngle.y - ca->spawnAngles.y;
	}
}

void Aimbot::SilentAim(usercmd_s* oldCommand, vec3 toAngle) {
	clientActive_s* ca = clientActive;
	if (ca) {
		float oldAngle = SHORT2ANGLE(oldCommand->ViewAngles[1]);
		oldCommand->ViewAngles[0] = ANGLE2SHORT(toAngle.x - ca->spawnAngles.x);
		oldCommand->ViewAngles[1] = ANGLE2SHORT(toAngle.y - ca->spawnAngles.y);
		FixMovement(oldCommand, SHORT2ANGLE(oldCommand->ViewAngles[1]), oldAngle, oldCommand->forwardmove, oldCommand->sidemove);
	}
}

int Aimbot::GetClosestClient() {
	int dwClosestClient = -1;
	float closestDistance = FLT_MAX;

	for (int i = 0; i < cgs->MaxClients; i++) {

		pInfo[i].Visible = false;
		pInfo[i].Wallbangable = false;
		pInfo[i].Bone = "";

		if (i == cg->clientNumber)
			continue;

		if (centity[i].eType != 1)
			continue;

		if ((*(int*)((DWORD)&centity[i] + 0x36C) & 0x40000000) == 0 || (*(int*)((DWORD)&centity[i] + 0x1D4) & 0x40000))
			continue;

		if (!Game::IsEnemy(i))
			continue;

		if (pInfo[i].Whitelisted)
			continue;

		pInfo[i].Bone = AimTags[CG::dwAimTag];

		if (pInfo[i].Prioritized) {
			bool bWallbangable = Autowall::IsPlayerPenetrable(i, SL_GetString("j_knee_le", 0));
			if (!(pInfo[i].Wallbangable = bWallbangable)) {
				bWallbangable = Autowall::IsPlayerPenetrable(i, SL_GetString("j_knee_ri", 0));
				if (!(pInfo[i].Wallbangable = bWallbangable)) {
					bWallbangable = Autowall::IsPlayerPenetrable(i, SL_GetString("j_ankle_le", 0));
					if (!(pInfo[i].Wallbangable = bWallbangable)) {
						bWallbangable = Autowall::IsPlayerPenetrable(i, SL_GetString("j_ankle_ri", 0));
						if (!(pInfo[i].Wallbangable = bWallbangable)) {
							bWallbangable = bCheckBoneArray(i);
							if (!(pInfo[i].Wallbangable = bWallbangable))
								continue;
						}
						else {
							pInfo[i].Bone = "j_ankle_ri";
						}
					}
					else {
						pInfo[i].Bone = "j_ankle_le";
					}
				}
				else {
					pInfo[i].Bone = "j_knee_ri";
				}
			}
			else {
				pInfo[i].Bone = "j_knee_le";
			}
		}
		else {
			if (CG::dwAimbotType == 1) {
				if (!(pInfo[i].Wallbangable = Autowall::IsPlayerPenetrable(i, SL_GetString(pInfo[i].Bone, 0))))
					continue;
			}
			else {
				if (!(pInfo[i].Visible = Game::IsClientVisible(i, SL_GetString(pInfo[i].Bone, 0))))
					continue;
			}
		}

		FLOAT TempDistance = centity[cg->clientNumber].Origin.distanceTo(centity[i].Origin);
		if (pInfo[i].Prioritized) {
			TempDistance = 0.0001f;
		}

		if (TempDistance < closestDistance)
		{
			dwClosestClient = i;
			closestDistance = TempDistance;
		}
	}
	return dwClosestClient;
}

void Aimbot::HandleAimbot(usercmd_s* currentCmd, usercmd_s* nextCmd) {
	if (CG::dwAimbot) {
		aimbotClient = GetClosestClient();
		if (aimbotClient != -1) {
			vec3 viewOrigin;
			CG_GetPlayerViewOrigin(0, (playerState_s*)((DWORD)cg + 0x480A8), viewOrigin);

			if (viewOrigin.IsNull()) return;

			vec3 bonePosition = Game::GetTagPos(&centity[aimbotClient], SL_GetString(pInfo[aimbotClient].Bone, 0));

			if (bonePosition.IsNull()) return;

			vec3 subtracted = (bonePosition - viewOrigin);

			vec3 angle;
			Utilities::VectorToAngle(&subtracted, &angle);

			if (CG::dwTargetType == 0) {
				NormalAim(angle);
			}
			else if (CG::dwTargetType == 1) {
				SilentAim(currentCmd, angle);
			}

			if (CG::NoSpread)
				NoSpread(nextCmd, currentCmd);

			if (CG::dwAutoShoot) {
				nextCmd->buttons |= 0x80000000;
				if (currentCmd->buttons & 0x80000000) {
					currentCmd->buttons &= 0x7FFFFFFFu;
				}
			}
		}
	}
	else {
		aimbotClient = -1;
	}

	XINPUT_STATE Controller;
	XInputGetState(0, &Controller);

	if (Controller.Gamepad.bRightTrigger > 35) {
		if (!CG::dwAutoShoot)
		{
			nextCmd->buttons |= 0x80000000;
			if (currentCmd->buttons & 0x80000000) {
				currentCmd->buttons &= 0x7FFFFFFFu;
			}
		}
	}
}