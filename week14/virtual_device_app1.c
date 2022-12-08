#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>

int main(int argc, char *argv[]){
	int dev;
	char buff[1024];
	
	printf("Device driver test \n");
	
	dev = open("/dev/virtual_device", O_RDWR);
	
	printf("dev : %d\n", dev);
	
	if(dev<0){
		printf("device file open error\n");
		return -1;
	}
	write(dev, "1234", 4);
	read(dev, buff, 4);
	buff[4] = 0;
	
	printf("read from device : %s\n", buff);
	close(dev);
	
	return 0;
}
