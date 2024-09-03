#include "stdafx.h"
#include "functions.h"
#include "setupgames.h"
#include "bo2_AdressHelper.h"
#include "util.h"

namespace GameSetup
{
	void StopHooks()
	{
		for (int i = 0; i < ARRAYSIZE(Hooks); i++)
			Hooks[i].Stop();
	}

	void CleanHooks()
	{
		for (int i = 0; i < ARRAYSIZE(Hooks); i++)
			Hooks[i].Clean();
	}

	void StartHooks()
	{
		for (int i = 0; i < ARRAYSIZE(Hooks); i++)
			Hooks[i].Start();
	}

	void Uninit()
	{
		StopHooks();
	}

	
	void BO2_Init()
	{
		CleanHooks();

		
			XNotify("Appendum - BO2 Multiplayer/Zombies [Detected]");

			BO2MP::InitOffHost();

			*(int*)0x8259A65C = 0x60000000; //challenge log
			*(int*)0x82497EB0 = 0x60000000; //call protection
			*(int*)0x82497F30 = 0x60000000; //cheat protection
			*(int*)0x82497EE0 = 0x60000000; //write protection
			*(int*)0x82497EC8 = 0x60000000; //read protection

			*(int*)0x826A5FBC = 0x60000000; //infinite class items (0x7F43D214)

			Hooks[0] = Hook(AuthProvider::GetAddress(BO2_MP_TU18_XamInputGetState), (unsigned long)BO2MP::XamInputGetState_Hook, false);
			Hooks[1] = Hook(AuthProvider::GetAddress(BO2_MP_TU18_Menu_PaintAll), (unsigned long)BO2MP::Menu_PaintAll_Hook, true);
			Hooks[2] = Hook(AuthProvider::GetAddress(BO2_MP_TU18_CL_ReadyToSendPacket), (unsigned long)BO2MP::CL_ReadyToSendPacket_Hook, true);

			Hooks[4] = Hook(AuthProvider::GetAddress(BO2_MP_TU18_CL_Disconnect), (unsigned long)BO2MP::CL_Disconnect_Hook, true);
			Hooks[5] = Hook(AuthProvider::GetAddress(BO2_MP_TU18_LiveStats_Probation_GiveProbation), (unsigned long)BO2MP::LiveStats_Probation_GiveProbation_Hook, true);
			Hooks[6] = Hook(0x8226AE80, (unsigned long)BO2MP::CL_ConsolePrint_Hook, true);
			Hooks[7] = Hook(0x82267520, (unsigned long)BO2MP::CL_ConsolePrint_AddLine_Hook, true);
		
		

		StartHooks();
	}

	

}
