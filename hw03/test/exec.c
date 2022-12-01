#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *env[] = {"USER=JAEMIN", NULL};
char *getenv(const char *name);

int main(int argc, char* argv[]){
	pid_t pid;
	int status;
	//printf("user name: %s\n", getenv("USER"));
	char *cvp[] = {"./show_env", "3", NULL};
	//pid = fork();
	if(strcmp(argv[1], "1") == 0){
		pid = fork();
		if(pid == 0){
			//printf("here is child\n");
			execlp("./show_env","./show_env", "1", NULL);
			kill(pid, SIGKILL);
		}
		else{
			sleep(1);
			printf("Print USER of env_var Complete!!\n");
			exit(0);
		}

		
	}
	
	else if(strcmp(argv[1], "2") == 0){
		pid = fork();
		if(pid == 0){
			execle("./show_env","./show_env", "2", NULL,NULL);
			kill(pid, SIGKILL);	
		}
		else{
			sleep(1);
			printf("Print USER of env_var Complete!!\n");
			exit(0);
		}
	}
	
	
	else if(strcmp(argv[1], "3") == 0){
		pid = fork();
		if(pid == 0){
			execvp("./show_env",cvp);
			kill(pid, SIGKILL);
			
		}
		else{
			sleep(1);
			printf("Print USER of env_var Complete!!\n");
			exit(0);
		}
	}
	
	else if(strcmp(argv[1], "4") == 0){
		pid = fork();
		if(pid == 0){
			execve("./show_env",cvp,env);
			kill(pid, SIGKILL);
			
		}
		else{
			sleep(1);
			printf("Print USER of env_var Complete!!\n");
			exit(0);
		}
	}
	
	
	
	return 0;
}
