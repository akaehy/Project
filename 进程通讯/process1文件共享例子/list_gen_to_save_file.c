#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

void list_gen_to_save_file(void)
{
	DIR *dirp = NULL;
	struct dirent *direntp = NULL;
	FILE *fp;
	char *p;
	char str[100] = {0};

	fp = fopen("audiolist.txt", "w+");
	if(fp == NULL)
	{
		perror("open audiolist.txt");
		exit(1);
	}
	if((dirp = opendir("mp3")) != NULL)
	{
		while((direntp = readdir(dirp)) != NULL)
		{
			p = strrchr(direntp -> d_name, '.');		
			if((strcmp(p, ".wav")) == 0 || (strcmp(p, ".mp3")) == 0)
			{
				strcpy(str, direntp -> d_name);
				strcat(str, "\n");
				fputs(str, fp);
			}

		}
	}
	closedir(dirp);
	fclose(fp);
}

int main(int argc, char *argv[])
{
	while(1)
	{
		list_gen_to_save_file();
		sleep(5);
	}
	return 0;
}
