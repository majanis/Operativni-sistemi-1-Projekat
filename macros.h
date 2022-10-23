/*
 * macros.h
 *
 *  Created on: Oct 17, 2020
 *      Author: OS1
 */

#ifndef MACROS_H_
#define MACROS_H_

#include <dos.h>

#define lock asm {pushf; cli;}
#define unlock asm popf;



#endif /* MACROS_H_ */
