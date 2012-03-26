#ifndef _FUNC_H_
#define	_FUNC_H_

#define	RED		0x00ff0000
#define	GREEN	0x0000ff00
#define BLUE	0x000000ff
#define WHITE	0x00ffffff
#define BLACK	0x0

typedef unsigned char u8_t;
typedef unsigned int u32_t;

typedef struct
{
	int w;
	int h;
	int bpp;

	void *memo;
} fbscr_t;

typedef struct
{
	int dx;
	int dy;
	int dz;

	char button;
} mouse_event;

int init_data(void);
int draw_cursor(int x, int y);
int restore_bg(int x, int y);
int save_bg(int x, int y);
int mouse_do(void);
int fb_one_pixel(int x, int y, u32_t color);
int init_data(void);

#endif
