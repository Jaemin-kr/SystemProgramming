#include <stdio.h>
#include <signal.h>

void catchsig(int signo){
    printf("CATCH signo = %d\n", signo);
}

int main(){
    sigset_t newmask, oldmask;
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGTSTP);
    sigpromask(SIG_BLOCK, &newmask, &oldmask);
    signal(SIGKILL, catchsig);
    signal(SIGQUIT, catchsig);
    signal(SIGTSTP, catchsig);
    signal(SIGTERM, catchsig);
    signal(SIGINT, SIG_IGN);
    signal(SIGUSR1, SIG_DFL);
    for(;;) pause();
}