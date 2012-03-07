#include <stdio.h>
#include <stdlib.h>
#include <error.h>

void cp_by_char(FILE *fpr, FILE *fpw)
{

	int ch;
	while((ch = fgetc(fpr)) != EOF)
	{
		fputc(ch, fpw);
	}
}

void cp_by_str(FILE *fpr, FILE *fpw)
{

	char buf[100];

	while((fgets(buf,100,fpr)) != NULL )
	{
		fputs(buf,fpw);
	}
}

void cp_by_rec(FILE *fpr, FILE *fpw)
{
	char buf[100];
	int ret;
	while((ret = fread(buf,1,100,fpr)))
		{
			fwrite(buf, 1, ret, fpw);
		}
}

int main(int argc, char* argv[])
{
	FILE *fpr, *fpw;
	if(argc != 3)
	{
		printf("Usage:program file1 file2.\n");
		exit(1);
	}

	fpr = fopen(argv[1], "r");
	fpw = fopen(argv[2], "w");
	if(fpr == NULL || fpw == NULL)
	{
		perror("Open file fail\n");
		exit(1);
	}

	cp_by_rec(fpr, fpw);

	fclose(fpr);
	fclose(fpw);
}
