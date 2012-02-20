
//用指针完成数组元素的存数及数据的反向输出
//
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 5

void init(int num[], int len)
{
	int *p;

	srand(time(NULL));
	for(p = num; p < num + len; p++)
		printf("%d ", *p = rand() % 50);
	printf("\n");
}

void opp(int num[], int len)
{
	int *p;

	for(p = num + len - 1; p >= num; p--)
		printf("%d ", *p);
	printf("\n");
}

int main(void)
{
	int num[LEN];

	init(num, LEN);
	opp(num, LEN);
	return 0;
}





//函数实现：删除字符数组中的空格：自己改成函数实现
//
//
#include <stdio.h>
#include <string.h>

#define LEN 100

int main(void)
{
	char str[LEN];	
	int i, j;

	fgets(str, LEN, stdin);
	printf("str:%s\n", str);
	if(str[strlen(str) - 1] == '\n')
		str[strlen(str) - 1] = '\0';
	
	for(i = j = 0; str[i] != '\0'; i++)
		if(str[i] != ' ')
			str[j++] = str[i];

	str[j] = '\0';
	printf("str:%s\n", str);
	return 0;
}



//猜数:首先生成一个介于1-100之间的整数,从
//键盘不断输入数值直到该数值与生成的那个数
//相符为止,并打印出猜数的次数
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void create(int *secretp)
{
	srand(time(NULL));
	*secretp = rand() % 100 + 1;
}

void guess(int secret)
{
	int n, count = 1;

	while(1){
		printf("enter a number:");
		scanf("%d", &n);
		if(n == secret){
			printf("You get it by %d times!\n", count);
			break;
		}
		if(n > secret)
			printf("Too high!\n");
		else
			printf("Too low!\n");
		count++;
	}
}

int main(void)
{
	int secret;
	create(&secret);
	guess(secret);
	return 0;
}



//生成26个排列好的英文字母
//
//
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void create(char letter[], int len)
{
	int i, tmp;

	srand(time(NULL));
	for(i = 0; i < 26; ){
		tmp = rand() % 26;
		if(*(letter + tmp) == 0){
			*(letter + tmp) = tmp + 'a';
			i++;
		}
	}
}


int main(void)
{
	char letter[26] = {0};
	int i;

	create(letter, 26);

	for(i = 0; i < 26; i++)
		printf("%c ", letter[i]);
	putchar('\n');
	return 0;
}




//用动态方法做
int id;
char *pname;
int score;
} *pstd;
输入5条学生信息,根据score进行升序排序
使用malloc函数或结构体数组
//定义结构体:struct student{
//int id;
//char *pname;
//int score;
//} *pstd;
//输入5条学生信息,根据score进行升序排序
//使用malloc函数或结构体数组
//

#include <stdio.h>
#include <stdlib.h>

typedef struct student{
	int id;
	char *pname;
	int score;
}std_t;

std_t *get_info(std_t *pstd, int len)
{
	int i;

	pstd = (std_t *)malloc(len * sizeof(std_t));
	if(pstd == NULL){
		printf("malloc fail!\n");
		exit(1);
	}
	for(i = 0; i < len; i++){
		printf("enter %d info:\n", i + 1);
		pstd[i].pname = (char *)malloc(20);
		if(pstd[i].pname == NULL){
			printf("malloc fail!\n");
			exit(1);
		}
		scanf("%d %s %d", &pstd[i].id, pstd[i].pname, &pstd[i].score);
	}
	return pstd;
}

void sort(std_t *pstd, int len)
{
	int i, j, pos;
	std_t tmp;

	for(i = 0; i < len - 1; i++){
		pos = i;
		for(j = i + 1; j < len; j++)
			if(pstd[pos].score > pstd[j].score)
				pos = j;
		if(pos != i){
			tmp = pstd[pos];
			pstd[pos] = pstd[i];
			pstd[i] = tmp;
		}
	}
}

void show_destroy(std_t *pstd, int len)
{

	int i;

	for(i = 0; i < len; i++){
		printf("%d %s %d\n", pstd[i].id, pstd[i].pname, pstd[i].score);
		free(pstd[i].pname);
	}
	free(pstd);
}

int main(void)
{
	std_t *pstd = NULL;

	pstd = get_info(pstd, 5);
	sort(pstd, 5);

	show_destroy(pstd, 5);
	return 0;
}


//用数珠的方法
//定义结构体:struct student{
//int id;
//char *pname;
//int score;
//} *pstd;
//输入5条学生信息,根据score进行升序排序
//使用malloc函数或结构体数组
//
#include <stdio.h> 
typedef struct student{
	int id;
	char *pname;
	int score;
}std_t;

void get_info(std_t *pstd, char (*parr_name)[20], int row)
{
	int i;

	for(i = 0; i < row; i++){
		printf("enter %d info:\n", i + 1);
		pstd[i].pname = parr_name[i];
		scanf("%d %s %d", &pstd[i].id, pstd[i].pname, &pstd[i].score);
	}
}

void sort(std_t *pstd, int len)
{
	int i, j, pos;
	std_t tmp;

	for(i = 0; i < len - 1; i++){
		pos = i;
		for(j = i + 1; j< len; j++)
			if(pstd[pos].score > pstd[j].score)
				pos = j;

		if(pos != i){
			tmp = pstd[pos];
			pstd[pos] = pstd[i];
			pstd[i] = tmp;
		}
	}
}

void bubble(std_t *pstd, int len)
{
	int i, j;
	std_t tmp;

	for(i = 0; i < len - 1; i++){
		for(j = 0; j < len - i - 1; j++)
			if(pstd[j].score > pstd[j + 1].score){
				tmp = pstd[j];
				pstd[j] = pstd[j + 1];
				pstd[j + 1] = tmp;
			}
	}
}

int main(void)
{
	std_t std[5];
	char name[5][20];
	int i;

	get_info(std, name, 5);
	bubble(std, 5);

	printf("after sort...\n");
	for(i = 0; i < 5; i++)
		printf("%d %s %d\n", std[i].id, std[i].pname, std[i].score);
	return 0;
}




//定义一个字符指针数组如:
//char *str[] = {“Wuhan”,”Tianjin“, “Beijing“,
//“Shanghai”};按照字典序完成排序操作
//
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *str[] = {"Wuhan", "Tianjin", "Beijing", "Shanghai"};
	char *tmp;
	int i, j;

	printf("*(*str + 0):%c\n", *(*str + 0));
	printf("*(*str + 1):%c\n", *(*str + 1));


	for(i = 0; i < 3; i++){
		for(j = 0; j < 3 - i; j++)
			if(strcmp(str[j], str[j + 1]) > 0){
				tmp = str[j];
				str[j] = str[j + 1];
				str[j + 1] = tmp;
			}
	}

	for(i = 0; i < 4; i++)
		printf("%s\n", str[i]);
	return 0;
}


//有字符串: ‚Today is a wonderful day!‛将该字
//符串中各个单词存放到二维数组:char str[5][10]
//
#include <stdio.h>

void parse(char *sp, char (*str)[10])
{
	int i = 0, j = 0;
	char *p = sp;

	while(*p){
		if(*p != ' '){
			str[i][j++] = *p;
		}else{
			str[i++][j] = '\0';
			j = 0;
		}
		p++;
	}
	str[i][j] = '\0';
}

int main(void)
{
	char *sp = "Today is a wonderful day!";
	char str[5][10];
	int i;

	parse(sp, str);

	for(i = 0; i < 5; i++)
		printf("%s\n", str[i]);
	return 0;
}
