/* frame.h */
#ifndef _FRAME_H_
#define _FRAME_H_

////////////////////////////////////////////////////////////////////////////
typedef unsigned char  u8_t;
typedef unsigned short u16_t;
typedef unsigned int   u32_t;

typedef struct 
{
    int w;				     /* width */
	  int h;				     /* high */
	  int bpp;				   /* bits per pixel */
	  u8_t *fbmem;
}fb_info;

////////////////////////////////////////////////////////////////////////////
/* initial framebuffer */
extern int init_fb(fb_info *fb_inf);

/* drawing pixel */
extern int fb_pixel(fb_info fb_inf, int x, int y, u32_t color);

/* draw a color ball */
extern int fb_draw_ball(const fb_info fb_inf, int x, int y, int len, u32_t color);

#endif /* _FRAME_H_ */
