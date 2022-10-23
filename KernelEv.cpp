///*
// * KernelEv.cpp
// *
// *  Created on: May 18, 2021
// *      Author: OS1
// */
//
#include "KernelEv.h"


KernelEv::KernelEv(IVTNo ivtno) {
	lock
	myValue=0;
	if(PCB::getRunningId()!=System::idle->getId())
	myOwnerThread=((PCB*)PCB::running)->myThread;
	myEntry=ivtno;
	IVTEntry::IVTable[ivtno]->myKEv = this;
	unlock
}


void KernelEv::wait() {
	lock

	if(PCB::getRunningId()==myOwnerThread->getId()) {
		if(--myValue<0) {
			myOwnerThread->getMyPCB()->curState=PCB::BLOCKED;
			dispatch();
		}
	}
	unlock
}




void KernelEv::signal() {
	lock
	if(myValue++<0) {
		myOwnerThread->getMyPCB()->curState=PCB::READY;
		Scheduler::put(myOwnerThread->getMyPCB());
	}
	else {myValue=1;}
	unlock
}


KernelEv::~KernelEv() {
	lock
	myOwnerThread=0;
	IVTEntry::IVTable[myEntry]->myKEv=0;
	unlock
}






