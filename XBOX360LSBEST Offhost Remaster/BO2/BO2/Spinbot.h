#pragma once

extern char* SpinbotTypesX[3];
extern char* SpinbotTypesY[4];

class Spinbot {
public:
	static int FindBestAntiAimTarget();
	static void HandleSpinbot(usercmd_s* currentCmd);
};