
//  ## 标记粘合运算符应用举例
#include <stdio.h>

#define GENERIC_MAX(type) \
	type type##_max(type a, type b) \
	{ 	\
		return (a > b) ? a : b;\
	}

GENERIC_MAX(int)
GENERIC_MAX(double)
int main(void)
{
	int max = int_max(2, 5);
	double m = double_max(2.69, 5.98);

	printf("max = %d\n", max);
	printf("m = %f\n", m);
	return 0;
}





//
//练习:
//
//编写宏来计算下面的值:
// x的立方
// n除以4的余数
// 如果x与y的乘积小于100则值为1,否则为0
//
#include <stdio.h>

#define CUBE(x) ((x) * (x) * (x))
#define MOD(n) ((n) % 4)
#define JUDGE(x, y) (((x) * (y) < 100) ? 1 : 0)

int main(void)
{
	int n;

	scanf("%d", &n);
	printf("cube(2):%d\n", CUBE(2));
	printf("MOD(n) = %d\n", MOD(n));
	printf("JUDGE(5, 6) = %d\n", JUDGE(5, 6));
	return 0;
}




//创建较长的宏:
//
//
//
//若宏的替换列表由多个表达式构成,则通
//过’,’进行多个表达式的连接,例如:
//#define ECHO(str) (gets(str), puts(str))
//若宏的替换列表由多条语句构成,则使用
//do{}while(0)的结构,
	//注意:while(0)后没有;
//第二种方法可以代替第一种方法

#include <stdio.h>
#define LEN 50
#define ECHO(str) (gets(str), puts(str))

#define N 0 
#define SETN(N) do{\
	if(N == 1)\
		printf("Yes!\n");\
	else\
		printf("No!\n");\
	}while(0)


int main(void)
{

	SETN(N);
	return 0;
}


//预处理--有个大练习project_one
