#include "pch.h"
#include "advertise.hpp"


ADVERTISE& Advertise = *(ADVERTISE*)0x8D6998;
TAdvBg*& gBG_PTR = *(TAdvBg**)0xA2FE38;



/*signed int ADV_2P::Initialize()
{
	int v0; // esi
	signed int v1; // edi
	int* v2; // eax
	int v3; // esi
	int* v4; // eax
	signed int result; // eax

	if (gBG_PTR)
	{
		IsndADX::BGM_Play2("SNG_SYS3.ADX");
		gBG_PTR->mode = 3;
	}
	MAESTRO_ONE::LoadOne(maestro_one_7);
	ADV_PLAYER::Initialize();
	if (maestro_one_7[3])
	{
		v0 = 0;
		do
		{
			v1 = 2;
			do
			{
				v2 = RwTexDictionaryFindNamedTexture(maestro_one_7[3], c_TexName_2[v0]);
				g_Texture_2[v0] = v2;
				if (v2)
					g_RasBackup_2[v0] = *v2;
				++v0;
				--v1;
			} while (v1);
		} while (v0 != 14);
		v3 = 0;
		do
		{
			v4 = RwTexDictionaryFindNamedTexture(maestro_one_7[3], off_7C9E08[v3]);
			if (v4)
				g_Ras_2[v3] = *v4;
			++v3;
		} while (v3 != 2);
	}
	result = 0xC2200000;
	Advertise.cam.x = 0.0;
	Advertise.cam.y = 0.0;
	Advertise.cam.z = -40.0;
	return result;
}*/