#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


#define TRUE 1
#define FALSE 0

int alarm_flag = FALSE;

void setflag(int sig){
	alarm_flag=TRUE;
}

int main(int argc, char **argv){
	int nsecs, j;
	pid_t pid;
	static struct sigaction act;

	if(argc <= 2){
		fprintf(stderr, "Usage: ./a.out #seconds message\n");
		exit(1);
	}
	if((nsecs = atoi(argv[1])) <= 0){
		fprintf(stderr, "invaild time\n");
		exit(2);
	}
	
	switch(pid = fork()){
		case 0:
			break;
		default:
			printf("child process id %d\n", pid);
			exit(0);
	}
	act.sa_handler = setflag;
	sigaction(SIGALRM, &act, NULL);

	alarm(nsecs);
	pause();

	if(alarm_flag == TRUE){
		printf("Alarmed!\t");
		for(j = 2; j<argc; j++)
			printf("%s", argv[j]);
		printf("\n");
	}
	exit(0);
}
