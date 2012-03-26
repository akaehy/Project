#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <string.h>
#include "func.h"

fbscr_t fb_v;

int init_data(void)
{
	int fd = open("/dev/fb0", O_RDWR);
	if(fd < 0)
	{
		perror("fb0");
		exit(1);
	}
	
	struct fb_var_screeninfo fb_var;

	if(ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0)//将读取的屏幕信息放到fb_var结构体中
	{
		perror("ioctl");
		exit(1);
	}

	fb_v.w = fb_var.xres;
	fb_v.h = fb_var.yres;
	fb_v.bpp = fb_var.bits_per_pixel;

	printf("%d\t%d\t%d\n", fb_v.w, fb_v.h, fb_v.bpp);

	fb_v.memo = mmap(NULL, fb_v.w*fb_v.h*fb_v.bpp/8, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);//将屏幕映射到内存的一
					//地方，从屏幕的左上角为（0,0）到右下角,上面的printf为打印屏幕的信息测试用，屏幕
					//宽(1024)，高(768)，和分辨率(32位此电脑),fb_v.memo为开辟空间的首地址
	if(fb_v.memo == MAP_FAILED)
	{
		perror("map");
		exit(1);
	}

	close(fd);

	memset(fb_v.memo, 0, fb_v.w*fb_v.h*fb_v.bpp/8);//清屏


	return 0;
}
