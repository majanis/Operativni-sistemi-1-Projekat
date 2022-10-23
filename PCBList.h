/*
 * PCBList.h
 *
 *  Created on: Oct 24, 2020
 *      Author: OS1
 */

#ifndef PCBLIST_H_
#define PCBLIST_H_

#include "pcb.h"
#include "thread.h"
#include "schedule.h"


class PCBList {
//public:
	struct Elem {
		PCB* pcb;
		Elem* next;
		Elem(PCB* pcb, Elem* next=0) {
			this->pcb=pcb;
			this->next=next;
		}
	};

	Elem* first, *last, *current, *prev;
	int numOfPCBs;

public: //modif
	PCBList();
	int getListNumber() {return numOfPCBs;}
	void emptyList();
	~PCBList();
	void toNext();
	void toFirst();
	int curExists();
	int nextExists();
	void addToLast(PCB* newPcb);
	PCB* getFirstPCB();
	PCB* removeFirstPCB();
	PCB* getPCBById(ID id);

	void removePCBById(ID id);

	PCB* getCurrent();
	void removeCurrent();

	void writeAll();

	void unblockPCBs();

	int wakeUpTime();
};




#endif /* PCBLIST_H_ */
