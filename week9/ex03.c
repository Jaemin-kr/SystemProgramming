#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void myhandler(int signo);
int main(void){
	signal(SIGQUIT, myhandler);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTERM, myhandler);
	signal(SIGUSR1, myhandler);

	for(;;) pause();
	return 0;
}

void myhandler(int signo){
	switch(signo){
		case SIGQUIT : printf("SIGQUIT(%d) is caught\n", SIGQUIT);
					   break;
		case SIGTSTP : printf("SIGTSTP(%d) is caught\n", SIGTSTP);
					   break;
		case SIGTERM : printf("SIGTERM(%d) is caught\n", SIGTERM);
					   break;
		default:
					   printf("other signal\n");
	}
	return;
}
		
