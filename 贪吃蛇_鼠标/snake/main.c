#include <stdio.h>
#include <unistd.h>
#include "func.h"

extern fbscr_t fb_v;

int main(void)
{
	init_data();
	snake_move();
		//init_data();
		//mouse_do();
	return 0;
}
