#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void print_msg(char *p, int sec)
{
	while(sec--)
	{
		sleep(1);
		printf("%s\n", p);
	}
}

int main(void)
{
	printf("process:\n");

	pid_t pid;

	pid = fork();
	if(pid == 0)
	{
		print_msg("child", 15);
		exit(0);
	}
	else if(pid > 0)
	{
		print_msg("parent", 4);
		//wait(NULL);
		exit(0);
	}
	else
	{
		perror("fork");
		exit(1);
	}

	return 0;
}
