/*
 * pcb.cpp
 *
 *  Created on: Oct 18, 2020
 *      Author: OS1
 */


#include "pcb.h"
#include <dos.h>
#include <iostream.h>

ID PCB::staticId=0;
volatile PCB* PCB::running=0;
PCBList* PCB::listOfAll= new PCBList();

PCB::PCB(StackSize stackSize, Time timeSlice, Thread* thread){

	lock

	myId=staticId++;
	sSize=stackSize;
	if(timeSlice!=0) timeIsZero=0;
	if(timeSlice==0) {
		timeIsZero=1; }
	tSlice=timeSlice;
	timeLeft=timeSlice;
	myThread=thread;
	curState=PCB::MADE;


	size=stackSize/sizeof(unsigned);
	if (stackSize>=65536) size=65536/sizeof(unsigned);
	if (stackSize<1024) size=1024/sizeof(unsigned);
	stack=new unsigned[size];
	stack[size-1]=0x200;
	stack[size-2]=FP_SEG(&wrapper);
	stack[size-3]=FP_OFF(&wrapper);
	sp=FP_OFF(stack+size-12);
	ss=FP_SEG(stack+size-12);
	bp=FP_OFF(stack+size-12);

	listOfAll->addToLast(this);

	waitingOnMe=new PCBList();

	timeOnSemaphore=0;
	timeOnSemEnded=0;

	unlock

}


PCB::~PCB() {
		lock
		PCB::listOfAll->removePCBById(this->myId);
		delete waitingOnMe;
		waitingOnMe=0;
		delete[] stack;
		stack=0;
		sp=0; ss=0; bp=0;
		myThread=0;
		unlock
}

ID PCB::getId() {
	return myId;
}

ID PCB::getRunningId(){
	if (PCB::running!=0){
		return ((PCB*)PCB::running)->getId();
	}
	else return -1;
}



void PCB::wrapper() {
#ifndef BCC_BLOCK_IGNORE
	PCB::running->myThread->run();
	lock
	PCB::running->curState=PCB::FINISHED;
	PCB::running->waitingOnMe->unblockPCBs();
	unlock
	dispatch();

#endif
}


PCB* PCB::getPCBById(ID id) {
	return listOfAll->getPCBById(id);
}


void PCB::waitToComplete() {
	lock
	if (PCB::running!=(volatile PCB*)this)
		if (this->curState!=PCB::MADE)
		if (this->getId()!=System::idle->myPCB->getId())
			if (this->curState!=PCB::FINISHED) {
				PCB::running->curState=PCB::BLOCKED;
				waitingOnMe->addToLast((PCB*)PCB::running);
				unlock
				dispatch();
				return;
			}
	unlock
}








