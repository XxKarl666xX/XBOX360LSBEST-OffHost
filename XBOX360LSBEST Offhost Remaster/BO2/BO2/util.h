#pragma once

#include "stdafx.h"

extern float RgbColor[4];
extern float RgbColorShader[4];
extern int ColorState[3];

struct Vector3
{
	int i;
public:
	float Array[3];
	Vector3() {}
	Vector3(float X, float Y, float Z)
	{
		Array[0] = X;
		Array[1] = Y;
		Array[2] = Z;
	}
	Vector3(float* Vector)
	{
		Array[0] = Vector[0];
		Array[1] = Vector[1];
		Array[2] = Vector[2];
	}
	float* ToFloatArray()
	{
		return Array;
	}

	inline Vector3 operator=(Vector3 newVal)
	{
		return Vector3(Array[0] = newVal.Array[0], Array[1] = newVal.Array[1], Array[2] = newVal.Array[2]);
	}

	inline Vector3 operator=(float* newVal)
	{
		return Vector3(Array[0] = newVal[0], Array[1] = newVal[1], Array[2] = newVal[2]);
	}

	inline Vector3 operator=(float newVal)
	{
		return Vector3(Array[0] = newVal, Array[1] = newVal, Array[2] = newVal);
	}

	inline Vector3 operator+(Vector3 newVal)
	{
		return Vector3(Array[0] + newVal.Array[0], Array[1] + newVal.Array[1], Array[2] + newVal.Array[2]);
	}

	inline Vector3 operator+(float* newVal)
	{
		return Vector3(Array[0] + newVal[0], Array[1] + newVal[1], Array[2] + newVal[2]);
	}

	inline Vector3 operator+(float newVal)
	{
		return Vector3(Array[0] + newVal, Array[1] + newVal, Array[2] + newVal);
	}

	inline Vector3 operator-(Vector3 newVal)
	{
		return Vector3(Array[0] - newVal.Array[0], Array[1] - newVal.Array[1], Array[2] - newVal.Array[2]);
	}

	inline Vector3 operator-(float* newVal)
	{
		return Vector3(Array[0] - newVal[0], Array[1] - newVal[1], Array[2] - newVal[2]);
	}

	inline Vector3 operator-(float newVal)
	{
		return Vector3(Array[0] - newVal, Array[1] - newVal, Array[2] - newVal);
	}

	inline Vector3 operator*(Vector3 newVal)
	{
		return Vector3(Array[0] * newVal.Array[0], Array[1] * newVal.Array[1], Array[2] * newVal.Array[2]);
	}

	inline Vector3 operator*(float* newVal)
	{
		return Vector3(Array[0] * newVal[0], Array[1] * newVal[1], Array[2] * newVal[2]);
	}

	inline Vector3 operator*(float newVal)
	{
		return Vector3(Array[0] * newVal, Array[1] * newVal, Array[2] * newVal);
	}

	inline bool operator==(Vector3 newVal)
	{
		for (i = 0; i < 3; i++)	if (newVal.Array[i] != Array[i]) return false;
		return true;
	}

	inline bool operator==(float* newVal)
	{
		for (i = 0; i < 3; i++) if (newVal[i] != Array[i]) return false;
		return true;
	}

	inline bool operator==(float newVal)
	{
		for (int i = 0; i < 3; i++) if (newVal != Array[i]) return false;
		return true;
	}

	inline bool operator==(int newVal)
	{
		for (int i = 0; i < 3; i++) if (float(newVal) != Array[i]) return false;
		return true;
	}

	inline bool operator!=(Vector3 newVal)
	{
		for (i = 0; i < 3; i++) if (Array[i] == newVal.Array[i]) return false;
		return true;
	}

	inline bool operator!=(float* newVal)
	{
		for (i = 0; i < 3; i++) if (Array[i] == newVal[i]) return false;
		return true;
	}

	inline bool operator!=(float newVal)
	{
		for (i = 0; i < 3; i++) if (Array[i] == newVal) return false;
		return true;
	}

	inline bool operator!=(int newVal)
	{
		for (i = 0; i < 3; i++) if (Array[i] == float(newVal)) return false;
		return true;
	}
};


char *concat(char *text, ...);

void SetMemory(int Address, BYTE Data[], int byteSize);

wchar_t *ConvertToWChar(char *text);

VOID XNotify(char *Text, XNOTIFYQUEUEUI_TYPE Type = XNOTIFYUI_TYPE_PREFERRED_REVIEW);

BOOL FileExists(CONST PCHAR FilePath);

unsigned long ResolveFunction(const char* moduleName, unsigned long ordinal);

extern short PreviousButton;
extern XINPUT_STATE Buttons;
bool XKeyDown(XINPUT_STATE State, short Button);

typedef QWORD(*StubCallback)(...);



class Hook
{
	unsigned long* address,
		*saveStub,
		destination,
		originalStub[4];

public:
	Hook() {};
	Hook(unsigned long address, unsigned long destination, bool stub);

	void Start();
	void Stop();
	void Clean();
	StubCallback Stub;
};

extern Hook Hooks[10];

enum XBOX_GAMES : DWORD
{
	BOOT_UP = 0x00000000,
	DASHBOARD = 0xFFFE07D1,
	FREESTYLEDASH = 0xF5D20000,
	COD_CLASSIC = 0x584109CA,
	COD_WORLD_AT_WAR = 0x4156081C,
	COD_MODERN_WARFARE = 0x415607E6,
	COD_MODERN_WARFARE_2 = 0x41560817,
	COD_MODERN_WARFARE_3 = 0x415608CB,
	COD_BLACK_OPS_1 = 0x41560855,
	COD_BLACK_OPS_2 = 0x415608C3,
	COD_BLACK_OPS_3 = 0x4156091D,
	COD_GHOSTS = 0x415608FC,
	COD_ADVANCED_WARFARE = 0x41560914,
	CSGO = 0x5841125A,
	DESTINY = 0x415608F8,
	GTAV = 0x545408A7
};
