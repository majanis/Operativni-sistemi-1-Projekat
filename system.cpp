/*
 * system.cpp
 *
 *  Created on: Oct 17, 2020
 *      Author: OS1
 */

#include "system.h"
#include <dos.h>
#include <iostream.h>
#include "schedule.h"
#include "pcb.h"
#include "KSem.h"
#include "KSList.h"
#include "KSem.h"

unsigned oldTimerOFF, oldTimerSEG;
volatile unsigned tss=0;
volatile unsigned tsp=0;
volatile unsigned tbp=0;

extern void tick();
volatile int System::contextOnDemand=0;

Thread* System::main=0;
Idle* System::idle=0;

void interrupt timer();

void System::inic() {
#ifndef BCC_BLOCK_IGNORE
	lock
		asm{
			cli
			push es
			push ax

			mov ax,0
			mov es,ax

			mov ax, word ptr es:0022h
			mov word ptr oldTimerSEG, ax
			mov ax, word ptr es:0020h
			mov word ptr oldTimerOFF, ax

			mov word ptr es:0022h, seg timer
			mov word ptr es:0020h, offset timer

			mov ax, oldTimerSEG
			mov word ptr es:0182h, ax
			mov ax, oldTimerOFF
			mov word ptr es:0180h, ax

			pop ax
			pop es
			sti
		}
	idle=new Idle();
	main=new Thread();
	PCB::running=(volatile PCB*)(main->getMyPCB());
	main->myPCB->curState=PCB::READY;
	unlock
#endif
}


void System::restore(){
#ifndef BCC_BLOCK_IGNORE
	lock
	asm {
			cli
			push es
			push ax

			mov ax,0
			mov es,ax

			mov ax, word ptr oldTimerSEG
			mov word ptr es:0022h, ax
			mov ax, word ptr oldTimerOFF
			mov word ptr es:0020h, ax

			pop ax
			pop es
			sti
		}
	delete idle;
	delete main;
	delete PCB::listOfAll;
	delete KernelSem::listOfKernelSemaphores;
	unlock
#endif
}


void interrupt timer() {

	if (System::contextOnDemand==0){
		if (PCB::running->timeLeft!=0)PCB::running->timeLeft--;
		tick();
		KernelSem::listOfKernelSemaphores->unblockTimeThreads();
		asm int 60h;
	}


	if ((PCB::running->timeLeft==0 && PCB::running->timeIsZero==0) || System::contextOnDemand==1) {

#ifndef BCC_BLOCK_IGNORE
			asm {
					mov tsp,sp
					mov tss, ss
					mov tbp, bp
				}
#endif
			PCB::running->sp=tsp;
			PCB::running->ss=tss;
			PCB::running->bp=tbp;


			if (PCB::running->curState == PCB::READY && PCB::running != System::idle->getMyPCB()) {
					Scheduler::put((PCB*) PCB::running);
			}

			PCB::running = Scheduler::get();

				if (PCB::running == 0){
				PCB::running= System::idle->getMyPCB();
				}

				tsp=PCB::running->sp;
				tss=PCB::running->ss;
				tbp=PCB::running->bp;

				PCB::running->timeLeft = PCB::running->tSlice;

#ifndef BCC_BLOCK_IGNORE
				asm {
				mov sp, tsp
				mov ss, tss
				mov bp, tbp
				}
#endif

	}

	System::contextOnDemand=0;
}





void dispatch() {
#ifndef BCC_BLOCK_IGNORE
	lock
	System::contextOnDemand=1;
	timer();
	unlock
#endif

}










