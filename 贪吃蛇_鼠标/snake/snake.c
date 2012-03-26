#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>

#include "func.h"

#define L_WALL 50
#define R_WALL 24
#define U_WALL 50
#define D_WALL 18

extern fbscr_t fb_v;
int iscover(int fx, int fy, int *sx, int *sy, int len)
{
	int i = 0;
	for(i=0; i<len; i++)
	{
		if((fx == sx[i]) && (fy == sy[i]))
		{
			return 1;
		}
	}
	return 0;
}
int move_one_step(int *x, int *y, int x_o, int y_o, int s_len, int eaten)
{
	if(((x[0]+x_o) < L_WALL)||((x[0]+x_o+50)>(fb_v.w-R_WALL)))
	{
		return -1;
	}
	if(((y[0]+y_o) < U_WALL)||((y[0]+y_o+50)>(fb_v.h-D_WALL)))
	{
		return -1;
	}
	if(eaten == 0)
	{
		square(x[s_len-1], y[s_len-1], 50, BLACK);
	}		
	int i = 0;
	for(i=s_len-1; i>0; i--)
	{
		x[i] = x[i-1];
		y[i] = y[i-1];
	}
	x[0] = x[1]+x_o;
	y[0] = y[1]+y_o;
	if(iscover(x[0], y[0], x+1, y+1, s_len-1) == 1)
	{
		return -1;
	}
	square(x[1], y[1], 50, RED);
	square(x[0], y[0], 50, GREEN);
	
	usleep(1000*200);

	return 0;
}

int keyhit(void)
{
	int i = 0;
	ioctl(STDIN_FILENO, FIONREAD, &i);

	return i;
}
char get_key(void)
{
	if(keyhit() > 0)
	{
		return getchar();
	}
	return 0;
}
void barriar(void)
{
	int i = 0;
	int j = 0;

	for(j = 0; j<U_WALL; j++)
	{
		for(i=0; i<fb_v.w; i++)
		{
			fb_one_pixel(i, j,  BLUE|GREEN);
		}
	}
	for(j = 0; j<D_WALL; j++)
	{
		for(i=0; i<fb_v.w; i++)
		{
			fb_one_pixel(i, fb_v.h-1-j,  BLUE|GREEN);
		}
	}

	for(i = 0; i<L_WALL; i++)
	{
		for(j=0; j<fb_v.h; j++)
		{
			fb_one_pixel(i, j, BLUE|GREEN);
		}
	}
	for(i = 0; i<R_WALL; i++)
	{
		for(j=0; j<fb_v.h; j++)
		{
			fb_one_pixel(fb_v.w-1-i,j, BLUE|GREEN);
		}
	}

}

void print_snake(int *sx, int *sy, int len)
{
	int i;

	square(sx[0], sy[0], 50, GREEN);
	for(i=1; i<len; i++)
	{
		square(sx[i],sy[i],50,RED);
	}
}
void erase_snake(int *sx, int *sy, int len)
{
	int i;

	for(i=0; i<len; i++)
	{
		square(sx[i],sy[i],50,BLACK);
	}
}
void restart_game(int *sx, int *sy, int len)
{
	int i = 5;
	while(i--)
	{
		print_snake(sx, sy, len);
		usleep(1000*500);
		erase_snake(sx,sy, len);
		usleep(1000*500);
	}
	memset(fb_v.memo, 0, fb_v.w*fb_v.h*fb_v.bpp/8);
	barriar();
	for(i=0; i<len; i++)
	{
		sx[i] = 250-i*50;
		sy[i] = 300;
	}
}


int show_food(int *fx, int *fy, int *sx, int *sy, int len,int *counter)
{
	(*counter)++;
	if((*counter) > 30)
	{
		*counter = 0;
		if(*fx != 0)
		{
			square(*fx, *fy, 50, BLACK);
		}		
		while(1)
		{
			*fx = (rand()%19+1)*50;
			*fy = (rand()%14+1)*50;
			if(iscover(*fx, *fy, sx, sy, len) == 0)
			{
				break;
			}
		}			
		square(*fx, *fy, 50, BLUE);
	}

	return 0;
}
int eat_food(int *fx, int *fy, int *sx, int *sy, int *len,int *counter)
{
	if(((*fx) == (*sx)) && ((*fy) == (*sy)))
	{
		*fx = 0;
		*counter = 100;
		(*len)++;
		return 1;
	}
	return 0;
}

int snake_move(void)
{
	int sx[100] = {250, 200, 150, 100, 50};
	int sy[100] = {300, 300, 300, 300, 300};
	int fx = 0;
	int fy = 0;
	int f_count = 100;
	int step = 50;
	int x_offset = step;
	int y_offset = 0;
	int s_len = 5;

	char dict = 'd';
	char new_dict = 0;
	char flag = 0;
	char eat_state = 0;
	barriar();
	system("stty raw -echo");
	while(flag == 0)
	{
		show_food(&fx, &fy, sx, sy, s_len, &f_count);

		if(move_one_step(sx, sy, x_offset,y_offset, s_len, eat_state) == -1)
		{
			restart_game(sx, sy, s_len);
			dict = 'd';
			new_dict = 0;
			x_offset = step;
			y_offset = 0;
			s_len = 5;
		}
		eat_state = eat_food(&fx, &fy, sx, sy, &s_len,&f_count);
		
		new_dict = get_key();
		switch(new_dict)
		{
			case 'a' : if(dict != 'd') dict = new_dict;break;
			case 'd' : if(dict != 'a') dict = new_dict;break;
			case 'w' : if(dict != 's') dict = new_dict;break;
			case 's' : if(dict != 'w') dict = new_dict;break;
			case 'q' : dict = new_dict;						   
			default  :  break;					   
		}

		switch(dict)
		{
			case 'a' : x_offset=-step; y_offset=0;break;
			case 'd' : x_offset=step; y_offset=0;break;
			case 'w' : x_offset=0; y_offset=-step;break;
			case 's' : x_offset=0; y_offset=step;break;
			case 'q' : flag = 1;break;				   
			default : break;				   
		}
		usleep(1000);
	}	
	system("stty cooked echo");

	return 0;
}
