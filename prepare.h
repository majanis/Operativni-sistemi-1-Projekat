///*
// * prepare.h
// *
// *  Created on: May 19, 2021
// *      Author: OS1
// */
//
#ifndef PREPARE_H_
#define PREPARE_H_
//
#include "IVTEntry.h"

#define PREPAREENTRY(num,old)\
void interrupt newIntr##num(...);\
IVTEntry ivtEntry##num(num, newIntr##num);\
void interrupt newIntr##num(...){\
(IVTEntry::IVTable[num])->signal();\
if(old==1)\
ivtEntry##num.oldIntr();\
dispatch();\
}\


#endif /* PREPENTR_H_ */
