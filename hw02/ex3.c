#include <stdio.h>
#include <stdlib.h>


#define BUFSIZE 5096

typedef struct student{
	int sno;
	char name[10];
	int score;
}student;

int main(int argc, char *argv[]){
	
	FILE *fp, *fp1;
	int write_buf = 0;
	int i = 0;
	int stu_num = atoi(argv[1]);
	struct student s[stu_num], s1[stu_num], s2[stu_num];
	float total_score = 0;
	float avg_score = 0;
	
	char buf[BUFSIZE];
	char buf1[BUFSIZE];
	
	//open stu.dat read and write
	/*
	if((fp = fopen("hw02stu.dat", "r+")) == NULL){
		fprintf(stderr,"error - fopen()");
		exit(1);
	}
	*/
	//sizeof(student) -> write buf size or sizeof(s[i])
	
	//get student score
	for(i = 0; i<stu_num; i++){
		printf("input sno >> ");
		scanf("%d", &s[i].sno);
		printf("input name >> ");
		scanf("%s", s[i].name);
		printf("input score >> ");
		scanf("%d", &s[i].score);
		total_score += s[i].score;
	}
	
	fp = fp = fopen("hw02stu.dat", "w+");
	
	fwrite(&s1, sizeof(struct student), i, fp);
	fread(s2, sizeof(struct student), i, fp);
	
	//get avg
	avg_score = (total_score/stu_num);
	printf("avg score: %.1f\n", avg_score);
	
	fclose(fp);
	return 0;

}