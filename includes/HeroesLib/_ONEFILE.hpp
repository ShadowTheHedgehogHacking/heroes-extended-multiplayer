#pragma once



// Struct Definitions //
struct ONEFILE
{
	signed int CheckFileID(char* fileName);
	int OpenData(RwUInt32 type, void* addressToDecompressTo);
	RpClump* OneFileLoadClump(int fileIndex, void* addressToDecompressTo);
	int LoadOneFile(char* fileName);
	signed int ReleaseOneFile();


	char fileName[64];
	void* ExBuffer;
	int fileNameSectionPointer;
	void* startOfFilePointer;
	int dword4C;
	int initialized;
	int after0CHeaderPointer;
	int fileSize;
};
// ~Struct Definitions~ //

int Expand2(unsigned char* a1, unsigned char* a2);