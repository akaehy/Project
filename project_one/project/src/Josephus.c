#include <stdio.h>
#include "header.h"

static void init(int persons[])
{
	int i;

	for(i = 0; i < PERSON; i++)
		persons[i] = i + 1;
}

void Josephus(int count)
{
	int persons[PERSON], remain = PERSON, step = 1, i = 0;

	init(persons);
	while(remain > 0){
		if(persons[i] != -1 && step != count){
			step++;
		}else if(persons[i] != -1 && step == count){
			printf("%d out!\n", persons[i]);
			persons[i] = -1;
			step = 1;
			remain--;
		}
		i++;
		if(i == PERSON)
			i = i % PERSON;
	}
	
}
