/*
 * system.h
 *
 *  Created on: Oct 17, 2020
 *      Author: OS1
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "macros.h"
#include <dos.h>
#include "thread.h"
#include "pcb.h"
#include "idle.h"

class System {
public:

	static void inic();
	static void restore();
	static volatile int contextOnDemand;
	static Thread* main;
	static Idle* idle;
};



#endif /* SYSTEM_H_ */
