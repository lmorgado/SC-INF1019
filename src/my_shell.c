#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define ISNEWDATA 8890
#define PATH 8891
#define POLICIE 8892
#define ISEND 8893

int main(void) {

	FILE *file = NULL;
	
	char command[5];
	
	int status, 
	    pid,
		rd;
		
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
	
	*isnewdata = 0;
	*isend = 0;
								
	if ( (pid = fork()) < 0 ) {
		printf("Erro ao criar processo escalonador filho.\n");
		exit(1);	
	
	} else if(pid == 0) {	
		
		if(execv("myscheduler", NULL) < 0) 
			printf("Erro ao executar o programa escalonador.\n");			
	} 
			
	if((file = fopen("files/exec.txt", "r")) == NULL) {
		printf("Erro ao abrir exec.txt\n");
		exit(1);
	}
	
	while((rd = fscanf(file, "%s %s %s", command, pathstr, policiestr)) != EOF) {

		*isnewdata = 1;		
		sleep(3);
	}
	
	*isnewdata = 0;
	*isend = 1;
	
	wait(&status);
	fclose(file);

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