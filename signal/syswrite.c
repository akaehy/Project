#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>

#define LEN 	1024
int main(int argc, char *argv[])
{
	int fd;
	char buf[LEN];

	if(argc != 2){
		fprintf(stderr, "usage: write1 ttyname\n");
		exit(1);
	}

	fd = open(argv[1], O_WRONLY);
	assert(fd);
	
	while(fgets(buf, LEN, stdin) != NULL){
		if(write(fd, buf, strlen(buf)) == -1)
			break;
	}

	close(fd);
	return 0;
}
