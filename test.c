#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <signal.h>
#include <stdlib.h>
#define NR_mycall 351



int main(void){
	int which = PRIO_PROCESS;
	
	int pid = getpid();
	int parent = pid;
	syscall(NR_mycall, pid, 1);	//setting nice_inc 
		
	
	if (fork() == 0){	//this section will run for 1st child
		pid = getpid();
		int nice = getpriority(which,pid);
		printf("I'm child!\nMy pid: %d\nMyParent: %d\nMy nice: %d\n\n", pid, getppid(),nice); 
		
		if (fork() == 0){ //this section will run for child of 1st child
			pid = getpid();
			int nice = getpriority(which,pid);
			printf("I'm 2nd child(child of 1st child)!\nMy pid: %d\nMyParent: %d\nMy nice: %d\n\n", pid, getppid(),nice); 
		}
	}
	else{	//this section will run parent process
		printf("I'm parent!\nMy pid: %d\nMy nice: %d\n\n", pid,  getpriority(which,pid)); 
		
	}
	
	sleep(1);
	if(getpid() == parent){
		exit(0);
	}
	
	printf("\nMy pid: %d\nMyParent: %d\nMy nice: %d\n\n", pid, getppid(),getpriority(which,pid)); 
	printf("*************");
	//For some reason, orphan process does not bond to init process but a different
	//process. Yet, you can observe that nice values are changed when
	//the parent is killed.
	
	
	
	return 0;
}
