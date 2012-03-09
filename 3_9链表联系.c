/*************************************************
*1、 创建一个有5个结点的单链表
*truct student{
*	unsigned id;
*	char name[20];
*	struct student *next;
*};
*2、根据上题创建的链表,删除指定name的结点。
*说明: 输入5个名字 选择其中的名字删除 再打印出来
**************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
    unsigned id;
    char name[20];
    struct node *next;
}node_t;


node_t *create(node_t *head, int len)
{
    int i;
    node_t *cur, *tail;

    for(i = 0; i < len; i++){
        cur = malloc(sizeof(node_t));
        if(cur == NULL){
            perror("malloc fail");
            exit(1);
        }
        cur->id = i + 1;
        scanf("%s", cur->name);
        cur->next = NULL;
        if(i == 0)
            head = tail = cur;
        else{
            tail->next = cur;
            tail = cur;
        }
    }
    return head;
}

node_t *del_node(node_t *head)
{
    char str[20];
    node_t *cur, *pre, *del;

    printf("input a name:");
    scanf("%s", str);

    pre = cur = head;
    while(cur){
       if(!strcmp(cur->name, str)){
            del = cur;
            if(cur == head){
                head = pre = cur = cur->next;
            }else{
                pre->next = cur = cur->next;
            }
            free(del);
       }else{
            pre = cur;
            cur = cur->next;
       }
    }
    return head;
}

void show_destroy(node_t *head)
{
    node_t *cur, *next;

    for(cur = head; cur; cur = next){
        printf("%d %s\n", cur->id, cur->name);
        next = cur->next;
        free(cur);
    }
}
int main(void)
{
    node_t *head = NULL;

    head = create(head, 5);
    head = del_node(head);
    show_destroy(head);
    return 0;
}





//如何判断一个链表中是否存在环。
//
#include <stdio.h>
#include <stdlib.h>

#define NUM 10

typedef struct node{
    unsigned n;
    struct node *next;
}node_t;


node_t *create(node_t *head, int len)
{
    int i;
    node_t *cur, *tail;

    for(i = 0; i < len; i++){
        cur = malloc(sizeof(node_t));
        if(cur == NULL){
            perror("malloc fail");
            exit(1);
        }
        cur->n = i + 1;
        cur->next = NULL;
        if(i == 0)
            head = tail = cur;
        else{
            tail->next = cur;
            tail = cur;
        }
    }
    tail->next = head;//构成环
    return head;
}

int main(void)
{
    node_t *head = NULL, *cur, *pre;

    head = create(head, NUM);

    pre = cur = head;
    while(1){
        pre = pre->next;
        cur = cur->next->next;//步常为2
        if(pre == NULL || cur == NULL){
            printf("No Ring!\n");
            return 0;
        }
        if(pre == cur){
            printf("Ring occurred!\n");
            return 0;
        }
    }
    return 0;
}




//实现某个单链表的逆序。
//
#include <stdio.h>
#include <stdlib.h>

#define LEN 5 
typedef struct node{
    int n;
    struct node *next;
}node_t;

node_t *create(node_t *head, int len)
{
    int i;
    node_t *cur, *tail;

    for(i = 0; i < len; i++){
        cur = malloc(sizeof(node_t));
        scanf("%d", &(cur->n));
        cur->next = NULL;
        if(i == 0)
            head = cur;
        else
            tail->next = cur;
        tail = cur;
    }
    return head;
}

node_t *reverse(node_t *head)
{
    node_t *pre, *next, *cur;
    int i = 1;

    pre = head;
    cur = next = head->next;
    while(cur){
        printf("i = %d\n", i++);
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    head->next = NULL;
    head = cur;//销毁head
    return pre;
}

int main(void)
{
    node_t *head = NULL, *cur, *del;
    head = create(head, LEN);

    for(cur = head; cur != NULL; cur = cur->next){
        printf("--%d--", cur->n);
    }
    printf("\n");
    head = reverse(head);

    cur = head;
    while(cur != NULL){
        printf("==%d==", cur->n);
        del = cur;
        cur = cur->next;
        free(del);
    }
    printf("\n");
    return 0;
}



//第一种方法
//链表实现约瑟夫环问题。
//
#include <stdio.h>
#include <stdlib.h>

#define PERSONS 10
#define COUNT 4

typedef struct node{
    unsigned n;
    struct node *next;
}node_t;


node_t *create(node_t *head, int len)
{
    int i;
    node_t *cur, *tail;

    for(i = 0; i < len; i++){
        cur = malloc(sizeof(node_t));
        if(cur == NULL){
            perror("malloc fail");
            exit(1);
        }
        cur->n = i + 1;
        cur->next = NULL;
        if(i == 0)
            head = tail = cur;
        else{
            tail->next = cur;
            tail = cur;
        }
    }
    tail->next = head;// 变成环状
    return head;
}

int main(void)
{
    node_t *head = NULL, *del, *cur, *pre, *next;;
    int remain = PERSONS, step = 1;

    head = create(head, PERSONS);

    pre = cur = head;
    while(remain > 0){
        if(step != COUNT){
            pre = cur;
            cur = cur->next;
            step++;
        }else{
            del = cur;
            printf("%d killed!\n", cur->n);
            pre->next = cur = cur->next;
            remain--;
            step = 1;
            free(del);
        }
    }
    return 0;
}




//链表实现约瑟夫环问题。第二种方法(比第一种好)
#include <stdio.h>
#include <stdlib.h>

#define PERSONS 10
#define COUNT 4

typedef struct node{
    int data;
    struct node *next;
}node_t;

node_t *make_node(int data, node_t *next)
{
    node_t *cur = malloc(sizeof(node_t));
    cur->data = data;
    cur->next = next;
    return cur;
}

int main(void)
{
    int i;
    node_t *cur, *del;

    cur = make_node(1, NULL);
    cur->next = cur;

    for(i = 2; i <= PERSONS; i++)
        cur = cur->next = make_node(i, cur->next);

    while(cur != cur->next){
        for(i = 1; i < COUNT; i++)
            cur = cur->next;
        del = cur->next;
        cur->next = cur->next->next;
        printf("%d killed!\n", del->data);
        free(del);
    }
    printf("%d survived!\n", cur->data);
    return 0;
}



//双链表练习 书上
#include <stdio.h>
#include <stdlib.h>

typedef struct node *link_t;

typedef struct node{
    unsigned char item;
    link_t prev, next;
}node_t;

node_t tailsentinel;
node_t headsentinel = {0, NULL, &tailsentinel};
node_t tailsentinel = {0, &headsentinel, NULL};


static link_t head = &headsentinel;
static link_t tail = &tailsentinel;

link_t make_node(unsigned char item)
{
    link_t p = malloc(sizeof(node_t));
    if(p != NULL){
        p->item = item;
        p->prev = p->next = NULL;
    }
    return p;
}

void free_node(link_t p)
{
    free(p);
}

link_t link_search(unsigned char key)
{
    link_t p;

    for(p = head->next; p != tail; p = p->next)
        if(p->item == key)
            return p;
    return NULL;
}

void link_insert(link_t p)
{
    p->next = head->next;
    head->next->prev = p;
    head->next = p;
    p->prev = head;
}

void link_delete(link_t p)
{
    p->prev->next = p->next;
    p->next->prev = p->prev;
}

void link_traverse(void (*visit)(link_t))
{
    link_t p;
    for(p = head->next; p!= tail; p = p->next)
        visit(p);
}

void link_destroy(void)
{
    link_t q, p = head->next;
    head->next = tail;
    tail->prev = head;
    while(p != tail){
        q = p;
        p = p->next;
        free_node(q);
    }
}

void link_print(link_t p)
{
    printf("%d\n", p->item);
}

int main(void)
{
    link_t p = make_node(10);
    link_insert(p);

    p = make_node(5);
    link_insert(p);

    p = make_node(90);
    link_insert(p);

    p = link_search(5);
    link_delete(p);
    free_node(p);
    link_traverse(link_print);

    link_destroy();
    return 0;
}
