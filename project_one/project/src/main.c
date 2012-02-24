#include <stdio.h>
#include "header.h"

int main(int argc, char *argv[])
{
	int choice;
	char dest[20];
	std_t std[LEN];

	while(1){
		printf("1.Josephus\n2.String combination\n3.Reading & writing std's info\n4.Exit!\n");
		printf("Please choose:");
		scanf("%d", &choice);
		switch(choice){
		case 1: Josephus(COUNT);
			break;
		case 2: printf("%s\n", str_combination(dest));
			break;
		case 3: read(std, LEN);
			write(std, LEN);
			break;
		default:return 0;
		}
	}
	return 0;
}
