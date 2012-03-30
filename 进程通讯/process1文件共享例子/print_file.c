#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_file(void)
{
	FILE *fp = NULL;
	char str[128];
	char *p;
	fp = fopen("audiolist.txt", "r");
	if(fp == NULL)
	{
		perror("open mp3");
		exit(1);
	}
	p = fgets(str, 128, fp);
	while(p != NULL)	
	{
		fputs(str, stdout);
		p = fgets(str, 128, fp);
	}


	fclose(fp);
	

}

int main(void)
{
	while(1)
	{
		print_file();
		sleep(5);
		system("clear");
	}
	return 0;
}
