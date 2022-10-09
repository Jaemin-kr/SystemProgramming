#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    int i;
    struct stat buf;
    char *ptr;
	DIR *dp;
	struct dirent *dirp;
	int num_file;
	//error
	if(argc!=2){
		fprintf(stderr, "usage: ls directory_name\n");
		exit(1);
	}
	if((dp=opendir(argv[1])) == NULL){
		fprintf(stderr, "can't open %s\n", argv[1]);
		exit(1);
	}
	//전체파일 개수 확인
	while((dirp=readdir(dp)) != NULL){

		printf("%s\n", dirp->d_name);
		num_file += 1;
	}
	printf("files: %d\n", num_file);
	
	closedir(dp);
	return 0;
}

//폴더, 파일 구분해서 print