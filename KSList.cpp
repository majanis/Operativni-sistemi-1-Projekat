/*
 * KSList.cpp
 *
 *  Created on: May 1, 2021
 *      Author: OS1
 */


#include "KSList.h"

KSList::KSList() {
	lock
	first=0;
	last=0;
	current=0;
	prev=0;
	numOfKernelSemaphores=0;
	unlock
}

void KSList::emptyList() {
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
		numOfKernelSemaphores=0;
		unlock
}

KSList::~KSList() {
	lock
	emptyList();
	unlock
}


void KSList::toNext() {
	lock
	if (current->next) {
		prev=current;
		current=current->next;
	}
	unlock
}

void KSList::toFirst() {
	lock
	if (first) {
		current=first;
		prev=0;
	}
	unlock
}

void KSList::addToLast(KernelSem* kernelSem) {
	Elem* newKernelSem=new Elem(kernelSem);
	lock
	if (!first) {
		first=newKernelSem;
		toFirst(); //flag
	}
	else {
		Elem* tek=first;
		while (tek->next) tek=tek->next;
		tek->next=newKernelSem;
	}
	numOfKernelSemaphores++;
	toNext();
	unlock
}

int KSList::curExists() {
	if (current==0) return 0;
	return 1;
}


int KSList::nextExists() {
	if(current->next==0) return 0;
	return 1;
}


void KSList::writeAll(){
		Elem* tek=first;
		lock
		while (tek) {
			cout<<tek->kerSem->val()<<endl;
			tek=tek->next;
		}
		unlock
}

volatile void KSList::unblockTimeThreads(){
	Elem* tek=first;
	lock
	while(tek) {
		tek->kerSem->value+=tek->kerSem->wakeUpThreadsOnTimer();
		tek=tek->next;
	}
	unlock
}

KernelSem* KSList::getCurrent(){
	return current->kerSem;
}










