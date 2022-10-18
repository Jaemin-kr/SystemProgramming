#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
	int fd;
	fd = creat("dup_result", 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	printf("hello world\n");
	return 0;
}
