#ifndef HEADER_H
#define HEADER_H
#define PERSON 10
#define COUNT 4
#define LEN 5 

typedef struct student{
	unsigned short id;
	char name[10];
	int s[4];
	double ave;
}std_t;
void Josephus(int);
char *str_combination(char *dest);

void read(std_t std[], int len);
void write(std_t std[], int len);
#endif
