/*
 * Memory.h
 *
 *  Created on: May 20, 2016
 *      Author: Moawiya
 */

#ifndef MEMORYCHECKER_H_
#define MEMORYCHECKER_H_


#include <stdio.h>
#include <stdlib.h>

typedef void* (*AllocateFunc)(size_t);
typedef void (*DeallocateFunc)(void*, size_t);
typedef struct _memoryCheck_t *Memory;

/*
 * initialize the memory checker
 */
void initMemory();
/*
 * allocates <size> bytes and return pointer to it
 */
void* allocate(size_t);
/*
 *	free the recieved pointer
 */
void deallocate(void*, size_t);
/*
 *	destroy memory checker and print summary about whether there is leaks
 *	or not.
 */
void finishMemory();


#endif /* MEMORYCHECKER_H_ */
