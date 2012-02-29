//求n个整数的最大值(n可变)
//
//
//
#include <stdio.h>
#include <stdarg.h>

int max(int n, ...)
{
	va_list ap;
	int max_n, tmp;

	va_start(ap, n);
	//ap = (char *)&n + 4;
	max_n = va_arg(ap, int);
	n--;

	while(n > 0){
		if(max_n < (tmp = va_arg(ap, int)))
			max_n = tmp;
		n--;
	}

	va_end(ap);
	return max_n;
}

int main(void)
{
	printf("max:%d\n", max(3, 1, 0, 2));
	printf("max:%d\n", max(5, 1, 0, -5, -1, -10));
	return 0;
}
