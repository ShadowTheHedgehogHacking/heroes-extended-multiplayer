#pragma once
#include "setGen.hpp"
#include "_CCL.hpp"
#include "TObject.hpp"



struct TObjWarp : TObject
{
    void checkCollision(int a1);

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