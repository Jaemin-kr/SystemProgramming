#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void cleanup_handler(void *arg);
void cleanup_handler2(void *arg);
void *start_new_thread(void *arg);

int main(){
	pthread_t thread;
	int ret;
	printf("start main thread...\n");
	pthread_create(&thread, NULL, start_new_thread, NULL);

	sleep(1);

	pthread_cancel(thread);
	pthread_join(thread, (void**)&ret);
	printf("end main thread...\n");
	return 0;
}

void cleanup_handler(void *arg){
	printf("cleanup_thread\n");
	return;
}
void cleanup_handler2(void *arg){
	printf("cleanup_thread2\n");
	return;
}

void *start_new_thread(void *arg){
	printf("start new thread...\n");
	pthread_cleanup_push(cleanup_handler, NULL);
	pthread_cleanup_push(cleanup_handler2, NULL);
	sleep(3);
	printf("end new thread...\n");
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return 0;
}
