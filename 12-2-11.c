
//随机输入10个数奇数在钱偶数在后
#include <stdio.h>

int main(int argc, const char *argv[])
{
	int i,j;
	int temp;
	int a[10];
	srand(time(NULL));
	for(i=0;i<10;i++)
		a[i]=rand()%101;
	for(i=0;i<10;i++)
		printf("%d ",a[i]);
	printf("\n");
	for(i=0,j=9;i<j;i++)
	{
		if(a[i]%2==0)
		{
			while(a[j]%2==0)
			j--;
			temp=a[i];
			a[i]=a[j];
			a[j]=temp;
		}
	}
	for(i=0;i<10;i++)
		printf("%d ",a[i]);
	printf("\n");

	return 0;
}


//去掉输入字符串中的空格
#include <stdio.h>

int main(int argc, const char *argv[])
{
	int i,j;
        char a[10];
	gets(a);
	for(i=0,j=0;i<10;i++)
		if(a[i]!=' ')
                   a[j++]=a[i];
	a[j]='\0';
	puts(a);
	return 0;
}


//将方阵倒置
#include <stdio.h>

int main(int argc, const char *argv[])
{
	int i,j,t;
	int arr[3][3]={{1,2,3},{4,5,6},{7,8,9}};
	for(i=0;i<3;i++)
	{
		for(j=0;j<i;j++)//j<i或者j>i时交换
		{
			t=arr[j][i];
		        arr[j][i]=arr[i][j];
		        arr[i][j]=t;
		} 
	}
	
        for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
			printf("%d",arr[i][j]);
			printf("\n");
	}
	return 0;
}




//统计输入数据中每个数的个数
#include <stdio.h>

int main(int argc, const char *argv[])
{
	int i;
	int n;
	int arr[10]={0};
	scanf("%d",&n);
	while(n)
	{
		arr[n%10]++;
		n=n/10;
	}
	for(i=1;i<10;i++)
	{
		if(arr[i]>1)
			printf("%d  appear %d times\n",i,arr[i]);
	}
	return 0;
}




//输入一个整数，判断这个数中有没有重复的数字，如：2822，有重复数字2
#include <stdio.h>

int main(int argc, const char *argv[])
{
        int i,j;
	int flag=0;
	int s;
	int a[4];
	printf("please input one number\n");
	scanf("%d",&s);
	for(i=0;i<4;i++)
	{
             a[i]=s%10;//取余
             s=s/10;//取整
	}
	for(i=0;i<3;i++)
	{
	      for(j=i+1;j<4;j++)
	      {
		      if(  a[i]==a[j] )
		      {
			      printf("有重复的数字%d\n",a[i]);
			      flag=1;
	                      break;
		      }
	      }
	    	
	}
	if(flag==0)
		printf("没有重复的数字\n");
        return 0;
}



