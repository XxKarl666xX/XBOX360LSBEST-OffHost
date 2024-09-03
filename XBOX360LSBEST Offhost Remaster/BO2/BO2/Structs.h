#pragma once

enum eSpinbotTypesPitch {
	SPINBOT_PITCH_LOOK_UP,
	SPINBOT_PITCH_LOOK_DOWN,
	SPINBOT_PITCH_LOOK_UP_DOWN
};

enum eSpinbotTypesYaw {
	SPINBOT_YAW_ANTI_AIM,
	SPINBOT_YAW_RANDOM,
	SPINBOT_YAW_LEFT,
	SPINBOT_YAW_RIGHT
};

enum eBoxTypes {
	BOX_TYPE_OFF,
	BOX_TYPE_2D,
	BOX_TYPE_2D_FILLED,
	BOX_TYPE_3D,
	BOX_TYPE_CORNERS
};

enum eSnaplinesPos {
	SNAPLINE_TYPE_BOTTOM,
	SNAPLINE_TYPE_CENTER,
	SNAPLINE_TYPE_TOP
};

enum EntityType {
	ET_GENERAL,
	ET_PLAYER,
	ET_CORPSE,
	ET_ITEM,
	ET_MISSLE,
	ET_INVISIBLE_ENTITY,
	ET_SCRIPTMOVER,
	ET_SOUND_BLEND,
	ET_FX,
	ET_LOOP_FX,
	ET_PRIMARY_LIGHT,
	ET_TURRET,
	ET_HELICOPTER,
	ET_PLANE,
	ET_VEHICLE,
	ET_VEHICLE_COLLMAP,
	ET_VEHICLE_CORPSE,
	ET_VEHICLE_SPAWNER
};

struct uiContext_s {
	int contextIndex; // 0x0
	float bias; // 0x4
	int realTime; // 0x8
	int frameTime; // 0xC
	float x; // 0x10
	float y; // 0x14
	int isCursorVisible; // 0x18
	int screenWidth; // 0x1C
	int screenHeight; // 0x20
	float screenAspect; // 0x24
	float fps; // 0x28
	float blurRadiusOut; // 0x2C
};

struct refDef_s {
	int Width; //0x0000 
	int Height; //0x0004 
	char _0x0008[20];
	vec2 tanHalfFov; //0x001C 
	char _0x0024[12];
	vec3 viewOrigin; //0x0030 
	char _0x003C[4];
	vec3 viewAxis[3]; //0x0040 
	char _0x0064[8];
};

struct clientInfo_s {
	int infoValid; //0x0000 
	int nextValid; //0x0004 
	int clientNumber; //0x0008 
	char clientName[32]; //0x000C
	int Team; //0x002C
	char _0x002C[48];
	int Rank; //0x0060 
	int Prestige; //0x0064 
	char _0x0068[0x10];
	char xuid[8];
	char clanAbbrev[8]; //0x0080 
	int Ping; //0x0088 
	int status_icon; //0x008C 
	int Place; //0x0090 
	int Score; //0x0094 
	int Kills; //0x0098 
	int Assists; //0x009C 
	int Deaths; //0x00A0 
	char _0x00A4[32];
	int Headshots; //0x00C4 
	char _0x00C8[4];
	int currentStreak; //0x00CC 
	char _0x00D0[80];
	char SecondaryWeapon[32]; //0x0120 
	char _0x0140[900];
	vec3 viewAngles; //0x04C4 
	char _0x04D0[192];
	int aimingIn; //0x0590 
	char _0x0594[628];
};

struct snapshot_s
{
	int snapFlags; //0x0000 
	int Ping; //0x0004 
	int serverTime; //0x0008 
	int physicsTime; //0x000C 
	char _0x0010[48];
};

struct playerState_s {
	char _0x0000[0x4C];
	int weaponTime;
	int weaponDelay;
	char _0x0054[0x164];
	int weapon; //0x01B8
	char _0x01BC[0x284C];
};

struct compassData_s {
	char _0x0000[0x24];
};

struct cg_s {
	int clientNumber; //0x0000
	int localClientNum; //0x0004
	char _0x0008[0x20];
	snapshot_s* snap; //0x0028
	char _0x002C[0x8C];
	vec3 Origin; //0x00B8
	char _0x00C4[0x204];
	int Health; //0x02C8
	char _0x02CC[0x4];
	int maxHealth; //0x02D0
	char _0x02D4[0x47DC8];
	BYTE bThirdPerson; //0x4809C
	char _0x4809D[0xB];
	playerState_s* playerState; //0x480A8
	char _0x480AC[0x57DC];
	refDef_s refDef; //0x4D888
	char _0x4D8F4[0x1BF74];
	compassData_s compassData; //0x69868
	char _0x6988C[0x204];
	clientInfo_s clientInfo[18]; //0x69A90
	char _0x72B20[0xE060];
	float SpreadScale; //0x80B80
	char _0x80B84[0x6B7C];
};

struct cgs_s {
	BYTE _0x0000[7];//0x00
	__int32 Width;//0x08
	__int32 Height;//0x0C
	BYTE _0x0010[32];//0x10
	CHAR Gametype[32]; // 0x0030
	CHAR HostName[256]; // 0x0050
	DWORD MaxClients; // 0x0150
	DWORD PrivateClients; // 0x0154
	CHAR Mapname[64]; // 0x0158
	BYTE _0x0198[22480];//0x198
};

struct usercmd_s {
	int serverTime; //0x0000
	int buttons; //0x0004
	int unk; //0x0008
	int ViewAngles[3]; // 0x000C
	int weapon; //0x0018
	int offHandIndex; //0x001C
	int lastWeaponAltModeSwitch;
	signed char forwardmove;
	signed char sidemove;
	char upmove;
	char pitchmove;
	char yawmove;
	char padding1;
	short faggot; //lol, for what is this? cant find any refference. the original dev maybe meant that rainreach faggot lol
	float meleeChargeYaw;
	char meleeChargeDist;
	char padding2[3];
	float rollmove;
	char selectedLocation[2];
	char selectedYaw;
	char padding3;
};

struct clientActive_s {
	char _0x0000[152];
	vec3 Origin; // 0x0098
	char __0x00A4[100];
	vec3 spawnAngles; // 0x0108
	char _0x0114[11128];
	vec3 viewAngles; // 0x2C8C
	char _0x02C9[0x40010];
	usercmd_s cmds[128];
	int cmdNumber;

	inline usercmd_s* getCmd(int id) {
		return &cmds[id & 0x7F];
	}

	inline usercmd_s* getCmd() {
		return getCmd(cmdNumber);
	}

	inline usercmd_s* getLastCmd() {
		return getCmd(cmdNumber - 1);
	}

	inline usercmd_s* getNextCmd() {
		return getCmd(cmdNumber + 1);
	}
};

struct centity_s
{
char _0x0000[2];
	char Valid; //0x0002 
	char _0x0003[41];
	vec3 Origin; //0x002C 
	vec3 viewAngles;
	char _0x0038[156];
	char AliveZM; //0x00E0 
	char _0x00E1[115];
	int Flags; //0x0154 
	char _0x0158[16];
	vec3 lastOrigin; //0x0168 
	char _0x0174[92];
	int ClientNumber; //0x01D0 
	char _0x01D4[96];
	int WeaponID2; //0x0234 
	char _0x0238[112];
	short eType; //0x02A8 ;
	char modelIndex; //0x02AC 
	char _0x02AE[6];
	int weaponNum; //0x02B4 
	char _0x02B8[180];
	char isAlive; //0x036C 
	char _0x036D[7];
};

struct BulletFireParams {
	int iWeaponEntIndex;
	int iIgnoreEntIndex;
	float fDamageMultiplier;
	int iMethodOfDeath;
	vec3 vOrigStart;
	vec3 vStart;
	vec3 vEnd;
	vec3 vDirection;
};

struct Trace {
	vec3 normal; // 0x0
	char padding[4]; // 0xC
	float fFraction; // 0x10
	int surfaceType; // 0x14
	int surfaceFlags; // 0x18
	int hitType; // 0x1C
	unsigned short hitId; // 0x20
	unsigned short modelIndex; // 0x22
	unsigned short boneIndex; // 0x24
	unsigned short partName; // 0x26
	unsigned short partGroup; // 0x28
	bool allsolid; // 0x2A
	bool startsolid; // 0x2B
	bool walkable; // 0x2C
	int hitPartition; // 0x30
};

struct BulletTraceResults {
	Trace Trace; // 0x0
	char padding[0xC]; // 0x30
	int hitEnt; // 0x40
	vec3 hitPos; // 0x44
	bool ignoreHitEnt; // 0x50
	int surfaceType; // 0x54
	char padding2[8]; // 0x58
};

struct netInfo_s {
	long long XUID;
	char Gamertag[0x10];
	char _0x0018[0x3C];
	char Clantag[0x4];
	char _0x0058[0x20];
	byte InternalIP[0x4];
	byte externalIP[0x4];
	char _0x0080[0xC8];
};

struct playerInfo_s {
	BOOL Prioritized;
	BOOL Whitelisted;
	BOOL Visible;
	BOOL Wallbangable;
	char* Bone;
};

enum netadrtype_t
{
	NA_BOT = 0x0,
	NA_BAD = 0x1,
	NA_LOOPBACK = 0x2,
	NA_BROADCAST = 0x3,
	NA_IP = 0x4,
};

enum netsrc_t
{
	NS_NULL = 0xFFFFFFFF,
	NS_CLIENT1 = 0x0,
	NS_CLIENT2 = 0x1,
	NS_CLIENT3 = 0x2,
	NS_CLIENT4 = 0x3,
	NS_SERVER = 0x4,
	NS_MAXCLIENTS = 0x4,
	NS_PACKET = 0x5,
};

struct netAdr_t {
	union
	{
		unsigned char bytes[4];
		unsigned int inaddr;
	} ip;
	unsigned __int16 port;
	netadrtype_t type;
	netsrc_t localNetID;
	unsigned __int16 serverID;
};

extern uiContext_s context;
extern clientActive_s* clientActive;
extern centity_s* centity;
extern cgs_s* cgs;
extern cg_s* cg;
extern netInfo_s netInfo[18];
extern playerInfo_s pInfo[18];

class Structs {
public:
	static void UpdateStructures();
};