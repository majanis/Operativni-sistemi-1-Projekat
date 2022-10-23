///*
// * IVTEntry.h
// *
// *  Created on: May 19, 2021
// *      Author: OS1
// */


#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "event.h"
#include "kernelev.h"

typedef void interrupt (*InterruptRoutine)(...);
typedef unsigned char IVTNo;

class IVTEntry{
private:
	IVTNo myEntryNum;
public:
	friend class KernelEv;
	KernelEv* myKEv;
	IVTEntry(IVTNo myEntryNum, InterruptRoutine newIntr);
	static IVTEntry* IVTable[256];
	InterruptRoutine oldIntr,newIntr;
	void setInterrupts();
	void signal();
	~IVTEntry();
};
#endif /* IVTENTRY_H_ */














