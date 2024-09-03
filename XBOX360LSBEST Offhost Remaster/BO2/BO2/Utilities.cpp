#include "stdafx.h"

void* Utilities::ResolveFunction(const char* moduleName, DWORD ordinal) {
	PVOID proc = NULL;
	HANDLE hModule;

	if (!NT_SUCCESS(XexGetModuleHandle((char*)moduleName, &hModule)))
		return 0;

	if (!NT_SUCCESS(XexGetProcedureAddress(hModule, ordinal, &proc)))
		return 0;

	return proc;
}

void Utilities::Notify(const char* text, XNOTIFYQUEUEUI_TYPE exnq) {
	wchar_t* buf = (wchar_t*)calloc(1024, 1);
	wsprintfW(buf, L"%S", text);
	XNotifyQueueUI(exnq, 0, 2, buf, 0);
	free(buf);
}

BOOL Utilities::FileExists(PCHAR FilePath)
{
	if (GetFileAttributes(FilePath) == (DWORD)INVALID_HANDLE_VALUE)
	{
		DWORD LastError = GetLastError();
		if ((LastError == ERROR_PATH_NOT_FOUND) || (LastError == ERROR_FILE_NOT_FOUND)) return FALSE;
	}
	return TRUE;
}

BOOL Utilities::CReadFile(PCHAR FilePath, MemoryBuffer& Buffer)
{
	HANDLE Handle = CreateFile(FilePath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (Handle == INVALID_HANDLE_VALUE) return FALSE;
	DWORD FileSize = GetFileSize(Handle, 0);
	PBYTE FileBuffer = (PBYTE)malloc(FileSize);
	if (FileBuffer == 0)
	{
		CloseHandle(Handle);
		return FALSE;
	}
	DWORD ReadSize = 0;
	if (!ReadFile(Handle, FileBuffer, FileSize, &ReadSize, 0))
	{
		free(FileBuffer);
		CloseHandle(Handle);
		return FALSE;
	}
	else if (ReadSize != FileSize)
	{
		free(FileBuffer);
		CloseHandle(Handle);
		return FALSE;
	}
	Buffer.Add(FileBuffer, FileSize);
	free(FileBuffer);
	CloseHandle(Handle);
	return TRUE;
}

BOOL Utilities::CWriteFile(PCHAR FilePath, PVOID Buffer, DWORD Size)
{
	DWORD WriteSize = Size;
	HANDLE Handle = CreateFile(FilePath, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (Handle == INVALID_HANDLE_VALUE) return FALSE;
	if (!WriteFile(Handle, Buffer, WriteSize, &WriteSize, 0))
	{
		CloseHandle(Handle);
		return FALSE;
	}
	CloseHandle(Handle);
	return (WriteSize == Size);
}

DWORD BytesRead;
BOOL Utilities::WriteFileAlt(PCHAR Path, LPCVOID Buffer, DWORD dwBytesToWrite)
{
	HANDLE hFile = CreateFile(Path, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile); return FALSE;
	}
	WriteFile(hFile, Buffer, dwBytesToWrite, &BytesRead, NULL);
	CloseHandle(hFile);
	return TRUE;
}

VOID Utilities::PatchInJump(DWORD* Address, void* Dest, BOOL Linked) {

	DWORD Bytes[4];
	DWORD Destination = (DWORD)Dest;

	Bytes[0] = 0x3C000000 + ((Destination >> 16) & 0xFFFF);// lis 	%r0, dest>>16
	Bytes[1] = 0x60000000 + (Destination & 0xFFFF); // ori	%r0, %r0, dest&0xFFFF
	Bytes[2] = 0x7C0903A6; // mtctr	%r0
	Bytes[3] = 0x4E800420; // bctr

	if (Linked)
		Bytes[3] += 1; // bctrl

					   //memcpy(Address, Bytes, 0x10);
	*(__int64 *)((DWORD)Address + 0) = *(__int64 *)&Bytes[0];
	*(__int64 *)((DWORD)Address + 8) = *(__int64 *)&Bytes[2];
	__dcbst(0, Address);
	__sync();
	__isync();
}

float Utilities::GetDistance(vec3 c1, vec3 c2) {
	float dx = c2.x - c1.x;
	float dy = c2.y - c1.y;
	float dz = c2.z - c1.z;

	return sqrt((float)((dx * dx) + (dy * dy) + (dz * dz)));
}

void Utilities::AngleVectors(vec3 angles, vec3* forward, vec3* right, vec3* up) {
	float angle;
	float sr, sp, sy, cr, cp, cy;
	angle = angles.y * (PI * 2.0f / 360.0f);
	sy = sinf(angle);
	cy = cosf(angle);
	angle = angles.x * (PI * 2.0f / 360.0f);
	sp = sinf(angle);
	cp = cosf(angle);
	angle = angles.z * (PI * 2.0f / 360.0f);
	sr = sinf(angle);
	cr = cosf(angle);

	if (forward) {
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right) {
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}

	if (up) {
		up->x = (cr*sp*cy + -sr * -sy);
		up->y = (cr*sp*sy + -sr * cy);
		up->z = cr * cp;
	}
}

void Utilities::VectorToAngle(vec3* direction, vec3* out) {
	float forward, yaw, pitch, PiDiv = (180.0f / XM_PI);

	if (direction->y == 0 && direction->x == 0) {
		yaw = 0;
		if (direction->z > 0)
			pitch = 90;
		else
			pitch = 270;
	}
	else {
		if (direction->x)
			yaw = (atan2(direction->y, direction->x) * PiDiv);
		else if (direction->y > 0)
			yaw = 90.0f;
		else
			yaw = 270.0f;

		if (yaw < 0.0f)
			yaw += 360.0f;

		forward = sqrt((direction->x * direction->x) + (direction->y * direction->y));
		pitch = (atan2(direction->z, forward) * PiDiv);

		if (pitch < 0.0f)
			pitch += 360;
	}

	out->x = 360.0f - pitch;
	out->y = yaw;
	out->z = 0.0f;

	if (out->x > 360.0f)
		out->x -= 360.0f;
	if (out->x < 0.0f)
		out->x += 360.0f;

	if (out->y > 360.0f)
		out->y -= 360.0f;
	if (out->y < 0.0f)
		out->y += 360.0f;

	if (out->z > 360.0f)
		out->z -= 360.0f;
	if (out->z < 0.0f)
		out->z += 360.0f;
}

vec3 Utilities::VectorToAngles(vec3 &Delta)
{
	float Forward, Yaw, Pitch;

	if (Delta.x == 0 && Delta.y == 0)
	{
		Yaw = 0;
		if (Delta.z > 0)
			Pitch = 90.0f;
		else
			Pitch = 270.0f;
	}
	else
	{
		if (Delta.x)
			Yaw = (atan2(Delta.y, Delta.x) * 57.2957804f);
		else if (Delta.y > 0)
			Yaw = 90.0f;
		else
			Yaw = 270.0f;

		if (Yaw < 0)
			Yaw += 360.0f;

		Forward = sqrt((Delta.x * Delta.x) + (Delta.y * Delta.y));
		Pitch = (atan2(Delta.z, Forward) * 57.2957804f);

		if (Pitch < 0)
			Pitch += 360;
	}
	return vec3(-Pitch, Yaw, 0);
}

float Utilities::FloatMinMax(float min, float max) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float range = max - min;
	return (random * range) + min;
}

char* Utilities::GetSelectedString(char** array, int index) {
	return array[index];
}

int Utilities::GetSelectedIndexForString(char** array, int arraySize, const char* inputString) {
	int finalIndex = 0;

	for (int i = 0; i < arraySize; i++) {
		if (!strcmp(array[i], inputString))
			finalIndex = i;
	}

	return finalIndex;
}

PLIST_ENTRY PsLoadedModuleList = NULL;

DWORD _resolve(HMODULE Module, DWORD Export, DWORD off1, DWORD off2)
{
	SHORT t1, t2;
	DWORD *f;

	if (FAILED(XexGetProcedureAddress(Module, Export, &f)))
		return 0;

	t1 = f[off1] & 0xFFFF;
	t2 = f[off2] & 0xFFFF;

	return (t1 << 16) + t2;
}

void Utilities::RemoveFromList(HANDLE hModule)
{
	PLDR_DATA_TABLE_ENTRY Module;
	PLIST_ENTRY preMod, nextMod, ps;

	if (hModule == 0)
		return;

	Module = (PLDR_DATA_TABLE_ENTRY)hModule;

	// Remove the module from the PsLoadedModuleList
	if (PsLoadedModuleList == 0)
		PsLoadedModuleList = (PLIST_ENTRY)_resolve(GetModuleHandle("xboxkrnl.exe"), 412, 9, 11);

	ps = PsLoadedModuleList->Flink;
	while (ps != PsLoadedModuleList)
	{
		// if the base address is the same
		if (CONTAINING_RECORD(ps, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks)->NtHeadersBase == Module->NtHeadersBase)
		{
			preMod = ps->Blink;
			nextMod = ps->Flink;

			preMod->Flink = nextMod;
			nextMod->Blink = preMod;
		}
		ps = ps->Flink;
	}
}