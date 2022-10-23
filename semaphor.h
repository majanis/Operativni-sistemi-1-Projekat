///*
// * semaphor.h
// *
// *  Created on: May 1, 2021
// *      Author: OS1
// */
//

// File: semaphor.h
#ifndef _semaphor_h_
#define _semaphor_h_
typedef unsigned int Time;
class KernelSem;
class Thread;
class Semaphore {
public:
 Semaphore (int init=1);
virtual ~Semaphore ();
 virtual int wait (Time maxTimeToWait);
 virtual void signal();
 int val () const; // Returns the current value of the semaphore
private:
 KernelSem* myImpl;
};
#endif
