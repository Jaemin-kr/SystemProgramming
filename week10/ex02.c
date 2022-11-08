#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t ntid;

void printids(const char *s);
void *thr_fn(void *arg);
int main(void){
	int err;

	pthread_create(&ntid, NULL, thr_fn, NULL);
	printids("Main Thread: ");
	sleep(1);

	return 0;
}

void printids(const char *s){
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();

	printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
}

void *thr_fn(void *arg){
	printids("New Thread: ");
}
