#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 4096

int main(int argc, char *argv[]){
	int fd, n;
	char buf[10];
	char buf1[BUFFSIZE];
	ssize_t bytes;
	int cursor_byte;
	int i = 1;
	int j,cnt=0;
	
	int total_line;
	int start_line;
	int current_line;
	
	
	fd = open("test2.txt", O_RDONLY);
	
	if(fd == -1){
		fprintf(stderr, "error - open()");
		exit(1);
	} //open error
	
	//read all(calculate byte)
	lseek(fd, 0, SEEK_SET);
	bytes = read(fd, buf1, sizeof(buf1));
	printf("Total bytes:%ld\n", bytes); 
	
	

	//read total line
	lseek(fd, 0, SEEK_SET);
	for(; ; ){
		int file_read = read(fd, buf, 1); //read file
		if (file_read == 0){
			break;
		}
		
		if(strcmp((const char *)buf, "\n") == 0){
			total_line += 1;
		}
	}
		
	printf("total:%d\n", total_line);

	if(strcmp(argv[1], "-a") == 0){
		lseek(fd, 0, SEEK_SET);
		while((n = read(fd, buf1, sizeof(buf))) > 0){
			write(STDIN_FILENO, buf1, n);
		}
	}
	
	//read start to total
	lseek(fd, 0, SEEK_SET);
	start_line = total_line - atoi(argv[1]);
	while(current_line < start_line){
		int file_read = read(fd, buf, 1);
		if(strcmp((const char *)buf, "\n") == 0){
			current_line++;
		}	
	}
	
	while((n = read(fd, buf, sizeof(buf))) > 0){
		write(STDIN_FILENO, buf, n);
	}
	
	
	/*
	for(; ;){
		int file_read = read(fd, buf, 1);
		if (file_read == 0){
			break;
		}
		int l = (int)argv[1];
		if((total_line - l) < total_line){
			write(STDIN_FILENO, buf, 1);
		}
	}
	*/
		
	

	
	close(fd);
	
	
	return 0;
}
