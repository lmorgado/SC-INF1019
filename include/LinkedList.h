#ifndef LIST_H
#define LIST_H

	typedef enum { FALSE, TRUE } bool;
	
	typedef int element;

	typedef struct no {
		
		element priority;
		void *info;
		struct no *prox;
	
	} Lista;

#endif

Lista* initLista();
int isEmpty(Lista *l);
long int size(Lista *l);
void insertEnd(Lista *l, void *i, element pr);
void insertBeginning(Lista *l, void *i, element pr);
void insertByPriority(Lista *l, void *i, element pr);
void *removeBeginning(Lista *l);
void *removeEnd(Lista *l);
void releaseList(Lista *l);