#include <stdio.h>
#include <stdlib.h>

void sys_err(const char *msg)
{
	perror(msg);
	exit(1);
}

void cp_by_char(FILE *fpr, FILE *fpw)
{
	int c;

	while((c = fgetc(fpr)) != EOF)
		fputc(c, fpw);
}

void cp_by_str(FILE *fpr, FILE *fpw)
{
	char buf[100];

	while(fgets(buf, 100, fpr) != NULL){
		fputs(buf, fpw);
	}
}

void cp_by_rec(FILE *fpr, FILE *fpw)
{
	char buf[100];
	int ret;
	
	while((ret = fread(buf, 1, 100, fpr)))
		fwrite(buf, 1, ret, fpw);
}

int main(int argc, char *argv[])
{
	int choice;
	FILE *fpr, *fpw;

	printf("1.Copy by char\n2.Copy by string\n3.Copy by record\n");
	printf("Your choice:");
	scanf("%d", &choice);

	fpr = fopen(argv[1], "r");
	fpw = fopen(argv[2], "w");
	if(!fpr || !fpw)
		sys_err("open file");

	switch(choice){
	case 1: cp_by_char(fpr, fpw);
			break;
	case 2: cp_by_str(fpr, fpw);
			break;
	case 3: cp_by_rec(fpr, fpw);
			break;
	}
	
	fclose(fpr);
	fclose(fpw);
	return 0;
}
