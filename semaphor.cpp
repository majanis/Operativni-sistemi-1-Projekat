/*
 * semaphor.cpp
 *
 *  Created on: May 1, 2021
 *      Author: OS1
 */


#include "semaphor.h"
#include "KSem.h"
#include "macros.h"
#include "stdio.h"

Semaphore::Semaphore(int init) {
	lock
	myImpl=new KernelSem(init, this);
	unlock
}


Semaphore::~Semaphore() {
	lock
	delete myImpl;
	myImpl=0;
	unlock
}

void Semaphore::signal() {
	myImpl->signal();
}


int Semaphore::wait(Time maxTimeToWait) {return myImpl->wait(maxTimeToWait);}

int Semaphore::val() const {return myImpl->val();}
