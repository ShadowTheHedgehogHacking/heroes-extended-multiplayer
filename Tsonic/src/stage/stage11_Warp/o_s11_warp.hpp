#pragma once
#include "../../../../includes/HeroesLib/TObject.hpp"
#include "../../../../includes/HeroesLib/setGen.hpp"
#include "../../../../includes/HeroesLib/Renderware.hpp"
#include "../../../../includes/HeroesLib/_CCL.hpp"



// Struct Definitions //
struct TObjS11Warp : TObject
{
    signed int CheckPlayer();
    RwV3d* NoSpeed();

    virtual void Exec();
    virtual void Disp();
    virtual void TDisp();
    virtual void PDisp();
    virtual void PCSpecific();
    virtual void ImmAftSetRaster();
    virtual void Debug();
    virtual void Error();
    virtual void Render();

    bool IsNowFading();
    void SetPosition();


    char gap28[4];
    SETOBJ_PARAM* SETOBJ_PARAM;
    C_COLLI C_COLLI;
    RwV3d position;
    char gapC4[12];
    RwV3d targetPosition;
    RwV3d warpDelayPosition[3];
    int warpState;
    int currentPlayerNo;
    int warpDelayTimer;
    float symbolGlowIntensity;
    float symbolGlowEffectLayer1Radius;
    float symbolGlowEffectLayer2Radius;
    float symbolGlowEffectLayer3Radius;
    float symbolGlowEffectLayer4Radius;
    float symbolGlowEffectLayer5Radius;
    float symbolGlowEffectLayer6Radius;
    float symbolGlowEffectLayer7Radius;
    float symbolGlowEffectLayer8Radius;
    float symbolGlowEffectLayer9Radius;
    float symbolGlowEffectLayer10Radius;
    int isInactive;
    int isUpsideDown;
    int* pBaseMaybe;
    char gap144[83];
    char field_0;
};
// ~Struct Definitions~ //



// Global Variables //
extern RwInt32 sS11WarpOnCount;
extern RwReal sS11WarpJumpSpeed;
extern RwInt32 sS11WarpRotSpd;
extern RwReal sS11WarpScale;
extern RwInt32 sS11WarpEffectRotateDelay;
extern RwInt32 S11_WARP_BRIGHTNESS_SPEED;
extern RwReal S11_WARP_MAX_BRIGHTNESS;
extern RwReal S11_WARP_MIN_BRIGHTNESS;
// ~Global Variables~ //


void TObjS11Warp_Exec_Hook();