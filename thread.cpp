/*
 * thread.cpp
 *
 *  Created on: Oct 18, 2020
 *      Author: OS1
 */


#include "thread.h"
#include "pcb.h"
#include "schedule.h"
#include "macros.h"
#include "System.h"

Thread::Thread(StackSize stackSize, Time timeSlice) {
	lock
	myPCB=new PCB(stackSize, timeSlice, this);
	unlock
}


Thread::~Thread() {
	waitToComplete();
	lock
	if (myPCB!=0) {
	delete myPCB;
	myPCB=0;
	}
	unlock
}


PCB* Thread::getMyPCB() {
	return myPCB;
}

ID Thread::getId() {
	if (!this) return -1; //in case of error
	return myPCB->getId();
}

ID Thread::getRunningId() {
	return PCB::getRunningId();
}

void Thread::start() {
	lock
	if(myPCB->curState!=PCB::MADE) {
		unlock return;}
	myPCB->curState=PCB::READY;
	Scheduler::put(myPCB);
	unlock
}

void Thread::waitToComplete() {
	if(myPCB!=0) myPCB->waitToComplete();
}

Thread* Thread::getThreadById(ID id) {
	PCB* PCBById=PCB::getPCBById(id);
	if (PCBById!=0)
	return PCBById->myThread;
	else return 0;
}



