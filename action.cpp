#include "action.hpp"
#include "includes/HeroesLib/_G_PARAM.hpp"
#include "includes/HeroesLib/_MODESWITCH.hpp"
#include "advertise.hpp" //temporary dirty hax


//void (*ACTION::timeoverFunction)(void (*)()) = (void (*)(void (*)()))0x8D696C;
ACTION& Action = *(ACTION*)0x8D66E8;

//dirty temp hax//
char team1 = 0;
char team2 = 1;
//~~//



void __declspec(naked) InitStageAndTeamInfo()
{
	__asm
	{
		//push edx;
		mov ecx, edx;
		call ACTION::InitStageAndTeamInfo;
		//add esp, 0x4;
		ret;
	}
}
void ACTION::InitStageAndTeamInfo()
{
	pModeSwitch->is2PMode = 1;

	for (int i = 0; i < 64; ++i)
	{
		stageConnect[i] = 0;
	}

 	teamKind[0] = team1;
	teamKind[1] = team2;
	teamKind[2] = -1;
	teamKind[3] = -1;
}


void ACTION::addFrame(int a1, ACTION* a2)
{
	int v2;
	void** v3;
	signed char v1[4];

	*(int*)v1 = a1;
	if (a2->mode == ActionMode_Normal)
	{
		if (pModeSwitch->eventNo < 0 && !pModeSwitch->SFAScreen && !pModeSwitch->TimeStop && !pModeSwitch->SETObjInteraction)      // #inline MODESWITCH::GetModeSwitch(const(MODESWITCH_ENUM))
		{
			if (!a2->addCountDisabled)
			{
				v3 = &a2->field_4;
				if (a2->timeoverFunction)
				{
					PARAM_TIME::addFrm(-1);
					getGameTime(&v1[0], &v1[1], &v1[2]);
					v2 = v1[1];
					if (!v1[1])
					{
						v2 = v1[2];
						if (!*(short*)&v1[2])
						{
							v2 = ((int (*)(void))a2->timeoverFunction)();
						}
					}
				}
				else
				{
					v2 = PARAM_TIME::addFrm(1);
				}
			}
		}
	}
}


void __declspec(naked) addFrame_Hook(int a1, ACTION* a2)
{

	__asm
	{
		push edi;
		push ecx;
		call ACTION::addFrame;
		add esp, 0x8;
		ret;
	}
}