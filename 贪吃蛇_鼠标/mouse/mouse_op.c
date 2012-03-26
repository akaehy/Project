#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "func.h"

#define C_W 10//cursor_pixel[]的长为10
#define C_H	17//宽为17

#define	BORD	WHITE
#define	T___	BLACK
#define X___	0x000fffff

static u32_t cursor_pixel[C_W*C_H]=                           //一维数组，其值为颜色
{
	BORD,T___,T___,T___,T___,T___,T___,T___,T___,T___,
	BORD,BORD,T___,T___,T___,T___,T___,T___,T___,T___,
	BORD,X___,BORD,T___,T___,T___,T___,T___,T___,T___,
	BORD,X___,X___,BORD,T___,T___,T___,T___,T___,T___,
	BORD,X___,X___,X___,BORD,T___,T___,T___,T___,T___,	
	BORD,X___,X___,X___,X___,BORD,T___,T___,T___,T___,
	BORD,X___,X___,X___,X___,X___,BORD,T___,T___,T___,
	BORD,X___,X___,X___,X___,X___,X___,BORD,T___,T___,
	BORD,X___,X___,X___,X___,X___,X___,X___,BORD,T___,
	BORD,X___,X___,X___,X___,X___,X___,X___,X___,BORD,
	BORD,X___,X___,X___,X___,X___,BORD,BORD,BORD,BORD,
	BORD,X___,X___,BORD,X___,X___,BORD,T___,T___,T___,
	BORD,X___,BORD,T___,BORD,X___,X___,BORD,T___,T___,
	BORD,BORD,T___,T___,BORD,X___,X___,BORD,T___,T___,
	T___,T___,T___,T___,T___,BORD,X___,X___,BORD,T___,
	T___,T___,T___,T___,T___,BORD,X___,X___,BORD,T___,
	T___,T___,T___,T___,T___,T___,BORD,BORD,T___,T___


};

u32_t bg[C_W*C_H] = {0};

fbscr_t fb_v;

int draw_cursor(int x, int y)//打印鼠标图形
{
	save_bg(x, y);//打印之前应该先保存,它俩个应该成对出现
	int i = 0;
	int j = 0;

	for(j=0; j<C_H; j++)
	{
		for(i=0; i<C_W; i++)
		{
			fb_one_pixel(x+i,y+j,cursor_pixel[i+j*C_W]);
		}
	}
	return 0;
}

int save_bg(int x, int y)//保存鼠标覆盖的背景,恢复使用
{
	int i = 0;
	int j = 0;

	for(j=0; j<C_H; j++)
	{
		for(i=0; i<C_W; i++)
		{
			bg[i+j*C_W] = *((u32_t *)fb_v.memo+(x+i)+(y+j)*fb_v.w);
		}
	}

	return 0;	
}

int restore_bg(int x, int y)//此时屏幕的信息在bg这个数组里面，用其数据恢复背景
{
	int i = 0;
	int j = 0;

	for(j=0; j<C_H; j++)
	{
		for(i=0; i<C_W; i++)
		{
			fb_one_pixel(x+i,y+j,bg[i+j*C_W]);
		}
	}
	return 0;
}
int get_mouse_info(int fd, mouse_event *p)//得到鼠标的移动信息
{
	char buf[5];
	int n = read(fd, buf, 4);
	if(n > 0)
	{
		p->dx = buf[1];//p->dx为x方向的偏移坐标
		p->dy = -buf[2];
		p->dz = buf[3];
		p->button = (buf[0]&0x07);//buf[0]为int型，用其低三位表示鼠标的中，右，左
	}
	return n;
}

int mouse_do(void)
{
	int mx = fb_v.w/2;
	int my = fb_v.h/2;

	mouse_event m_e;

	int fd = open("/dev/input/mice", O_RDWR|O_NONBLOCK);
	if(fd < 0)
	{
		perror("mice");
		exit(1);
	}
	draw_cursor(mx, my);

	while(1)
	{

		if(get_mouse_info(fd, &m_e) > 0)
		{
			restore_bg(mx, my);
			mx += m_e.dx;
			my += m_e.dy;
			draw_cursor(mx, my);
			
			switch(m_e.button)
			{
				case 0 : break;
				case 1 : printf("left\n");break;
				case 2 : printf("right\n");break;
				case 4 : printf("mid\n");break;
				default : break;						 
			}

		}			
		usleep(500);
	}
	return 0;
}





