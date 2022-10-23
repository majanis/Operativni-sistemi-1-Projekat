///*
// * KernelEv.h
// *
// *  Created on: May 18, 2021
// *      Author: OS1
// */
//
#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "event.h"
#include "thread.h"
#include "pcb.h"
#include "macros.h"
#include "IVTEntry.h"

typedef unsigned char IVTNo;

class KernelEv {

private:
	IVTNo myEntry;
	Thread* myOwnerThread;

public:
	unsigned int priority;
	int myValue; //flag, modif
	KernelEv(IVTNo ivtno);
	~KernelEv();
	void wait();
	void signal();
	friend class IVTEntry;
};


#endif /* KERNELEV_H_ */



