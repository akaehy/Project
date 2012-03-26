#include <stdio.h>
#include "func.h"

extern fbscr_t fb_v;

int fb_one_pixel(int x, int y, u32_t color)
{
	*((u32_t *)fb_v.memo + x + y*fb_v.w) = color;

	return 0;
}

int square(int x, int y, int len, u32_t color)
{
	int i = 0;
	int j = 0;

	for(j=0; j<len; j++)
	{
		for(i=0; i<len; i++)
		{
			fb_one_pixel(x+i, y+j, color);
		}
	}
	return 0;	
}





