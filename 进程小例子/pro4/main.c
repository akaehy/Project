#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		puts("parameters!");
		return 0;
	}
	int fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	execl("../pro3/main", "main", NULL);
	return 0;
}
