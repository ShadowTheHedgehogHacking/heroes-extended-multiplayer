#pragma once
#include "includes/HeroesLib/setGen.hpp"
#include "includes/HeroesLib/_CCL.hpp"
#include "includes/HeroesLib/TObject.hpp"



struct TObjWarp : TObject
{
    void checkCollision();

    void Exec();
    void Disp();
    void TDisp();
    void PDisp();
    void PCSpecific();
    void ImmAftSetRaster();
    void Debug();
    void Error();
    void Render();

    TObjSetObj* TObjSetObj;
    SETOBJ_PARAM* SETOBJ_PARAM;
    C_COLLI C_COLLI;
};




void TObjWarp_Exec_Hook();
