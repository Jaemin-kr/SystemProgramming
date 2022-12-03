#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct foo{
	int f_count;
	pthread_mutex_t f_lock;

};

struct foo* foo_alloc(void);
void foo_hold(struct foo*);
void foo_rele(struct foo*);
void *t_handler(void*);

struct foo* f_share;

int main(){
	int err;

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;

	f_share = foo_alloc();

	printf("Main thread count value = %d\n", f_share->f_count);

	pthread_create(&thread1, NULL, t_handler, NULL);
	pthread_create(&thread2, NULL, t_handler, NULL);
	pthread_create(&thread3, NULL, t_handler, NULL);
	pthread_create(&thread4, NULL, t_handler, NULL);
	pthread_join(thread1, NULL);
	printf("Thread1 terminated\n");
	pthread_join(thread2, NULL);
	printf("Thread2 terminated\n");
	pthread_join(thread3, NULL);
	printf("Thread3 terminated\n");
	pthread_join(thread4, NULL);
	printf("Thread4 terminated\n");

	foo_rele(f_share);
}

struct foo* foo_alloc(void){
	struct foo *fp;

	if((fp = malloc(sizeof(struct foo))) != NULL){
		fp->f_count = 1;
		if(pthread_mutex_init(&fp->f_lock, NULL) != 0){
			free(fp);
			return(NULL);
		}
	}
	return(fp);
}

void foo_hold(struct foo *fp){
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(struct foo *fp){
	pthread_mutex_lock(&fp->f_lock);
	if(--fp->f_count == 0){
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	} else{
		pthread_mutex_unlock(&fp->f_lock);
	}
}
