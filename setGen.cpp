#include "pch.h"
#include "includes/HeroesLib/setGen.hpp"
#include "includes/HeroesLib/Renderware.hpp"
#include "includes/HeroesLib/team.hpp"
#include "includes/HeroesLib/_MODESWITCH.hpp"
#include "includes/HeroesLib/Globals.hpp"
#include "includes/HeroesLib/Player.hpp"



//
int TObjSetObj::CheckRangeOutWithoutIgnorRangeFlag(SETOBJ_PARAM* a1, RwReal a2)
{
	int v1 = (a1->renderDistance + 1) * 100.0 * (a1->renderDistance + 1) * 100.0;
	return setobjCheckRangeOut2(&a1->position, v1);
}


int TObjSetObj::CheckRangeOut(SETOBJ_PARAM* a1, RwReal a2)
{
	if (!(*(sBitFlag*)(char*)(a1->SETFlag_HHC)).TstBit(0x400))  //#inline TObjSetObj::CheckMustKill((void))
	{
		int v1 = (a1->renderDistance + 1) * 100.0 * (a1->renderDistance + 1) * 100.0;
		return setobjCheckRangeOut2(&a1->position, v1);
	}
}


int setobjCheckRangeOut2(RwV3d const* position, RwReal range)
{
	if (Distance2P2P(PlayerMaster::GetPlayerPositionHistory(teamTOp[0]->GetLeaderPlayerNo(), 0), position) < range)
	{
		return false;
	}
	if (pModeSwitch->is2PMode)
	{
		if (Distance2P2P(PlayerMaster::GetPlayerPositionHistory(teamTOp[1]->GetLeaderPlayerNo(), 0), position) < range)
		{
			return false;
		}
	}
	return true;
}


signed int ObjSwitchesAreAllOn(unsigned char a1)
{
	int v1; // ecx
	__int16 v3; // ax
	int v4; // eax

	v1 = *(int*)(SetGenTp + 4 * a1 + 0x30);             // #inline TObjSetGen::GetCommunicateList((uchar))
	if (!v1)
	{
		return 0;
	}
	while (1)
	{
		v3 = *(short*)(v1 + 0x28);
		if (v3 == 5 || v3 == 7 || v3 == 6 || v3 == 0x1104)
		{
			v4 = *(int*)(v1 + 0x30);
			if (!v4 || *(int*)(v4 + 0x10) != 2)
			{
				break;
			}
		}
		v1 = *(int*)(v1 + 0x38);
		if (!v1)
		{
			return 1;
		}
	}
	return 0;
}



void __declspec(naked) setobjCheckRangeOut2_hook(RwV3d* position, float a2)
{
	__asm 
	{
		push [esp + 0x4];
		push ecx;
		call setobjCheckRangeOut2;
		add esp, 0x8;
		ret;
	}
}
// ~



//
char*& TObjSetGen::OneFileUsualName = *(char**)0xA23D28;
SETOBJ_PARAM*& TObjSetGen::objTable = *(SETOBJ_PARAM**)0xA825D8;
TObjSetGen*& SetGenTp = *(TObjSetGen**)0xA7784C;