/*
 * KSList.h
 *
 *  Created on: May 1, 2021
 *      Author: OS1
 */

#ifndef KSLIST_H_
#define KSLIST_H_

#include "macros.h"
#include "KSem.h"

class KSList{
	struct Elem {
		KernelSem* kerSem;
		//int blockedVal; //modif
		Elem* next;
		Elem(KernelSem* kerSem, Elem* next=0) {
			this->kerSem=kerSem;
			this->next=next;
			//blockedVal=0; //modif
		}
	};

	Elem* first, *last, *current, *prev;
	int numOfKernelSemaphores;

public:
	KSList();
	int getListNumber() {return numOfKernelSemaphores;}
	void emptyList();
	~KSList();
	void toNext();
	void toFirst();
	int curExists();
	void addToLast(KernelSem* newKerSem);

	KernelSem* getCurrent();
	void removeCurrent();
	volatile void unblockTimeThreads();

	int nextExists();

	void writeAll();

};



#endif /* KSLIST_H_ */
