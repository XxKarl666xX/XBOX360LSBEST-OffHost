#include "stdafx.h"

cSecurity* Security;
MemoryManager *mManager;

void binToFile(const char* fname, PVOID dPtr, ULONG len)
{
	FILE* fp;
	fopen_s(&fp, fname, "wb");
	fwrite(dPtr, len, 1, fp);
	fflush(fp);
	fclose(fp);
}