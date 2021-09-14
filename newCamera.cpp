#include "pch.h"
#include "includes/HeroesLib/TObject.hpp"
#include "includes/HeroesLib/Renderware.hpp"
#include "includes/HeroesLib/Player.hpp"
#include "includes/HeroesLib/Globals.hpp"
#include "newCamera.hpp"


//
TObjCamera* const& cameraTp = *(TObjCamera * *)0xA78D1C;
char*& CameraModeTable = *(char**)0x746700;
char*& CameraAdjustTable = *(char**)0x746860;
//



//
TObjCamera::cameraParamType** const TObjCamera::CameraParameterP = (TObjCamera::cameraParamType**)0xA4CE98;
TObjCamera::cameraParamType** const TObjCamera::CurrentCameraParameterP = (TObjCamera::cameraParamType**)0xA4CEA8;
TObjCamera::cameraParamType* const TObjCamera::cameraParam = (TObjCamera::cameraParamType*)0xA60C30;
int const& TObjCamera::maxCamera = *(int*)0xA60BE4;
int &TObjCamera::currentCamera = *(int*)0xA60BE8;
//



void TObjCamera::WarpCameraAndPlayer(RwV3d* targetPosition, char HHC_teamNo)
{
	int v26;
	RwV3d* v30;
	int v31;


	RwV3d var[3];
	for (int i = 0; i < 3; ++i)
	{
		TObjPlayer* vv1 = playerTOp[i + (3 * HHC_teamNo)];
		if (vv1)
		{
			if (vv1->mode != PlayerMode_Captured)
			{
				vv1->position = *targetPosition;
				vv1->C_COLLI.flag |= 0x100u;     // #inline C_COLLI::Ignore_On((void))
				vv1->PlayerFlag |= 0x200u;           // #inline TObjOldPlayer::SetFlagOfMoved((void))
				PlayerMaster::SetPlayerPosition(i + (3 * HHC_teamNo), 0, targetPosition, 0);
				PlayerMaster::SetPlayerPosition(i + (3 * HHC_teamNo), 1, targetPosition, 0);
			}
		}
	}
	v26 = TObjCamera::currentCamera;
	TObjCamera::cameraParam[HHC_teamNo].position = *targetPosition;
	TObjCamera::cameraParam[HHC_teamNo].position.x += 1.0;
	TObjCamera::cameraParam[HHC_teamNo].targetPosition = *targetPosition;
	*teamTOp[HHC_teamNo]->GetCameraTargetPosition() = *targetPosition;

	TObjTeam* v2 = teamTOp[HHC_teamNo];
	v2->SetCameraTargetPositionHistory(targetPosition);
	//EntryAdjustMode(currentCamera, (MODE_TYPE)0);
	if (HHC_teamNo <= TObjCamera::cameraParam[HHC_teamNo].cameraLevel)
	{
		v31 = HHC_teamNo * 0x2324 + 0x114 * HHC_teamNo;
		*(int*)&TObjCamera::cameraParam[0].gap54[v31 + 0x113C] = 0;
		*(int*)&TObjCamera::cameraParam[0].gap54[v31 + 0x1140] = 0;
		*(int*)&TObjCamera::cameraParam[0].gap54[v31 + 0x1144] = 0;
		memset(&TObjCamera::cameraParam[0].gap54[v31 + 0x1150], 0, 0x100u);
		*(int*)&TObjCamera::cameraParam[0].gap54[v31 + 0x1148] = 0;
	}
}


void TObjCamera::WarpCameraAndPlayerKeepRelativePosition(int warpPlayerNo, sAngle* a2, RwV3d* targetPosition)
{
	TObjTeam* pCurrentWarpTeam;
	RwV3d* v6; // esi
	RwReal* v7; // ebp
	char v9;
	TObjPlayer* v10; // ecx
	RwReal oneMinusCosine; // ST14_4
	int currentWarpTeamPlayerNoIndex;
	TObjPlayer* pCurrentPlayerIndex;
	RwV3d* currentPlayerPosition;
	int v26;
	TObjTeam* result; // eax
	RwV3d* v30; // esi
	int v31;
	int currentWarpTeamLeaderPlayerNo; // [esp+24h] [ebp-14h]
	int v36; // [esp+28h] [ebp-10h]
	RwMatrix matrix; // [esp+48h] [ebp+10h]


	pCurrentWarpTeam = teamTOp[warpPlayerNo];
	currentWarpTeamLeaderPlayerNo = pCurrentWarpTeam->playerNo[(char)pCurrentWarpTeam->nowLeaderPlayerNo];
	RwV3d* v37 = PlayerMaster::GetPlayerPositionHistory(currentWarpTeamLeaderPlayerNo, 0);
	RwV3d var[3];
	for (int i = 0; i < 3; ++i)
	{
		v9 = pCurrentWarpTeam->playerNo[i];
		v10 = playerTOp[v9];
		if (v10)
		{
			if (v10->mode != PlayerMode_Captured)
			{
				v10->C_COLLI.flag |= 0x100u;     // #inline C_COLLI::Ignore_On((void))
				v10->PlayerFlag |= 0x200u;           // #inline TObjOldPlayer::SetFlagOfMoved((void))
				if (v9 != currentWarpTeamLeaderPlayerNo)
				{
					v36 = playerTOp[v9]->role - 1;
					if (v36 < 0 || gFormationPositionDat[4 * (v36 + 2 * (pCurrentWarpTeam->teamKind + 5 * pCurrentWarpTeam->formationNo)) + 7] == 3) // #inline TObjTeam::GetFormation(const(void))
					{
						var[i] = *targetPosition;
					}
					else
					{
						var[i] = *PlayerMaster::GetPlayerPositionHistory(v9, 0);
						var[i].x = var[i].x - v37->x;
						var[i].y = var[i].y - v37->y;
						var[i].z = var[i].z - v37->z;
						
						if (a2)
						{
							oneMinusCosine = 1.0 - sine[(unsigned short)(a2->z + 0x4000)];
							RwMatrixRotateOneMinusCosineSine(&matrix, &AxisZ, oneMinusCosine, sine[(unsigned short)a2->z], rwCOMBINEREPLACE);
							oneMinusCosine = 1.0 - sine[(unsigned short)(a2->x + 0x4000)];
							RwMatrixRotateOneMinusCosineSine(&matrix, &AxisX, oneMinusCosine, sine[(unsigned short)a2->x], rwCOMBINEPRECONCA);
							oneMinusCosine = 1.0 - sine[(unsigned short)(a2->y + 0x4000)];
							RwMatrixRotateOneMinusCosineSine(&matrix, &AxisY, oneMinusCosine, sine[(unsigned short)a2->y], rwCOMBINEPRECONCA);
							RwMatrixTranslate(&matrix, &var[i], rwCOMBINEPRECONCA);
							var[i] = matrix.pos;
						}
						var[i].x = targetPosition->x + var[i].x;
						var[i].y = targetPosition->y + var[i].y;
						var[i].z = targetPosition->z + var[i].z;
					}
				}
			}
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		currentWarpTeamPlayerNoIndex = pCurrentWarpTeam->playerNo[i];
		pCurrentPlayerIndex = playerTOp[currentWarpTeamPlayerNoIndex];
		if (pCurrentPlayerIndex && pCurrentPlayerIndex->mode != PlayerMode_Captured)
		{
			currentPlayerPosition = &pCurrentPlayerIndex->position;
			if (currentWarpTeamPlayerNoIndex == currentWarpTeamLeaderPlayerNo)
			{
				*currentPlayerPosition = *targetPosition;
				if (playerTOp[currentWarpTeamPlayerNoIndex])
				{
					PlayerMaster::pos_history->entry[PlayerMaster::n_history[currentWarpTeamPlayerNoIndex] + (currentWarpTeamPlayerNoIndex * 0x100)] = *targetPosition; // #inline PlayerMaster::SetPlayerPosition((int,uchar,RwV3d *,sAngle *))
				}
				if (playerTOp[currentWarpTeamPlayerNoIndex])
				{
					PlayerMaster::pos_history->entry[(PlayerMaster::n_history[currentWarpTeamPlayerNoIndex] - 1) + (currentWarpTeamPlayerNoIndex * 0x100)] = *targetPosition; // #inline PlayerMaster::SetPlayerPosition((int,uchar,RwV3d *,sAngle *))
				}
			}
			else
			{
				currentPlayerPosition->x = var[i].x;;
				currentPlayerPosition->y = var[i].y;;
				currentPlayerPosition->z = var[i].z;;
				if (playerTOp[currentWarpTeamPlayerNoIndex] && var)
				{
					PlayerMaster::SetPlayerPosition(currentWarpTeamPlayerNoIndex, 0, &var[i], 0);
				}
				if (playerTOp[currentWarpTeamPlayerNoIndex] && var)
				{
					PlayerMaster::SetPlayerPosition(currentWarpTeamPlayerNoIndex, 1, &var[i], 0);
				}
			}
		}
	}
	v26 = TObjCamera::currentCamera;
	TObjCamera::cameraParam[v26].position = *targetPosition;
	TObjCamera::cameraParam[v26].position.x += 1.0;
	TObjCamera::cameraParam[v26].targetPosition = *targetPosition;
	teamTOp[v26]->cameraTargetPosition = *targetPosition;
	result = teamTOp[v26];
	v30 = &result->cameraTargetPositionHistory[result->cameraTargetPositionHistoryCount];
	v30->x = result->cameraTargetPosition.x;
	v30->y = result->cameraTargetPosition.y;
	v30->z = result->cameraTargetPosition.z;
	if (++result->cameraTargetPositionHistoryCount >= 16)
	{
		result->cameraTargetPositionHistoryCount = 0;
	}
	if (v26 <= TObjCamera::cameraParam[v26].cameraLevel)
	{
		v31 = v26 * 0x2324 + 0x114 * v26;
		*(int*)&TObjCamera::cameraParam[0].gap54[v31 + 0x113C] = 0;
		*(int*)&TObjCamera::cameraParam[0].gap54[v31 + 0x1140] = 0;
		*(int*)&TObjCamera::cameraParam[0].gap54[v31 + 0x1144] = 0;
		result = 0;
		memset(&TObjCamera::cameraParam[0].gap54[v31 + 0x1150], 0, 0x100u);
		*(int*)&TObjCamera::cameraParam[0].gap54[v31 + 0x1148] = 0;
	}
}


int TObjCamera::SetCameraEarthquake(RwReal a1, signed int frameCount)
{
	TObjCamera::cameraParam[currentCamera].earthquakeFrameCount = frameCount;
	TObjCamera::cameraParam[currentCamera].earthquakeMagnitude = 1.0 / frameCount;
	TObjCamera::cameraParam[currentCamera].earthquakeAmplitude = a1;
	return currentCamera * 0x2324;
}


bool TObjCamera::EntryAdjustMode(int cameraLevel, MODE_TYPE mode)
{
	if (cameraLevel <= GetCameraLevel())
	{
		int v1 = (0x114 * cameraLevel) + (currentCamera * 0x2324);
		*&cameraParam[0].gap54[v1 + 0x113C] = mode;
		*&cameraParam[0].gap54[v1 + 0x1140] = 0;
		*&cameraParam[0].gap54[v1 + 0x1144] = 0;
		memset(&cameraParam[0].gap54[v1 + 0x1150], 0, 0x100u);
		*&cameraParam[0].gap54[v1 + 0x1148] = CameraAdjustTable[2 * mode + 1];
		return true;
	}
	return false;
}


int TObjCamera::GetCameraLevel()
{
	return cameraParam[currentCamera].cameraLevel;
}


int TObjCamera::GetCurrentCameraNumber()
{
	return currentCamera;
}