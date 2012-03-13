
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char c;
    int n;
    char str[8];
    struct node *next;
}node_t;

node_t *create(char *filename, node_t *head)
{
    FILE *fp;
    node_t data, *cur;

    fp = fopen(filename, "r");
    if(fp == NULL){
        perror("fopen fail");
        exit(1);
    }
    while(EOF != fscanf(fp, "%c %d %s\n", &data.c, &data.n, data.str)){
        cur = malloc(sizeof(node_t));
        if(cur == NULL){
            fprintf(stderr, "malloc fail!\n");
            exit(1);
        }
        *cur = data;
        cur->next = NULL;

        cur->next = head;
        head = cur;
    }
    fclose(fp);
    return head;
}
void link_print_destroy(node_t *head)
{
    node_t *cur, *next;

    for(cur = head; cur != NULL; cur = next){
        next = cur->next;
        printf("%c %d %s\n", cur->c, cur->n, cur->str);
        free(cur);
    }
}
int main(void)
{
    node_t *head = NULL;

    head = create("file.txt", head);
    link_print_destroy(head);

    return 0;
}
