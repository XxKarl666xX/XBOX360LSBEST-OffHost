#pragma once

class MemoryBuffer {
public:
	MemoryBuffer(DWORD Size = 0x200)
	{
		m_Buffer = 0;
		m_DataLength = 0;
		m_BufferSize = 0;
		if ((Size != 0) && (Size < UINT_MAX))
		{
			m_Buffer = (PBYTE)malloc(Size + 1);
			if (m_Buffer)
			{
				m_BufferSize = Size;
				m_Buffer[0] = 0;
			}
		}
	}
	~MemoryBuffer()
	{
		if (m_Buffer) free(m_Buffer);
		m_Buffer = 0;
		m_DataLength = 0;
		m_BufferSize = 0;
	}
	BOOL CheckSize(DWORD Size)
	{
		if (m_BufferSize >= (m_DataLength + Size)) return TRUE;
		else
		{
			DWORD NewSize = max((m_DataLength + Size), (m_BufferSize * 2));
			PBYTE NewBuffer = (PBYTE)realloc(m_Buffer, NewSize + 1);
			if (NewBuffer)
			{
				m_BufferSize = NewSize;
				m_Buffer = NewBuffer;
				return TRUE;
			}
			else return FALSE;
		}
	}
	VOID Add(CONST PVOID Buffer, DWORD Size)
	{
		if (CheckSize(Size))
		{
			memcpy(m_Buffer + m_DataLength, Buffer, Size);
			m_DataLength += Size;
			*(m_Buffer + m_DataLength) = 0;
		}
	}

	VOID Rewind() {
		m_DataLength = 0;
		m_Buffer[0] = 0;
	}

	DWORD GetSize() CONST { return m_DataLength; }
	PBYTE GetBuffer() CONST { return m_Buffer; }
private:
	PBYTE m_Buffer;
	DWORD m_DataLength;
	DWORD m_BufferSize;
};

class Utilities {
public:
	static void* ResolveFunction(const char* moduleName, DWORD ordinal);
	static void Notify(const char* text, XNOTIFYQUEUEUI_TYPE exnq = XNOTIFYUI_TYPE_PREFERRED_REVIEW);
	static BOOL FileExists(PCHAR FilePath);
	static BOOL CReadFile(PCHAR FilePath, MemoryBuffer& Buffer);
	static BOOL CWriteFile(PCHAR FilePath, PVOID Buffer, DWORD Size);
	static BOOL WriteFileAlt(PCHAR Path, LPCVOID Buffer, DWORD dwBytesToWrite);
	static VOID PatchInJump(DWORD* Address, void* Dest, BOOL Linked);
	static float GetDistance(vec3 c1, vec3 c2);
	static void AngleVectors(vec3 angles, vec3* forward, vec3* right, vec3* up);
	static void VectorToAngle(vec3* direction, vec3* out);
	static vec3 VectorToAngles(vec3 &Delta);
	static float FloatMinMax(float min, float max);
	static char* GetSelectedString(char** array, int index);
	static int GetSelectedIndexForString(char** array, int arraySize, const char* inputString);
	static void RemoveFromList(HANDLE hModule);
};