//有一个unsigned int型整数,现要分别将其前两个字
//节和后两个字节作为两个unsigned short型整数输出。
//试编写函数partition实现上述要求:
//void partition(unsigned int n)
//
//
//
#include <stdio.h>

typedef union{
	unsigned int n;
	unsigned short s_n[2];
}un_t;

void partition(unsigned n)
{
	un_t u;
	u.n = n;
	printf("%hx, %hx\n", u.s_n[0], u.s_n[1]);
}
int main(void)
{
	unsigned n;
	
	printf("enter a num:");
	scanf("%x", &n);
	partition(n);
	return 0;
}
