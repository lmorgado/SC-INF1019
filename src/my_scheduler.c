#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include "Queue.h"
#include "PriorityQueue.h"

#define ISNEWDATA 8890
#define PATH 8891
#define POLICIE 8892
#define ISEND 8893

#define QUANTUM 0.5

typedef enum bound {	
	CPU_BOUND, 
	IO_BOUND
} Bound;

typedef enum policie {	
	REAL_TIME,
	PRIORITY_01,
	PRIORITY_02,
	PRIORITY_03,
	PRIORITY_04,
	PRIORITY_05,
	PRIORITY_06,
	PRIORITY_07,
	ROUND_ROBIN
} Policie;

typedef struct proc {	
	int id;
	const char *path;	
	int bound;
	double time_created;
	double CPUt0;
	double CPUt1;
} Process;

PriorityQueue *READYQueue;
Queue *IOQueue;
int num_processes = 0;
double beginning, now;

double getTimeElapsed(double b);
double getSeconds(double us);
bool isProcessFinish(void);
Process *newProcess();
void removeNodeFromQueue(Lista *queue, int id);
void priorities(Process *P);
void roundrobin(Process *P);
void realtime(Process *P);
void onalarm(void);


int main(void) {

	int isnewdataSeg,
	    isEndSeg,
		pathSeg,
	    policieSeg;
		
	int *isnewdata,
		*isend;
	char *pathstr,	
	     *policiestr;
	
	
	if ((isnewdataSeg = shmget(ISNEWDATA, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR)) == -1) { 		
		perror("NEWINFO");
		exit(1);
	}	
	isnewdata = (int*)shmat(isnewdataSeg, 0, 0);	
	
	if ((isEndSeg = shmget(ISEND, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR)) == -1) { 		
		perror("END");
		exit(1);
	}	
	isend = (int*)shmat(isEndSeg, 0, 0);	
			
	if ((policieSeg = shmget(POLICIE, 20 * sizeof(char), IPC_CREAT | S_IRUSR | S_IWUSR)) == -1) { 		
		perror("POLICIE");
		exit(1);
	}
	policiestr = (char*)shmat(policieSeg, 0, 0);	
		
	if ((pathSeg = shmget(PATH, 20 * sizeof(char), IPC_CREAT | S_IRUSR | S_IWUSR)) == -1) { 		
		perror("PATH");
		exit(1);
	}		
	pathstr = (char*)shmat(pathSeg, 0, 0);
									
	while(1) {

		if(*isnewdata == 1) {
	
			printf("\nPATH: %s", policiestr);			
			*isnewdata = 0;
			
			
			
			
			
			
		
		} else if (*isend == 1) {
			
			
			
			
			
			
			
			break;
		}
	}
	
	
	shmdt(pathstr);
	shmdt(policiestr);
	shmdt(isnewdata);
	shmdt(isend);
	shmctl(isnewdataSeg, IPC_RMID, 0);
	shmctl(pathSeg, IPC_RMID, 0);
	shmctl(policieSeg, IPC_RMID, 0);
	shmctl(isEndSeg, IPC_RMID, 0);

	return 0;
	
}


void priorities(Process *P) {
		
	if (execv(P->path, NULL) < 0)
		exit(1);	

	removeNodeFromQueue(READYQueue, P->id);
}

void roundrobin(Process *P) {

	


		
}

void realtime(Process *P) {
	
	
	
		
}

void onalarm() { 





}


Process *newProcess() {
	
	Process *p = (Process*)malloc(sizeof(Process));	
	p->id = num_processes;
	num_processes++;	
	p->bound = -1;
	p->time_created = getTimeElapsed(beginning);
	p->CPUt0 = 0.000000;
	p->CPUt1 = 0.000000;	
	p->path = "";
	
	return p;
}

void removeNodeFromQueue(Lista *queue, int id) {
		
	Lista **pptr = &(queue->prox);
	
	while (*pptr != NULL) {
	
	    Lista *currentNode = *pptr;	    
		Process *p = (Process*)currentNode->info;
		
	    if (p->id == id) {	        
			*pptr = currentNode->prox;
	        free(currentNode);
	        break;	    
		}
	    
		pptr = &(currentNode->prox);
	}	
}

double getTimeElapsed(double b) {
    
	struct timeval tm;
    gettimeofday( &tm, NULL);
    double t = (double) tm.tv_sec + (double)tm.tv_usec / 1000000.0;

    t = t - b;

    t *= 10000;
	t = (long int) t;
	t /= 10000;

    return t;
}

double getSeconds(double us) {
	
	return us / 1000000;
}

bool isProcessFinish() {
	
	int status;
	
	pid_t return_pid = waitpid(getpid(), &status, WNOHANG);
	
	if (return_pid == 0)
		return FALSE;
	   
	return TRUE;
}
