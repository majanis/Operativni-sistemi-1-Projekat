///*
// * Event.cpp
// *
// *  Created on: May 18, 2021
// *      Author: OS1
// */
//
#include "event.h"
#include "kernelev.h"
#include "macros.h"


Event::Event(IVTNo ivtNo) {
	lock
	myImpl=new KernelEv(ivtNo);
	unlock
}

Event::~Event() {
	lock
	if(myImpl!=0) delete myImpl;
	myImpl=0;
	unlock
}

void Event::wait() {
	myImpl->wait();
}

void Event::signal() {
	myImpl->signal();
}

