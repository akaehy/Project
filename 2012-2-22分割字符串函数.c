
//目的：取出key值和value值并打印；
//首先strchr搜索？号找到地址+1得到complete中c的地址给begin
//进入for循环； 第一次key中保存complete中c的地址，saveptr1中保存hl中h的地址
//往下执行； 到strtok_r（key,"=",&saveptr2);是取出1的地址放在saveptr2中；
//执行printf时key中保存的是=好左边字符串的首地址，saveptr2保存的是=右边字串右边的地址
//分别打印，再进入下次循环
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[] = "http://www.google.cn/search?complete=1&hl=zh-CN&ie=GB2312&q=lionux&meta";

	char *begin, *key, *saveptr1, *saveptr2;

	for(begin = strchr(str, '?') + 1; ; begin = NULL){
		key = strtok_r(begin, "&", &saveptr1);
		if(key == NULL)
			break;
		strtok_r(key, "=", &saveptr2);
		printf("key = %s, value = %s\n", key, saveptr2);
	}
	return 0;
}



//给定程序中,函数fun的功能是:将形参s所指字符串中
//的所有字母字符顺序前移,其他字符后移,处理后新字
//符串的首地址作为函数值返回。例如,s所指字符串为
//:asd123fgh543df,处理后新字符串为:asdfghdf123543
//
#include <stdio.h>
#include <string.h>

#define LEN 100

int main(void)
{
	char str[LEN], tmp;
	int len, i, j, end;

	printf("enter a string:");
	fgets(str, LEN, stdin);
	len = strlen(str);

	if(str[len - 1] == '\n'){
		str[len - 1] = '\0';
		len--;
	}

	for(i = end = len - 1; i >= 0; i--){
		if(str[i] >= '0' && str[i] <= '9'){
			tmp = str[i];
			for(j = i + 1; j <= end; j++)
				str[j- 1] = str[j];
			str[end--] = tmp;
		}
	}

	printf("str:%s\n", str);
	return 0;
}



//strcspn函数范例strcspn(“abc”,bcd”),搜索字
//符串“abc”中出现在”bcd”字符集中的字符返回
//其下标,则函数应该返回“abc”中„b‟的下标:1
//;若第一个参数中所有字符都没有在第二个参
//数中出现则返回„\0'的下标
//
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	printf("%d\n", strcspn(argv[1], argv[2]));
	return 0;
}



//strtok_r的使用举例1
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str1[] = "abcd;,bcde:;,defg";
	char str2[] = "helloaworldbedu";
	char *retp, *savep1, *savep2;

	retp = strtok_r(str1, ",:;", &savep1);
	printf("retp:%s\n", retp);
	retp = strtok_r(str2, "ab", &savep2);
	printf("retp:%s\n", retp);

	while((retp = strtok_r(NULL, ",:;", &savep1)))
		printf("retp:%s\n", retp);

	return 0;
}

//strtok_r函数使用举例2
//输入 ./a.out 'a/bbb///cc;xxx:yyy: ':;' '/'
//结果为
//1：a/bbb///cc
//-->a
//-->bbb
//-->cc
//2:xxx
//-->xxx
//3:yyy
//-->yyy
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *str1, *str2, *token, *subtoken;
	char *saveptr1, *saveptr2;
	int j;

	if(argc != 4){
		fprintf(stderr, "Usage:%s string delim subdelim\n", argv[0]);
		exit(1);
	}

	for(j = 1, str1 = argv[1]; ; j++, str1 = NULL){
		token = strtok_r(str1, argv[2], &saveptr1);
		printf("saveptr1:%p, token:%p\n", saveptr1, token);
		if(token == NULL)
			break;
		printf("%d:%s\n", j, token);
		
		for(str2 = token; ; str2 = NULL){
			subtoken = strtok_r(str2, argv[3], &saveptr2);
			if(subtoken == NULL)
				break;
			printf("-->%s\n", subtoken);
		}
	}

	return 0;
}


//strtok函数举例
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[] = "root:x::0:root:/root:/bin/bash";
	char *token;

	token = strtok(str, ":");
	printf("token:%s\n", token);

	while((token = strtok(NULL, ":")))
		printf("token:%s\n", token);
	return 0;
}



//给定程序中,函数fun的功能是:找出形参s所指字符串
//中出现频率最高的字母(不区分大小写),并统计出其
//出现的次数。例如,形参s所指的字符串为:
//abcAbsmaxless,程序执行后的输出结果为:letter 'a' : 3
//times letter 's' : 3 times
//
//
//
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	int times[26] = {0}, i = 0, max_i, j, pos, tmp;

	if(argc != 2){
		fprintf(stderr, "Usage %s!\n", argv[0]);
		exit(1);
	}
	
	while(argv[1][i]){
		times[tolower(argv[1][i]) - 'a']++;//tolower()将字符转换成小写toupper()将字符转换成大写
		i++;
	}

	for(i = 0; i < 26; i++)
		printf("'%c':%d!\n", i + 'a', times[i]);

	
	for(i = 0; i < 25; i++){
		pos = max_i = i;
		for(j = i + 1; j < 26; j++){
			if(times[pos] < times[j])
				pos = max_i = j;
		}
		if(pos != i){
			tmp = times[pos];
			times[pos] = times[i];
			times[i] = tmp;
		}
		if(i == 0)
			printf("max:'%c' occurs %d!\n", max_i + 'a', times[0]);
		else if(times[i] == times[0])
			printf("max:'%c' occurs %d!\n", max_i + 'a', times[i]);
		else 	break;
			
	}
	return 0;
}




//自行编写strtok函数
#include <stdio.h>
#include <string.h>

char *my_strtok(char *s, const char *delim)
{
	char *sbegin, *send;
	static char *savep = "";

	sbegin = s ? s : savep;

	//"root:::0:x" ":"
	sbegin += strspn(sbegin, delim);
	if(*sbegin == '\0'){
		savep = "";
		return NULL;
	}

	send = sbegin + strcspn(sbegin, delim);
	if(*send != '\0')
		*send++ = '\0';
	savep = send;
	return sbegin;
}


int main(void)
{
	char str[] = "root::::x::0:root:/root:/bin/bash";
	char *token;

	token = my_strtok(str, ":");
	printf("token:%s\n", token);

	while((token = my_strtok(NULL, ":")))
		printf("token:%s\n", token);
	return 0;
}



//自行编写strtok_r函数
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *my_strtok_r(char *s, const char *delim, char **savepp)
{
	char *sbegin, *send;

	sbegin = s ? s : *savepp;

	sbegin += strspn(sbegin, delim);
	if(*sbegin == '\0'){
		return NULL;
	}

	send = sbegin + strcspn(sbegin, delim);
	if(*send != '\0')
		*send++ = '\0';
	*savepp = send;
	return sbegin;
}


int main(int argc, char *argv[])
{
	char *str1, *str2, *token, *subtoken;
	char *saveptr1, *saveptr2;
	int j;

	if(argc != 4){
		fprintf(stderr, "Usage:%s string delim subdelim\n", argv[0]);
		exit(1);
	}

	for(j = 1, str1 = argv[1]; ; j++, str1 = NULL){
		token = strtok_r(str1, argv[2], &saveptr1);
		printf("saveptr1:%p, token:%p\n", saveptr1, token);
		if(token == NULL)
			break;
		printf("%d:%s\n", j, token);
		
		for(str2 = token; ; str2 = NULL){
			subtoken = strtok_r(str2, argv[3], &saveptr2);
			if(subtoken == NULL)
				break;
			printf("-->%s\n", subtoken);
		}
	}

	return 0;
}
