#include "stdafx.h"

char* DrawingTypes[5] = { "OFF",  "2D", "2D Filled", "3D", "Corners" };

char* espBoneNames[14] = {
	"j_helmet", "j_neck", "j_head", "j_ankle_le",
	"j_ankle_ri", "j_wrist_le", "j_wrist_ri",
	"j_mainroot", "j_knee_le", "j_knee_ri",
	"j_elbow_le", "j_elbow_ri", "j_shoulder_le",
	"j_shoulder_ri"
};

char* bonesESP[26] = {
	"j_helmet", "j_head", "j_neck",
	"j_shoulder_le", "j_elbow_le", "j_wrist_le", "j_elbow_le", "j_shoulder_le", "j_neck",
	"j_shoulder_ri", "j_elbow_ri", "j_wrist_ri", "j_elbow_ri", "j_shoulder_ri", "j_neck",
	"j_spineupper", "j_spinelower",
	"j_hip_le", "j_knee_le", "j_ankle_le", "j_knee_le", "j_hip_le",
	"j_spinelower",
	"j_hip_ri", "j_knee_ri", "j_ankle_ri"
};

float GetBoxWidth(int value)
{
	if (value & 0x8)
		return 35;
	else return 17;
}

float GetBoxHeight(int value)
{
	if (value & 0x8)
		return 25;
	else if (value & 0x4)
		return 55;
	else return 70;
}

void CalcBoundingBox(int index, color Color)
{
	vec2 corner2, corner3, corner4, corner5, corner6, corner7, vMins, vMaxes;

	vec3 Mins(999999.0f, 999999.0f, 999999.0f), Maxes(-999999.0f, -999999.0f, -999999.0f);

	vec3 BonePos[14];
	for (int t = 0; t < ARRAYSIZE(espBoneNames) - 1; t++)
	{
		vec3* Bones;
		BonePos[t] = Game::GetTagPos(&centity[index], SL_GetString(espBoneNames[t], 0));
		Bones = &BonePos[t];

		if (Bones->x < Mins.x)
			Mins.x = Bones->x;
		if (Bones->y < Mins.y)
			Mins.y = Bones->y;
		if (Bones->z < Mins.z)
			Mins.z = Bones->z;
		if (Bones->x > Maxes.x)
			Maxes.x = Bones->x;
		if (Bones->y > Maxes.y)
			Maxes.y = Bones->y;
		if (Bones->z > Maxes.z)
			Maxes.z = Bones->z;
	}

	vec3 crnr2 = vec3(Maxes.x, Mins.y, Mins.z);
	vec3 crnr3 = vec3(Maxes.x, Mins.y, Maxes.z);
	vec3 crnr4 = vec3(Mins.x, Mins.y, Maxes.z);
	vec3 crnr5 = vec3(Mins.x, Maxes.y, Maxes.z);
	vec3 crnr6 = vec3(Mins.x, Maxes.y, Mins.z);
	vec3 crnr7 = vec3(Maxes.x, Maxes.y, Mins.z);
	vec3 mins = vec3(Mins);
	vec3 maxes = vec3(Maxes);

	int checksPassed = 0;
	checksPassed += !Game::WorldToScreen(crnr2, corner2);
	checksPassed += !Game::WorldToScreen(crnr3, corner3);
	checksPassed += !Game::WorldToScreen(crnr4, corner4);
	checksPassed += !Game::WorldToScreen(crnr5, corner5);
	checksPassed += !Game::WorldToScreen(crnr6, corner6);
	checksPassed += !Game::WorldToScreen(crnr7, corner7);
	checksPassed += !Game::WorldToScreen(mins, vMins);
	checksPassed += !Game::WorldToScreen(maxes, vMaxes);

	if (checksPassed == 0)
	{
		//mins to 2, 4, and 6
		Render::DrawLine(vMins.x, vMins.y, corner2.x, corner2.y, 1.0f, Color, CG::dwWhite);
		Render::DrawLine(vMins.x, vMins.y, corner4.x, corner4.y, 1.0f, Color, CG::dwWhite);
		Render::DrawLine(vMins.x, vMins.y, corner6.x, corner6.y, 1.0f, Color, CG::dwWhite);
		//maxes to 3, 5, and 7
		Render::DrawLine(vMaxes.x, vMaxes.y, corner3.x, corner3.y, 1.0f, Color, CG::dwWhite);
		Render::DrawLine(vMaxes.x, vMaxes.y, corner5.x, corner5.y, 1.0f, Color, CG::dwWhite);
		Render::DrawLine(vMaxes.x, vMaxes.y, corner7.x, corner7.y, 1.0f, Color, CG::dwWhite);
		//from 2 to 3 and 7
		Render::DrawLine(corner2.x, corner2.y, corner3.x, corner3.y, 1.0f, Color, CG::dwWhite);
		Render::DrawLine(corner2.x, corner2.y, corner7.x, corner7.x, 1.0f, Color, CG::dwWhite);
		//from 4 to 3 and 5
		Render::DrawLine(corner4.x, corner4.y, corner3.x, corner3.y, 1.0f, Color, CG::dwWhite);
		Render::DrawLine(corner4.x, corner4.y, corner5.x, corner5.y, 1.0f, Color, CG::dwWhite);
		//from 6 to 5 and 7
		Render::DrawLine(corner6.x, corner6.y, corner5.x, corner5.y, 1.0f, Color, CG::dwWhite);
		Render::DrawLine(corner6.x, corner6.y, corner7.x, corner7.y, 1.0f, Color, CG::dwWhite);
	}
}

void Visuals::DrawESPBox(color color, int Index, int currentType) {
	float fHeight, fWidth;
	vec3 HeadPos;
	vec2 FeetLocation, HeadLocation;
	if (currentType != BOX_TYPE_OFF) {
		if (currentType == BOX_TYPE_CORNERS) //Corners
		{
			HeadPos = Game::GetTagPos(&centity[Index], SL_GetString("j_head", 0));

			if (Game::WorldToScreen(centity[Index].Origin, FeetLocation) && Game::WorldToScreen(HeadPos, HeadLocation))
			{
				fHeight = FeetLocation.y - HeadLocation.y;
				if (*(int*)((DWORD)&centity[Index] + 0x1D4) & 0x08)
					fWidth = fHeight / 0.9;
				else
					fWidth = fHeight / 2;

				Render::DrawBox((FeetLocation.x - (fWidth / 2)), (FeetLocation.y - fHeight), (fWidth / 4), 1, color);
				Render::DrawBox((FeetLocation.x - (fWidth / 2)), FeetLocation.y, (fWidth / 4), 1, color);
				Render::DrawBox((FeetLocation.x - (fWidth / 2)), (FeetLocation.y - fHeight), 1, (fHeight / 4), color);
				Render::DrawBox((FeetLocation.x + (fWidth / 2)), (FeetLocation.y - fHeight), 1, (fHeight / 4), color);
				Render::DrawBox((FeetLocation.x + ((fWidth / 2) - (fWidth / 4))), (FeetLocation.y - fHeight), (fWidth / 4), 1, color);
				Render::DrawBox((FeetLocation.x + ((fWidth / 2) - (fWidth / 4))), FeetLocation.y, (fWidth / 4), 1, color);
				Render::DrawBox((FeetLocation.x - (fWidth / 2)), (FeetLocation.y - (fHeight / 4)), 1, (fHeight / 4), color);
				Render::DrawBox((FeetLocation.x + (fWidth / 2)), (FeetLocation.y - (fHeight / 4)), 1, (fHeight / 4), color);

			}
		}
		else if (currentType == BOX_TYPE_2D || BOX_TYPE_2D_FILLED) //2D
		{

			vec3 MainRoot, Feet;
			vec2 MainRootOut, FeetOut;
			MainRoot = Game::GetTagPos(&centity[Index], SL_GetString("j_mainroot", 0));
			MainRoot.z += 10;

			int BoxHeight = 55; // 8 or 0x0A = prone|| 4 or 6 = crouched||0 or 2 = standing
			if (*(int*)((DWORD)&centity[Index] + 0x1D4) & 0x08)
				BoxHeight = 17;
			else if (*(int*)((DWORD)&centity[Index] + 0x1D4) & 0x04)
				BoxHeight = 35;

			Feet.x = MainRoot.x; Feet.y = MainRoot.y; Feet.z = (MainRoot.z - -BoxHeight - 10);

			if (Game::WorldToScreen(MainRoot, MainRootOut) == TRUE && Game::WorldToScreen(Feet, FeetOut) == TRUE)
			{
				FLOAT Height = (MainRootOut.y - FeetOut.y);
				FLOAT Width = (Height / 3.0f);

				if (currentType == BOX_TYPE_2D_FILLED) {
					R_AddCmdDrawStretchPic((MainRootOut.x - Width), (MainRootOut.y - (Height*0.5f)), Width*2.0f, Height*1.5f, 0.0f, 0.0f, 0.0f, 0.0f, color, CG::dwWhite);
				}
				else {
					Render::DrawLine((int)(MainRootOut.x - Width), (int)(MainRootOut.y - Height * 0.5f), (int)(MainRootOut.x - Width), (int)(MainRootOut.y + Height), 1.0f, color, CG::dwWhite); // Left side line
					Render::DrawLine((int)(MainRootOut.x - Width), (int)(MainRootOut.y - Height * 0.5f), (int)(MainRootOut.x + Width), (int)(MainRootOut.y - Height * 0.5f), 1.0f, color, CG::dwWhite); // Bottom line
					Render::DrawLine((int)(MainRootOut.x + Width), (int)(MainRootOut.y - Height * 0.5f), (int)(MainRootOut.x + Width), (int)(MainRootOut.y + Height), 1.0f, color, CG::dwWhite); // Right side line
					Render::DrawLine((int)(MainRootOut.x - Width), (int)(MainRootOut.y + Height), (int)(MainRootOut.x + Width), (int)(MainRootOut.y + Height), 1.0f, color, CG::dwWhite); // Top line
				}
			}
		}
		else if (currentType == BOX_TYPE_3D) //3D
		{
			CalcBoundingBox(Index, color);
		}
	}
}

void Visuals::DrawBones(int clientNum, color color) {
    vec3 TagPos[2];
    vec2 TagScreen[2];

    for (int b = 0; b < ARRAYSIZE(bonesESP) - 1; b++) {
        TagPos[0] = Game::GetTagPos(&centity[clientNum], SL_GetString(bonesESP[b], 0));
        TagPos[1] = Game::GetTagPos(&centity[clientNum], SL_GetString(bonesESP[b + 1], 0));

        if (TagPos[0] == vec3() || TagPos[1] == vec3()) {
            return;  // Exit if positions are invalid
        }

        if (Game::WorldToScreen(TagPos[0], TagScreen[0]) && Game::WorldToScreen(TagPos[1], TagScreen[1])) {
            // Draw the line between the two screen coordinates using the specified color
            Render::DrawLine(TagScreen[0].x, TagScreen[0].y, TagScreen[1].x, TagScreen[1].y, 2.0f, color, CG::dwWhite);
        }
    }
}


void Visuals::DrawESP(int clientNum, color colorESP) {
	DrawESPBox(colorESP, clientNum, CG::dwESPBoxType);

	vec2 FeetLocation, HeadLocation;

	if (Game::WorldToScreen(centity[clientNum].Origin, FeetLocation) && Game::WorldToScreen(Game::GetTagPos(&centity[clientNum], SL_GetString("j_head", 0)), HeadLocation)) {
		float fontSize = 0.75f;

		if (CG::dwESPName) {
			char* nameTag = va("%s", cg->clientInfo[clientNum].clientName);

			if (nameTag && strlen(nameTag) > 0) {
				Render::DrawString(nameTag, FeetLocation.x, HeadLocation.y - 3, CG::dwSmallFont, 0.7f, colorESP, JustifyCenter);
			}
		}

		if (CG::dwESPDistance) {
			Render::DrawString(va("%.1fm", Utilities::GetDistance(cg->refDef.viewOrigin, centity[clientNum].Origin) / 100), FeetLocation.x, FeetLocation.y + 18, CG::dwSmallFont, 0.7f, colorESP, JustifyCenter);
		}

		
		if (CG::dwESPBones) {
    bool bIsEnemy = Game::IsEnemy(clientNum);
    color espColor = colorEnemy;  // Default to enemy color

    // Determine the correct color based on whether the player is an enemy or friendly
    if (bIsEnemy) {
        if (pInfo[clientNum].Prioritized)
            espColor = colorPrioritized;
        else if (pInfo[clientNum].Whitelisted)
            espColor = colorWhitelisted;
        else if (pInfo[clientNum].Wallbangable)
            espColor = colorWallbangable;
        else if (pInfo[clientNum].Visible)
            espColor = colorVisible;
        else
            espColor = colorEnemy;  // Default enemy color if no other condition is met
    } else {
        espColor = colorFriendly;  // Friendly color
    }

    // Call DrawBones with the determined color
    DrawBones(clientNum, espColor);
}




		if (CG::dwESPWeapon) {
			float aspectX, aspectY;
			int WeaponIcon = Game::GetWeaponIcon(centity[clientNum].weaponNum, &aspectX, &aspectY);
			if (WeaponIcon != 0 && MmIsAddressValid((DWORD*)WeaponIcon)) {
				CG_DrawRotatedPicPhysical(Security->addrs.ScreenPlacement, FeetLocation.x - (aspectX / 2), FeetLocation.y + (aspectY / 2) + 6, aspectX, aspectY, 0.0, colorESP, WeaponIcon);
			}
		}

		if (CG::dwSnaplines)
			Render::DrawLine((cg->refDef.Width / 2), cgs->Height, FeetLocation.x, FeetLocation.y, 1, colorESP, CG::dwWhite);
	}
}

void Visuals::HandleVisuals() {
	Structs::UpdateStructures();

	if (Game::UserInGame()) {
		if (CG::dwESPDrawCrosshair) {
			if (UIItems.submenu == CLOSED) {
				
				Render::DrawLine((cg->refDef.Width / 2) - 10, cg->refDef.Height / 2, (cg->refDef.Width / 2) + 10, cg->refDef.Height / 2, 2, colorBackground, CG::dwWhite);
				Render::DrawLine(cg->refDef.Width / 2, (cg->refDef.Height / 2) - 10, cg->refDef.Width / 2, (cg->refDef.Height / 2) + 10, 2, colorBackground, CG::dwWhite);
			}
		}

		for (int i = 0; i < cgs->MaxClients; i++) {
			if (cg->clientNumber != i && centity[i].ClientNumber != cg->clientNumber) {
				if (centity[i].eType != 1)
					continue;

				if ((*(int*)((DWORD)&centity[i] + 0x36C) & 0x40000000) == 0 || (*(int*)((DWORD)&centity[i] + 0x1D4) & 0x40000))
					continue;

				bool bIsEnemy = Game::IsEnemy(i);
				color espColor = colorEnemy;

				if (bIsEnemy) {
					if (pInfo[i].Prioritized)
						espColor = colorPrioritized;
					else if (pInfo[i].Whitelisted)
						espColor = colorWhitelisted;
					else if (pInfo[i].Wallbangable)
						espColor = colorWallbangable;
					else if (pInfo[i].Visible)
						espColor = colorVisible;
					else
						espColor = colorEnemy;
				}
				else {
					espColor = colorFriendly;
				}

				if ((CG::dwESPDrawAllies && !bIsEnemy) || (CG::dwESPDrawAxis && bIsEnemy)) {
					DrawESP(i, espColor);
				}
			}
		}
	}
}