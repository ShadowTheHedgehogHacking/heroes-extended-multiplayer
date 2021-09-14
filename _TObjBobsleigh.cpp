#include "pch.h"
#include "_TObjBobsleigh.hpp"
#include "includes/HeroesLib/Globals.hpp"
#include "includes/HeroesLib/Renderware.hpp"
#include "includes/HeroesLib/_Land.hpp"
#include "includes/HeroesLib/_PCStuff.hpp"
#include "includes/HeroesLib/setGen.hpp"
#include "includes/HeroesLib/_ONEFILE.hpp"
#include "includes/HeroesLib/_MODESWITCH.hpp"
#include "newCamera.hpp"



//
float sBobArrowOffsetY = 25.0;

RpClump** pClumpBobArrow = (RpClump * *)0xA77AD4;
//



void initObjS31Bob()
{
	int v4;

	if (LandManager->texDictionary)
	{
		RwTexDictionarySetCurrent(LandManager->texDictionary);
		SetGenTp->field_A50->LoadOneFile((char*)"s31obj.one");
		for (int i = 0; i < 2; ++i)
		{
			v4 = SetGenTp->field_A50->CheckFileID(bobArrow[(i * 7) + pModeSwitch->textLang]);
			if (SetGenTp->field_A50->LoadOneFile((char*)"s31obj.one"))
			{
				pClumpBobArrow[i] = SetGenTp->field_A50->OneFileLoadClump(v4, SetGenTp->field_A50->ExBuffer);
			}
			else
			{
				pClumpBobArrow[i] = 0;
			}
		}
	}
}


void __declspec(naked) SetArrowPosition_hook(TObjBobsleigh* a1)
{
	__asm 
	{
		push ebx;
		call TObjBobsleigh::SetArrowPosition;
		add esp, 0x4;
		ret;
	}
}


RwV3d* TObjBobsleigh::SetArrowPosition(TObjBobsleigh* a1)
{
	int v1;
	RwV3d* result;
	float v4;
	float v5;
	float v7;
	float v8;
	float v9;
	RwFrame* v10; 
	RwMatrix* v11;
	RwV3d* v12;
	RwV3d* v13;
	RwMatrix* v14;
	RwV3d* v15;
	RwV3d* v16;
	RwV3d bobArrowPos;
	RwMatrix matrix;
	RwV3d bobArrowPoints;
	RwMatrix dst;

	v1 = 0;
	do
	{
		result = (RwV3d*)pClumpBobArrow[v1];
		if (result && TObjCamera::currentCamera != v1 && a1->playerIndex == v1)
		{
			sAngle* v3 = &TObjCamera::CurrentCameraParameterP[0]->angle;
			RwMatrixTranslate(&matrix, (RwV3d*)TObjCamera::CurrentCameraParameterP[0], rwCOMBINEREPLACE);
			v4 = 1.0 - sine[(unsigned short)(v3->y + 0x4000)];
			RwMatrixRotateOneMinusCosineSine(&matrix, &AxisY, v4, sine[(unsigned short)v3->y], rwCOMBINEPRECONCA);
			v5 = 1.0 - sine[(unsigned short)(v3->x + 0x4000)];
			RwMatrixRotateOneMinusCosineSine(&matrix, &AxisX, v5, sine[(unsigned short)v3->x], rwCOMBINEPRECONCA);
			v7 = 1.0 - sine[(unsigned short)(v3->z + 0x4000)];
			RwMatrixRotateOneMinusCosineSine(&matrix, &AxisZ, v7, sine[(unsigned short)v3->z], rwCOMBINEPRECONCA);
			RwMatrixInvert(&dst, &matrix);
			v8 = a1->position.y;
			v9 = a1->position.z;
			bobArrowPos.x = a1->position.x;
			bobArrowPos.z = v9;
			bobArrowPos.y = sBobArrowOffsetY + v8;
			RwV3dTransformPoints(&bobArrowPoints, &bobArrowPos, 1, &dst);
			v10 = RpClumpGetFrame(pClumpBobArrow[v1])->child;
			v11 = RwFrameGetLTM(v10);
			v11->right.x = matrix.right.x;
			v11->right.y = matrix.right.y;
			v11->right.z = matrix.right.z;
			v12 = &v11->up;
			v12->x = matrix.up.x;
			v12->y = matrix.up.y;
			v12->z = matrix.up.z;
			v13 = &v11->at;
			v13->x = matrix.at.x;
			v13->y = matrix.at.y;
			v13->z = matrix.at.z;
			RwV3dTransformPoints(&v11->pos, &bobArrowPoints, 1, &matrix);
			v14 = RwFrameGetLTM(v10->child);
			v14->right.x = matrix.right.x;
			v14->right.y = matrix.right.y;
			v14->right.z = matrix.right.z;
			v15 = &v14->up;
			v15->x = matrix.up.x;
			v15->y = matrix.up.y;
			v15->z = matrix.up.z;
			v16 = &v14->at;
			v16->x = matrix.at.x;
			v16->y = matrix.at.y;
			v16->z = matrix.at.z;
			result = RwV3dTransformPoints(&v14->pos, &bobArrowPoints, 1, &matrix);
		}
		++v1;
	} while (v1 < 2);


	int llv = playerTOp[0]->characterNo;
	int address = 0x639120;

	__asm
	{
		mov edi, llv;
		call address;
	}
	return result;
}

void arrowdisptest()
{
	int v1;
	RwV3d* result;
	int* v3;
	float v4;
	float v5;
	unsigned int v6;
	float v7;
	float v8;
	float v9;
	RwFrame* v10;
	RwMatrix* v11;
	RwV3d* v12;
	RwV3d* v13;
	RwMatrix* v14;
	RwV3d* v15;
	RwV3d* v16;
	RwV3d bobArrowPos;
	RwMatrix matrix;
	RwV3d bobArrowPoints;
	RwMatrix dst;
	TObjTeam* a1;

	v1 = 0;
	do
	{
		a1 = teamTOp[v1];
		result = (RwV3d*)pClumpBobArrow[v1];
		if (!result)
		{
			return;
		}
		if (result && TObjCamera::currentCamera != v1 && a1->controllerNo == v1)
		{
			sAngle* v3 = &TObjCamera::CurrentCameraParameterP[0]->angle;
			RwMatrixTranslate(&matrix, (RwV3d*)TObjCamera::CurrentCameraParameterP[0], rwCOMBINEREPLACE);
			v4 = 1.0 - sine[(unsigned short)(v3->y + 0x4000)];
			RwMatrixRotateOneMinusCosineSine(&matrix, &AxisY, v4, sine[(unsigned short)v3->y], rwCOMBINEPRECONCA);
			v5 = 1.0 - sine[(unsigned short)(v3->x + 0x4000)];
			RwMatrixRotateOneMinusCosineSine(&matrix, &AxisX, v5, sine[(unsigned short)v3->x], rwCOMBINEPRECONCA);
			v7 = 1.0 - sine[(unsigned short)(v3->z + 0x4000)];
			RwMatrixRotateOneMinusCosineSine(&matrix, &AxisZ, v7, sine[(unsigned short)v3->z], rwCOMBINEPRECONCA);
			RwMatrixInvert(&dst, &matrix);
			v8 = a1->playerPtr[0]->position.y;
			v9 = a1->playerPtr[0]->position.z;
			bobArrowPos.x = a1->playerPtr[0]->position.x;
			bobArrowPos.z = v9;
			bobArrowPos.y = sBobArrowOffsetY + v8;
			RwV3dTransformPoints(&bobArrowPoints, &bobArrowPos, 1, &dst);
			v10 = RpClumpGetFrame(pClumpBobArrow[v1])->child;
			v11 = RwFrameGetLTM(v10);
			v11->right.x = matrix.right.x;
			v11->right.y = matrix.right.y;
			v11->right.z = matrix.right.z;
			v12 = &v11->up;
			v12->x = matrix.up.x;
			v12->y = matrix.up.y;
			v12->z = matrix.up.z;
			v13 = &v11->at;
			v13->x = matrix.at.x;
			v13->y = matrix.at.y;
			v13->z = matrix.at.z;
			RwV3dTransformPoints(&v11->pos, &bobArrowPoints, 1, &matrix);
			v14 = RwFrameGetLTM(v10->child);
			v14->right.x = matrix.right.x;
			v14->right.y = matrix.right.y;
			v14->right.z = matrix.right.z;
			v15 = &v14->up;
			v15->x = matrix.up.x;
			v15->y = matrix.up.y;
			v15->z = matrix.up.z;
			v16 = &v14->at;
			v16->x = matrix.at.x;
			v16->y = matrix.at.y;
			v16->z = matrix.at.z;
			result = RwV3dTransformPoints(&v14->pos, &bobArrowPoints, 1, &matrix);
		}
		++v1;
	} while (v1 < 2);


	int a2;
	signed int i = 0;
	do
	{
		if (TObjCamera::currentCamera != i && pClumpBobArrow[i])// #inline TObjCamera::GetCurrentCameraNumber(void)
		{
			RwRenderStateGet(rwRENDERSTATECULLMODE, &a2);
			RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)1);
			RpClumpRender(pClumpBobArrow[i]);
			RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)a2);
		}
		++i;
	} while (i < 2);

}

void __declspec(naked) arrowdisptest_hook()
{
	static int address = 0x5B391D;

	__asm
	{
		call arrowdisptest;
		jmp address;
	}
}