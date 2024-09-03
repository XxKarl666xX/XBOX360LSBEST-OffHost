#include "stdafx.h"

char* SpinbotTypesX[3] = { "Look Up", "Look Down", "Up & Down"};
char* SpinbotTypesY[4] = { "Anti Aim", "Random", "Left", "Right" };


vec2 spinAngles = vec2();

int Spinbot::FindBestAntiAimTarget()
{
	int dwAAClosestClient = -1;
	float ClosestAA = FLT_MAX;

	// Loop for all players
	for (int i = 0; i < cgs->MaxClients; i++)
	{
		if (i == cg->clientNumber)
			continue;

		if (pInfo[i].Whitelisted)
			continue;

		if (centity[i].eType != 1)
			continue;

		if ((*(int*)((DWORD)&centity[i] + 0x36C) & 0x40000000) == 0 || (*(int*)((DWORD)&centity[i] + 0x1D4) & 0x40000))
			continue;

		if (!Game::IsEnemy(i))
			continue;

		// Grab our temp distance
		FLOAT TempDistance = centity[cg->clientNumber].Origin.distanceTo(centity[i].Origin);

		// just make them seem closest
		if (pInfo[i].Prioritized)
			TempDistance = 0.0001f;

		// Update our closest player info
		if (TempDistance < ClosestAA)
		{
			dwAAClosestClient = i;
			ClosestAA = TempDistance;
		}
	}

	return dwAAClosestClient;
}

void Spinbot::HandleSpinbot(usercmd_s* currentCmd) {
    // If we aren't prone, not mantling, not dead, not climbing a ladder, not pressing LB or RB
    if ((*(BYTE*)((DWORD)cg + 0x18F) & 0x8) || (cg->Health <= 0) || currentCmd->weapon == 0 || currentCmd->buttons & 0x00010000 || currentCmd->buttons & 0x00020000)
        return;

    // Check if AntiAim is enabled
    if (CG::dwAntiAim) {
        

        if (CG::dwAntiAimPitch == SPINBOT_PITCH_LOOK_UP) {
            currentCmd->ViewAngles[0] = ANGLE2SHORT(-69.99f - clientActive->spawnAngles.x);
        }
        else if (CG::dwAntiAimPitch == SPINBOT_PITCH_LOOK_DOWN) {
            currentCmd->ViewAngles[0] = ANGLE2SHORT(69.99f - clientActive->spawnAngles.x);
        }
        else if (CG::dwAntiAimPitch == SPINBOT_PITCH_LOOK_UP_DOWN) {
            if ((rand() % 2) == 0) {
                currentCmd->ViewAngles[0] = ANGLE2SHORT(-69.99f - clientActive->spawnAngles.x);
            }
            else {
                currentCmd->ViewAngles[0] = ANGLE2SHORT(69.99f - clientActive->spawnAngles.x);
            }
        }

        if (CG::dwAntiAimYaw == SPINBOT_YAW_ANTI_AIM) {
            int AAClient = FindBestAntiAimTarget();
            if (aimbotClient != -1 || AAClient != -1) {
                int target = aimbotClient == -1 ? AAClient : aimbotClient;

                vec3 viewOrigin;
                CG_GetPlayerViewOrigin(0, (playerState_s*)((DWORD)cg + 0x480A8), viewOrigin);

                vec3 pos = Game::GetTagPos(&centity[target], SL_GetString("j_mainroot", 0));
                vec3 subtracted = pos - viewOrigin;

                vec3 angle;
                Utilities::VectorToAngle(&subtracted, &angle);

                currentCmd->ViewAngles[1] = ANGLE2SHORT((angle.y - 180.0f) - clientActive->spawnAngles.y);
            }
        }
        else if (CG::dwAntiAimYaw == SPINBOT_YAW_RANDOM) {
            currentCmd->ViewAngles[1] = ANGLE2SHORT((FLOAT)(rand() % 360) - clientActive->spawnAngles.y);
        }
        else if (CG::dwAntiAimYaw == SPINBOT_YAW_LEFT) {
            spinAngles.y = spinAngles.y - 25.0f;
            if (spinAngles.y >= -360.0f)
                spinAngles.y = 0.0f;

            currentCmd->ViewAngles[1] = ANGLE2SHORT(spinAngles.y - clientActive->spawnAngles.y);
        }
        else if (CG::dwAntiAimYaw == SPINBOT_YAW_RIGHT) {
            spinAngles.y = spinAngles.y + 25.0f;
            if (spinAngles.y >= 360.0f)
                spinAngles.y = 0.0f;

            currentCmd->ViewAngles[1] = ANGLE2SHORT(spinAngles.y - clientActive->spawnAngles.y);
        }
    } 
   
}
