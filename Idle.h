/*
 * Idle.h
 *
 *  Created on: Nov 11, 2020
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_

#include "thread.h"


class Idle: public Thread {

public:
	void run();
	Idle(): Thread() {}
};




#endif /* IDLE_H_ */
