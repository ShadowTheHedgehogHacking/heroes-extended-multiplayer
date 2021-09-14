#include "pch.h"
//#include "_CCL.hpp"
//#include "_PCStuff.hpp"
#include <HeroesLib\_CCL.hpp>



// //
int& CCL_MASTER::GrvDir = *(int*)0x9CD388;
short& CCL_MASTER::enemy2_entry_num_pre = *(short*)0x9CD38C;
short& CCL_MASTER::enemy_entry_num_pre = *(short*)0x9CD390;
int*& CCL_MASTER::chao_entry_list = *(int**)0x9CD398;
short& CCL_MASTER::chao_entry_num = *(short*)0x9CD3D8;
int*& CCL_MASTER::wall_entry_list = *(int**)0x9CD3D8;
short& CCL_MASTER::wall_entry_num = *(short*)0x9CD7E0;
int*& CCL_MASTER::item2_entry_list = *(int**)0x9CD7E8;
short& CCL_MASTER::item2_entry_num = *(short*)0x9CD9E8;
int*& CCL_MASTER::item_entry_list = *(int**)0x9CD9F0;
short& CCL_MASTER::item_entry_num = *(short*)0x9CDBF0;
int*& CCL_MASTER::object2_entry_list = *(int**)0x9CDBF8;
short& CCL_MASTER::object2_entry_num = *(short*)0x9CDDF8;
C_COLLI** CCL_MASTER::object_entry_list = (C_COLLI**)0x9CDE00;
short& CCL_MASTER::object_entry_num = *(short*)0x9CE200;
int*& CCL_MASTER::enemy2_entry_list = *(int**)0x9CE208;
short& CCL_MASTER::enemy2_entry_num = *(short*)0x9CE408;
int*& CCL_MASTER::enemy_entry_list = *(int**)0x9CE410;
short& CCL_MASTER::enemy_entry_num = *(short*)0x9CE610;
int*& CCL_MASTER::bullet_entry_list = *(int**)0x9CE618;
short*& CCL_MASTER::bullet_entry_num = *(short**)0x9CE818;
C_COLLI** CCL_MASTER::player_entry_list = (C_COLLI**)0x9CE820;
short*& CCL_MASTER::player_entry_num = *(short**)0x9CE860;
CCL_SEARCH& CCL_MASTER::Search = *(CCL_SEARCH*)0x9CE864;
int*& CCL_MASTER::ael_num = *(int**)0x9CE874;
int*& CCL_MASTER::around_ring_list = *(int**)0x9CE888;
int*& CCL_MASTER::arl_num = *(int**)0x9D28C8;
int*& CCL_MASTER::around_enemy_list = *(int**)0x9D28D8;
// ~ ~ //



C_COLLI* C_COLLI::GetHitTarget(CCL_HIT_INFO* a1)
{
    if (!a1)
    {
        return 0;
    }
    return (C_COLLI*)a1->hit_twp;
}


int C_COLLI::GetCharacterId()
{
    return my_num;
}


C_COLLI* C_COLLI::IsHitKind(unsigned char kind)
{
    return GetHitTarget(IsHitKindEx(kind));
}


CCL_HIT_INFO* C_COLLI::IsHitKindEx(unsigned char kind)
{
    int v2; // eax
    int v3; // edi
    CCL_HIT_INFO* result; // eax
    C_COLLI* v5; // edx

    v2 = CCL_MASTER::GetCurrSearchNum(this, kind, 0x23B4);
    v3 = v2;
    if (!(flag & 1))
    {
        return 0;
    }
    for (result = &hit_info[v2]; result < &hit_info[8]; ++v3)
    {
        v5 = (C_COLLI*)result->hit_twp;
        if (result->hit_num == -1)
        {
            break;
        }
        if (v5 && info[result->hit_num].kind == kind)
        {
            CCL_MASTER::Search.CurrNum = v3;
            return result;
        }
        ++result;
    }
    return 0;
}


C_COLLI* C_COLLI::IsHitPlayer()
{
    return GetHitTarget(IsHitPlayerEx());
}


CCL_HIT_INFO* C_COLLI::IsHitPlayerEx()
{
    int v2; // ecx
    int v3; // ecx
    CCL_HIT_INFO* result; // eax
    CCL_HIT_INFO* v5; // edx

    if ((C_COLLI*)CCL_MASTER::Search.pTaskwk != this)// #inline CCL_MASTER::GetCurrSearchNum(const(C_COLLI const *, int, int))
    {
        CCL_MASTER::Search.pTaskwk = (void**)this;
    LABEL_4:
        CCL_MASTER::Search.FuncAddr = (void*)0x22FC;
        CCL_MASTER::Search.Kind = -1;
        v2 = -1;
        goto LABEL_6;
    }
    if (CCL_MASTER::Search.FuncAddr != (void*)0x22FC)
    {
        goto LABEL_4;
    }
    v2 = CCL_MASTER::Search.CurrNum;
LABEL_6:
    v3 = v2 + 1;
    CCL_MASTER::Search.CurrNum = v3;
    if (v3 > 8)
    {
        v3 = 8;
        CCL_MASTER::Search.CurrNum = 8;
    }
    result = &this->hit_info[v3];
    v5 = &this->hit_info[8];
    if (result < v5)
    {
        while (result->hit_num != -1)
        {
            if (!*(short*)result->hit_twp)         // #inline C_COLLI::GetID(const(void))
            {
                CCL_MASTER::Search.CurrNum = v3;        // #inline CCL_MASTER::SetCurrSearchNum((int))
                return result;
            }
            ++result;
            ++v3;
            if (result >= v5)
            {
                return 0;
            }
        }
    }
    return 0;
}


void CCL_MASTER::ClearSearch()
{
    Search.pTaskwk = 0;
    Search.FuncAddr = (void*)-1;
    Search.CurrNum = -1;
    Search.Kind = -1;
};


void __cdecl CCL_MASTER::ClearHoming()
{
    int* around_ring_list;
    int* around_enemy_list;

    ael_num[0] = 0;
    ael_num[1] = 0;
    ael_num[2] = 0;
    ael_num[3] = 0;
    arl_num[0] = 0;
    arl_num[1] = 0;
    arl_num[2] = 0;
    around_ring_list = CCL_MASTER::around_ring_list;
    around_enemy_list = CCL_MASTER::around_enemy_list;
    arl_num[3] = 0;
    int i = 0;
    do
    {
        *around_enemy_list = 0;
        *around_ring_list = 0;
        around_enemy_list += 0x522;
        around_ring_list += 0x202;
    } while (i < 20);
}


int CCL_MASTER::GetCurrSearchNum(C_COLLI const* const twp, int kind, int a3)
{
    int v3; // eax
    int result; // eax

    if ((C_COLLI*)CCL_MASTER::Search.pTaskwk == twp)
    {
        v3 = CCL_MASTER::Search.CurrNum;
    }
    else
    {
        CCL_MASTER::Search.pTaskwk = (void**)twp;
        CCL_MASTER::Search.FuncAddr = (void*)-1;
        CCL_MASTER::Search.Kind = -1;
        v3 = -1;
    }
    if (CCL_MASTER::Search.FuncAddr != (void*)a3)
    {
        CCL_MASTER::Search.FuncAddr = (void*)a3;
        CCL_MASTER::Search.Kind = -1;
        v3 = -1;
    }
    if (kind != -1 && CCL_MASTER::Search.Kind != kind)
    {
        CCL_MASTER::Search.Kind = kind;
        v3 = -1;
    }
    result = v3 + 1;
    CCL_MASTER::Search.CurrNum = result;
    if (result > 8)
    {
        result = 8;
        CCL_MASTER::Search.CurrNum = 8;
    }
    return result;
}


bool CCL_MASTER::EntryPlayerCCL(C_COLLI* a1)
{
    if (CCL_MASTER::player_entry_num[0] >= 0x10u)
    {
        return 0;
    }
    ++CCL_MASTER::player_entry_num[0];
    CCL_MASTER::player_entry_list[CCL_MASTER::player_entry_num[0]] = a1;
    return 1;
}


bool CCL_MASTER::EntryBulletCCL(C_COLLI* a1)
{
    int v1; // ecx

    if (CCL_MASTER::bullet_entry_num[0] >= 0x80u)
        return 0;
    v1 = CCL_MASTER::bullet_entry_num[0];
    ++CCL_MASTER::bullet_entry_num[0];
    CCL_MASTER::bullet_entry_list[v1] = (int)a1;
    return 1;
}


bool CCL_MASTER::EntryEnemyCCL(C_COLLI* a1)
{
    int v1; // ecx

    if (CCL_MASTER::enemy_entry_num >= 0x80u)
        return 0;
    v1 = CCL_MASTER::enemy_entry_num++;
    CCL_MASTER::enemy_entry_list[v1] = (int)a1;
    return 1;
}


bool CCL_MASTER::EntryEnemy2CCL(C_COLLI* a1)
{
    int v1; // ecx

    if (CCL_MASTER::enemy2_entry_num >= 0x80u)
        return 0;
    v1 = CCL_MASTER::enemy2_entry_num++;
    CCL_MASTER::enemy2_entry_list[v1] = (int)a1;
    return 1;
}


bool CCL_MASTER::EntryObjectCCL(C_COLLI* a1)
{
    int v1; // ecx

    if (CCL_MASTER::object_entry_num >= 0x100u)
        return 0;
    v1 = CCL_MASTER::object_entry_num;
    CCL_MASTER::object_entry_num++;
    object_entry_list[v1] = a1;
    return 1;
}


bool CCL_MASTER::EntryObject2CCL(C_COLLI* a1)
{
    int v1; // ecx

    if (CCL_MASTER::object2_entry_num >= 128u)
        return 0;
    v1 = CCL_MASTER::object2_entry_num++;
    CCL_MASTER::object2_entry_list[v1] = (int)a1;
    return 1;
}


bool CCL_MASTER::EntryItemCCL(C_COLLI* a1)
{
    int v1; // ecx

    if (CCL_MASTER::item_entry_num >= 0x80u)
        return 0;
    v1 = CCL_MASTER::item_entry_num++;
    CCL_MASTER::item_entry_list[v1] = (int)a1;
    return 1;
}


bool CCL_MASTER::EntryItem2CCL(C_COLLI* a1)
{
    int v1; // ecx

    if (CCL_MASTER::item2_entry_num >= 0x80u)
        return 0;
    v1 = CCL_MASTER::item2_entry_num++;
    CCL_MASTER::item2_entry_list[v1] = (int)a1;
    return 1;
}


bool CCL_MASTER::EntryWallCCL(C_COLLI* a1)
{
    int v1; // ecx

    if (CCL_MASTER::wall_entry_num >= 0x100u)
        return 0;
    v1 = CCL_MASTER::wall_entry_num++;
    CCL_MASTER::wall_entry_list[v1] = (int)a1;
    return 1;
}


bool CCL_MASTER::EntryChaoCCL(C_COLLI* a1)
{
    int v1; // ecx

    if (CCL_MASTER::chao_entry_num >= 0x10u)
        return 0;
    v1 = CCL_MASTER::chao_entry_num++;
    CCL_MASTER::chao_entry_list[v1] = (int)a1;
    return 1;
}


CCL_HIT_INFO* C_COLLI::ClearInfo()
{
    short v1; // edx
    CCL_HIT_INFO* result; // eax
    CCL_HIT_INFO* v3; // esi
    ::CCL_INFO* v4; // ecx
    char* v5; // ecx

    v1 = this->nbInfo;
    this->flag &= ~0x13Fu;
    result = this->hit_info;
    v3 = &this->hit_info[8];
    this->field_2 = 0;
    v4 = this->info;
    if (v1)
    {
        v5 = &v4->damage;
        v1 = (unsigned short)v1;
        do
        {
            *v5 &= ~0x10u;
            v5 += 0x30;
            --v1;
        } while (v1);
    }
    for (; result != (CCL_HIT_INFO*)v3; ++result)
    {
        result->flag &= ~3u;
        result->my_num = -1;
        result->hit_num = -1;
        result->hit_twp = 0;
    }
    return result;
}


int C_COLLI::Entry()
{
    int result;

    ClearInfo();
    switch (this->id)
    {
    case 0u:
    {
        CCL_MASTER::EntryPlayerCCL(this);
        result = 0;
        break;
    }
    case 1u:
    {
        CCL_MASTER::EntryBulletCCL(this);
        result = 0;
        break;
    }
    case 2u:
    {
        CCL_MASTER::EntryEnemyCCL(this);
        result = 0;
        break;
    }
    case 3u:
    {
        CCL_MASTER::EntryEnemy2CCL(this);
        result = 0;
        break;
    }
    case 4u:
    {
        CCL_MASTER::EntryObjectCCL(this);
        result = 0;
        break;
    }
    case 5u:
    {
        CCL_MASTER::EntryObject2CCL(this);
        result = 0;
        break;
    }
    case 6u:
    {
        CCL_MASTER::EntryItemCCL(this);
        result = 0;
        break;
    }
    case 7u:
    {
        CCL_MASTER::EntryItem2CCL(this);
        result = 0;
        break;
    }
    case 8u:
    {
        CCL_MASTER::EntryWallCCL(this);
        result = 0;
        break;
    }
    case 9u:
    {
        CCL_MASTER::EntryChaoCCL(this);
        result = 0;
        break;
    }
    default:
    {
        result = 0;
        break;
    }
    }
    return result;
}


int C_COLLI::Entry(RwV3d* position, sAngle* rotation)
{
    RwV3d* v4;
    RwV3d* v5;
    RwReal v6;

    v4 = &this->normal;
    v5 = &field_7C;
    v5->x = v4->x;
    v6 = v4->z;
    v5->y = v4->y;
    v5->z = v6;
    *v4 = *position;
    this->angle = *rotation;
    return Entry();
}
//~



//
int GetPlayerNumberFromCCLCharacterId(int a1)
{
    for (int i = 0; i < 6; ++i)
    {
        if (a1 == id_table$1906[i])
        {
            return i;
        }
    }
    return -1;
}
//~



// Global Variable Definitions //
unsigned int id_table$1906[6] = { 1, 2, 3, 4, 5, 6 };
//~