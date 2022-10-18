#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>


int glob=6;

int main(){
    int var;
    pid_t pid;

    var = 88;
    printf("before vfork\n");

    if ((pid = vfork()) < 0){
        printf("fork error");
    } else if(pid == 0){
        glob++;
        var++;
		exit(0);
	}
	//parent continue here.
    printf("pid=%ld, glob = %d, var = %d\n",(long)getpid(), glob, var);

	exit(0);
}
