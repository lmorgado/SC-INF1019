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
	double instantI;
	double deltaD;
} Process;

PriorityQueue *READYQueue;
Queue *IOQueue;
int num_processes = 0;
double beginning, now;

double getTimeElapsed(double b);
double getSeconds(double us);
char *str_slice(char str[], int slice_from, int slice_to);
bool isProcessFinish(void);
Process *newProcess();
void insertNodeToQueue(PriorityQueue *pqueue, char *path, char *policie);
void removeNodeFromQueue(Lista *queue, int id);
void priorities(void);
void roundrobin(void);
void realtime(void);
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
	 
	 beginning = getTimeElapsed(0.00000);
	 now = getTimeElapsed(beginning);
		
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
	
	READYQueue = initPriorityQueue();
	IOQueue = initQueue();
									
	while(1) {

		if(*isnewdata == 1) {		
			
			*isnewdata = 0;
			insertNodeToQueue(READYQueue, pathstr, policiestr);
		
		} else if (*isend == 1 && EmptyPriorityQueue(READYQueue)) { break; }
	
		priorities();
		roundrobin();
		realtime();	
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

void priorities() {
		
	if (execv(P->path, NULL) < 0)
		exit(1);	

	removeNodeFromQueue(READYQueue, P->id);
}




void roundrobin() {

	


		
}

void realtime() {
	
	
	
		
}

void onalarm() { 


}






Process *newProcess() {
	
	Process *p = (Process*)malloc(sizeof(Process));	
	p->id = num_processes;
	num_processes++;
	p->bound = -1;
	p->time_created = getTimeElapsed(beginning);
	p->instantI = 0.00;
	p->deltaD = 0.00;	
	p->path = "";
		
	return p;
}

void insertNodeToQueue(PriorityQueue *pqueue, char *path, char *policie) {
	
	Policie priority;
	
	Process *process = newProcess();
	
	process->path = path;
		
	if(policie[0] == 'R')	
		priority = ROUND_ROBIN;
			
	 else if(policie[0] == 'P') 
		priority = (Policie)(policie[3] - '0');
			
	 else {
		
		char *substr;
		
		priority = REAL_TIME;
				
		substr = strstr(policie, "I=") + 2;
		process->instantI = atof(substr);		
		
		substr = strstr(policie, "D=") + 2;
		process->deltaD = atof(substr);							
	}
	
	Priority_enQueue(queue, process, priority);
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

char *str_slice(char str[], int slice_from, int slice_to) {
   
    if (str[0] == '\0')
        return NULL;

    char *buffer;
    size_t str_len, buffer_len;

    if (slice_to < 0 && slice_from < slice_to) {
        str_len = strlen(str);

        if (abs(slice_to) > str_len - 1)
            return NULL;

        if (abs(slice_from) > str_len)
            slice_from = (-1) * str_len;

        buffer_len = slice_to - slice_from;
        str += (str_len + slice_from);

    } else if (slice_from >= 0 && slice_to > slice_from) {
        str_len = strlen(str);

        if (slice_from > str_len - 1)
            return NULL;

        buffer_len = slice_to - slice_from;
        str += slice_from;

    } else
        return NULL;

    buffer = calloc(buffer_len, sizeof(char));
    strncpy(buffer, str, buffer_len);
    return buffer;
}
