#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

void *t_handler(void* arg);
int thread_num, element_num;
pthread_mutex_t mutex;


int cursor = 0; //element index

int main(int argc, char* argv[]){
	thread_num = atoi(argv[1]);
	element_num = atoi(argv[2]);
	int element[element_num];
	int rand_num;
	
	//create random number
	srand(time(NULL));
	for(int i = 0; i<element_num; i++){
		element[i] = (rand()%6)+5;
		//printf("%d ",element[i]);
		printf("element[%d] : %d\n", i, element[i]);
	}
	printf("\n");
	
	char argument[10] = "hello";
	
	for(int i=0; i<thread_num; i++){
		pthread_t thread[i];
		pthread_create(&thread[i], NULL, t_handler, (void*)argument);
		sleep(0.1);
	}
    for(int i=0; i<thread_num; i++){
		pthread_join(thread[i], NULL);
		sleep(0.1);
	}

}

void *t_handler(void *arg){
	pthread_t tid;
	tid = pthread_self();
	char *argument = (char *)arg;
	//sleep(arg);
	//printf("%s\n", argument);
	printf("This is thread %u, this arr is %s \n", (unsigned int)tid, argument);
}
	