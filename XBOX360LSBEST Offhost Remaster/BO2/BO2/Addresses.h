#pragma once

struct addresses_s {
	/*[Hooks]*/
	DWORD SND_EndFrameHook;
	DWORD XamInputGetStateHook;
	DWORD CL_CreateNewCommandsHook;
	DWORD CL_SendCommandHook;

	/*[Game Functions]*/
	DWORD R_AddCmdDrawText;
	DWORD R_AddCmdDrawStretchPic;
	DWORD R_TextWidth;
	DWORD R_TextHeight;
	DWORD R_NormalizedTextScale;

	DWORD BG_GetSpreadForWeapon;
	DWORD BG_GetWeaponDef, BG_GetWeaponDef2;

	DWORD Material_RegisterHandle;
	DWORD CL_RegisterFont;
	DWORD DB_FindXAssetHeader;

	DWORD CG_DrawRotatedPicPhysical;
	DWORD CG_DObjGetWorldTagPos;
	DWORD CG_IsEntityFriendlyNotEnemy;
	DWORD CG_GetPlayerViewOrigin;
	DWORD CG_LocationalTrace;
	DWORD CG_GetWeaponIndexForName;

	DWORD va;

	DWORD Dvar_FindVar;

	DWORD CL_AllLocalClientsDisconnected;
	DWORD CL_AddReliableCommand;
	DWORD CL_GetScreenDimensions;

	DWORD Cbuf_AddText;

	DWORD Com_GetClientDObj;
	DWORD SL_GetString;
	DWORD TransformSeed;
	DWORD RandomBulletDir;
	DWORD sub_82697FC0;
	DWORD FireBulletPenetrate;

	DWORD NET_OutOfBandPrint;
	DWORD Live_GetCurrentSession;
	DWORD Live_GetPlayerNetAddr;

	DWORD UI_OpenToastPopup;

	/*[Game Addresses]*/
	DWORD ScreenPlacement;
	DWORD ServerID;
	DWORD NoRecoil;
	DWORD NoSway1;
	DWORD Radar;
	DWORD FOV;
	DWORD hostname;//test for hostname

	DWORD CrashFix;

	DWORD Autowall[8];

	DWORD EmptyMemory;
	DWORD XamGetUserName;
	DWORD ErrorPatch[2];
	DWORD GT_Addrs[2];

	/*[Structures]*/
	DWORD strct_uiContext;
	DWORD strct_clientActive;
	DWORD strct_centity;
	DWORD strct_cgArray;
	DWORD strct_cgsArray;
	DWORD strct_netInfo;
	DWORD strct_playerState;



};

extern void binToFile(const char* fname, PVOID dPtr, ULONG len);

class cSecurity {
public:
	BOOL bHasPatches;
	addresses_s addrs;

	BOOL SetAddresses() {
		/*[Hooks]*/
		addrs.SND_EndFrameHook = 0x828B9F58;
		addrs.XamInputGetStateHook = 0x827D8A48;
		addrs.CL_CreateNewCommandsHook = 0x82261A40;
		addrs.CL_SendCommandHook = 0x8225EAA8;

		/*[Game Functions]*/
		addrs.R_AddCmdDrawText = 0x828B8BA0;
		addrs.R_AddCmdDrawStretchPic = 0x828B86C0;
		addrs.R_TextWidth = 0x828B6FD8;
		addrs.R_TextHeight = 0x82490390;
		addrs.R_NormalizedTextScale = 0x828B6ED8;

		addrs.BG_GetSpreadForWeapon = 0x826BB4E0;
		addrs.BG_GetWeaponDef = 0x826BF988;
		addrs.BG_GetWeaponDef2 = 0x826BF970;

		addrs.Material_RegisterHandle = 0x828B78F0;
		addrs.CL_RegisterFont = 0x82275F78;
		addrs.DB_FindXAssetHeader = 0x822CAE50;

		addrs.CG_DrawRotatedPicPhysical = 0x821C7F58;
		addrs.CG_DObjGetWorldTagPos = 0x821D03F0;
		addrs.CG_IsEntityFriendlyNotEnemy = 0x821CD948;
		addrs.CG_GetPlayerViewOrigin = 0x822544B0;
		addrs.CG_LocationalTrace = 0x8225C568;
		addrs.CG_GetWeaponIndexForName = 0x826C06E8;

		addrs.va = 0x8249E440;

		addrs.Dvar_FindVar = 0x82496430;

		addrs.CL_AllLocalClientsDisconnected = 0x827504D0;
		addrs.CL_AddReliableCommand = 0x822786E0;
		addrs.CL_GetScreenDimensions = 0x82261D30;

		addrs.Cbuf_AddText = 0x824015E0;

		addrs.Com_GetClientDObj = 0x82414578;
		addrs.SL_GetString = 0x82533528;
		addrs.TransformSeed = 0x826961B8;
		addrs.RandomBulletDir = 0x82696250;
		addrs.sub_82697FC0 = 0x82697FC0;
		addrs.FireBulletPenetrate = 0x82258840;

		addrs.NET_OutOfBandPrint = 0x8241D580;
		addrs.Live_GetCurrentSession = 0x8259B878;
		addrs.Live_GetPlayerNetAddr = 0x825B70B8;

		addrs.UI_OpenToastPopup = 0x82454800;

		/*[Game Addresses]*/
		addrs.ScreenPlacement = 0x82CBC168;
		addrs.ServerID = 0x82C15758;

		addrs.NoRecoil = 0x82259BC8;
		addrs.NoSway1 = 0x826C6E6C;
		addrs.Radar = 0x821B8FD4;
		addrs.FOV = 0x82BC2774;
		

		addrs.CrashFix = 0x8295FFF8;

		addrs.Autowall[0] = 0x822DFB90;
		addrs.Autowall[1] = 0x82258520;
		addrs.Autowall[2] = 0x82257E30;
		addrs.Autowall[3] = 0x82258CE4;
		addrs.Autowall[4] = 0x82258FAC;
		addrs.Autowall[5] = 0x8225900C;
		addrs.Autowall[6] = 0x82258D60;
		addrs.Autowall[7] = 0x82259B40;

		addrs.EmptyMemory = 0x82C55D00;
		addrs.XamGetUserName = 0x8293D724;
		addrs.ErrorPatch[0] = 0x8259B6A7;
		addrs.ErrorPatch[1] = 0x822D1110;
		addrs.GT_Addrs[0] = 0x82C55D60;
		addrs.GT_Addrs[1] = 0x841E1B30;

		/*[Structures]*/
		addrs.strct_uiContext = 0x83BA29F0;
		addrs.strct_clientActive = 0x82C70F4C;
		addrs.strct_centity = 0x82BBC554;
		addrs.strct_cgArray = 0x82BBAE68;
		addrs.strct_cgsArray = 0x82BBAE44;
		addrs.strct_netInfo = 0x82CAC3A0;
		addrs.strct_playerState = 0x83551A10;

		bHasPatches = TRUE;
		return TRUE;
	}
};

extern cSecurity* Security;
extern MemoryManager *mManager;