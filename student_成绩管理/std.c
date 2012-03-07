#include <stdio.h>
#include <stdlib.h>
#define ITEM 5

typedef struct{
    unsigned id;
    char name[20];
    unsigned math, eng;
    double average;
}std_t;

void show_msg(int sign)
{
    switch(sign){
    case 1:printf("1.Display std msg\n2.Sort by average\n3.Insert a new rec\n4.Exit\nPlease choose:");
           break;
    case 2:printf("ID\tNAME\tMATH\tENG\tAVE\n");
           printf("-------------------------------------------\n");
           break;
    }
}

void sys_err(const char *msg)
{
    perror(msg);
    exit(1);
}

std_t *get_info(FILE *fp, std_t *stdp, int *lenp)
{
    int cur_i, max_i;
    std_t tmp;
    stdp = malloc(ITEM * sizeof(std_t));
    if(stdp == NULL)
        sys_err("malloc fail");
    cur_i = 0, max_i = ITEM;
    while(EOF != fscanf(fp, "%d %s %d %d\n", &tmp.id, tmp.name, &tmp.math, &tmp.eng)){
        if(cur_i == max_i){
            max_i += ITEM;
            stdp = realloc(stdp, max_i * sizeof(std_t));
        }
        tmp.average = (tmp.math + tmp.eng) / 2.0;
        stdp[cur_i++] = tmp;
    }
    *lenp = cur_i;
    return stdp;
}

void display(std_t *stdp, int len)
{
    int i;
    show_msg(2);
    for(i = 0; i < len; i++){
        printf("%u\t%s\t%d\t%d\t%.2f\n", stdp[i].id, stdp[i].name, stdp[i].math, stdp[i].eng, (stdp[i].math + stdp[i].eng) / 2.0);
    }
}

/*
 *sign:1:sort by average
 *     2:sort by id;
 */
void sort(std_t *stdp, int len, int sign)
{
    int i, j, pos;
    std_t tmp;

    printf("in sort...\n");
    for(i = 0; i < len - 1; i++){
        pos = i;
        for(j = i + 1; j < len; j++){
            switch(sign){
            case 1:if(stdp[pos].average < stdp[j].average)
                    pos = j;
                  break;
            case 2:if(stdp[pos].id > stdp[j].id)
                        pos = j;
                    break;
            }
        }
        if(pos != i){
            tmp = stdp[pos];
            stdp[pos] = stdp[i];
            stdp[i] = tmp;
        }
    }
    if(sign == 1)
        display(stdp, len);
}

void insert(std_t *stdp, int len, FILE *fp)
{
    int i, max_id;
    std_t tmp;

    for(max_id = stdp[0].id, i = 1; i < len; i++)
        if(max_id < stdp[i].id)
            max_id = stdp[i].id;

    printf("enter a new recored(name math eng):\n");
    scanf("%s %d %d", tmp.name, &tmp.math, &tmp.eng);
    fprintf(fp, "%d %s %d %d\n", ++max_id, tmp.name, tmp.math, tmp.eng);
    fflush(fp);
}

int main(void)
{
    FILE *fp;
    std_t *stdp = NULL;
    int choice, len;
    
    fp = fopen("student_score", "r+");
    if(fp == NULL)
        sys_err("fopen student_score");
    stdp = get_info(fp, stdp, &len);

    while(1){
        show_msg(1);
        scanf("%d", &choice);
        switch(choice){
        case 1:display(stdp, len);
                break;
        case 2:sort(stdp, len, 1);
                break;
        case 3:insert(stdp, len, fp);
               break;
        case 4:sort(stdp, len, 2);
                free(stdp);
                fclose(fp);
                return 0;
        default:fputs("Invalid choice, rechoose!\n", stdout);
                break;
        }
    }

    return 0;
}
