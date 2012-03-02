//从一组整形数据中找出最大值
//从一组字符串中找出字典序最大的字符串
//从一组学生的信息中找到成绩最高的学生
//要求使用泛型函数解决这类问题,对以上三
//种情况均适用
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
typedef struct student{
	char name[20];
	unsigned score;
}std_t;

typedef int (*cmp_t)(void *, void *);

int cmp_int(void *a, void *b)
{
	return *(int *)a - *(int *)b;
}

int cmp_str(void *a, void *b)
{
	return strcmp(*(char **)a, *(char **)b);
}

int cmp_std(void *a, void *b)
{
	return ((std_t *)a)->score - ((std_t *)b)->score;
}

void *max(void *base, int len, int size, cmp_t cmp)
{
	char *baseaddr = base, *maxp = base;
	int i;
	for(i = 1; i < len; i++)
		if(cmp(maxp, baseaddr + i * size) < 0)
			maxp = baseaddr + i * size;
	return (void *)maxp;
}

int main(void)
{
	int num[5], i;
	char *strp[5] = {"hello", "aka", "world", "program", "week"};
	char **maxstrp;
	
	std_t stdinfo[4] = {{"name1", 78}, {"name2", 69}, {"name3", 88}, {"name4", 67}};
	std_t *maxstdp;

	srand(time(NULL));
	for(i = 0; i < 5; i++)
		printf("%d ", num[i] = rand() % 50);
	printf("\n");
	
	printf("max_n:%d\n", *((int *)(max(num, 5, 4, cmp_int))));

	maxstdp = max(stdinfo, 4, sizeof(std_t), cmp_std);
	printf("max_std:%s %u\n", maxstdp->name, maxstdp->score);

	maxstrp = max(strp, 5, 4, cmp_str);
	printf("max_str:%s\n", *maxstrp);
	return 0;
}
