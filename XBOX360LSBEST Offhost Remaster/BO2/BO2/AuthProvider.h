#pragma once
#include "stdafx.h";

namespace AuthProvider
{

	//enum CODs
	//{
		//BO2 = 1
		
//	};

	typedef QWORD(*Function)(...);
	extern int currentGame;
	DWORD GetAddress(int index);
	Function GetFunction(int index);
}