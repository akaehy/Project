/*******************************************************
 * 编程读写一个文件test.txt，每隔1秒向文件中写入一行记录
 * ****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILE_NAME "test.txt"

int main(void)
{
	FILE *fp;
	char arr[40];
	int ln = 0;
	fp = fopen(FILE_NAME,"a+");
	if(fp == NULL)
	{
		perror("Open text.txt");
		exit(1);
	}
	while(fgets(arr, 40, fp) != NULL)
	{
		ln = ln + 1;
	}
	while(1)
	{
		time_t t = time(NULL);
		struct tm *t_s = localtime(&t);
		ln = ln + 1;
		fprintf(fp, "%d %d-%d-%d %d:%d:%d\n",ln,t_s->tm_year + 1900,t_s->tm_mon + 1,t_s->tm_mday,t_s->tm_hour,t_s->tm_min,t_s->tm_sec);
		fflush(fp);

		fprintf(stderr, "%d %d-%d-%d %d:%d:%d\n",ln,t_s->tm_year + 1900,t_s->tm_mon + 1,t_s->tm_mday,t_s->tm_hour,t_s->tm_min,t_s->tm_sec);
		sleep(1);	
	}

	fclose(fp);
	return 0;
}
