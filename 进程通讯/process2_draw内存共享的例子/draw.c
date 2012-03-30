/* draw.c */
#include <unistd.h>
#include <math.h>
#include <stdio.h>

#include "frame.h"

/* 
* draw a color ball 
*/
int fb_draw_ball(const fb_info fb_inf, int x, int y, int len, u32_t color)
{
    int iloop;
    int jloop;
    
    for (iloop = x - len; iloop <= x + len; iloop++)
    {
    	  for (jloop = y - len; jloop <= y + len; jloop++)
    	  {
    	  	  if ((iloop - x) * (iloop - x) + (jloop - y) * (jloop - y) <= len * len)
    	  	  {
    	  		    fb_pixel(fb_inf, iloop, jloop, color);
    	  		}
    	  }
    }
    return 0;
}
