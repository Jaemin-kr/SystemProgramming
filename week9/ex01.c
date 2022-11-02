#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sig_handler(int signo);

int i = 0;
int main(void){
	signal(SIGINT, (void*)sig_handler);

	while(1);
	return 0;
}
void sig_handler(int signo){
	printf("%d\n", i++);
}
