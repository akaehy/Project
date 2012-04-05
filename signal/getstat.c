#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

int main(int argc, const char *argv[])
{
	struct termios info;
	int rv;

	rv = tcgetattr(0, &info);
	if(rv == -1){
		perror("tcgetarr");
		exit(EXIT_FAILURE);
	}

	if(info.c_lflag & ECHO)
		printf("echo is on, since its it is 1\n");
	else
		printf("echo is off, since its bit is 0\n");

	return 0;
}
