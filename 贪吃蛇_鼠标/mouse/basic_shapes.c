#include <stdio.h>
#include "func.h"

extern fbscr_t fb_v;

int fb_one_pixel(int x, int y, u32_t color)//在坐标处打印一个点
{
	*((u32_t *)fb_v.memo + x + y*fb_v.w) = color;

	return 0;
}



