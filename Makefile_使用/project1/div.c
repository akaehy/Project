#include <stdio.h>
#include <stdlib.h>

int my_div(int a, int b)
{
	return a / b;
}

int main(int argc, char *argv[])
{
	printf("hello!\n");
	printf("div:%d\n", my_div(atoi(argv[1]), atoi(argv[2])));
	return 0;
}
