
//统计子串substr在源串src中出现的次数。
//源串及子串数据从命令行参数获取。

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int count = 0;
	char *tmp, *p;

	for(p = argv[1]; (*argv[2] != '\0') && (tmp = strstr(p, argv[2])); ){
		count++;
		p = tmp + strlen(argv[2]);
	}
	printf("count = %d\n", count);
	return 0;
}



//定义一个字符指针数组如:
//char‫*‏‬str[]‫"{‏=‏‬hello‫‏‬world“,
//"hello‫‏‬hell“,
//"hello‫‏‬aka“,‫"‏‏‬hello‫‏‬hello‫‏‬hoho"};
//从键盘输入字符串,从字符指针数组对应的字符串
//中查找输入的字符串是否存在,若存在返回该字
//符串存在于指针数组的行列位置。若输入”exit”
//(不区分大小写)结束字符串输入

//老师做的
#include <stdio.h>
#include <string.h>
#include <strings.h>

int main(void)
{
	char sub[20], *p, *tmp;
	char *strp[] = {"hello world", "hello hell", "hello aka", "hello hello hoho"};
	int i;

	while(1){
		printf("enter a string:");
		scanf("%s", sub);
		if(!strcasecmp(sub, "exit"))
			break;
		for(i = 0; i < 4; i++){
			p = strp[i];
			while((tmp = strstr(p, sub))){
				printf("\"%s\" at row %d, col:%d!\n", sub, i + 1, tmp - strp[i] + 1);
				p = tmp + strlen(sub);
			}
		}
		printf("end...\n");
	}
	return 0;
}

//自己做的
//
#include <stdio.h>
#include<string.h>
#include<strings.h>
int main(int argc, char *argv[])
{
	char *str[]={"hello world","hello hell","hello aka","hello hello hoho"};
	char arr[20];
	char *p,*temp;
	int len;
	int i;

	while(1)
	{
		fgets(arr,20,stdin);
		len=strlen(arr);

		if(arr[len-1]=='\n')
		{
			arr[len-1]='\0';
			len--;
		}

		if(strcasecmp(arr,"exit")==0)
			break;

		for(i=1;i<5;i++)
		{
			for(p=str[i-1];*arr!=0&&(temp=strstr(p,arr));)
			{
				p = temp + strlen(arr);
				printf("%d row %d col\n",i, (temp-str[i - 1] + 1));
			}
		}
	}
	return 0;
}




//自行编写strcat函数
#include <stdio.h>

char *my_strcat(char *dest, const char *src)
{
	int i, j = 0;

	while(dest[j])
		j++;
	for(i = 0; dest[j + i] = src[i]; i++)
		;
	return dest;
}

int main(int argc, char *argv[])
{
	char dest[50] = "hello";

	printf("strcat:%s\n", my_strcat(dest, argv[1]));
	return 0;
}

//自行编写strcpy函数
#include <stdio.h>

char *my_strcpy(char *dest, const char *src)
{
	int i;
	static char tmp[100];

	if(!dest)
		dest = tmp;

	for(i = 0; dest[i] = src[i]; i++)
		;
	return dest;
}

int main(int argc, char *argv[])
{
	char *dest = NULL;

	printf("%s\n", dest = my_strcpy(dest, argv[1]));
	return 0;
}


//自行编写strcmp函数
#include <stdio.h>

int my_strcmp(const char *s1, const char *s2)
{
	int i;

	for(i = 0; s1[i] == s2[i]; i++)
		if(s1[i] == '\0')
			return 0;
	return s1[i] - s2[i];
}

int main(int argc, char *argv[])
{
	printf("strcmp:%d\n", my_strcmp(argv[1], argv[2]));
	return 0;
}



//strncpy函数使用举例
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int arg, char *argv[])
{
	char dest[10] = "aaaaaaaaa";

	printf("strncpy(dest, argv[1], atoi(argv[2])):%s\n", strncpy(dest, argv[1], atoi(argv[2])));
	return 0;
}




//strchr函数使用举例
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	printf("%s\n", strrchr(argv[1], argv[2][0]));
	return 0;
}



//strtol函数使用举例
#include <stdio.h>
#include <stdlib.h>

int  main(int argc, char *argv[])
{
	char *savep;

	printf("%ld\n", strtol(argv[1], &savep, 10));
	printf("argv[1]:%p, savep:%p\n", argv[1], savep);
	return 0;
}


//memcmp函数使用举例
#include <stdio.h>
#include <string.h>

typedef struct{
	char *p;
	int n;
}struct_t;

int main(void)
{
	int n = 97;
	char str[] = "abcd";
	struct_t s = {str, 15};

	printf("%d\n", memcmp(str, s.p, 4));
	return 0;
}




//memset函数使用举例将num中所有的字节置1并打印
#include <stdio.h>
#include <string.h>

void *my_memset(void *s, int c, int n)
{
	int i;

	for(i = 0; i < n; i++)
		*((char *)s + i) = c;
	return s;
}

int main(void)
{
	int num[5] = {1, 2, 3, 4, 5};
	int i, j;

	for(i = 0; i < 5; i++)
		printf("%d ", num[i]);
	printf("\n");

	my_memset(num, 0xff, 20);

	for(i = 0; i < 5; i++){
		for(j = 31; j >= 0; j--)
			printf("%x%c", (num[i] >> j) & 0x01, (j % 8)?'\0':'\n');
	//		printf("\n");
	}
	return 0;
}




//自行编写memmove函数
#include <stdio.h>
#include <stdlib.h>

void *my_memmove(void *dest, const void *src, int n)
{
	int i;
	char *p = malloc(n);
	
	for(i = 0; i < n; i++)
		*(p + i) = *((char *)(src) + i);
	
	for(i = 0; i < n; i++)
		*((char *)dest + i) = *(p + i);
	free(p);
	return dest;
}

int main(void)
{
	int i, src[5] = {1, 2, 3, 4, 5};

	my_memmove(src + 2, src, 12);

	for(i = 0; i < 5; i++)
		printf("%d ", src[i]);
	printf("\n");


	return 0;
}
