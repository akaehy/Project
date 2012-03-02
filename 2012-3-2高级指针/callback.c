// 回调函数举例
//
//
//
//
#include <stdio.h>


typedef void (*funcp_t)(void *);

void printstr(void *str)
{
	printf("%s\n", (char *)str);
}

void printnum(void *n)
{
	printf("%d\n", (int)n);
}
void printmsg(funcp_t fp, void *arg)
{
	fp(arg);
}

int main(void)
{
	printmsg(printstr, (void *)"hello");
	printmsg(printnum, (void *)123);
	return 0;
}
