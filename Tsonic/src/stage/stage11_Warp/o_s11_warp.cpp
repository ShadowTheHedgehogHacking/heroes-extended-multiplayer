//#include "pch.h"
#include "../../../../includes/HeroesLib/Globals.hpp"
#include "o_s11_warp.hpp"
#include "../../../../includes/HeroesLib/setGen.hpp"
#include "../../../../includes/HeroesLib/Player.hpp"
#include "../../../../includes/HeroesLib/_MODESWITCH.hpp"
#include "../../../../includes/HeroesLib/action.hpp"
#include "../../../../includes/HeroesLib/_PCStuff.hpp"
#include "../../../../newCamera.hpp"
#include "../../../../includes/HeroesLib/_IsndSE.hpp"
#include "../../../../includes/HeroesLib/_FADEWINDOW.hpp"
#include "../../../../includes/HeroesLib/o_setparticle.hpp"



void TObjS11Warp::Exec()
{
    ::SETOBJ_PARAM* v3; // eax
    int v4; // ecx
    float a2; // ST10_4
    bool v8; // zf
    TObjTeam* v9; // edx
    TObjTeam* currentPlayerTeam; // eax
    int warpPlayerNo; // eax
    double v15; // st6
    sAngle* v16; // ecx
    RwV3d* targetPosition; // [esp-4h] [ebp-38h]
    sAngle rotation; // [esp+10h] [ebp-24h]
    sAngle v19; // [esp+1Ch] [ebp-18h]
    sAngle v20; // [esp+28h] [ebp-Ch]

    v3 = SETOBJ_PARAM;
    v4 = *&v3->SETFlag_HHC;
    v20.x = 0;
    v20.y = 0;
    v20.z = 0;
    if (!(v4 & 0x400) && (a2 = (v3->renderDistance + 1) * 100.0 * ((v3->renderDistance + 1) * 100.0), setobjCheckRangeOut2(&v3->position, a2)) || v3->SETFlag_HHC & 4)  //#inline TObjSetObj::CheckMustKill((void))
    {
        Kill();
    }
    else
    {
        if (isInactive != 1)
        {
            switch (warpState)
            {
                case 0:
                {
                    symbolGlowIntensity = (sine[(unsigned short)(S11_WARP_BRIGHTNESS_SPEED * pModeSwitch->frame + 0x4000)] + 1.0) * ((S11_WARP_MAX_BRIGHTNESS - S11_WARP_MIN_BRIGHTNESS) * 0.5) + S11_WARP_MIN_BRIGHTNESS;
                    if (CheckPlayer() && !IsNowFading())
                    {
                        warpState = 1;
                        warpDelayTimer = 0;
                        if (SndSE)
                        {
                            IsndSE::Play(0x5A00, SndSE, 0, 0);
                            if (SndSE)
                            {
                                IsndSE::Play(0x5A01, SndSE, 0, 0);
                            }
                        }
                        FADESCREEN::GetMainFadeScreenPointer()->CustomOut();
                        v8 = this->isUpsideDown == 1;
                        rotation.x = 0;
                        rotation.y = 0;
                        rotation.z = 0;
                        if (v8)
                        {
                            rotation.z = 0x8000;
                        }
                        Construct_PtclTask_Stage(0, &this->position, &rotation);
                        v9 = teamTOp[currentPlayerNo];


                        for (int i = 0; i < 3; ++i)
                        {
                            warpDelayPosition[(v9->playerNo[i] % 3)] = *PlayerMaster::GetPlayerPositionHistory(v9->playerNo[i], 0);
                        }
                        NoSpeed();
                        teamTOp[currentPlayerNo]->SetMutekiTime(sS11WarpOnCount);
                    }
                    break;
                }
                case 1:
                {
                    ++warpDelayTimer;
                    NoSpeed();
                    if (warpDelayTimer == sS11WarpOnCount)
                    {
                        warpState = 2;
                        NoSpeed();
                    }
                    currentPlayerTeam = teamTOp[this->currentPlayerNo];
                    if (currentPlayerTeam->MutekiTime <= 1)// #inline TObjTeam::GetMutekiTime(const(void))
                    {
                        currentPlayerTeam->SetMutekiTime(2);
                    }
                    break;
                }
                case 2:
                {
                    if (IsNowFading())
                    {
                        NoSpeed();
                        currentPlayerTeam = teamTOp[this->currentPlayerNo];
                        if (currentPlayerTeam->MutekiTime <= 1)// #inline TObjTeam::GetMutekiTime(const(void))
                        {
                            currentPlayerTeam->SetMutekiTime(2);
                        }
                    }
                    else
                    {
                        if (Action.stageNo == LevelID_HangCastle)// #inline ACTION::GetCurrentStageNo(void)
                        {
                            warpPlayerNo = this->currentPlayerNo;
                            v8 = teamTOp[warpPlayerNo]->formationNo == 2;
                            v19.x = 0;
                            v19.y = 0;
                            v19.z = 0x8000;
                            if (v8)
                            {
                                rotation.x = LODWORD(this->targetPosition.x);
                                *&rotation.y = this->targetPosition.y - 35.0;
                                targetPosition = (RwV3d*)&rotation;
                                rotation.z = LODWORD(this->targetPosition.z);
                            }
                            else
                            {
                                targetPosition = &this->targetPosition;
                            }
                            v16 = &v19;
                        }
                        else
                        {
                            targetPosition = &this->targetPosition;
                            warpPlayerNo = this->currentPlayerNo;
                            v16 = 0;
                        }
                        TObjCamera::WarpCameraAndPlayerKeepRelativePosition(warpPlayerNo, v16, targetPosition);
                        FADESCREEN::GetMainFadeScreenPointer()->CustomIn();
                        this->warpState = 3;
                    }
                    break;
                }
                case 3:
                {
                    this->warpState = 0;
                    break;
                }
                default:
                {
                    break;
                }
            }
            TObjS11Warp::SetPosition();
        }
        this->C_COLLI.Entry(&this->position, &v20);
    }
}


bool TObjS11Warp::IsNowFading()
{
    return FADESCREEN::GetMainFadeScreenPointer()->GetRatio() != FADESCREEN::GetMainFadeScreenPointer()->GetRatioTarget();
}



signed int TObjS11Warp::CheckPlayer()
{
    CCL_MASTER::ClearSearch();
    ::C_COLLI* hitTarget = C_COLLI.IsHitKind(0x14u);
    if (!hitTarget)
    {
        CCL_MASTER::ClearSearch();
        while (1)
        {
            hitTarget = C_COLLI.IsHitPlayer();
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
                            this->currentPlayerNo = v7;
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}


RwV3d* TObjS11Warp::NoSpeed()
{
    TObjTeam* TObjTeam = teamTOp[currentPlayerNo];
    PeriCtrl.controlsDisabled[PeriCtrlMap[TObjTeam->controllerNo]] = 1;
    for (int i = 0; i < 3; ++i)
    {
        int v3 = TObjTeam->playerNo[i];
        TObjPlayer* v4 = playerTOp[v3];
        if (v4)
        {
            v4->speedCopy.z = 0.0;
            v4->speedCopy.y = 0.0;
            v4->speedCopy.x = 0.0;
            v4->spd.x = 0.0;
            v4->spd.y = 0.0;
            v4->spd.z = 0.0;
            v4->acceleration.z = 0.0;
            v4->acceleration.y = 0.0;
            v4->acceleration.x = 0.0;
            v4->flt_0xfc.z = 0.0;
            v4->flt_0xfc.y = 0.0;
            v4->flt_0xfc.x = 0.0;
            if (v4)                                  // #inline PlayerMaster::SetPositionP(int, float, float, float)
            {
                v4->position = warpDelayPosition[i];
                RwV3d* v5 = &PlayerMaster::pos_history->entry[0x100 * TObjTeam->playerNo[i] + PlayerMaster::n_history[TObjTeam->playerNo[i]]];
                v5->x = warpDelayPosition[v3 % 3].x;
                v5->y = warpDelayPosition[v3 % 3].y;
                v5->z = warpDelayPosition[v3 % 3].z;
            }
            warpDelayPosition[i].y = sS11WarpJumpSpeed + warpDelayPosition[i].y;
        }
    }
    return 0;
}


void TObjS11Warp::SetPosition()
{
    int result; // eax
    RwFrame* v2; // esi
    RwReal oneMinusCosine; // ST18_4
    RwReal v4; // ecx
    double v5; // st7
    RwReal v6; // edx
    bool v7; // zf
    double v8; // st7
    int v9; // eax
    RwFrame* v10; // esi
    RwReal v11; // ST18_4
    RwReal v12; // ST18_4
    signed int v13; // ebx
    float* v14; // ebp
    double v15; // st7
    float v16; // eax
    int v17; // edi
    unsigned __int16 v18; // di
    RwFrame* v19; // esi
    RwReal v20; // ST18_4
    RwReal v21; // ST18_4
    RwV3d translation; // [esp+1Ch] [ebp-18h]
    RwV3d scale; // [esp+28h] [ebp-Ch]

    result = (int)this->pBaseMaybe;
    if (result)
    {
        scale.z = sS11WarpScale;
        scale.y = sS11WarpScale;
        scale.x = sS11WarpScale;
        v2 = *(RwFrame**)(result + 4);
        RwFrameTranslate(*(RwFrame**)(result + 4), &this->position, rwCOMBINEREPLACE);
        if (this->isUpsideDown == 1)
        {
            oneMinusCosine = 1.0 - flt_A0EE08;
            RwMatrixRotateOneMinusCosineSine(&v2->modelling, &AxisZ, oneMinusCosine, dword_9FEE08, rwCOMBINEPRECONCA);
            RwFrameUpdateObjects(v2);
        }
        RwFrameScale(v2, &scale, rwCOMBINEPRECONCA);
        result = this->isInactive;
        if (!result)
        {
            v4 = this->position.y;
            v5 = sS11WarpScale * 10.0;
            v6 = this->position.z;
            translation.x = this->position.x;
            v7 = this->isUpsideDown == 1;
            translation.y = v4;
            translation.z = v6;
            if (v7)
                v8 = translation.y - v5;
            else
                v8 = v5 + translation.y;
            v9 = *(int*)this->gap144;
            translation.y = v8;
            v10 = *(RwFrame**)(v9 + 4);
            RwFrameTranslate(*(RwFrame**)(v9 + 4), &translation, rwCOMBINEREPLACE);
            if (this->isUpsideDown == 1)
            {
                v11 = 1.0 - flt_A0EE08;
                RwMatrixRotateOneMinusCosineSine(&v10->modelling, &AxisZ, v11, dword_9FEE08, rwCOMBINEPRECONCA);
                RwFrameUpdateObjects(v10);
            }
            v12 = 1.0 - sine[(unsigned __int16)(sS11WarpRotSpd * pModeSwitch->frame + 0x4000)];
            RwMatrixRotateOneMinusCosineSine(
                &v10->modelling,
                &AxisY,
                v12,
                sine[(unsigned __int16)(sS11WarpRotSpd * pModeSwitch->frame)],
                rwCOMBINEPRECONCA);
            RwFrameUpdateObjects(v10);
            RwFrameScale(v10, &scale, rwCOMBINEPRECONCA);
            v13 = 0;
            v14 = (float*)&this->gap144[4];
            do
            {
                v15 = sS11WarpScale + *(v14 - 14);
                v16 = *v14;
                v17 = pModeSwitch->frame - v13 * sS11WarpEffectRotateDelay;
                scale.z = v15;
                v18 = sS11WarpRotSpd * v17;
                scale.y = v15;
                scale.x = v15;
                v19 = *(RwFrame**)(LODWORD(v16) + 4);
                RwFrameTranslate(*(RwFrame**)(LODWORD(v16) + 4), &translation, rwCOMBINEREPLACE);
                if (this->isUpsideDown == 1)
                {
                    v20 = 1.0 - flt_A0EE08;
                    RwMatrixRotateOneMinusCosineSine(&v19->modelling, &AxisZ, v20, dword_9FEE08, rwCOMBINEPRECONCA);
                    RwFrameUpdateObjects(v19);
                }
                v21 = 1.0 - sine[(unsigned __int16)(v18 + 0x4000)];
                RwMatrixRotateOneMinusCosineSine(&v19->modelling, &AxisY, v21, sine[v18], rwCOMBINEPRECONCA);
                RwFrameUpdateObjects(v19);
                result = RwFrameScale(v19, &scale, rwCOMBINEPRECONCA);
                ++v13;
                ++v14;
            } while (v13 < 10);
        }
    }
}


void __declspec(naked) TObjS11Warp_Exec_Hook()
{
    TObjS11Warp* v1;
    __asm
    {
        mov v1, esi;
        mov ecx, esi;
        call TObjS11Warp::Exec;
        ret;
    }
}




RwInt32 sS11WarpOnCount = 30;
RwReal sS11WarpJumpSpeed = 0.050000001;
RwInt32 sS11WarpRotSpd = 60;
RwReal sS11WarpScale = 1.5;
RwInt32 sS11WarpEffectRotateDelay = 2;
RwInt32 S11_WARP_BRIGHTNESS_SPEED = 0x200;
RwReal S11_WARP_MAX_BRIGHTNESS = 1.0;
RwReal S11_WARP_MIN_BRIGHTNESS = 0.1;