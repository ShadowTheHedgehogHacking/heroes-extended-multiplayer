#pragma once
#include "Renderware.hpp"
#include "TObject.hpp"



struct FADESCREEN : TObject
{
    virtual void Exec();
    virtual void Disp();
    virtual void TDisp();
    virtual void PDisp();
    virtual void PCSpecific();
    virtual void ImmAftSetRaster();
    virtual void Debug();
    virtual void Error();
    virtual void Render();
    virtual int Disp_Uso();
    virtual int Disp_Uso2();
    virtual int SetCustomClump(int* RpClump);
    virtual RwReal GetRatio();
    virtual RwReal GetRatioTarget();
    virtual void FadeIn();
    virtual void FadeOut();
    virtual int WhiteIn();
    virtual int WhiteOut();
    virtual int BlackIn();
    virtual int BlackOut();
    virtual int FlashIn();
    virtual int FlashOut();
    virtual int SpiralIn();
    virtual int SpiralOut();
    virtual void CustomIn();
    virtual void CustomOut();
    virtual int SetFadeObject(int FADEOBJ);
    virtual int WipeUp();
    virtual int KeepScreen();

    static FADESCREEN* GetMainFadeScreenPointer();
    static void SetAlpha(RwRGBA& a1, unsigned char a2);
    static RwUInt8 GetRed(RwRGBA& a1);

    RwInt32 field_28;
    RwRGBA ScreenColor;
    RwRGBA ScreenColor2;
    RwReal field_34;
    char gap38[4];
    int field_3C;

    //static constexpr FADESCREEN*& pMainFadeScreen = *(FADESCREEN**)0x0A776F0;
    static FADESCREEN*& pMainFadeScreen;
};


struct FADEWINDOW : FADESCREEN
{
    void Exec();
    void Disp();
    void TDisp();
    void PDisp();
    void PCSpecific();
    void ImmAftSetRaster();
    void Debug();
    void Error();
    void Render();
    int Disp_Uso();
    int Disp_Uso2();
    int SetCustomClump(int* RpClump);
    RwReal GetRatio();
    RwReal GetRatioTarget();
    void FadeIn();
    void FadeOut();
    int WhiteIn();
    int WhiteOut();
    int BlackIn();
    int BlackOut();
    int FlashIn();
    int FlashOut();
    int SpiralIn();
    int SpiralOut();
    void CustomIn();
    void CustomOut();
    int SetFadeObject(int FADEOBJ);
    int WipeUp();
    int KeepScreen();


    char gap40[4];
    RwReal ratio;
    RwReal ratioTarget;
    RwInt32 field_4C;
    RwInt32 field_50;
    int field_0;
};
