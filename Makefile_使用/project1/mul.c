#include <stdio.h>
#include <stdlib.h>

int mul(int a, int b)
{
	return a * b;
}

int main(int argc, char *argv[])
{
	printf("hello!\n");
	printf("mul:%d\n", mul(atoi(argv[1]), atoi(argv[2])));
	return 0;
}
