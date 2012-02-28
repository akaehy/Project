//从键盘输入一个最多5位的整数,要求计算该数的实
//际位数并正向及反向输出各位数字
//
//
//
#include <stdio.h>

int main(void)
{
	int n, count = 0, num[5], i = 0;

	scanf("%d", &n);
	
	do{
		num[i++] = n % 10;
		count++;
		printf("%d ", n % 10);
	}while(n /= 10);
	
	
	printf("\ncount = %d\n", count);

	for(i--; i>= 0; i--)
		printf("%d ", num[i]);
	printf("\n");
	return 0;
}
