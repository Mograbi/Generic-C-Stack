/*
 * Stack.h
 *
 *  Created on: May 19, 2016
 *      Author: Moawiya
 */

#ifndef STACK_H_
#define STACK_H_

#include "Memory/MemoryChecker.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct _Stack_t *Stack;
typedef enum _ret_t {
	Success, Failure, NullArgument, MemoryError, NoElements
} ReturnVal;

typedef struct _StackElement_t *StackElement;
typedef void* StackData;
typedef StackData (*copyStackData)(StackData);
typedef void (*freeStackData)(StackData);

/*
 *
 */
Stack createStack(copyStackData, freeStackData);
/*
 *
 */
void destroyStack(Stack);
/*
 * push element to the stack O(1)
 */
ReturnVal push(StackData, Stack);
/*
 * pop element from the top of stack O(1)
 */
ReturnVal pop(Stack);
/*
 * return the value of the top element O(1)
 */
ReturnVal top(Stack, StackData*);
/*
 *
 */
unsigned int stackSize(Stack);
/*
 *
 */
void printStack(Stack);
#endif /* STACK_H_ */
