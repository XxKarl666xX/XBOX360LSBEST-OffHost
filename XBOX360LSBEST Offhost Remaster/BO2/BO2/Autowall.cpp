#include "stdafx.h"

bool Autowall::IsPlayerPenetrable(int clientNum, short tag) {
	vec3 end = Game::GetTagPos(&centity[clientNum], tag);

	vec3 viewOrigin;
	CG_GetPlayerViewOrigin(0, (playerState_s*)((DWORD)cg + 0x480A8), viewOrigin);

	BulletFireParams bulletFireParams;
	bulletFireParams.iIgnoreEntIndex = cg->clientNumber;
	bulletFireParams.iWeaponEntIndex = 0x3FE;
	bulletFireParams.fDamageMultiplier = 1.0f;
	bulletFireParams.iMethodOfDeath = 2;
	bulletFireParams.vOrigStart = viewOrigin;
	bulletFireParams.vStart = viewOrigin;
	bulletFireParams.vEnd = end;

	vec3 endDirection = end - viewOrigin;

	vec3 angle;
	Utilities::VectorToAngle(&endDirection, &angle);

	vec3 hax;
	Utilities::AngleVectors(angle, &hax, nullptr, nullptr);

	bulletFireParams.vDirection = hax;

	*(QWORD*)Security->addrs.Autowall[0] = 0x386000004E800020;
	*(QWORD*)Security->addrs.Autowall[1] = 0x386000004E800020;
	*(DWORD*)Security->addrs.Autowall[2] = 0x48000218;
	*(DWORD*)Security->addrs.Autowall[3] = 0x38600000;
	*(DWORD*)Security->addrs.Autowall[4] = 0x38600000;
	*(DWORD*)Security->addrs.Autowall[5] = 0x38600000;
	*(DWORD*)Security->addrs.Autowall[6] = 0x38600001;
	*(DWORD*)Security->addrs.Autowall[7] = 0x60000000;

	BulletTraceResults bulletTraceResults;
	FireBulletPenetrate(0, &bulletFireParams, centity[cg->clientNumber].weaponNum, &centity[cg->clientNumber], viewOrigin, 0, 1, &bulletTraceResults);

	*(QWORD*)Security->addrs.Autowall[0] = 0x7D8802A69181FFF8;
	*(QWORD*)Security->addrs.Autowall[1] = 0x7D8802A6486BDA55;
	*(DWORD*)Security->addrs.Autowall[2] = 0x419A00AC;
	*(DWORD*)Security->addrs.Autowall[3] = 0x4BFA1B15;
	*(DWORD*)Security->addrs.Autowall[4] = 0x4BFA184D;
	*(DWORD*)Security->addrs.Autowall[5] = 0x4BFA17ED;
	*(DWORD*)Security->addrs.Autowall[6] = 0x4BFF4301;
	*(DWORD*)Security->addrs.Autowall[7] = 0x4BFFF669;

	return (bulletFireParams.iIgnoreEntIndex == clientNum);
}