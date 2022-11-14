#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void sig_int(int);
int main(void){
	char buf[255];
	pid_t pid;
	int status;

	signal(SIGTERM, sig_int);

	if((pid = fork()) < 0){
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if(pid == 0){
		for(;;);
		exit(1);
	}
	printf("Child Process (%d)\n", pid);
	kill(pid, SIGTERM);
	sleep(3);
	kill(pid, SIGKILL);

	exit(0);
}
static void sig_int(int signo){
	printf("Process Terminated\n");
}
