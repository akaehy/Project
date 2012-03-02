#include <stdio.h>
typedef int (*funcp_t)(int, int);
int add(int a, int b)
{
	return a + b;
}
int sub(int a, int b)
{
	return a - b;
}
int mul(int a, int b)
{
	return a * b;
}
int main(void)
{	
	funcp_t p[3] = {add, sub, mul};
	int i;
	for(i = 0; i < 3; i++)
		printf("result:%d\n", p[i](2, 3));
	return 0;
}
