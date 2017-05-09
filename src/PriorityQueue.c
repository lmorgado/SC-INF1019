#include "PriorityQueue.h"
#include <stdio.h>
#include <stdlib.h>

/* Priority queue implemented using Linked List */

PriorityQueue* initPriorityQueue() {
	
	return initLista();
}

void Priority_enQueue(PriorityQueue *pQueue, void *i, element pr) {
	
	insertByPriority(pQueue, i, pr); 
}

void *Priority_deQueue(PriorityQueue *pQueue) {
	
	void *removed = removeBeginning(pQueue);
	return removed;
}

int EmptyPriorityQueue(PriorityQueue *pQueue) {
	
	return isEmpty(pQueue);
}

void releasePriorityQueue(PriorityQueue *pQueue) {
	
	releaseList(pQueue);
}