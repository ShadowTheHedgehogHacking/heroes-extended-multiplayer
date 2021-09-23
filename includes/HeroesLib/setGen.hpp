#pragma once

#include "Renderware.hpp"
#include "TObject.hpp"



//
struct TObjSetObj;
struct SetObjParam;
struct SETOBJ_PARAM;
struct BINFile;
struct ONEFILE;
struct C_COLLI;
//



//
struct TObjSetGen : TObject
{
	void** RebuildCommunicateIdList(unsigned char a1);


	static char*& OneFileUsualName;
	static SETOBJ_PARAM*& objTable;

	char gap28[2056];
	int currentObj;
	char gap834[540];
	ONEFILE* field_A50;
};


struct TObjSetObj
{	
public:
	static int CheckRangeOutWithoutIgnorRangeFlag(SETOBJ_PARAM* a1, RwReal a2);
	static int CheckRangeOut(SETOBJ_PARAM* a1, RwReal a2);


	char gap0[4];
	SETOBJ_PARAM* objTableMaybe;
	C_COLLI* C_COLLI;
	char gap8[40];
	SETOBJ_PARAM* field_34;
};


struct SetObjParam
{
	char data[36];
};


struct SETDATA_PARAM
{
	RwV3d position;
	sAngle rotation;
	char SETFlag_HHC;
	char teamLayoutNo;
	short ignored_Usually0x0002;
	int ignored_Usually0x00000000;
	char oddFlag_Usually0x09_Repeat;
	char teamLayoutNo_Repeat;
	short ignored_Usually0x0002_Repeat;
	int ignored_Usually0x00000000_Repeat;
	char itemNo;
	char listNo;
	char communicateId;
	char renderDistance;
	SetObjParam* PARAM;
};


struct SETOBJ_PARAM : SETDATA_PARAM
{
	int field_30;
	int field_34;
	int field_38;
	int field_3C;
};



struct BINFile
{
	RwV3d position;
	sAngle rotation;
	char usually0x09Maybe0x0B;
	char objectTeamID;
	short usually0x0002;
	int usually0x0000;
	__int64 repeatLast8Bytes;
	char objectType;
	char objectList;
	char communicateId;
	char renderDistanceMultiplier;
	int* pMiscProperties;
};



// Function Prototypes //
void setobjCheckRangeOut2_hook(RwV3d* position, RwReal a2);
int setobjCheckRangeOut2(RwV3d const* position, RwReal range);
signed int ObjSwitchesAreAllOn(unsigned char a1);
// ~Function Prototypes~ //



// Global Variables //
extern TObjSetGen*& SetGenTp;
