#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_SIZE  100
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

void logcat(char *str)
{
	FILE *fp;
	int i = 0;
	char buf[MAX_SIZE];

	if((fp = fopen("test.txt", "a+")) == NULL){
			sys_err("fail to open");
	}
	
	time_t t = time(NULL);
	struct tm *t_s = localtime(&t);	
	fprintf(fp, "%d-%02d-%02d  %02d:%02d:%02d:%s\n", t_s->tm_year + 1900, t_s->tm_mon + 1, t_s->tm_mday, t_s->tm_hour, t_s->tm_min, t_s->tm_sec, str);
	printf("%d-%02d-%02d  %02d:%02d:%02d:%s\n", t_s->tm_year + 1900, t_s->tm_mon + 1, t_s->tm_mday, t_s->tm_hour, t_s->tm_min, t_s->tm_sec, str);

	printf("%s-%d:\n", __func__, __LINE__ );
	fclose(fp);
}

int main(void)
{
	logcat("Add one record.");
	logcat("Delete one record.");
	return 0;
}
