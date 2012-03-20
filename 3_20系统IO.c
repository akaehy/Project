/******************************************************************
*fcntl的用法，例先获取STDIN_FILENO的状态，在将其设置成
*非阻塞的，试验
******************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	char buf[1024];	
	int n = 0;
	int flags = 0;


	flags = fcntl(STDIN_FILENO, F_GETFL);
	flags |= O_NONBLOCK;
	if(fcntl(STDIN_FILENO, F_SETFL, flags) < 0)
	{
		perror("fcntl");
		exit(1);
	}

	n = read(STDIN_FILENO, buf, 1023);
	if(n > 0)
	{
		write(STDOUT_FILENO, buf, n);
	}
	else
	{
		write(STDOUT_FILENO, "no word\n", 8);
	}
	
	
	return 0;
}


/**************************************************************************
 * ioctl用于向设备发控制和配置命令
 * ioctl命令传送的是控制信息
 * 以下程序使用TIOCGWINSZ命令获得终端的窗口大小
 * ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(void)
{
	struct winsize size;
	if(isatty(STDOUT_FILENO) == 0)//判断是否为终端描述符,因为STDOUT_FILENO本质为一个数
		                      //不是一一对应，因为打开的时候0，1，2被占用,之后可能改变
	{
		exit(1);
	}
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0)
	{
		perror("ioctl");
		exit(1);
	}
	printf("%d rows, %d columns\n", size.ws_row, size.ws_col);

	return 0;
}


/****************************************************************************
 * mmap的举例
 *void *mmap(void *addr, size_t len, int prot, int flag, int filedes, off_t off);
 *首先建立一个空文件txt4，打开，找到1000字节的位置写个\n,为mmap的第二个参数做
 *准备，如果此文件的大小，小于mmap的第二个参数，则出现总线错误
 *映射之后就可以将文件关闭
 * **************************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

int main(void)
{
	void *ptr = NULL;
	int fd = open("txt4", O_RDWR);
	if(fd < 0)
	{
		perror("open txt4");
		exit(1);
	}

	lseek(fd, 1000, SEEK_SET);
	write(fd, "\n", 1);
	
	ptr = mmap(NULL, 1000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(ptr == MAP_FAILED)
	{
		perror("mmap");
		exit(1);
	}
	close(fd);

	int *p = ptr;

	*p = 0x31323334;//小端，低地址存放低字节高地址存放高字节,文件中为4321

	return 0;
}


/***************************************************************
 * 简易秒表
 * ************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	int i = 0;
	char buf[10];

	while(1)
	{
		sleep(1);
		sprintf(buf, "%d", i++);
		write(STDOUT_FILENO, buf, strlen(buf));
		write(STDOUT_FILENO, "\r", 1);
	}
	return 0;
}


/**************************************************************
 * 将text1文件的内容拷贝到text3中没有则创建它
 *O_CREAT需要提供第三个参数mode
 *程序中写的为0666，运行后用ls -l text3查看text3的权限为0644
 *用umask查看掩码为0022，
 *0644 = 0666&（~0022）
 * ***********************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int fd1, fd2;
	char buff[128];
	fd1 = open("text1", O_RDONLY);
	if(fd1 < 0)
	{
		perror("open text1");
		exit(1);
	}


	fd2 = open("text3", O_WRONLY|O_CREAT|O_EXCL, 0666);
	if(fd2 < 0)
	{
		perror("open text3");
		exit(1);
	}
	int n = read(fd1, buff, 128); 
	
	while(n > 0)
	{
		write(fd2, buff, n);
		n = read(fd1, buff, 128);
	}
	
	close(fd1);	
	close(fd2);
	return 0;
}



/*************************************************
 * 在txt中写入几行字符
 * 不够1024个
 * n小于1024，全部读取，n为读取字符的个数
 * **********************************************/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	char arr[1024];
	int fd = open("txt", O_RDONLY);
	if(fd < 0)
	{
		perror("txt");
		exit(1);
	}
	int n = read(fd, arr, 1024);
	write(STDOUT_FILENO, arr, n);
	
	close(fd);
	return 0;
}


/*****************************************************************
 * 小练习：将一个文件中的内容拷贝到另外一个文件，不用read，write
 * **************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <string.h>

int main(void)
{
	void *p1 = NULL;
	int fd = open("txt4",O_RDWR);
	if(fd < 0)
	{
		perror("txt4");
		exit(1);
	}

	int n1 = lseek(fd, 0, SEEK_END);
	printf("%d\n", n1);
	p1 = mmap(NULL, n1, PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
	if(p1 == MAP_FAILED)
	{
		perror("map");
		exit(1);
	}
	
	close(fd);

	int fd1 = open("txt5",O_RDWR|O_TRUNC);
	if(fd1 < 0)
	{
		perror("txt5");
		exit(1);
	}

	lseek(fd1, n1, SEEK_SET);
	write(fd1, "\n", 1);	
	char *p2 = NULL;
	p2 = mmap(NULL, n1, PROT_READ|PROT_WRITE,MAP_SHARED, fd1, 0);
	if(p2 == MAP_FAILED)
	{
		perror("map1");
		exit(1);
	}

	strncpy(p2, p1, n1);
	close(fd1);

	return 0;
}
