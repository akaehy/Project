#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define LEN 100

int main(int argc, char *argv[])
{
    char buf[LEN];
    int i;
    FILE *fp;

    fp = fopen(argv[1], "w");
    if(fp == NULL){
        perror("fopen file");
        exit(1);
    }
    while(fgets(buf, LEN, stdin)){
        for(i = 0; buf[i]; i++)
            buf[i] = toupper(buf[i]);
        fputs(buf, fp);
    }
    
    fclose(fp);
    return 0;
}
