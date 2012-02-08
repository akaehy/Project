#include <stdio.h>

int main(int argc, const char *argv[])
{

	int h=23,m=59,s=50;
	while(1)
	{
		printf("%02d:%02d:%02d",h,m,s);
		fflush(stdout);
		sleep(1);
		putchar('\r');
		s++;
		if(s==60)
		{
			s=0;
			m++;
			if(m==60)
			{
				m=0;
				h++;
				if(h==24)
				{
					h=0;
				}
			}
		}

		
           }

	return 0;
}
