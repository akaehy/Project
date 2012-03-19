#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LEN	100
#define EX_LEN		1024

struct word
{
	char word[50];
	long position;
	struct word *next;
};

typedef struct word V_NODE;

int menu(void)
{
	int choice;
	puts("\nPlease make a choice:\n1.search for a word\n2.add a word\n9.quit");
	scanf("%d", &choice);
	getchar();
	return choice;
}

void print_ex(char *ex)
{
	ex += 6;
	char buf[EX_LEN];
	strcpy(buf, ex);
	ex = buf;
	ex = strtok(ex, "@");
	int i = 0;
	while(ex != NULL)
	{
		printf("%d.%s\n", ++i, ex);
		ex = strtok(NULL, "@");
	}

	

}
void search(char *word)
{
	char wbuf[WORD_LEN];
	char ebuf[EX_LEN];
	FILE *fp = fopen("dict.txt", "r+");
	if(fp == NULL)
	{
		perror("open");
		exit(0);
	}

	char *ret_v;

	ret_v = fgets(wbuf, WORD_LEN-1, fp);
	fgets(ebuf, EX_LEN-1, fp);
	while(ret_v != NULL)
	{
		if(strcmp(word, wbuf+1) == 0)
		{
			print_ex(ebuf);
			return;
		}
		ret_v = fgets(wbuf, WORD_LEN-1, fp);
		fgets(ebuf, EX_LEN-1, fp);
	}

	fclose(fp);
}

void search1(char *word)
{
	char wbuf[WORD_LEN];
	char ebuf[EX_LEN];
	FILE *fp = fopen("dict.txt", "r+");
	if(fp == NULL)
	{
		perror("open");
		exit(0);
	}

	char c;
	while((c = getc(fp)) != EOF)
	{
		if(c == '#')
		{
			fgets(wbuf,WORD_LEN-1, fp);
			if(strcmp(word, wbuf) == 0)
			{
				fgets(ebuf, EX_LEN, fp);
				print_ex(ebuf);
				return;
			}
		}			
	}

	fclose(fp);

}

void get_word(char *cbuf, char *word)
{

	while(*cbuf != '\n')
	{
		*word = *cbuf;
		word++;
		cbuf++;
	}
	*word = '\n';
	word++;
	*word = '\0';
}

void get_ex(char *cbuf, char *ex)
{
	while(*cbuf != '\n')
	{
		cbuf++;
	}
	cbuf++;

	while(*cbuf != '\n')
	{
		*ex = *cbuf;
		cbuf++;
		ex++;
	}
	*ex = '\n';
	ex++;
	*ex = '\0';
}
int find_word(char *buf, char *w)
{

	int i = 0;
	char word[WORD_LEN];
	char ex[EX_LEN];

	for(i=0; i<1024*9; i++)
	{
		
		if(buf[i] == '#')
		{
			get_word(buf+i+1, word);
			if(strcmp(word, w) == 0)
			{
				get_ex(buf+i+1, ex);
				print_ex(ex);
				return 1;
			}
		}
		
	}
	
	return 0;
}

void sort_buf(char *buf)
{
	int i = 0;

	for(i=0; i<1024; i++)
	{
		buf[i] = buf[i+1024*9];
	}
}

char buf[1024*10];
void search2(char *word)
{
	
	FILE *fp = fopen("dict.txt", "r+");
	if(fp == NULL)
	{
		perror("open");
		exit(1);
	}

	int n = 0;
	int ret_v = 0;
	n = fread(buf, 1, 1024*10, fp);
	while(n > 0)
	{
		ret_v = find_word(buf, word);
		if(ret_v > 0)
		{
			return;
		}

		sort_buf(buf);

		n = fread(buf+1024, 1, 1024*9, fp);
		
	}

	fclose(fp);

}

void get_explanation(V_NODE *p)
{
	FILE *fp = fopen("dict.txt", "r+");
	if(fp == NULL)
	{
		perror("open");
		exit(0);
	}

	fseek(fp, p->position, SEEK_SET);
	char buf[1024];
	fgets(buf, WORD_LEN, fp);
	fgets(buf, EX_LEN, fp);
	print_ex(buf);


	fclose(fp);
}
int search3(V_NODE *p, char *w)
{
		while(p != NULL)
		{
			if(strcmp(p->word, w) == 0)
			{
				get_explanation(p);	
				return 0;
			}
			p = p->next;
		}

		return -1;
}

void print_similar(V_NODE *p, char *w)
{
	int i = 1;
	char buf[20];
	while(p != NULL)
	{
		if(strncmp(p->word, w, strlen(w) - 1) == 0)
		{
			printf("%s", p->word);
			if(((i++)%20) == 0)
			{
				puts("press enter to continue...(press 'q' to quit)");
				fgets(buf, 19, stdin);
				if(buf[0] == 'q')
				{
					break;
				}
			}
		}
		p = p->next;
	}
}

void search_for_word(V_NODE *head)
{
	char word[WORD_LEN];

	while(1)
	{
		puts("Please input the word:(input 1 to quit)");
		fgets(word, WORD_LEN-1, stdin);		
		if(word[0] == '1')
		{
			break;
		}
		if(word[strlen(word) - 2] == '*')
		{
			word[strlen(word) - 2] = '\n';
			word[strlen(word) - 1] = '\0';
			print_similar(head, word);
		}
		else
		{
			if(search3(head, word) < 0)
			{
				print_similar(head, word);
			}
		}			

	}		
}

void print_link(V_NODE *p)
{
	int i = 0;
	while(p != NULL)
	{
		printf("%ld:%s",p->position, p->word);
		p  = p->next;
		if(((i++)%1000) == 0)
		{
			getchar();
		}
	}
}
V_NODE *insert_to_link(V_NODE *head, char *w, long pos)
{
	V_NODE *p = malloc(sizeof(V_NODE));
	if(p == NULL)
	{
		perror("malloc");
		exit(1);
	}
	strcpy(p->word, w);
	p->position = pos;
	p->next = head;

	return p;
}

V_NODE *create_link(void)
{
	V_NODE *head = NULL;

	FILE *fp = fopen("dict.txt", "r+");
	if(fp == NULL)
	{
		perror("open");
		exit(1);
	}
	
	char c;
	char w[WORD_LEN];
	long pos = 0;
	while((c = getc(fp)) != EOF)
	{
		if(c == '#')
		{
			pos = ftell(fp);
			fgets(w, WORD_LEN-1, fp);
			head = insert_to_link(head, w, pos);
		}
	}
	fclose(fp);

	return head;
}

int get_info(char *w, char *ex)
{
	char ex_buf[1024];
	w[0] = '#';
	strcpy(ex, "Trans:");

	puts("please input word:");
	fgets(w+1, WORD_LEN, stdin);
	int i = 1;
	while(1)
	{
		printf("input explanation %d(input 1 to quit)\n", i++);
		fgets(ex_buf,EX_LEN, stdin);
		if(*ex_buf == '1')
		{
			break;
		}
		if(i > 2)
		{
			ex[strlen(ex)-1] = '@';
		}			
		strcat(ex, ex_buf);
	}
	return 1;
}
V_NODE *add_to_file(char *w, char *ex, V_NODE *head)
{
	FILE *fp = fopen("dict.txt", "a");
	if(fp == NULL)
	{
		perror("open");
		exit(1);
	}
	long pos = ftell(fp);
	fwrite(w, 1, strlen(w), fp);
	fwrite(ex, 1, strlen(ex), fp);
	V_NODE *p = malloc(sizeof(V_NODE));
	if(p == NULL)
	{
		perror("malloc");
		exit(1);
	}
	strcpy(p->word, w+1);
	p->position = pos;
	p->next = head;


	fclose(fp);

	return p;

}

void move_info(long pos, char *w, char *ex)
{
	FILE *fp = fopen("dict.txt", "r+");
	if(fp == NULL)
	{
		perror("open");
		exit(1);
	}
	fseek(fp, pos, SEEK_SET);
	char c;
	while((c = getc(fp)) != EOF)
	{
		if(c == '#')
		{
			break;
		}
	}
	pos = ftell(fp)-1;
	FILE *fp_temp = fopen("temp.txt", "w+");
	if(fp_temp == NULL)
	{
		perror("open temp");
		exit(1);
	}
	fwrite(w, 1, strlen(w), fp_temp);
	fwrite(ex, 1, strlen(ex), fp_temp);
	fseek(fp, pos, SEEK_SET);
	while((c = getc(fp)) != EOF)
	{
		putc(c, fp_temp);
	}

	rewind(fp_temp);
	fseek(fp, pos, SEEK_SET);
	while((c = getc(fp_temp)) != EOF)
	{
		putc(c, fp);
	}
	fclose(fp_temp);
	fclose(fp);		
}


V_NODE *update_link(V_NODE *p)
{
	V_NODE *ptr = NULL;
	while(p != NULL)
	{
		ptr = p;
		p = p->next;
		free(ptr);
	}

	ptr = create_link();
	return ptr;
}
V_NODE *insert_to_file(char *w, char *ex, V_NODE *head)
{
	V_NODE *p = head;
	while(p != NULL)
	{
		
		if(strcmp(p->word, w+1) < 0)
		{
			move_info(p->position, w, ex);
			head = update_link(head);
			break;
		}
		p = p->next;
	}
	return head;
}

V_NODE *add_word(V_NODE *head)
{
	char w[WORD_LEN];
	char ex[EX_LEN];

	if(get_info(w, ex) > 0)
	{
//		head = add_to_file(w, ex, head);//在后面插入的
		head = insert_to_file(w, ex, head);//改进后按字母ascii码大小插入的
	}		

	return head;
}
int main(void)
{
	int choice;
	V_NODE *head = NULL;

	head = create_link();
	while(1)
	{
		choice = menu();
		if(choice == 1)
		{
			search_for_word(head);
		}
		else if(choice == 2)
		{
			head = add_word(head);
		}
		else if(choice == 9)
		{
			break;
		}
	}
	return 0;
}
