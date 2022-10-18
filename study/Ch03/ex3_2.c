#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
char buf1[] = "abcdefghiij";
char buf2[] = "ABCDEFGHIJ";

int main(void){
	int fd;

	if((fd = creat("file.hole", 0644)) < 0)
		printf("creat error");
	if(write(fd, buf1, 10) != 10)
		printf("buf1 write error");

	if(lseek(fd, 16384, SEEK_SET) == -1)
		printf("lseek error");

	if(write(fd, buf2, 10) != 10)
		printf("buf2 write error");

	exit(0);
}

