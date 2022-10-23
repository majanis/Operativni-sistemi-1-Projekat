///*
// * IVTEntry.cpp
// *
// *  Created on: May 19, 2021
// *      Author: OS1
// */


#include <dos.h>
#include "IVTEntry.h"
#include "System.h"
#include "KernelEv.h"

IVTEntry* IVTEntry::IVTable[256]={0};

void IVTEntry::setInterrupts() {
	lock
	oldIntr=getvect(myEntryNum);
	setvect(myEntryNum, newIntr);
	unlock
}


IVTEntry::IVTEntry(IVTNo myEntryNum, InterruptRoutine newIntr) {
	lock
	this->myEntryNum=myEntryNum;
	this->newIntr=newIntr;
	myKEv=0;
	oldIntr=0;
	setInterrupts();
	IVTable[myEntryNum]=this;
	unlock
}


IVTEntry::~IVTEntry(){
	lock
	setvect(myEntryNum,oldIntr);
	oldIntr = 0;
	newIntr = 0;
	myKEv = 0;
	IVTable[myEntryNum] = 0;
	unlock
}


void IVTEntry::signal(){
	if(myKEv!=0)
	myKEv->signal();
}







