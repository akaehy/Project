
//返回最大值和下标
#include <stdio.h>

struct s{
	int max;
	int subscript;
};

struct s func(int *arr, int n)
{
	struct s s1 = {arr[0], 0};
	int i;
	for (i = 0; i < n; i++) 
	{
		if(arr[i] > s1.max)
		{
			s1.max = arr[i];
			s1.subscript = i;
		}
	}

	return s1;
}

int main(int argc, const char *argv[])
{
	int arr[10] = {1, 2, 33, 4, 5, 3, 44, 23, 23};
	struct s result;
	result = func(arr, 10);
	printf("max = %d, subscript = %d\n", result.max, result.subscript);
	return 0;
}



//define 与 typedef函数
#include <stdio.h>

#define u32p_t unsigned int *  //替换关系
typedef unsigned int * u32p;//起个别名

int main(int argc, const char *argv[])
{
	u32p_t a, b;
	u32p c, d;

	return 0;
}



//输入5个人的信息打印
#include <stdio.h>

typedef struct{
	char name[20];
	int age;
	char gender[7];
}person_t;

int main(int argc, const char *argv[])
{
	person_t arr[5];
	int i;
	for (i = 0; i < 5; i++) 
	{
		scanf("%s %d %s", arr[i].name, &arr[i].age, arr[i].gender);
	}
	for (i = 0; i < 5; i++) 
	{
		printf("%s %d %s\n", arr[i].name, arr[i].age, arr[i].gender);
	}
	return 0;
}





//输入五个人的成绩，并找出平均成绩打印
#include <stdio.h>
typedef struct student{
	int id;
	char name[32];
	int chinese;
	int math;
	int english;
	float average;
	} stu_t;


int main(int argc, const char *argv[])
{	stu_t stu[5];
	int i;
	int sum=0;
	int average;
	for(i=0;i<5;i++)
	{
	printf("Enter stu inform\n");
	scanf("%d %s %d %d %d",&stu[i].id,stu[i].name,&stu[i].chinese,&stu[i].math,&stu[i].english);
	stu[i].average=((stu[i].chinese+stu[i].math+stu[i].english)/3);
	printf("Average is %f\n",stu[i].average);
	}
	return 0;
}



//最大值 平均值 偶数的个数
#include <stdio.h>

typedef struct s{
	int max;
	float average;
	int even;
}s_t;

s_t func(int *arr, int n)
{
	s_t s1 = {arr[0], 0.0, 0};
	int i;
	int sum = 0;
	for (i = 0; i < n; i++) 
	{
		if(arr[i] > s1.max)
			s1.max = arr[i];
		if(arr[i] % 2 == 0)
			s1.even++;
		sum += arr[i];
	}
	s1.average = (float)sum / n;

	return s1;
}

int main(int argc, const char *argv[])
{
	int arr[10] = {1, 2, 33, 4, 5, 3, 44, 23, 23};
	struct s result;
	result = func(arr, 10);
	printf("max = %d, average = %f, even = %d\n", result.max, result.average, result.even);
	return 0;
}



//输入5个人的成绩找出平均成绩的最大值的那个人的信息打印
#include <stdio.h>

typedef struct student{
	int id;
	char name[32];
	int chinese;
	int math;
	int english;
	float average;
}stu_t;

int main(int argc, const char *argv[])
{
	stu_t arr[5];
	int i;
	int sum = 0;
	for (i = 0; i < 5; i++) 
	{
		scanf("%d %s %d %d %d", &arr[i].id, arr[i].name, &arr[i].chinese, &arr[i].math, &arr[i].english);
		sum = arr[i].chinese + arr[i].math + arr[i].english;
		arr[i].average = (float)sum/3;
	}
	stu_t max = arr[0];
	for (i = 0; i < 5; i++) 
	{
		if(arr[i].average > max.average)
			max = arr[i];
	}
	printf("%d %s %f\n", max.id, max.name, max.average);
	return 0;
}



//看看联合体
#include <stdio.h>

union uni{
	int x;
	int y;
	int z;
	char a;
}u;

int main(int argc, const char *argv[])
{
	printf("%d\n", sizeof(u));
	u.x = 0x110;
	printf("%d\n", u.x);
	printf("%d\n", u.y);
	printf("%d\n", u.z);
	printf("%d\n", u.a);
	return 0;
}



// 成员多种引用方式
#include <stdio.h>
#include <string.h>

struct student{
	int id;
	int score;
	char name[32];
};

void sample(int *a)
{
	*a = 10;
}

void print_student(struct student *stu1)
{
	printf("%d\n", stu1.id);
	printf("%d\n", stu1.score);
	printf("%s\n", stu1.name);
	*stu1.id = 10;
	stu1->id = 10;
}

int main(int argc, const char *argv[])
{
	int aa;
	sample(&aa);
	struct student a = {1, 100, "jack"};
	struct student b = a;

	print_student(&a);

	return 0;
}



//以上输入程序需要的数据 用写在一个txt文件中用输入重定向<
1 jack 78 35  56
2 billy 78 89 90
3 alex 56 67 78
4 angella 67 54 56
5 tom 23 45 67

