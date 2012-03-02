//为什么输出的都是Sunday？？？？？
//因为从右向左依次压栈
//第一次压入Monday的地址
//第二次压入Sunday的地址将第一次压入的地址覆盖
//第三次压入"%s %s\n"的地址
//输出时buf里面是Sunday
//
//
#include <stdio.h>
#include <string.h>

static const char *msg[] = {"Sunday", "Monday", "Tuesday"};

char *get_a_day(int idx)
{
	static char buf[20];
	strcpy(buf, msg[idx]);
	return buf;
}

int main(void)
{
	printf("%s %s\n", get_a_day(0), get_a_day(1));
	return 0;
}
