/*
 * stack_test.c
 *
 *  Created on: May 20, 2016
 *      Author: Moawiya
 */

#include "Stack.h"

char* copyChar(char* c) {
	char* copied = allocate(sizeof(char));
	*copied = *c;

	return copied;
}

void freeChar(char* c) {
	if (c != NULL)
		deallocate(c, sizeof(*c));
	//free(c);
}

int main(void) {
	initMemory();
	Stack s = createStack((StackData)&copyChar, (freeStackData)(&freeChar));
	char c = 'a';
	ReturnVal ret = push(&c, s);
	c = 'b';
	push(&c, s);
	c = 'c';
	push(&c, s);
	c = 'a';
	push(&c,s);
	if (ret == Success) {
		printf("pushed\n");
	}
	char* ch;
	ret = top(s, (void**)&ch);
	printf("%d\n", stackSize(s));
	if (*ch == 'a') {
		printf("heeeeee\n");
	}
	deallocate(ch, 1);
	printStack(s);
	ret = pop(s);
	printf("after pop\nsize: %d\n\n", stackSize(s));
	printStack(s);
	destroyStack(s);

	finishMemory();
	return 0;
}
