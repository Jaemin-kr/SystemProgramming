#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void *thread_function(void *arg);
int main(void){
	pthread_t thread_id;
	char *b;

	pthread_create(&thread_id, NULL, &thread_function, NULL);
	pthread_join(thread_id, (void**)&b);
	printf("b is %s", b);

	return 0;
}
void *thread_function(void *arg){
	char *a = (char*)malloc(10);
	strcpy(a, "hello world\n");
	pthread_exit((void*)a);
};
