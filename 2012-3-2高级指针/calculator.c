//使用函数指针数组实现一个小型计算器
//,计算器支持加减乘除四则运算。
//如输入:+
//2 3
//输出结论为:5
//输入:„#‟,表示计算器退出
//北京亚嵌教育-中国嵌入式技术的黄埔军校
//
//
//
#include <stdio.h>

	typedef int (*funcp_t)(int, int);
typedef struct command{
	char op;
	funcp_t fp;
}cmd_t;

int add(int a, int b){	return a + b;}
int sub(int a, int b){	return a - b;}
int mul(int a, int b){	return a * b;}
int mydiv(int a, int b){ return a / b;}

int main(void)
{	
	cmd_t cmd[4] = {{'+', add}, {'-', sub}, {'*', mul}, {'/', mydiv}};
	char c;
	int a, b, i;

	while(1){
		printf("input the operator:");
		scanf("%c", &c);
		if(c == '#')
			break;
		printf("input a b:");
		scanf("%d %d", &a, &b);
		getchar();
		for(i = 0; i < 4; i++){
			if(c == cmd[i].op){
				printf("result:%d\n", cmd[i].fp(a, b));
				break;
			}
		}
	}
	return 0;
}
