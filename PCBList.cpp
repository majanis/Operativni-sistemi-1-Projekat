/*
 * PCBList.cpp
 *
 *  Created on: Oct 24, 2020
 *      Author: OS1
 */

#include "PCBList.h"


PCBList::PCBList() {
	lock
	first=0;
	last=0;
	current=0;
	prev=0;
	numOfPCBs=0;
	unlock
}

void PCBList::emptyList() {
	lock
	while (first) {
		Elem* old=first;
		first=first->next;
		delete old;
	}
		first=0;
		last=0;
		current=0;
		prev=0;
		numOfPCBs=0;
		unlock
}

PCBList::~PCBList() {
	lock
	emptyList();
	unlock
}

PCB* PCBList::getPCBById(ID id) {
	PCB* found=0;
	lock
	current=first;
	while (current) {
		if (current->pcb->getId()==id) found=current->pcb;
		prev=current;
		current=current->next;
	}
	toFirst();
	unlock
	return found;
}


void PCBList::removePCBById(ID id) {
	current=first;
	prev=0;
	lock
	while (current) {
		if (current->pcb->getId()==id) {
			removeCurrent();
			break;
		}
		prev=current;
		current=current->next;
		if (!current) {
			toFirst(); //FLAG
			unlock
			return;
		}
	}
	unlock
}


void PCBList::toNext() {
	lock
	if (current->next) {
		prev=current;
		current=current->next;
	}
	unlock
}

void PCBList::toFirst() {
	lock
	if (first) {
		current=first;
		prev=0;
	}
	unlock
}

void PCBList::addToLast(PCB* newPcb) {
	Elem* newpcb=new Elem(newPcb);
	lock
	if (!first) {
		first=newpcb;
		toFirst(); //flag
	}
	else {
		Elem* tek=first;
		while (tek->next) tek=tek->next;
		tek->next=newpcb;
	}
	numOfPCBs++;
	toNext();
	unlock
}


void PCBList::writeAll() {
	Elem* tek=first;
	lock
	while (tek) {
		cout<<tek->pcb->getId()<<endl;
		tek=tek->next;
	}
	unlock
}

PCB* PCBList::getFirstPCB() {
	return first->pcb;
}

PCB* PCBList::getCurrent() {
	return current->pcb;
}

int PCBList::curExists() {
	if (current==0) return 0;
	return 1;
}

int PCBList::nextExists(){
	if ((current->next)==0) return 0;
	return 1;
}


void PCBList::removeCurrent() {
	lock
	if (curExists()) {
		Elem* old=current;
		current=current->next;
		(!prev? first: prev->next)=current;
		delete old;
		numOfPCBs--;
	}
	unlock
}

PCB* PCBList::removeFirstPCB() {
	lock
	PCB* theFirst=getFirstPCB();
	toFirst();
	removeCurrent();
	unlock
	return theFirst;
}

int PCBList::wakeUpTime(){
lock
if(numOfPCBs==0) {
	unlock
	return 0;
}
if(first==0) {
	unlock
	return 0;
}
current=first;
prev=0;
int addToValue=0;

while(curExists()){
	if(current->pcb->timeOnSemaphore>0) current->pcb->timeOnSemaphore--;
	if(current->pcb->timeOnSemaphore==0) {
		current->pcb->timeOnSemEnded=1; //flag 13.5.
		addToValue++;
		current->pcb->curState=PCB::READY;
		Scheduler::put(current->pcb);
		removeCurrent();
	}
	else {
		prev=current;
		current=current->next;
	}
}
toFirst();
unlock
return addToValue;
}


void PCBList::unblockPCBs() {
	if(numOfPCBs==0) return;
	lock
	toFirst();
	while(curExists()) {
		current->pcb->curState=PCB::READY;
		Scheduler::put(current->pcb);
		removeCurrent();
		if(first) toFirst();
		else current=0;
	}
	first=prev=0;
	unlock
}










