#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
    time_t t1;
    time_t t2;

    int i, j;
    int count;

    t1 = time(NULL);
    for(i =0; i< 100000; i++){
        for(j=0; j<100000; j++){
            count++;
        }
    }
    time(&t2);
    printf("second %ld\n", t2 - t1);

    return 0;
}
