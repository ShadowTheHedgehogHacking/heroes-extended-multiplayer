#include "pch.h"
#include "includes/HeroesLib/Controls.hpp"
#include "includes/HeroesLib/_MAIN.hpp"
#include "includes/HeroesLib/_PCStuff.hpp"
#include "includes/HeroesLib/_DVDREAD.hpp"
#include "includes/HeroesLib/setGen.hpp"
#include "_Hook.hpp"
#include "_TObjBobsleigh.hpp"
#include "action.hpp"
#include "advertise.hpp"
#include "newCamera.hpp"
#include "Tsonic/src/stage/stage11_Warp/o_s11_warp.hpp"
#include "o_warp.hpp"
#include <HeroesLib\_MODESWITCH.hpp>
//#include <fstream> //TODO: remove me when you release / are done with file io debug

struct TObjRingSubstance;
struct ObjRingStrage
{
	int gottenFlag;
	int field_4;
	int field_8;
	int field_C;
};

struct teststruct
{
	SETDATA_PARAM field_0;
	ObjRingStrage* pStrage_HHC;
};

struct TObjRing : TObject
{
	char numRings;
	char type_HHC;
	char switchCommState__;
	char field_2B;
	RwV3d pos;
	sRealAngle3 ang;
	float length;
	float radius;
	TObjRingSubstance* TObjRingSubstance_HHC;
};

struct TObjSetRing : TObjRing
{
	TObjSetObj* field_50;
	teststruct* field_54;
};

struct TObjRingSubstance
{
	void* __vftable /*VFT*/;
	C_COLLI C_COLLI;
	char OBJ_MoveOnGround[0x38];
	char gapC4[5];
	char state__;
	char ringNo;
	__int16 field_CC;
	float field_D0;
	__int16 field_D4;
	char field_D6;
	TObjSetRing* pTObjSetRing;
	float shadowPos_HHC;
	__int16 field_E0_BAMS__;
	__int16 field_E2_BAMS__;
	int field_E4;
};

struct TObjTrainCore
{
	TObject TObject;
	TObjSetObj* TObjSetObj;
	SETOBJ_PARAM* SETOBJ_PARAM;
	C_COLLI C_COLLI;
	RwV3d position;
	sAngle rotation;
	RwInt32 crashDestroyCountMaybe;
	void* ptclTask;
	RpClump* field_D8;
	int field_DC;
	RpClump* field_E0;
	int field_E4;
	RpClump* field_E8;
	int field_EC;
};




int layoutTeamKind = 0;
//char team1;
//char team2;


extern "C" __declspec(dllexport) void Init();



BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			//Init();
			break;
		}
		case DLL_THREAD_ATTACH:
		{
			break;
		}
		case DLL_THREAD_DETACH:
		{
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
	}
	return TRUE;
}


//temp dirty//
char*& DemoLocator = *(char**)0x9DDD88;
int*& gStartStageLocator2p = *(int**)0x7C5E18;
int* gStartStageLocator = (int*)0x7C2FC8;

char* SearchStartStageLocator_Hook(int teamKind)
{
	unsigned int stageNoIndex_HHC; // ecx
	char* result; // eax
	unsigned int v4; // eax
	int playerNoIndex_HHC; // edx
	TObjTeam* v6; // eax
	int* v7; // eax
	
	stageNoIndex_HHC = 0;
	if (pModeSwitch->demoMode && *(int*)&DemoLocator[0x1C * teamKind + 0x18])
	{
		return &DemoLocator[0x1C * teamKind];
	}
	/*if (pModeSwitch->is2PMode)
	{
		playerNoIndex_HHC = 0;
		while (1)
		{
			v6 = teamTOp[playerNoIndex_HHC];
			if (v6)
			{
				if (v6->teamKind == teamKind && stageNoIndex_HHC < 0x17)
				{
					break;
				}
			}
		LABEL_17:
			if (++playerNoIndex_HHC >= 4)
			{
				return 0;
			}
		}
		v7 = &gStartStageLocator2p[0xF * stageNoIndex_HHC];
		while (*v7 != Action.stageNo)
		{
			++stageNoIndex_HHC;
			v7 += 0xF;
			if (stageNoIndex_HHC >= 0x17)
			{
				goto LABEL_17;
			}
		}
		result = (char*)&gStartStageLocator2p[0xF * stageNoIndex_HHC + 1 + 7 * playerNoIndex_HHC];
	}*/
	//else
	{
		v4 = 0;
		while (gStartStageLocator[v4] != Action.stageNo)
		{
			v4 += 0x24;
			++stageNoIndex_HHC;
			if (v4 >= 0x57C)
			{
				return 0;

			}
		}
		result = (char*)&gStartStageLocator[0x24 * stageNoIndex_HHC + 1 + 7 * layoutTeamKind];
	}
	return result;
}

int IncChaotixClearItem(TObjTeam* t)
{
	int v1;

	*(char*)0x9DD6F2 = *(char*)0x9DD70A;
	*(char*)0x9DD6F1 = *(char*)0x9DD709; //for now am lazy
	*(char*)0x9DD6F0 = *(char*)0x9DD708;

	return ++teamTOp[0]->chaotixClearItem;
}

void __declspec(naked) SearchStartStageLocator_ASM()
{
	__asm 
	{
		push eax;
		call SearchStartStageLocator_Hook;
		add esp, 0x4;
		ret
	}
};

void __declspec(naked) IncChaotixClearItem_ASM()
{
	__asm
	{
		push eax;
		call IncChaotixClearItem;
		add esp, 0x4;
		ret
	}
}

void* CreateTrampoline(void* address, void* trampoline, char overwriteSize)
{
	Hook Hooker;
	char nopCount = overwriteSize - 0x5;

	void* myCode = VirtualAlloc(nullptr, overwriteSize + 0x5, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(myCode, address, overwriteSize);
	if (nopCount)
	{
		void* nopAddress = (void*)((char*)address + (overwriteSize - nopCount));
		for (char i = 0; i < nopCount; ++i)
		{
			{
				char data[] = { 0x90 };
				Hooker.WritePatch((void*)((char*)nopAddress + i), data, 1);
			}
		}
	}
	Hooker.WriteJMP(address, trampoline);
	Hooker.WriteJMP((void*)((char*)myCode + overwriteSize), (void*)((char*)address + overwriteSize));
	return myCode;
}

void(__cdecl* myCode2)(void*);
void(__cdecl* myCode3)(void*);
void(__cdecl* myCodeSetBobsleigh)(int, char*);
void(__cdecl* myCodeSetBobsleigh2)(int, char*, void*, void*);
void __declspec(naked) ADV_2P_Create()
{
	__asm
	{
		call myCode2;
	}
}
void ADV_2P_Create_Tramp(TObject* a1)
{
	
	//ADV_2P_Create();
	//__asm call myCode;
	myCode2(a1);
	//((ADVERTISE_CONTROL*)((char*)(*Advertise.folder_HHC) + 0x18))->lastSubMode = 6;
	((ADVERTISE_CONTROL*)(a1->Child))->lastSubMode = 6;
	((ADVERTISE_CONTROL*)(a1->Child))->animCount = 14;
	*(float*)0x7C933C = 13;
	//Advertise.lastSubMode = 6;
}
void ADV_2P_ExecSelect2_Tramp(ADV_2P* a1)
{
	__asm
	{
		mov eax, a1;
		call myCode3;
	}
	team1 = a1->p1Team;
	team2 = a1->p2Team;
}
void __declspec(naked) ADV_2P_ExecSelect2()
{
	__asm
	{
		push eax;
		call ADV_2P_ExecSelect2_Tramp;
		add esp, 0x4;
		ret;
	}
}
int address = 0x43D16D;
void __declspec(naked) superdirtybinpatch()
{
	__asm
	{
		mov eax, layoutTeamKind;
		cmp eax, 4;
		jmp address;
	}
}
int address2 = 0x44B67D;
void __declspec(naked) dirtygotogamechallengepatch()
{
	__asm
	{
		mov layoutTeamKind, eax
		jmp address2;
	}
}
void SetBobsleigh_Hook(int bobsleighID_HHC, char* BobsleighParam)
{
	*(float*)(BobsleighParam + 0x1C) = 0;
	myCodeSetBobsleigh(bobsleighID_HHC, BobsleighParam);
	*(int*)(BobsleighParam + 0x38) = 1;
	*(float*)(BobsleighParam + 0x1C) = 1;
	bobsleighID_HHC = 4;
	myCodeSetBobsleigh(bobsleighID_HHC, BobsleighParam);
}
void SetBobsleigh_Hook2(int bobsleighID_HHC, char* BobsleighParam, void* a6, void* a7)
{
	*(float*)(BobsleighParam + 0x1C) = 0;
	myCodeSetBobsleigh2(bobsleighID_HHC, BobsleighParam, a6, a7);
	*(int*)(BobsleighParam + 0x38) = 1;
	*(float*)(BobsleighParam + 0x1C) = 0.5;
	bobsleighID_HHC = 4;
	myCodeSetBobsleigh2(bobsleighID_HHC, BobsleighParam, a6, a7);
}
void __declspec(naked) BobCatchPlayer_Hook()
{
	static int addytrue = 0x45EEF7;
	static int addyfalse = 0x45EF41;
	__asm
	{
		mov ecx, [esi + 0x198];
		cmp eax, ecx;
		jne itsfalse;
		jmp itstrue;

	itsfalse:
		jmp addyfalse;

	itstrue:
		cmp eax, 3;
		jmp addytrue;
	}
}

void ringtest()
{
	TObjRingSubstance* t;
	__asm mov [t], esi;
	if (!((1 << (t->ringNo & 31)) &*(&t->pTObjSetRing->field_54->pStrage_HHC->gottenFlag + ((t->ringNo >> 5) & 3))))
	{
		int addy = 0x4832F0;
		__asm jmp [addy];
	}
}

	static int addy = 0x4832F0;
	static int addy2 = 0x482FF8;
	TObjRingSubstance* t;
	//std::ofstream file; //TODO: remove me when you release / are done with file io debug

	//void terribleFunc() {
	//	if (!file.is_open()) {
	//		file.open("C:\\Users\\DonutStopGaming\\Desktop\\Mod\\Debug\\yeet.txt", std::ios_base::app);
	//	}
	//	file << t->pTObjSetRing->field_54;
	//	file << std::endl;
	//}

void __declspec(naked) ringsubstanceexechook_ASM()
{
	__asm push eax;
	__asm push ecx;
	__asm push edx;
	__asm mov[t], esi;
	if (*(int*)t->pTObjSetRing != 0x7525CC)//(t->pTObjSetRing->type_HHC != 4)//(t->field_CC)
	{
		// terribleFunc(); enable for logging, when releasing also remove import fstream at top

		// null and common case
		//if (t->pTObjSetRing->field_54 == NULL || (int)(t->pTObjSetRing->field_54) <= 0xCFFF) {
		//	goto endOfRingCheck;
		//}

		if (!((1 << (t->ringNo & 31)) & *(&t->pTObjSetRing->field_54->pStrage_HHC->gottenFlag + ((t->ringNo >> 5) & 3))))
		{
				heretest:
			{
				__asm
				{
					pop edx;
					pop ecx;
					pop eax;
					call[addy];
					push eax;
					push ecx;
					push edx;
				}
			}
		}
		else
		{
			if (t->pTObjSetRing->numRings < 5)
			{
				t->state__ = 5;
			}
		}
	}
	else
	{
		goto heretest;
	}
endOfRingCheck: ; //label marker, do nothing before pop and return
	__asm
	{
		pop edx;
		pop ecx;
		pop eax;
		jmp [addy2];
	}
}

static int addybacktocheckcolli = 0x4833DD;
void __declspec(naked) RingSubstanceCheckCollisionHook_ASM()
{
	__asm
	{
		push eax;
		push ecx;
	}
	if (*(int*)t->pTObjSetRing == 0x7525CC)
	{
		t->state__ = 5;
	}
	__asm
	{
		pop ecx;
		pop eax;
		jmp addybacktocheckcolli;
	}
}

static int addyback = 0x471951;
void __declspec(naked) WarpCameraAndPlayer_ASM()
{
	__asm
	{
		push[ebp + 0xF8];
		push eax;
		call TObjCamera::WarpCameraAndPlayer;
		add esp, 0x8;
		jmp [addyback];
	}
}

RwV3d warpPosition[4] = {
{-150.0, 2030.0, 8100.0},
{84000.0, 2576.0, -2320.0},
{-12050.0, 2030.0, 8190.0},
{100000.0, 8600.0, 12510.0}
};

signed int CheckPlayerHack(TObjTrainCore* a1)
{
	CCL_MASTER::ClearSearch();
	C_COLLI* hitTarget = a1->C_COLLI.IsHitKind(0xdu);
	if (!hitTarget)
	{
		CCL_MASTER::ClearSearch();
		while (1)
		{
			//hitTarget = a1->C_COLLI.IsHitKind(0x14);
			hitTarget = a1->C_COLLI.IsHitPlayer();
			if (!hitTarget)
			{
				break;
			}
			int v1 = GetPlayerNumberFromCCLCharacterId(hitTarget->GetCharacterId());
			TObjPlayer* v6 = playerTOp[v1];
			if (v6)
			{
				int v7 = v6->teamNo;
				TObjTeam* v3 = teamTOp[v7];
				if (v3)
				{
					if (v3->playerNo[v3->GetNowLeaderPlayerNo() % 3] == v1 || v3->playerNo[v3->GetLeaderPlayerNo() % 3] == v1)
					{
						if (v3->IsThisPostedPlayer(v1))
						{
							//this->currentPlayerNo = v7;
							return v7;
						}
					}
				}
			}
		}
	}
	return 0;
}

void TrainHack(TObjTrainCore* a1)
{
	TObjCamera::WarpCameraAndPlayer(&warpPosition[(int)a1->SETOBJ_PARAM->PARAM->data[0]], CheckPlayerHack(a1));
	*(int*)&a1->SETOBJ_PARAM->SETFlag_HHC &= ~0x10002;
}

static int trainAddy = 0x4DA6B6;
void __declspec(naked) TObjTrainCore_Exec_ASM()
{
	//do st
	__asm
	{
		push edi;
		call TrainHack;
		add esp, 0x4;
		jmp trainAddy;
	}
}
//~ //
extern "C" __declspec(dllexport) void Init()
{
	Hook Hooker;

	Hooker.Replace(0x5865E0, MakePlayersKeyData);
	Hooker.Replace(0x435550, MakeGameKeyData);
	Hooker.Replace(0x427510, MAIN::InitModules);
	Hooker.Replace(0x444D20, PCSpecific::SetupDInput);
	Hooker.Replace(0x5C9C10, ChangeModeFormationFly_Hook);
	Hooker.Replace(0x463A60, SetArrowPosition_hook);
	Hooker.Replace(0x4198D0, CLASS_DVDREAD::Start);
	Hooker.Replace(0x465BB0, initObjS31Bob);
	Hooker.Replace(0x5B3917, arrowdisptest_hook);
	Hooker.Replace(0x404DB0, addFrame_Hook);
	//Hooker.Replace(0x40206E, initObjS31Bob);
	Hooker.Replace(0x43E1B0, setobjCheckRangeOut2_hook);
	Hooker.Replace(0x503000, TObjS11Warp_Exec_Hook);
	Hooker.Replace(0x48AE70, TObjWarp_Exec_Hook);
	Hooker.Replace(0x404700, InitStageAndTeamInfo);
	Hooker.Replace(0x426F10, SearchStartStageLocator_ASM);
	Hooker.Replace(0x4DA6AA, TObjTrainCore_Exec_ASM);



	// Dirty Hax For Now //
	{
		short data = 0x9090;
		Hooker.WritePatch((void*)0x426F48, (char*)&data, 2); //multiplayer start position patch
	}

	{
		char data = 0xEB;
		Hooker.WritePatch((void*)0x557ADA, &data, 1); //Skip a check that calls TObjTeam::TObjTeam() if its not "2PMode" for team battles
	}

	{
		char data = 0xEB;
		Hooker.WritePatch((void*)0x5AB053, &data, 1); //Skip a check that calls SetGame2PManager()
	}

	{
		char data = 0xEB;
		Hooker.WritePatch((void*)0x41DD51, &data, 1);
	}

	{
		char data = 0xEB;
		Hooker.WritePatch((void*)0x5AB6EA, &data, 1); //Skip a check that calls SetGame2PManager()
	}

	{
		char data = 0x06;
		Hooker.WritePatch((void*)0x44737A, &data, 1); //bring up character select on first 2p page
	}

	{
		char data = 0x02;
		Hooker.WritePatch((void*)0x447C81, &data, 1); //goto challange after picking characters
	}

	{
		char data[] = { 0xB1, 0x02, 0x90 };
		Hooker.WritePatch((void*)0x4BA322, data, 3); //allow p2 to control casino flippers
	}

	{
		char data[] = { 0x90, 0x90 };
		Hooker.WritePatch((void*)0x4029F2, data, 2); //dirty rank screen patch to make it show
	}

	{
		char data[] = { 0x90, 0x90 };
		Hooker.WritePatch((void*)0x402A21, data, 2); //dirty rank screen patch to make it show
	}

	{
		char data[]{ 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }; // nop setobjdestroy for train after breaking
		Hooker.WritePatch((void*)0x4DA6AF, data, 7);
	}

	Hooker.WriteJMP((void*)0x43D167, superdirtybinpatch);
	Hooker.WriteJMP((void*)0x44B678, dirtygotogamechallengepatch);
	Hooker.WriteJMP((void*)0x5B48D0, IncChaotixClearItem_ASM);
	//Hooker.WriteJMP((void*)0x482FF3, ringsubstanceexechook_ASM);
	//Hooker.WriteJMP((void*)0x4833D6, RingSubstanceCheckCollisionHook_ASM);
	Hooker.WriteJMP((void*)0x47194C, WarpCameraAndPlayer_ASM);

	{
		char data[] = { 0x90 };
		Hooker.WritePatch((void*)0x43D16C, data, 1); //last byte left over to nop from previous JMP
	}

	{
		char data[] = { 0x90, 0x90, 0x90, 0x90 };
		Hooker.WritePatch((void*)0x45EEF1, data, 4);
		Hooker.Replace(0x45EEEC, BobCatchPlayer_Hook);
	}

	{
		char data[]{ 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
		Hooker.WritePatch((void*)0x401858, data, 6);
	}

	{
		char data[]{ 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
		//Hooker.WritePatch((void*)0x4833D6, data, 7);
	}

	{
		char data[]{ 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
		//Hooker.WritePatch((void*)0x483156, data, 7);
	}

	{
		char data[]{ 0x90, 0x90, 0x90, 0x90 };
		//Hooker.WritePatch((void*)0x4823D6, data, 4);
	}

	myCode2 = (void(__cdecl*)(void*))CreateTrampoline((void*)0x447280, ADV_2P_Create_Tramp, 7);
	myCode3 = (void(__cdecl*)(void*))CreateTrampoline((void*)0x447C10, ADV_2P_ExecSelect2, 10);
	myCodeSetBobsleigh = (void(__cdecl*)(int, char*))CreateTrampoline((void*)0x45C9A0, SetBobsleigh_Hook, 7);
	myCodeSetBobsleigh2 = (void(__cdecl*)(int, char*, void*, void*))CreateTrampoline((void*)0x45CA70, SetBobsleigh_Hook2, 7);

}
