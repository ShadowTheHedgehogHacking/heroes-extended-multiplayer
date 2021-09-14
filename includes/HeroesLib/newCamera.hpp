#pragma once
#include "team.hpp"



enum MODE_TYPE
{
	Sample,
	Test,
	Editor,
	Editor2,
	Napa,
	Snapshot,
	Saratoga,
	ColiCheck,
	Klamath,
	Point,
	Ashland,
	Survey,
	Path,
	Leave,
	Easy,
	Motion,
	Fix,
	Point2,
	Takuto,
	Incontinence,
	Rabbit,
	Jones,
	Linepath,
	Bosspoint,
	Sacramento,
	Saratoma
};



struct TObjCamera;
struct TObjCamera__cameraParam;



//(Temp) CLASS STATIC VARIABLES//
//extern TObjCamera::cameraParam** const TObjCamera::CameraParameterP;
//extern TObjCamera::cameraParam** const TObjCamera::CurrentCameraParameterP;
//extern int const& TObjCamera__maxCamera;
//extern int& TObjCamera::currentCamera;
extern char*& CameraModeTable;
extern char*& CameraAdjustTable;
extern TObjCamera* const& cameraTp;
//~(Temp) CLASS STATIC VARIABLES//



struct TObjCamera__cameraParam
{
	float xPosition;
	float yPosition;
	float zPosition;
	int zAngle;
	int xAngle;
	int yAngle;
	char gap18[6];
	short objectSize;
	char gap20[4];
	float aimXPosition;
	float aimZPosition;
	float aimYPosition;
	float xSpeed;
	float zSpeed;
	float ySpeed;
	int stateOrPresetAngle_;
	char gap40[12];
	int cameraLevel;
	int cameraMode;
	char gap54[8908];
	int field_58;
};

struct TObjCamera
{
	static void WarpCameraAndPlayer(RwV3d* targetPosition);
	static void WarpCameraAndPlayerKeepRelativePosition(int warpPlayerNo, sAngle* a2, RwV3d* targetPosition);
	static int SetCameraEarthquake(RwReal a1, signed int frameCount);
	bool EntryAdjustMode(int a1, MODE_TYPE a2);
	int GetCameraLevel();
	int GetCurrentCameraNumber();

	TObject TObject;
	int* RwCamera;
	RwRaster* frameBuffer;
	RwRaster* frameBufferSubRaster[4];
	RwRaster* zBuffer;
	RwRaster* zBufferSubRaster[4];
	char gap54[4];
	int field_0;


	struct cameraParamType
	{
		RwV3d position;
		sAngle angle;
		char gap18[6];
		short objectSize;
		char gap20[4];
		RwV3d targetPosition;
		float xSpeed;
		float zSpeed;
		float ySpeed;
		int stateOrPresetAngle_;
		int earthquakeFrameCount;
		RwReal earthquakeMagnitude;
		RwReal earthquakeAmplitude;
		int cameraLevel;
		int cameraMode;
		char gap54[8908];
		int field_58;
	};

	static cameraParamType** const CameraParameterP;
	static cameraParamType** const CurrentCameraParameterP;
	static cameraParamType* const cameraParam;
	static int const& maxCamera;
	static int &currentCamera;
};