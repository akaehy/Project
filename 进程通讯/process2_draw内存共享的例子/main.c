/* main.c */
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "frame.h"

#include "fb.c"
#include "draw.c"

/* main */
int main(int argc, char *argv[]) 
{
    fb_info fb_inf;
    
    if (init_fb(&fb_inf) < 0)
    {
    	  fprintf(stderr, "Error initial framebuffer\b")	;
    	  return -1;
    }
    
    //fb_inf.fbmem  - map start address
    while(1) 
    {
        fb_draw_ball( fb_inf, 300, 300, 50, *(int *)fb_inf.fbmem);
    }

    munmap(fb_inf.fbmem, fb_inf.w * fb_inf.h * fb_inf.bpp / 8);
    
    return 0;
}
