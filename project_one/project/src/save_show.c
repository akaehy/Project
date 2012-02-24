#include <stdio.h>
#include "header.h"

void read(std_t std[], int len)
{
	int i, j;

	for(i = 0; i < len; i++){
		printf("Please input %d info:\n", i + 1);
		scanf("%hu %s", &std[i].id, std[i].name);
		for(j = 0; j < 4; j++)
			scanf("%d", &(std[i].s[j]));
	}

}

void write(std_t std[], int len)
{
	int i, j;
	
	printf("ID  %10s%8s%8s%8s%8s%8s\n", "NAME", "S1", "S2", "S3", "S4", "AVE");
	printf("------------------------------------------\n");
	for(i = 0; i < len; i++){
		std[i].ave = 0;
		printf("%hu %10s", std[i].id, std[i].name);
		for(j = 0; j < 4; j++){
			printf("%8d", std[i].s[j]);
			std[i].ave += std[i].s[j];
		}
		printf("%10.1f\n", std[i].ave / 4);
	}
}
