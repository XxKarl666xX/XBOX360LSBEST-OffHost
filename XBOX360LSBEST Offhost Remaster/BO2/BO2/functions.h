#pragma once

#include "stdafx.h"


namespace BO2MP
{
	void InitOffHost();

	DWORD XamInputGetState_Hook(int userIndex, int flags, PXINPUT_STATE pState);
	void Menu_PaintAll_Hook(int r3);
	void CL_ReadyToSendPacket_Hook(int localClientNum);
	void R_AddCmdDrawStretchPic_Hook(int r5, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, int f9, int f10);
	void CL_Disconnect_Hook(DWORD r3, QWORD r4);
	void LiveStats_Probation_GiveProbation_Hook(int controllerIndex, int gamemode, float time);
	void CL_ConsolePrint_Hook(int localClientNum, int channel, const char *txt, int duration, int pixelWidth, int flags);
	void CL_ConsolePrint_AddLine_Hook(int localClientNum, int channel, const char *txt, int duration, int pixelWidth, char color, int flags);
}