#include <signal.h> //signal
#include <stdio.h> //printf
#include <unistd.h> //pause()
void myhandler(int signo){ //handler 함수 작성(signal number input)
	switch(signo){
		//sigquit: 입력시 foreground의 모든 group process에 신호전달, 디버그용 core파일 생성
		case SIGQUIT : printf("SIGQUIT(%d) is caught\n", SIGQUIT);
					   break;
		case SIGTSTP : printf("SIGTSTP(%d) is caught\n", SIGTSTP);
					   break;
		case SIGTERM : printf("SIGTERM(%d) is caught\n", SIGTERM);
					   break;
		case SIGUSR1 : printf("SIGUSR1(%d) is caught\n", SIGUSR1);
					   break;
		default: printf("other signal\n");
	}
	return;
}

int main(){
	signal(SIGQUIT, myhandler);
	signal(SIGTSTP, SIG_DFL); //use default handler
	signal(SIGTERM, myhandler);
	signal(SIGUSR1, myhandler);

	for(;;)
		pause(); //stop until receive a signal
}
