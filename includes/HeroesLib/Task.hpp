#pragma once



// Struct Forward Declarations //
struct TObject;
// ~Struct Forward Declarations~ //



// Struct Definitions //
struct sHeap
{
	sHeap* Next;
	unsigned int Size;
};


struct THeapCtrl
{
	sHeap* HeapTop;
	unsigned int HeapSize;
	unsigned int Boundary;


	void* Malloc(unsigned int size);
	void* Free(void* addr);
};
// ~Struct Definitions~ //



// Global Variables //
extern THeapCtrl*& TaskHeap;
extern TObject*& StageObjTop;
extern TObject*& TL_05;
// ~Global Variables~ //