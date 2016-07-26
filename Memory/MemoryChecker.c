/*
 * Memory.c
 *
 *  Created on: May 20, 2016
 *      Author: Moawiya
 */

#include "MemoryChecker.h"

static Memory m;

struct _memoryCheck_t {
	int size;
	unsigned int allocsNum;
	unsigned int freesNum;
	unsigned int totalAllocated;
	AllocateFunc allocate;
	DeallocateFunc deallocate;
};

void initMemory() {
	m = malloc(sizeof(*m));
	if (m == NULL) {
		printf("initializing MemoryChecker Failed !!!\n");
		return;
	}
	m->size = sizeof(*m);
	m->allocsNum = 1;
	m->freesNum = 0;
	m->totalAllocated = sizeof(*m);
	m->allocate = &allocate;
	m->deallocate = &deallocate;
}

void* allocate(size_t size) {
	if (m == NULL) {
		printf("Stack is not initialized !!!\n");
		return NULL;
	}
	void* pntr = malloc(size);
	if (pntr == NULL) {
		return NULL;
	}
	m->size += size;
	m->totalAllocated += size;
	m->allocsNum++;
	return pntr;
}

void deallocate(void* pntr, size_t size) {
	if (pntr == NULL || m == NULL) {
		return;
	}
	m->size -= size;
	m->freesNum++;
	free(pntr);
}

void finishMemory() {
	if (m == NULL) {
		printf("Memory is NULL\n");
		return;
	}
	int size = m->size;
	unsigned int allocsNum = m->allocsNum;
	unsigned int freesNum = m->freesNum;
	unsigned int totalAllocated = m->totalAllocated;
	int sizetoReduce = sizeof(struct _memoryCheck_t);
	free(m);
	freesNum += 1;
	size -= sizetoReduce;
	char *line = "===========================================================";
	printf("HEAP SUMMARY:\n%s\n", line);
	if (size == 0) {
		printf("All heap blocks were freed -- no leaks are possible\n");
	} else {
		printf("%d bytes leaked !!!\n", size);
	}
	printf("total heap usage: %u allocs, %u frees, %u bytes allocated\n",
			allocsNum, freesNum, totalAllocated);
	printf("%s\n", line);
}
