/*
 * KSem.cpp
 *
 *  Created on: May 1, 2021
 *      Author: OS1
 */

#include "KSem.h"
#include "KSList.h"
#include "macros.h"
#include "stdio.h"
#include "schedule.h"

KSList* KernelSem::listOfKernelSemaphores= new KSList();

KernelSem::KernelSem(int init, Semaphore* mySem) {
	lock
	value=init;
	this->mySem=mySem;
	listOfKernelSemaphores->addToLast(this);
	waitingOnTimer=new PCBList();
	waitingOnSignal=new PCBList();
	unlock
}

KernelSem::~KernelSem() {
	lock
	delete waitingOnTimer;
	delete waitingOnSignal;
	mySem=0;
	unlock
}



int KernelSem::val() const {return value;}

void KernelSem::signal() {
	lock
	value++;
	if(value<=0) {
		if(waitingOnSignal->getListNumber()>0) {
			PCB* backToScheduler=waitingOnSignal->removeFirstPCB();
			backToScheduler->curState=PCB::READY;
			Scheduler::put(backToScheduler);
		}
		else if(waitingOnTimer->getListNumber()>0) {
			PCB* backToScheduler=waitingOnTimer->removeFirstPCB();
					backToScheduler->curState=PCB::READY;
					Scheduler::put(backToScheduler);
		}
	}
	unlock
}

volatile int KernelSem::wakeUpThreadsOnTimer() {
	return waitingOnTimer->wakeUpTime();
}


int KernelSem::waitOnTime(Time maxTimeToWait) {
	lock
	if(value<=0) {
		value--;
		PCB::running->timeOnSemaphore=maxTimeToWait;
		PCB::running->curState=PCB::BLOCKED;
		waitingOnTimer->addToLast((PCB*)PCB::running);
		unlock
		dispatch();
		if(PCB::running->timeOnSemEnded==1) //13.5.
		return 0;
		else return 1; //13.5.
	}
	else {
		value--;
		unlock
		return 1;
	}
}


int KernelSem::waitOnSignal() {
	lock
	if(value<=0) {
		value--;
		PCB::running->curState=PCB::BLOCKED;
		waitingOnSignal->addToLast((PCB*)PCB::running);
		unlock
		dispatch();
		return 1;
	}
	else {
		value--;
		unlock
		return 1;
	}
}


int KernelSem::wait(Time maxTimeToWait) {
lock
	if(maxTimeToWait==0) {
		unlock
	return waitOnSignal();
	}
	else {
		unlock
		return waitOnTime(maxTimeToWait);
	}
}







