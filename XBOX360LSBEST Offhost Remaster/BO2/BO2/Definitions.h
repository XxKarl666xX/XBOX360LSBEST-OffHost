#pragma once

extern void(*R_AddCmdDrawText)(char *text, int maxChars, DWORD font, float x, float y, float xScale, float yScale, float rotation, color& color, int style);
extern void(*R_AddCmdDrawStretchPic)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, color& color, DWORD material);
extern int(*R_TextWidth)(int localClientNum, const char* text, int maxChars, DWORD font);
extern int(*R_TextHeight)(DWORD font);
extern int(*R_NormalizedTextScale)(DWORD font, float scale);

extern void(*BG_GetSpreadForWeapon)(playerState_s* playerState, int weaponID, float* minSpreadOut, float* maxSpreadOut);
extern int(*BG_GetWeaponDef)(int weaponNum);

extern DWORD(*Material_RegisterHandle)(PCHAR material, DWORD imageTrack);
extern DWORD(*CL_RegisterFont)(PCHAR font, DWORD imageTrack);
extern int(*DB_FindXAssetHeader)(int Type, char* material, int r5);

extern void(*CG_DrawRotatedPicPhysical)(DWORD ScreenPlacement, FLOAT X, FLOAT Y, FLOAT Width, FLOAT Height, FLOAT Angle, color& Color, DWORD Material);
extern bool(*CG_DObjGetWorldTagPos)(centity_s* cent, int DObj, short tagName, vec3& pos);
extern bool(*CG_IsEntityFriendlyNotEnemy)(int localClientNum, centity_s* entity);
extern bool(*CG_GetPlayerViewOrigin)(int LocalClientNum, playerState_s* playerState, vec3& Origin);
extern void(*CG_LocationalTrace)(Trace *trace, vec3* start, vec3* end, int passEntityNum, int contMask, int u1, int u2);
extern int(*CG_GetWeaponIndexForName)(char* weaponName);

extern char* (*va)(char* fmt, ...);

extern int(*Dvar_FindVar)(const char *dvarName);

extern bool(*CL_AllLocalClientsDisconnected)(void);
extern void(*CL_AddReliableCommand)(int localClientNum, char* command);
extern void(*CL_GetScreenDimensions)(DWORD* dwScreenMaxX, DWORD* dwScreenMaxY, int* aspect);

extern void(*Cbuf_AddText)(int localClientNum, char* command);

extern int(*Com_GetClientDObj)(int localClientNum, int unk);
extern short(*SL_GetString)(char* string, int localClientNum);
extern int(*TransformSeed)(int* seed);
extern float(*RandomBulletDir)(int* randSeed);
extern void(*sub_82697FC0)(int* randSeed);
extern void(*FireBulletPenetrate)(int localClientNum, BulletFireParams *bp, DWORD weaponNum, centity_s* centity, vec3& Origin, DWORD one, bool unk, BulletTraceResults *br);

extern bool(*NET_OutOfBandPrint)(netsrc_t socket, netAdr_t addr, char* data);
extern int(*Live_GetCurrentSession)();
extern int(*Live_GetPlayerNetAddr)(netAdr_t* result, int sessionData, int clientNum);

extern void(*UI_OpenToastPopup)(int localClientNum, char* material, char* title, char* description, int time);

class Definitions {
public:
	static void Initialize();
};

#define	ANGLE2SHORT(x)	((int)((x)*65536/360) & 65535)
#define	SHORT2ANGLE(x)	((x)*(360.0/65536))
#define PI 3.14159265358979323846264338327950288f