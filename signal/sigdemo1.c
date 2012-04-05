#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void f(int signum)
{
	printf("OUCH!\n");
}

int main(void)
{
	int i;

	signal(SIGINT, f);              //f handle contrl + c
	for(i = 0; i < 5; i++){
		printf("hello\n");
		sleep(1);
	}
	return 0;
}
