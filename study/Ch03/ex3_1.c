#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
	int fd, fd1, fd2;
	char buf[100] = "hello";
	fd = creat("dup_result", 0644);
	fd1 = dup2(fd, STDOUT_FILENO);
	fd2 = dup(fd1);
	close(fd);
	printf("hello world\n");
	printf("FD #: %d\n", fd);
	printf("FD #: %d\n", fd1);
	printf("FD #: %d\n", fd2);
	printf("FD #: %d", STDOUT_FILENO);
	write(fd2, buf, 5);
	printf("Hello world %d\n", fd2);
	return 0;
}
