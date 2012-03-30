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

#endif /* _FRAME_H_ */
