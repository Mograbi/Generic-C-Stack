/*
 * Stack.c
 *
 *  Created on: May 19, 2016
 *      Author: Moawiya
 */

#include "Stack.h"

struct _Stack_t {
	StackElement head;
	StackElement tail;
	copyStackData copyFunc;
	freeStackData freeFunc;
	unsigned int size;
};
struct _StackElement_t {
	StackData data;
	StackElement next;
};

Stack createStack(copyStackData copyFunc, freeStackData freeFunc) {
	if (copyFunc == NULL || freeFunc == NULL) {
		return NULL;
	}
	Stack s = allocate(sizeof(*s));
	if (s == NULL) {
		return NULL;
	}
	s->copyFunc = copyFunc;
	s->freeFunc = freeFunc;
	s->head = NULL;
	s->tail = NULL;
	s->size = 0;
	return s;
}

void destroyStack(Stack s) {
	if (s == NULL) {
		return;
	}
	while (s->head != NULL) {
		StackElement tmp = s->head;
		s->head = s->head->next;
		s->freeFunc(tmp->data);
		deallocate(tmp, sizeof(*tmp));
		//free(tmp);
		s->size--;
	}
	deallocate(s, sizeof(*s));
	//free(s);
}

ReturnVal push(StackData elmnt, Stack s) {
	if (s == NULL || elmnt == NULL) {
		return NullArgument;
	}
	StackData copy_data = s->copyFunc(elmnt);
	if (copy_data == NULL) {
		return MemoryError;
	}
	StackElement new_elmnt = allocate(sizeof(*new_elmnt));
	//StackElement new_elmnt = malloc(sizeof(*new_elmnt));
	if (new_elmnt == NULL) {
		s->freeFunc(copy_data);
		return MemoryError;
	}
	new_elmnt->data = copy_data;
	new_elmnt->next = s->head;
	s->head = new_elmnt;
	if (s->size == 0) {
		s->tail = s->head;
	}
	s->size++;
	return Success;
}

ReturnVal pop(Stack s) {
	if (s == NULL) {
		return NullArgument;
	}
	if (s->size == 0) {
		return NoElements;
	}
	StackElement tmp = s->head;
	s->head = tmp->next;
	s->freeFunc(tmp->data);
	deallocate(tmp, sizeof(*tmp));
	//free(tmp);
	s->size--;
	if (s->size == 0) {
		s->tail = NULL;
	}
	return Success;
}

ReturnVal top(Stack s, StackData* retrieved) {
	if (s == NULL) {
		return NullArgument;
	}
	if (s->size == 0) {
		return NoElements;
	}
	*retrieved = s->copyFunc(s->head->data);
	if (*retrieved == NULL) {
		return MemoryError;
	}
	return Success;
}

unsigned int stackSize(Stack s) {
	if (s == NULL) {
		return 0;
	}
	return s->size;
}

void printStack(Stack s) {
	if (s == NULL || s->size == 0) {
		return;
	}
	char* delim = "|===|";
	char* wall =  "|   |";
	StackElement pntr = s->head;
	while (pntr != NULL) {
		//printf("%s\n", wall);
		printf("| %c |\n", *(char*)pntr->data);
		if (pntr->next == NULL) {
			printf("=====\n");
		} else {
			printf("%s\n", delim);
		}
		pntr = pntr->next;
	}
}
