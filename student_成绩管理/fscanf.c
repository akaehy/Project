#include <stdio.h>
#include <stdlib.h>

typedef struct{
    unsigned int id;
    char name[20];
    unsigned math, eng;
}std_t;

void sys_err(const char *msg)
{
    perror(msg);
    exit(1);
}

void get_record(std_t std[], int len)
{
    int i;
	printf("Please input student record like zhang 88 78, then Enter\n"); 
    for(i = 0; i < len; i++)
	{
		std[i].id = i+1;
        scanf("%s %d %d", std[i].name, &std[i].math, &std[i].eng);
	}
}

void write_to_file(std_t std[], int len, FILE *fp)
{
    int i;
    for(i = 0; i < len; i++)
        fwrite(std + i, 1, sizeof(std_t), fp);
}

int main(void)
{
    std_t std[5];
    int i;
    FILE *fp;

    get_record(std, 5);
    fp = fopen("std_rec", "w+");
    if(fp == NULL)
        sys_err("fopen file");
    write_to_file(std, 5, fp);
    rewind(fp);
	printf("All students records:\n");
    printf("ID\tNAME\tMATH\tENG\tAVE\n");
    printf("--------------------------------------------------\n");
    for(i = 0; i < 5; i++){
        fread(std + i, 1, sizeof(std_t), fp);
        printf("%d\t%s\t%d\t%d\t%.2f\n", std[i].id, std[i].name, std[i].math, std[i].eng, (std[i].math + std[i].eng)/2.0);
    }
    fclose(fp);
    return 0;
}
