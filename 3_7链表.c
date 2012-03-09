/********************************************************************
 * 单向链表的创建
 * 在前面连入结点
 *******************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node *next;
}node_t;

node_t *create(node_t *head)
{
	int n;
	node_t *cur, *tail;

	while(1){
		scanf("%d", &n);
		if(n == 0)
			break;

		cur = malloc(sizeof(node_t));//第1步：申请空间
		if(cur == NULL){
			perror("malloc fail");
			exit(1);
		}

		cur->data = n;//第2步：向空间中存放数据
		cur->next = NULL;

		cur->next = head;//第3步：插入链表——头部链入或尾部链入，此为头部链入
		head = cur;


	}
	return head;
}

void link_print_destroy(node_t *head)
{
	node_t *cur, *next;

	for(cur = head; cur != NULL; cur = next){
		next = cur->next;
		printf("--%d--\n", cur->data);
		free(cur);
	}
}


int main(void)
{
	node_t *head = NULL;

	head = create(head);
	link_print_destroy(head);
	return 0;
}


/************************************************************************
 * 此为尾部链入
 * *********************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node *next;
}node_t;

node_t *create(node_t *head)//创建节点和连入链表放在一个里面了
{
	int n;
	node_t *cur, *tail;
	while(1)
	{
		scanf("%d", &n);
		if(n == 0)
			break;
		cur = malloc(sizeof(node_t));//1
		if(cur == NULL)
		{
			perror("malloc fail");
			exit(1);
		}


		cur->data = n;//2
		cur->next = NULL;


		if(head == NULL)//3
			head = tail = cur;
		else
			tail->next = cur;
		tail = cur;


	}
	return head;
}

void link_print_destroy(node_t *head)
{
	node_t *cur, *next;

	for(cur = head; cur != NULL; cur = next){
		next = cur->next;
		printf("--%d--\n", cur->data);
		free(cur);
	}
}

int main(int argc, const char *argv[])
{
	node_t *head = NULL;
	
	head = create(head);
	return 0;
}


/****************************************************************
 * malloc的使用
 * *************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	char *p = malloc(20);//p:stack(栈); *p:pead(堆)	
	if(p == NULL){
		perror("malloc fail");
		exit(1);
	}

	printf("malloc:p = %p\n", p);//13行和16行
	printf("%s\n", strcpy(p, "hello!"));
	free(p);//free heap memorys(释放的是堆上的)
	printf("free:p = %p\n", p);//p变量本身是statck中的而p中的值是pead中的数据
	                           //free释放的是堆区的空间所以p值没变

	p = NULL;//防止野指针出现 (如果它的上一行有*p=？？)可段错误

	return 0;
}



/******************************************************************
 * realloc的使用
 * ***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	
	char *p = malloc(10);
	if(p == NULL){
		perror("malloc fail");
		//fprintf(stderr,"malloc
		//fail");stderr与stdout的区别stdout有行缓存特性stderr没有
		exit(1);
	}
	printf("%s\n",strcpy(p, "hello!"));

	p = realloc(p, 20);//20为最终使用的字节数 p为malloc或者calloc申请的地址值
	printf("%s\n",strcpy(p, "hello!"));//数据没变

	free(p);
	p = NULL;
	return 0;
}


/************************************************************************
 * 输入若干自然数,若输入数据为0则结束输
 * 入,把以上数据保存到堆中,然后打印。
 *(关键在于如何动态分配空间)
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define ITEM 10

int main(void)
{
	int *p, n, i, max_i = ITEM, cur_i = 0;

	p = malloc(sizeof(int) * ITEM);
	if(p == NULL){
		fprintf(stderr, "malloc fail!\n");
		exit(1);
	}
	while(1){
		printf("enter a number:");
		scanf("%d", &n);
		if(n == 0)
			break;
		if(cur_i == max_i){
			max_i += ITEM;
			p = realloc(p, sizeof(int) * max_i);
			if(p == NULL){
				fprintf(stderr, "realloc fail!\n");
				exit(1);
			}
		}
		p[cur_i++] = n;
	}

	for(i = 0; i < cur_i; i++)
		printf("%d ", p[i]);
	printf("\n");

	free(p);
	p = NULL;
	return 0;
}



//链表
//Makefile这样写将main函数(此处为测试函数)在调试的时候打开
//在应用中关闭
//make CPPFLAGS=-DDEBUG(打开main)
//直接make没有打开main函数
/***********************************************************
*src = $(wildcard *.c) 
*targets = $(patsubst %.c, %, $(src))

*CC = gcc
*CFLAGS = -Wall -g
*CPPFLAGS = 

*all:$(targets)
*$(targets):%:%.c 
*	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@	
*
*clean:
*	-rm -rf $(targets)
*.PHONY:clean all
**********************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node *next;
}node_t;

static node_t *mk_node(int val)
{
	node_t *p = malloc(sizeof(node_t));
	if(p != NULL){
		p->data = val;
		p->next = NULL;
	}
	return p;
}

node_t *link_insert(node_t *head, int val)
{
	node_t *cur = mk_node(val);
	node_t *tail;

	if(cur == NULL || head == NULL){
		if(head == NULL)
			head = cur;
		return head;
	}

	for(tail = head; tail->next != NULL; tail = tail->next)
		;
	tail->next = cur;
	return head;
}

void link_show(node_t *head)
{
	node_t *cur;

	for(cur = head; cur != NULL; cur = cur->next)
		printf("--%d--\n", cur->data);
}

node_t *link_remove(node_t *head, int val)
{
	node_t *pre, *cur;
	
	if(head == NULL)
		return NULL;
	if(head->data == val){
		head = head->next;
		return head;		
	}
	for(pre = head, cur = head->next; cur != NULL; pre = pre->next, cur = cur->next){
		if(cur->data == val){
			pre->next = cur->next;
			cur->next = NULL;
			return cur;
		}
	}
	return NULL;
}

void link_destroy(node_t *head)
{
	node_t *cur, *next;

	for(cur = head; cur != NULL; cur = next){
		next = cur->next;
		free(cur);
	}
}

void link_print_destroy(node_t *head)
{
	node_t *cur, *next;

	for(cur = head; cur != NULL; cur = next){
		next = cur->next;
		printf("--%d--\n", cur->data);
		free(cur);
	}
}

#ifdef DEBUG
int main(void)
{
	node_t *head = NULL, *rmp;
	int n;
	while(1){
		scanf("%d", &n);
		if(n == 0)
			break;
		head = link_insert(head, n);
	}
	link_show(head);

	rmp = link_remove(head, 3);
	printf("rmp->data = %d\n", rmp->data);

	free(rmp);
	rmp = NULL;

	link_destroy(head);
	head = NULL;

	return 0;
}
#endif
