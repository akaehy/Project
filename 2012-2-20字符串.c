
//#include <stdio.h>
//int main(int argc, char * argv[])
//{
//char str[] = “I like programming!”;
//int i = 0;
//while(str[i] != '\0')
/* 思考一下为啥是 \0 呢?及其作用*/
//{
//printf(“%c”, str[i]);
//i++;
//}
//printf(“\n”);
//return 0;
//}
//1、将以上代码改成自定义函数
//2、怎么能将str数组里的内容反向输出?
//3、对于str数组里的所有小写字符改成大写输出
//
#include <stdio.h>

int show(char str[])
{
	int i = 0;

	while(str[i]){
		printf("%c", str[i]);
		i++;
	}
	printf("\n");
	return i;
}

void reverse(char str[], int len)
{
	int i = --len;

	while(i >= 0){
		printf("%c", str[i]);
		i--;
	}
	printf("\n");
}

void up_low(char str[])
{
	int i = 0;

	while(str[i]){
		if(str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		else if(str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
}
int main(void)
{
	char str[100] = "I like programming!";
	int len;

	
	len = show(str);
	reverse(str, len);

	up_low(str);
	printf("%s\n", str);
	return 0;
}



//判断输入的字符串是否为“回文”(顺读和倒读都一样)
//字符串
//
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[100];
	int len, i, j;
	while(fgets(str, 100, stdin)){
	len = strlen(str);
	if(str[len - 1] == '\n'){
		str[len - 1] = '\0';
		len--;
	}
	if(strcmp(str, "exit") == 0)
		break;

	for(i = 0, j = len - 1; i <= j; i++, j--){
		if(str[i] != str[j])
			break;
	}
	if(i > j)
		printf("Palindrom!\n");
	else
		printf("Not palindrom!\n");
	}
	return 0;
}

//从键盘接收一个字符串,然后按照字符顺序从小到大进
//行排序并删除重复字符。
//如从键盘输入的内容为“agehiagehp”,执行完程序之后变
//为:“aeghip”
//
#include <stdio.h>
#include <string.h>

void del(char str[])
{
	int i, j, k;

	for(i = j = k = 0; str[i]; i++){
		for(j = k - 1; j >= 0; j--)
			if(str[j] == str[i])
				break;
		if(j < 0)
			str[k++] = str[i];
	}
	str[k] = '\0';
}

void sort(char str[])
{
	int len = strlen(str), i, j, pos;
	char tmp;

	for(i = 0; i < len - 1; i++){
		pos = i;
		for(j = i + 1; j < len; j++)
			if(str[pos] > str[j])
				pos = j;
		if(pos != i){
			tmp = str[pos];
			str[pos] = str[i];
			str[i] = tmp;
		}

	}
	
}
int main(void)
{
	char str[100];

	gets(str);
	del(str);
	sort(str);
	puts(str);
	return 0;

}




//编写程序计算一个英文句子中最长单词的长度(字母个
//数(max。假设该英文句子中只含有字母和空格,在空格
//之间连续的字母串称为单词。
//

#include <stdio.h>

int main(void)
{
	char str[100];
	int i, start, end, max = 0;

	gets(str);

	for(i = 0; str[i]; i++){
		for(start = i; str[start] == ' '; start++)
			;
		for(end = start; str[end] && str[end] != ' '; end++)
			;
		i = end;
		if(max < end - start)
			max = end - start;
	}
	printf("max = %d\n", max);

	return 0;
}


