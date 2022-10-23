/*
 * pcb.h
 *
 *  Created on: Oct 18, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "thread.h"
#include <dos.h>
#include <iostream.h>
#include "macros.h"
#include "PCBList.h"
#include "system.h"

class PCB {
	private:
	ID myId;
	static ID staticId;
	friend class KSList;
	friend class KernelSem;

	public:
	enum State {MADE, READY, BLOCKED, FINISHED};
	volatile State curState;

	Thread* myThread;

	StackSize sSize;
	int size;
	volatile Time tSlice;
	volatile Time timeLeft;

	volatile int timeIsZero;

	volatile Time timeOnSemaphore;
	volatile int timeOnSemEnded;

	volatile unsigned ss, sp, bp;
	unsigned* stack;

	static void wrapper();
	static volatile PCB* running;


	static ID getRunningId();

	PCB(StackSize stackSize, Time timeSlice, Thread* thread);

	~PCB();
	ID getId();

	void waitToComplete();

	static PCBList* listOfAll;

	static PCB* getPCBById(ID id);

	PCBList* waitingOnMe;

	friend class Thread;

};



#endif /* PCB_H_ */
