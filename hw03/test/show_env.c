#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *env[] = {"USER=JAEMIN", NULL}; // USER
char *getenv(const char *name); //user

int main(int argc, char* argv[]){

	if(strcmp(argv[1], "1") == 0){
		printf("USER = %s\n", getenv("USER"));
		exit(0);
		
	}
	else if(strcmp(argv[1], "2") == 0){
		printf("%s\n", env[0]);
		exit(1);
		
	}
	else if(strcmp(argv[1], "3") == 0){
		printf("USER = %s\n", getenv("USER"));
		exit(2);
		
	}
	else if(strcmp(argv[1], "4") == 0){
		printf("%s\n", env[0]);
		exit(3);
		
	}
	

}
