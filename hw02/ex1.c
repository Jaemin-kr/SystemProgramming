#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, char *argv[1]){
	struct stat statbuf;
	uid_t uid = statbuf.st_uid;
	uid_t gid = statbuf.st_gid;
	
    stat(argv[1], &statbuf);


	if(strcmp(argv[1] ,"0") == 0){
		chmod("./ex1",((statbuf.st_mode & S_ISUID) | S_ISGID));
		chown("./ex1", uid, gid);
	}
	
	else if(strcmp(argv[1] ,"1") == 0){
		chmod("./ex1",(statbuf.st_mode & ~S_IXGRP) | S_ISUID);
		chown("./ex1", 0, 0);
		//chown("./ex1.c", uid, gid);
		
	}
	
	
	else if(strcmp(argv[1] ,"2") == 0){ //chmod 0755
		chmod("./ex1", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	}
	else if(strcmp(argv[1] ,"3") == 0){ //chmod 0644
		chmod("./ex1", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	
	
	return 0;
}