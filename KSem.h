/*
 * KSem.h
 *
 *  Created on: May 1, 2021
 *      Author: OS1
 */

#ifndef KSEM_H_
#define KSEM_H_

#include "semaphor.h"
#include "PCBList.h"
#include "pcb.h"
#include "macros.h"

class KSList;

class KernelSem {
friend class PCB;
friend class KSList;
public:
	volatile int value;
	KernelSem(int init=1, Semaphore* mySem);
	~KernelSem();
	Semaphore* mySem;
	static KSList* listOfKernelSemaphores;
	int val() const;
	int wait (Time maxTimeToWait);
	void signal();
	volatile int wakeUpThreadsOnTimer();

	PCBList* waitingOnTimer;
	PCBList* waitingOnSignal;

	int waitOnTime(Time maxTimeToWait);
	int waitOnSignal();

};


#endif /* KSEM_H_ */
