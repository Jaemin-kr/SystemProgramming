#include <stdio.h>
#include <time.h>

int main(){
	time_t t;
	char *ct, buf[80];
	struct tm *lt;

	time(&t);
	printf("time:\n\t%ld\n", t);

	ct = ctime(&t);
	printf("ctime:\n\t%s", ct);

	lt = localtime(&t);
	printf("local time:\n");
	printf("\tyear\t:%d\n", lt->tm_year);
	printf("\tmon\t:%d\n", lt->tm_mon);
	printf("\tday\t:%d\n", lt->tm_mday);
	printf("\thour\t:%d\n", lt->tm_hour);
	printf("\tminute\t:%d\n", lt->tm_min);
	printf("\tsecond\t:%d\n", lt->tm_sec);
	printf("\tweekday\t:%d\n", lt->tm_wday);
	printf("\tyear day\t:%d\n", lt->tm_yday);

	strftime(buf, 80, "%A\t%B\t%c",lt);
	printf("strftime:\n\t%s\n", buf);
}

