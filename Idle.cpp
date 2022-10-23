/*
 * Idle.cpp
 *
 *  Created on: Nov 11, 2020
 *      Author: OS1
 */

#include "idle.h"
#include "macros.h"
#include <iostream.h>

void Idle::run() {
	while (1) {
		for (int i=0; i<10000; i++)
			for (int j=0; j<1000; j++)
			for (int l=0; l<100; l++){}
	}
}


