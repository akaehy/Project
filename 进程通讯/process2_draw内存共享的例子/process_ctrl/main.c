/* main.c */
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "frame.h"

#include "fb.c"

/* main */
int main(int argc, char *argv[]) 
{
    fb_info fb_inf1;

    if (init_fb(&fb_inf1) < 0)
    {
    	  fprintf(stderr, "Error initial framebuffer\b")	;
    	  return -1;
    }
    
    //fb_inf.fbmem  - map start address
    while(1)
    {
        *((u32_t *)fb_inf1.fbmem) = 0x000000ff;
        sleep(3);
        *((u32_t *)fb_inf1.fbmem) = 0x0000ff00;
        sleep(3);
        *((u32_t *)fb_inf1.fbmem) = 0x00ff0000;
        sleep(3);
    }
    munmap(fb_inf1.fbmem, fb_inf1.w * fb_inf1.h * fb_inf1.bpp / 8);
    
    return 0;
}
