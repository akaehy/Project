#include <stdio.h>

int main(int argc, const char *argv[])
{
	int n;
	int i,count=0;
	int temp;
	printf("input one number\n");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		temp=i;
	        while(temp%5==0)
		{
			count++;
		        temp=temp/5;
		}
	}
	printf("%d\n",count);
	return 0;
}
