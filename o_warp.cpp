#include "o_warp.hpp"
#include "newCamera.hpp"
#include "includes/HeroesLib/Player.hpp"



void TObjWarp::checkCollision()
{
    ::C_COLLI* hitTarget;
    int v6;

    CCL_MASTER::ClearSearch();
    while (1)
    {
        hitTarget = C_COLLI.IsHitPlayer();
        if (!hitTarget)
        {
            break;
        }
        v6 = GetPlayerNumberFromCCLCharacterId(hitTarget->GetCharacterId());
        //TObjCamera::currentCamera = playerTOp[v6]->teamNo;
        if (v6 == teamTOp[playerTOp[v6]->teamNo]->GetLeaderPlayerNo())
        {
            TObjCamera::WarpCameraAndPlayer((RwV3d*)&SETOBJ_PARAM->PARAM->data[4], playerTOp[v6]->teamNo);
        }
    }
}


void TObjWarp::Exec()
{
    RwReal v4;

    if (!(SETOBJ_PARAM->SETFlag_HHC & 0x400) && (v4 = (SETOBJ_PARAM->renderDistance + 1) * 100.0 * ((SETOBJ_PARAM->renderDistance + 1) * 100.0), setobjCheckRangeOut2(&SETOBJ_PARAM->position, v4)) || SETOBJ_PARAM->SETFlag_HHC & 4)  //#inline TObjSetObj::CheckMustKill((void))
    {
        Kill();
    }
    else
    {
        checkCollision();
        C_COLLI.Entry(&SETOBJ_PARAM->position, &SETOBJ_PARAM->rotation);
    }
}



void __declspec(naked) TObjWarp_Exec_Hook()
{
    TObjWarp* v1;
    __asm
    {
        mov v1, esi;
        mov ecx, esi;
        call TObjWarp::Exec;
        ret;
    }
}