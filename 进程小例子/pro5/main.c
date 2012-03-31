#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>


int main(void)
{
	int filedes1[2];//0读1写
	int filedes2[2];

	if(pipe(filedes1) < 0)
	{
		perror("pipe");
		exit(1);
	}
	if(pipe(filedes2) < 0)
	{
		perror("pipe");
		exit(1);
	}

	char rbuf[1024];
	char wbuf[1024];
	int n = 0;

	pid_t pid;
	pid = fork();

	if(pid == 0)
	{
		close(filedes1[0]);
		close(filedes2[1]);
		while(1)
		{
			n = read(filedes2[0], rbuf, 1023);
			if(n > 0)
			{
				int i = 0;
				for(i=0; i<n; i++)
				{
					wbuf[i] = toupper(rbuf[i]);
				}
				write(filedes1[1], wbuf, n);
			}
		}			
	}
	else if(pid > 0)
	{
		close(filedes1[1]);
		close(filedes2[0]);
		while(1)
		{
			n = read(STDIN_FILENO, wbuf, 1023);
			write(filedes2[1], wbuf, n);
			n = read(filedes1[0], rbuf, 1023);
			if(n > 0)
			{
				write(STDOUT_FILENO, rbuf, n);
				write(STDOUT_FILENO, "\n", 1);
			}	
		}			
	}
	else
	{
		perror("fork");
		exit(1);
	}
	return 0;
}

