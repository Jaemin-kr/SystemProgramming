#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


//각각의 원소를 1개씩 출력하는 스레드
int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void* routine(void* arg) {
    sleep(1);
    int index = *(int*)arg;
    printf("%d ", primes[index]);
    free(arg);
}

int main(int argc, char* argv[]) {
    pthread_t th[10];
    int i;
    for (i = 0; i < 10; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0) {
            perror("Failed to created thread");
        }
    }
    for (i = 0; i < 10; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    
    return 0;
}
/*
void printInfo(){
    pthread_t tid = pthread_self();   //thread id
    for(int i=0; i<num; i++){
      int rev = pthread_mutex_trylock(&(lock[i]));   //if lock failed, not block
      if(rev != 0)    //check return value
         continue;
      if(isVisit[i] == 0){   //handle element not visited
         sleep(cursor[i]);   // sleep cursor[i] seconds
         printf("%x - ", (unsigned int)tid);
         printf("element[%d] : %d", i, cursor[i]);
         printf("\n");
         isVisit[i] = 1;   
      }
      else 
         continue;
         
      pthread_mutex_unlock(&(lock[i]));
    }
}
*/

#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/syscall.h>

int num;
int *cursor;   //manage array index
int *isVisit;
pthread_mutex_t *lock;

void printInfo(){
    pthread_t tid = pthread_self();   //thread id
    for(int i=0; i<num; i++){
      int rev = pthread_mutex_trylock(&(lock[i]));   //if lock failed, not block
      if(rev != 0)    //check return value
         continue;
      if(isVisit[i] == 0){   //handle element not visited
         sleep(cursor[i]);   // sleep cursor[i] seconds
         printf("%x - ", (unsigned int)tid);
         printf("element[%d] : %d", i, cursor[i]);
         printf("\n");
         isVisit[i] = 1;   
      }
      else 
         continue;
         
      pthread_mutex_unlock(&(lock[i]));
    }
}

int main(int argc, char* argv[]){

   int thread_count=atoi(argv[1]);
   pthread_t thread[thread_count];
   
   num = atoi(argv[2]);
   int array[num];
   
   pthread_mutex_t locks[num];
   int isVisits[num];
   
   lock = locks;
   cursor = array;
   isVisit = isVisits;
   
   srand(time(NULL));   
   for(int i=0;i<num;i++){
      array[i]= rand() %6 +5;   //5~10 
      printf("%d ",array[i]);
      isVisits[i] = 0;
      pthread_mutex_init(&locks[i], NULL);
   }
   printf("\n");
   
   void *printInfoFunc = printInfo;  //function pointer addr
    
   for (int j = 0; j<thread_count; j++){ 
      pthread_create(&thread[j], NULL, printInfoFunc, NULL);
       }

   for (int j = 0; j<thread_count; j++){ 
      pthread_join(thread[j], NULL);
       }
      
}