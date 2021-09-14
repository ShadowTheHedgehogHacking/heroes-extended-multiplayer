#pragma once
#include "TObject.hpp"
#include "_CCL.hpp"



//Forward Declarations//
struct TObjSetObj;
struct SETOBJ_PARAM;
// ~


struct TObjTrainCore
{
    TObject TObject;
    TObjSetObj* TObjSetObj;
    SETOBJ_PARAM* SETOBJ_PARAM;
    C_COLLI C_COLLI;
    RwV3d position;
    sAngle rotation;
    RwInt32 crashDestroyCountMaybe;
    char gapD4[24];
    int field_EC;
};
