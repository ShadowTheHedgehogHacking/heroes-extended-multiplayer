#pragma once
#include "Task.hpp"



// Enums //
enum TObjectStatus
{
	TObjectStatus_Killed = 0x1,
	TObjectStatus_Disabled = 0x4,
	TObjectStatus_Hidden = 0x10,
	TObjectStatus_Deleted = 0x20,
};
// ~Enums~ //



// Struct Definitions //
struct TObject
{
	enum Msg
	{
		Msg_KillOk = 0x1
	};


	void Kill();
	bool is(const char* a2);

	TObject(TObject* parent);
	virtual ~TObject();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void PDisp();
	virtual void PCSpecific();
	virtual void ImmAftSetRaster();
	virtual void Debug();
	virtual void Error();
	virtual void Render();

	void* operator new(unsigned int size)
	{
		return TaskHeap->Malloc(size);
	}

	void operator delete(void* addr)
	{
		TaskHeap->Free(addr);
	}


	const char* ClassName;
	unsigned short Signal;
	unsigned short Tag;
	TObject* Prev;
	TObject* Next;
	TObject* Parent;
	TObject* Child;
	short field_1C;
	short objectSize;
	short field_20;
	short field_22;
	short field_24;
	short field_26;
};
// ~Struct Definitions~ //



// //
extern const char* CL_TObject;

extern int& ObjectCount;
// //