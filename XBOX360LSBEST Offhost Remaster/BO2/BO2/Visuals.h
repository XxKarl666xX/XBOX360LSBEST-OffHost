#pragma once

extern char* DrawingTypes[5];
extern char* SnaplineTypes[3];

extern char* espBoneNames[14];
extern char* bonesESP[26];

class Visuals {
public:
	static void DrawESPBox(color color, int Index, int currentType);
	static void DrawBones(int clientNum, color color);
	static void DrawESP(int clientNum, color colorESP);
	static void HandleVisuals();
};