//说明
//今天学习了函数

//将大写字母改成小写，小写改成大写

#include <stdio.h>

void swap(char str[])
{
	int i;
	for (i = 0; str[i]; i++) 
	{
		if(str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		else if(str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
	}
}

int main(int argc, const char *argv[])
{
	char str[100] = "HelLo!!";
	printf("%s\n", str);
	swap(str);
	printf("%s\n", str);
	return 0;
}



//例如输入2012 输出2 0 1 2
#include <stdio.h>

void func(int n)
{
	int arr[4];
	int i = 0;
	while(n)
	{
		arr[i++] = n % 10;
		n/=10;
	}
	for(i = i - 1; i >= 0; i--)
		printf("%d ", arr[i]);
	printf("\n");
}

int main(int argc, const char *argv[])
{
	int num;
	scanf("%d", &num);
	func(num);
	return 0;
}



//将十进制改成二进制输出
//例如输入8输出1000
#include <stdio.h>

void func(int num)
{
	int arr[32];
	int i = 0;
	while(num)
	{
		arr[i++] = num % 2;
		num /= 2;
	}
	for(i = i - 1; i >= 0; i--)
		printf("%d", arr[i]);
	printf("\n");
}

int main(int argc, const char *argv[])
{
	int num;
	scanf("%d", &num);
	func(num);
	return 0;
}

//例如输入2012 3 13判断这天为该年的第几天
#include <stdio.h>

int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int is_leapyear(int year)
{
	if((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
		return 1;
	else
		return 0;
}

int calc(int year, int month, int day)
{
	int sum = 0;
	int i;
	for(i = 0; i < month; i++)
	{
		sum += days[i];
	}
	sum += day;
	if(month > 2 && is_leapyear(year))
		sum++;

	return sum;
}

int main(int argc, const char *argv[])
{
	int year, month, day;
	scanf("%d %d %d", &year, &month, &day);
	printf("%d\n",calc(year, month, day));
	return 0;
}



//实现strcat功能 将world连接在hello后面
#include <stdio.h>

void mystrcat(char s1[], char s2[])
{
	int i = 0;
	int j = 0;
	while(s1[i])
		i++;
	while(s2[j])
		s1[i++] = s2[j++];
	s1[i] = '\0';
}

int main(int argc, const char *argv[])
{
	char s1[100] = "hello";
	char s2[100] = "world";
	mystrcat(s1, s2);
	printf("%s\n", s1);
	return 0;
}


//数组传入之后不在是数组此为地址32位所以输出4即4个字节
//输出结果为 40
//           0
//           4
//           10
#include <stdio.h>

void swap(int *a)
{
	printf("%d\n", sizeof(a));
	a[3] = 10;
}

int main(int argc, const char *argv[])
{
	int arr[10] = {0};
	printf("%d\n", sizeof(arr));
	printf("%d\n", arr[3]);
	swap(arr);
	printf("%d\n", arr[3]);
	return 0;
}


