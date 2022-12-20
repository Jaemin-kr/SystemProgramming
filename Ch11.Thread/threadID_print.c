#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t ntid;

void printids(const char *s){
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
    //스레드의 pid와 tid출력
}
//start rtn - print "new thread"
void *thr_fn(void *arg){
    printids("new thread: ");
    return((void *)0);
}

int main(void){
    int err;

    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    /* ntid에 스레드 ID를 저장하며 기본 특성으로 
    thr_fn을 실행하며 새로운 스레드 생성, arg는 NULL
    */
    if(err != 0)
        err_quit("can't create thread: %s\n", stderror(err));
    printids("main thread:"); //메인 스레드에 대한 정보 출력
    sleep(1); //자식 스레드의 출력을 기다린 후 종료
    exit(0);
}