#pragma once

extern char OriginalGT[33];
extern char DefaultGT[33];
extern BOOL GTEntered;
extern DWORD SigninState;
extern bool freshSignedIn;
class Game {
public:
	static bool Dvar_GetBool(char *dvarName);
	static char* Dvar_GetString(char *dvarName);
	static bool UserInGame();
	static bool CheckIsMigrating();
	static bool CheckInGame();
	static void LeaveGame();
	static void EndGame();
	static bool IsEnemy(int i);
	static bool WorldToScreen(vec3& WorldLocation, vec2& Screen);
	static vec3 GetTagPos(centity_s* cent, short tag);
	static void FixTextForDistance(const char* text, float* x, float* y, DWORD font, float scale, vec3 worldPos, float* outDist);
	static void getWeaponAspectRatio(DWORD killIconType, float *aspectWidth, float *aspectHeight);
	static int GetWeaponIcon(int Weapon, float *aspectX, float *aspectY);
	static bool IsClientVisible(int clientNum, short tag);
	static int GetNetInfoAddress(int index);
	static QWORD GetXUIDFromNetInfo(int index, BOOL read = FALSE);
	static void CacheSignInState();
	static bool FixGamertag();
	static string BuildUserInfoString(string name, string clantag, string xuid);
	static void ModGamertag();

	static void ToggleNoRecoil(BOOL* bState);
	static void ToggleNoSway(BOOL* bState);
	static void ToggleVSAT(BOOL* bState);
	static void ToggleThirdPerson(BOOL* bState);
	static void SetFOV(FLOAT fFov);

	static void SendCommand(int clientNum, char* command);
	static void OffhostKick(int clientNum);
	static void GiveMigrationScreen(int clientNum);
};