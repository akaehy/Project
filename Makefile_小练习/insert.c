//随意输入5个整数并存入数组,完成对这5个整数的升
//序排列,然后再输入一个数,插入到此有序数列中来,
//要求插入后数组仍有序。
//
//
#include <stdio.h>

int main(void)
{
	int i, num[6], n;

	for(i = 0; i < 5; i++)
		scanf("%d", &num[i]);

	for(i = 0; i < 5; i++)
		printf("%d ", num[i]);
	printf("\n");
	
	scanf("%d", &n);
	for(i = 4; i >= 0 && n < num[i]; i--){
		num[i + 1] = num[i];
	}
	num[i + 1] = n;

	
	for(i = 0; i < 6; i++)
		printf("%d ", num[i]);
	printf("\n");
	
	return 0;
}
