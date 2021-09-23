#pragma once
#include "Renderware.hpp"


struct CCL_HIT_INFO
{
	char my_num;
	char hit_num;
	unsigned short flag;
	void* hit_twp;
};




struct CCL_INFO
{
	char kind;
	char form;
	char push;
	char damage;
	unsigned int attr;
	RwV3d center;
	RwReal objectCollisionRadius;
	RwReal objectCollisionRadiusRelatedMaybe;
	RwReal horizontalObjectCollisionRadiusMaybe;
	int field_20;
	int field_24;
	int field_28;
	int field_2C;
	int field_30;
	int field_34;
	RwV3d field_38;
	RwReal field_44;
	int field_48;
	int field_4C;
	int field_50;
	int field_54;
	int field_58;
	int field_5C;
};


struct C_COLLI
{
public:
	C_COLLI* GetHitTarget(CCL_HIT_INFO* a1);
	int GetCharacterId();
	C_COLLI* IsHitKind(unsigned char kind);
	CCL_HIT_INFO* IsHitKindEx(unsigned char kind);
	C_COLLI* IsHitPlayer();
	CCL_HIT_INFO* IsHitPlayerEx();
	CCL_HIT_INFO* ClearInfo();
	int Entry();
	int Entry(RwV3d* position, sAngle* rotation);


	unsigned __int16 id;
	__int16 field_2;
	__int16 strength;
	__int16 vitality;
	__int16 flag;
	__int16 nbInfo;
	float colli_range;
	CCL_INFO* info;
	CCL_HIT_INFO hit_info[9];
	char gap5C[4];
	RwV3d normal;
	sAngle angle;
	int my_num;
	RwV3d field_7C;
};


struct CCL_SEARCH
{
	void** pTaskwk;
	void* FuncAddr;
	int CurrNum;
	int Kind;
};


struct CCL_MASTER
{
	static void ClearSearch();
	static void __cdecl ClearHoming();
	static int GetCurrSearchNum(C_COLLI const* const twp, int kind, int a3);
	static bool EntryPlayerCCL(C_COLLI* a1);
	static bool EntryBulletCCL(C_COLLI* a1);
	static bool EntryEnemyCCL(C_COLLI* a1);
	static bool EntryEnemy2CCL(C_COLLI* a1);
	static bool EntryObjectCCL(C_COLLI* a1);
	static bool EntryObject2CCL(C_COLLI* a1);
	static bool EntryItemCCL(C_COLLI* a1);
	static bool EntryItem2CCL(C_COLLI* a1);
	static bool EntryWallCCL(C_COLLI* a1);
	static bool EntryChaoCCL(C_COLLI* a1);

	static int& GrvDir;
	static short& enemy2_entry_num_pre;
	static short& enemy_entry_num_pre;
	static int*& chao_entry_list;
	static short& chao_entry_num;
	static int*& wall_entry_list;
	static short& wall_entry_num;
	static int*& item2_entry_list;
	static short& item2_entry_num;
	static int*& item_entry_list;
	static short& item_entry_num;
	static int*& object2_entry_list;
	static short& object2_entry_num;
	static C_COLLI** object_entry_list;
	static short& object_entry_num;
	static int*& enemy2_entry_list;
	static short& enemy2_entry_num;
	static int*& enemy_entry_list;
	static short& enemy_entry_num;
	static int*& bullet_entry_list;
	static short*& bullet_entry_num;
	static C_COLLI** player_entry_list;
	static short*& player_entry_num;
	static CCL_SEARCH& Search;
	static int*& ael_num;
	static int*& around_ring_list;
	static int*& arl_num;
	static int*& around_enemy_list;
};
//~



// Global Variables //
extern unsigned int id_table$1906[6];
//~



//
int GetPlayerNumberFromCCLCharacterId(int a1);
//~