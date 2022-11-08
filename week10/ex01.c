#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *printf_1(void *arg);
void *printf_2(void *arg);
void *printf_3(void *arg);

int main(void){
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;

	pthread_create(&thread1, 0, printf_1, 0);
	pthread_create(&thread2, 0, printf_2, 0);
	pthread_create(&thread3, 0, printf_3, 0);

	printf("This is a main\n");
	sleep(5);

	return 0;
}

void *printf_1(void *arg){
	while(1){
		printf("Thread 1\n");
		sleep(1);
	}
}
void *printf_2(void *arg){
	while(1){
		printf("Thread 2\n");
		sleep(1);
	}
}
void *printf_3(void *arg){
	while(1){
		printf("Thread 3\n");
		sleep(1);
	}
}
