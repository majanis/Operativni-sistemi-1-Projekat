/*
 * main.cpp
 *
 *  Created on: Oct 17, 2020
 *      Author: OS1
 */

#include "system.h"
#include "macros.h"
#include "thread.h"
#include <iostream.h>

extern int userMain(int argc, char* argv[]);

int main(int argc, char* argv[]) {

	System::inic();
	int retVal=userMain(argc, argv);
	System::restore();

	return retVal;
}

