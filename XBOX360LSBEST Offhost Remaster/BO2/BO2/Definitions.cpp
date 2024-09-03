#include "stdafx.h"

void(*R_AddCmdDrawText)(char *text, int maxChars, DWORD font, float x, float y, float xScale, float yScale, float rotation, color& color, int style);
void(*R_AddCmdDrawStretchPic)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, color& color, DWORD material);
int(*R_TextWidth)(int localClientNum, const char* text, int maxChars, DWORD font);
int(*R_TextHeight)(DWORD font);
int(*R_NormalizedTextScale)(DWORD font, float scale);

void(*BG_GetSpreadForWeapon)(playerState_s* playerState, int weaponID, float* minSpreadOut, float* maxSpreadOut);
int(*BG_GetWeaponDef)(int weaponNum);

DWORD(*Material_RegisterHandle)(PCHAR material, DWORD imageTrack);
DWORD(*CL_RegisterFont)(PCHAR font, DWORD imageTrack);
int(*DB_FindXAssetHeader)(int Type, char* material, int r5);

void(*CG_DrawRotatedPicPhysical)(DWORD ScreenPlacement, FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, FLOAT Angle, color& Color, DWORD Material);
bool(*CG_DObjGetWorldTagPos)(centity_s* cent, int DObj, short tagName, vec3& pos);
bool(*CG_IsEntityFriendlyNotEnemy)(int localClientNum, centity_s* entity);
bool(*CG_GetPlayerViewOrigin)(int LocalClientNum, playerState_s* playerState, vec3& Origin);
void(*CG_LocationalTrace)(Trace *trace, vec3* start, vec3* end, int passEntityNum, int contMask, int u1, int u2);
int(*CG_GetWeaponIndexForName)(char* weaponName);

char* (*va)(char* fmt, ...);

int(*Dvar_FindVar)(const char *dvarName);

bool(*CL_AllLocalClientsDisconnected)(void);
void(*CL_AddReliableCommand)(int localClientNum, char* command);
void(*CL_GetScreenDimensions)(DWORD* dwScreenMaxX, DWORD* dwScreenMaxY, int* aspect);

void(*Cbuf_AddText)(int localClientNum, char* command);

int(*Com_GetClientDObj)(int localClientNum, int unk);
short(*SL_GetString)(char* string, int localClientNum);
int(*TransformSeed)(int* seed);
float(*RandomBulletDir)(int* randSeed);
void(*sub_82697FC0)(int* randSeed);
void(*FireBulletPenetrate)(int localClientNum, BulletFireParams *bp, DWORD weaponNum, centity_s* centity, vec3& Origin, DWORD one, bool unk, BulletTraceResults *br);

bool(*NET_OutOfBandPrint)(netsrc_t socket, netAdr_t addr, char* data);
int(*Live_GetCurrentSession)();
int(*Live_GetPlayerNetAddr)(netAdr_t* result, int sessionData, int clientNum);

void(*UI_OpenToastPopup)(int localClientNum, char* material, char* title, char* description, int time);

void Definitions::Initialize() {
	R_AddCmdDrawText = (void(*)(char *, int, DWORD, float, float, float, float, float, color&, int))Security->addrs.R_AddCmdDrawText;
	R_AddCmdDrawStretchPic = (void(*)(float x, float y, float width, float height, float xScale, float yScale, float xay, float yay, color& color, DWORD material))Security->addrs.R_AddCmdDrawStretchPic;
	R_TextWidth = (int(*)(int, const char*, int, DWORD))Security->addrs.R_TextWidth;
	R_TextHeight = (int(*)(DWORD))Security->addrs.R_TextHeight;
	R_NormalizedTextScale = (int(*)(DWORD, float))Security->addrs.R_NormalizedTextScale;

	BG_GetSpreadForWeapon = (void(*)(playerState_s*, int, float*, float*))Security->addrs.BG_GetSpreadForWeapon;
	BG_GetWeaponDef = (int(*)(int))Security->addrs.BG_GetWeaponDef;

	Material_RegisterHandle = (DWORD(*)(PCHAR, DWORD))Security->addrs.Material_RegisterHandle;
	CL_RegisterFont = (DWORD(*)(PCHAR, DWORD))Security->addrs.CL_RegisterFont;
	DB_FindXAssetHeader = (int(*)(int, char*, int))Security->addrs.DB_FindXAssetHeader;

	CG_DrawRotatedPicPhysical = (void(*)(DWORD, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, color&, DWORD))Security->addrs.CG_DrawRotatedPicPhysical;
	CG_DObjGetWorldTagPos = (bool(*)(centity_s*, int, short, vec3&))Security->addrs.CG_DObjGetWorldTagPos;
	CG_IsEntityFriendlyNotEnemy = (bool(*)(int, centity_s*))Security->addrs.CG_IsEntityFriendlyNotEnemy;
	CG_GetPlayerViewOrigin = (bool(*)(int, playerState_s*, vec3&))Security->addrs.CG_GetPlayerViewOrigin;
	CG_LocationalTrace = (void(*)(Trace*, vec3*, vec3*, int, int, int, int))Security->addrs.CG_LocationalTrace;
	CG_GetWeaponIndexForName = (int(*)(char*))Security->addrs.CG_GetWeaponIndexForName;

	va = (char*(*)(char*, ...))Security->addrs.va;

	Dvar_FindVar = (int(*)(const char*))Security->addrs.Dvar_FindVar;

	CL_AllLocalClientsDisconnected = (bool(*)(void))Security->addrs.CL_AllLocalClientsDisconnected;
	CL_AddReliableCommand = (void(*)(int, char*))Security->addrs.CL_AddReliableCommand;
	CL_GetScreenDimensions = (void(*)(DWORD*, DWORD*, int*))Security->addrs.CL_GetScreenDimensions;

	Cbuf_AddText = (void(*)(int, char*))Security->addrs.Cbuf_AddText;

	Com_GetClientDObj = (int(*)(int, int))Security->addrs.Com_GetClientDObj;
	SL_GetString = (short(*)(char*, int))Security->addrs.SL_GetString;
	TransformSeed = (int(*)(int*))Security->addrs.TransformSeed;
	RandomBulletDir = (float(*)(int*))Security->addrs.RandomBulletDir;
	sub_82697FC0 = (void(*)(int*))Security->addrs.sub_82697FC0;
	FireBulletPenetrate = (void(*)(int, BulletFireParams*, DWORD, centity_s*, vec3&, DWORD, bool, BulletTraceResults*))Security->addrs.FireBulletPenetrate;

	NET_OutOfBandPrint = (bool(*)(netsrc_t, netAdr_t, char*))Security->addrs.NET_OutOfBandPrint;
	Live_GetCurrentSession = (int(*)())Security->addrs.Live_GetCurrentSession;
	Live_GetPlayerNetAddr = (int(*)(netAdr_t*, int, int))Security->addrs.Live_GetPlayerNetAddr;

	UI_OpenToastPopup = (void(*)(int, char*, char*, char*, int))Security->addrs.UI_OpenToastPopup;
}