#include "stdafx.h"

uiContext_s context;
clientActive_s* clientActive;
centity_s* centity;
cgs_s* cgs;
cg_s* cg;
netInfo_s netInfo[18];
playerInfo_s pInfo[18];

void Structs::UpdateStructures() {
	context = *(uiContext_s*)Security->addrs.strct_uiContext;
	clientActive = (clientActive_s*)*(int*)(Security->addrs.strct_clientActive);
	centity = (centity_s*)*(int*)(Security->addrs.strct_centity);
	cg = (cg_s*)*(int*)(Security->addrs.strct_cgArray);
	cgs = (cgs_s*)*(int*)(Security->addrs.strct_cgsArray);

	for (int i = 0; i < 18; i++)
		netInfo[i] = *(netInfo_s*)(Security->addrs.strct_netInfo + (i * 0x148));
}