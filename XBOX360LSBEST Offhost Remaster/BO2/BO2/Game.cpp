#include "stdafx.h"
#include <string>

char OriginalGT[33];
char DefaultGT[33];
BOOL GTEntered = FALSE;
DWORD SigninState = eXamUserSigninState_NotSignedIn;
bool freshSignedIn = false;

bool Game::Dvar_GetBool(char *dvarName) {
	int dvar_t = Dvar_FindVar(dvarName);
	if (dvar_t == 0)
		return false;
	return *(bool*)(dvar_t + 0x18);
}

char* Game::Dvar_GetString(char *dvarName) {
	int dvar_t = Dvar_FindVar(dvarName);
	if (dvar_t == 0)
		return false;
	return (char*)(*(int*)(dvar_t + 0x18));
}

bool Game::UserInGame() {
	return (Dvar_GetBool("cl_ingame") && !CL_AllLocalClientsDisconnected());
}

bool Game::CheckIsMigrating() {
	return *(int*)(0x82C6FDC8 + 0x10) != 0;
}

bool Game::CheckInGame() {
	// Make sure we are connected to a game session
	CG::bConnected = !CL_AllLocalClientsDisconnected() ? TRUE : FALSE;

	// Check the cl_ingame dvar
	bool bInGame = Dvar_GetBool("cl_ingame");
	if (!bInGame) {
		if (CG::bQuittingGame) {
			CG::bQuittingGame = FALSE;
		}
	}

	// If we're in game and all local clients aren't disconnected, we're fully ingame.
	return bInGame && CG::bConnected && !CheckIsMigrating() && !CG::bQuittingGame;
}

void Game::LeaveGame() {
	Cbuf_AddText(0, "disconnect;");
}

void Game::EndGame() {
	Cbuf_AddText(0, va("cmd mr %i -1 endround;", *(int*)(Security->addrs.ServerID)));
}

bool Game::IsEnemy(int i) {
	return (!CG_IsEntityFriendlyNotEnemy(0, &centity[i]));
}

bool Game::WorldToScreen(vec3& WorldLocation, vec2& Screen) {
	vec3 Local = WorldLocation - cg->refDef.viewOrigin, Transform;
	Transform.x = Local.dot(cg->refDef.viewAxis[1]);
	Transform.y = Local.dot(cg->refDef.viewAxis[2]);
	Transform.z = Local.dot(cg->refDef.viewAxis[0]);

	if (Transform.z < 0.01)
	{
		return false;
	}

	Screen.x = (cg->refDef.Width / 2) * (1 - (Transform.x / cg->refDef.tanHalfFov.x / Transform.z));
	Screen.y = (cg->refDef.Height / 2) * (1 - (Transform.y / cg->refDef.tanHalfFov.y / Transform.z));

	return (Transform.z > 0);
}

vec3 Game::GetTagPos(centity_s* cent, short tag) {
	vec3 tagPos = vec3();
	int dobj = Com_GetClientDObj(cent->ClientNumber, 0);

	if (dobj == 0)
		return cent->Origin;

	if (CG_DObjGetWorldTagPos(cent, dobj, tag, tagPos)) {
		return tagPos;
	}

	return vec3();
}

void Game::FixTextForDistance(const char* text, float* x, float* y, DWORD font, float scale, vec3 worldPos, float* outDist) {
	float distanceSq = Utilities::GetDistance(cg->refDef.viewOrigin, worldPos);
	float distance = sqrt(distanceSq);
	float distFrac = (float)(distance - 64) / 448;
	float distScale = (float)(distFrac * scale) + (float)(1 - distFrac);
	*outDist = distFrac;

	float x2 = (float)(floor(-((((float)R_TextWidth(0, text, 0x7FFFFFFF, font) * R_NormalizedTextScale(font, scale * distScale)) * 0.5) - *x) + 0.5));

	__asm {
		frsp x2, x2
	}

	*x = x2;
	*y = (float)(floor(*y + 0.5));
}

void Game::getWeaponAspectRatio(DWORD killIconType, float *aspectWidth, float *aspectHeight) {
	float width = 1.4f, height = 1.4f;
	if (killIconType == 0) //1:1
	{
		width = 1.4f;
		height = 1.4f;
	}
	else if (killIconType == 1) //2:1
	{
		width = 2.8f;
		height = 1.4f;
	}
	else if (killIconType == 2) //3:1
	{
		width = 2.8f;
		height = 0.7f;
	}
	width *= 20.0f;
	height *= 20.0f;
	*aspectWidth = width;
	*aspectHeight = height;
}

int Game::GetWeaponIcon(int Weapon, float *aspectX, float *aspectY) {
	int weaponDef = BG_GetWeaponDef(Weapon);
	if (weaponDef) {
		DWORD weapDef2 = ((DWORD(*)(...))Security->addrs.BG_GetWeaponDef2)(Weapon);
		if (weapDef2) {
			DWORD killIconType = *(DWORD*)(*(DWORD*)(weapDef2 + 0x8) + 0x664);

			getWeaponAspectRatio(killIconType, aspectX, aspectY);
			return *(int*)(weaponDef + 0x3AC);
		}
	}
	return 0;
}

bool Game::IsClientVisible(int clientNum, short tag) {
	Trace trace;

	vec3 tagPos = GetTagPos(&centity[clientNum], tag);

	vec3 myPos;
	CG_GetPlayerViewOrigin(0, (playerState_s*)((DWORD)cg + 0x480A8), myPos);

	CG_LocationalTrace(&trace, &myPos, &tagPos, clientNum, 0x803003, 0, 0);

	return (trace.fFraction >= 0.95f);
}

int Game::GetNetInfoAddress(int index) {
	return (Security->addrs.strct_netInfo + (index * 0x200));
}

QWORD Game::GetXUIDFromNetInfo(int index, BOOL read) {
	if (read)
		return *(QWORD*)GetNetInfoAddress(index);
	return GetNetInfoAddress(index);
}

void Game::CacheSignInState() {
	for (int i = 0; i < 0x4; i++) {
		if (XamUserGetSigninState(i) == eXamUserSigninState_SignedInLocally)
			SigninState = eXamUserSigninState_SignedInLocally;
		else if (XamUserGetSigninState(i) == eXamUserSigninState_SignedInToLive)
			SigninState = eXamUserSigninState_SignedInToLive;
		else
			SigninState = eXamUserSigninState_NotSignedIn;
	}
}

bool Game::FixGamertag() {
	XUSER_SIGNIN_INFO userInfo; ZeroMemory(&userInfo, sizeof(XUSER_SIGNIN_INFO));
	if (XUserGetSigninInfo(0, XUSER_GET_SIGNIN_INFO_ONLINE_XUID_ONLY, &userInfo) == ERROR_SUCCESS)
	{
		strcpy(OriginalGT, userInfo.szUserName);
		strcpy(DefaultGT, userInfo.szUserName);

		strcpy((char*)Security->addrs.GT_Addrs[0], userInfo.szUserName);
		strcpy((char*)Security->addrs.GT_Addrs[1], userInfo.szUserName);
		return true;
	}
	return false;
}

string Game::BuildUserInfoString(string name, string clantag, string xuid) {
	string userInfoString;
	userInfoString = "userinfo \"\\rate\\20000\\snaps\\20\\name\\" + name;
	if (clantag != "")
		userInfoString += "\\clanAbbrev\\" + clantag;
	userInfoString += "\\xuid\\000" + xuid + "\\natType\\1\\rank\\1\\prestige\\0\"";
	return userInfoString;
}


void Game::ToggleNoRecoil(BOOL* bState) {
	DWORD dwNoRecoil = Security->addrs.NoRecoil;
	
	if (dwNoRecoil) {
		if (*bState) {
			*(DWORD*)dwNoRecoil = 0x60000000;
			
		}
		else {
			*(DWORD*)dwNoRecoil = 0x48461341;
		}
	}
}

void Game::ToggleNoSway(BOOL* bState) {
	DWORD dwNoSway = Security->addrs.NoSway1;
	if (dwNoSway) {
		if (*bState) {
			*(DWORD*)dwNoSway = 0x60000000;
		}
		else {
			*(DWORD*)dwNoSway = 0x4BFFE975;
		}
	}
}

void Game::ToggleVSAT(BOOL* bState) {
	DWORD dwVSAT = Security->addrs.Radar;
	if (dwVSAT) {
		if (*bState) {
			*(DWORD*)dwVSAT = 0x60000000;
		}
		else {
			*(DWORD*)dwVSAT = 0x419A0060;
		}
	}
}

void Game::ToggleThirdPerson(BOOL* bState) {
	DWORD dwThirdPerson = ((DWORD)cg + 0x4809C);
	if (MmIsAddressValid((PVOID)dwThirdPerson)) {
		if (*bState)
			*(BYTE*)dwThirdPerson = 1;
		else
			*(BYTE*)dwThirdPerson = 0;
	}
}

void Game::SetFOV(FLOAT fFov) {
	*(float*)(*(int*)(Security->addrs.FOV) + 0x18) = fFov;
}

void Game::SendCommand(int clientNum, char* command) {
	netAdr_t netAdr = netAdr_t();
	memset(&netAdr, 0x00, sizeof(netAdr_t));

	Live_GetPlayerNetAddr(&netAdr, Live_GetCurrentSession(), clientNum);

	NET_OutOfBandPrint(NS_SERVER, netAdr, command);
}

void Game::OffhostKick(int clientNum) {
	SendCommand(clientNum, "connectResponseMigration"); //for the offhost kick
}

void Game::GiveMigrationScreen(int clientNum) {
	SendCommand(clientNum, "mstart"); //for the offhost migration
}


