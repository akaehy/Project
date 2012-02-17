// 指针练习============================指针练习
// 使用指针改写求一个数组中的最大值

#include <stdio.h>

int *find_max(int *arr, int n)
{
	int *max = arr;
	int i;
	for (i = 0; i < n; i++) 
	{
		if(arr[i] > *max)
			max = &arr[i];
	}

	return max;
}

int main(int argc, const char *argv[])
{
	int arr[10] = {1, 2, 3, 4, 55, 4, 3, 2, 3 ,4};
	int *p;
	p = find_max(arr, 10);
	printf("%d\n", *p);
	printf("%d\n", p - arr);
	
	return 0;
}



//使用指针改写将一数组反向

#include <stdio.h>

void back(int *arr, int n)
{
	int *p = arr;
	int *q = arr + n - 1;
	int tmp;
	while(p < q)
	{
		tmp = *p;
		*p = *q;
		*q = tmp;
		p++;
		q--;
	}
}

int main(int argc, const char *argv[])
{
	int arr[10] = {1, 2, 3, 4, 55, 4, 3, 2, 3 ,4};
	int i;
	for (i = 0; i < 10; i++) 
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	back(arr, 10);
	for (i = 0; i < 10; i++) 
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	return 0;
}

//用指针实现strlen函数

#include <stdio.h>

int mystrlen(char *s)
{
	char *bak = s;
	printf("%p\n", bak);
	//int cnt = 0;
	while(*s)
	{
		//cnt++;
		s++;
	}
	printf("%p\n", s);

	return s - bak;
}

int main(int argc, const char *argv[])
{
	char *s = "hello";
	printf("%d\n", mystrlen(s));
	return 0;
}


//编写一程序，输入月份号，输出该月的英文名字，例如：输入3，则输出
//March要求用指针数组实现
#include <stdio.h>

char *arr[] = {"Jan", "Feb", "Mar", "Apr"};

int main(int argc, const char *argv[])
{
	int n;
	scanf("%d", &n);
	printf("%s\n", arr[n - 1]);
	return 0;
}

//用指针实现求出两个数的最大值

#include <stdio.h>

int *max(int *a, int *b)
{
	if(*a > *b)
		return a;
	else
		return b;
}

int main(int argc, const char *argv[])
{
	int i = 3, j = 4;
	//int *p;
	//p = max(&i, &j);
	//printf("%d\n", *p);
	printf("%d\n", *max(&i, &j));
	return 0;
}


//例如输入./a.out hello world
#include <stdio.h>

int main(int argc, const char *argv[])
{
	int i;
	for (i = 0; i < argc; i++) 
	{
		puts(argv[i]);
	}
	return 0;
}



//实现加减乘除取余 用指针
#include <stdio.h>
#include <string.h>

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

int mul(int a, int b)
{
	return a * b;
}

int div(int a, int b)
{
	if(b == 0)
		return 0;
	return a / b;
}

int mod(int a, int b)
{
	return a % b;
}

int (*fun[])(int, int) = {add, sub, mul, div, mod};//函数指针数组

int main(int argc, const char *argv[])
{
	int a, b;
	char c;
	int result;
	char *s = "+-*/%";
	scanf("%d %c %d", &a, &c, &b);
	int i;
	for (i = 0; i < strlen(s); i++) 
	{
		if(c == s[i])
			result = fun[i](a, b);
	}

	printf("%d %c %d = %d\n", a, c, b, result);
	return 0;
}



//实现atoi功能
#include <stdio.h>

int myatoi(char *s)
{
	int num = 0;
	int flag = 1;

	if(*s == '-')
	{
		flag = -1;
		s++;
	}
	else if(*s == '+')
		s++;

	while(*s)
	{
		if(*s < '0' || *s > '9')
			return num * flag;
		num = num * 10 + *s - '0';
		s++;
	}

	return num * flag;
}

int main(int argc, const char *argv[])
{
	char *s = "-1234abc";
	printf("myatoi = %d\n", myatoi(s));
	printf("atoi = %d\n", atoi(s));
	return 0;
}



//实现strcmp函数
#include <stdio.h>

int mystrcmp(char *s1, char *s2)
{
	while(*s1 == *s2)
	{
		if(*s1 == '\0')
			return 0;
		s1++;
		s2++;
	}

	return *s1 > *s2 ? 1 : -1;
}

int main(int argc, const char *argv[])
{
	char *s1 = "hellop";
	char *s2 = "hfllo";
	printf("mystrcmp = %d\n", mystrcmp(s1, s2));
	printf("strcmp = %d\n", strcmp(s1, s2));
	return 0;
}



//实现strcpy函数
#include <stdio.h>
#include <string.h>

char *mystrcpy(char *dest, char *src)
{
	char *bak = dest;

	while(*dest++ = *src++);

	return bak;
}

int main(int argc, const char *argv[])
{
	char dest[20] = "akaedu";
	char src[20] = "hel";
	printf("%s\n", mystrcpy(dest, src));
	return 0;
}


//实现strchr函数
#include <stdio.h>
#include <string.h>

char *mystrchr(char *s, char c)
{
	while(*s)
	{
		if(*s == c)
			return s;
		s++;
	}

	return NULL;
}

char *mystrrchr(char *s, char c)
{
	char *bak = s;
	while(*s)
		s++;
	s--;
	while(s >= bak)
	{
		if(*s == c)
			return s;
		s--;
	}

	return NULL;
}


int main(int argc, const char *argv[])
{
	char *s = "hello world";
	char *p;
	//printf("%s\n", strrchr(s, 'o'));
	if((p = mystrrchr(s, 'h') )!= NULL)
		printf("%s\n", p);
	return 0;
}
