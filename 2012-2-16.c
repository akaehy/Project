
//将某些位置一    某些位置清零
#include <stdio.h>

/*

0x12345678 4 7
00010010001101000101011001111000
11111111111111111111111100001111

00000000000000000000000011110000

0:
00000000000000000000000000000000
~0:
11111111111111111111111111111111
~0 << (end - start + 1):~0 << 4
11111111111111111111111111110000
~(~0 << (end - start + 1)):
00000000000000000000000000001111
~(~0 << (end - start + 1)) << start:
00000000000000000000000011110000
*/

unsigned cleanbits(unsigned n, int start, int end)
{
	return n & ~(~(~0 << (end - start + 1)) << start);
}

unsigned setbits(unsigned n, int start, int end)
{
	return n | ~(~0 << (end - start + 1)) << start;
}

int main(void)
{
	unsigned int n;
	int start, end;

	scanf("%x %d %d", &n, &start, &end);

	printf("cleanbits:0x%x\n", cleanbits(n, start, end));
	printf("setbits:0x%x\n", setbits(n, start, end));
	
	return 0;
}



//使用位操作的知识向数组中保存26个没有重复
//的英文字母
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	char letter[26];
	int tmp, i, j, flag = 0;

	srand(time(NULL));
	for(i = 0; i < 26;){
		tmp = rand() % 26;
		if(((flag >> tmp) & 0x01) == 0){
			letter[i++] = tmp + 'a';
			flag |= (0x01 << tmp);
			//for(j = 25; j >= 0; j--)
			//printf("%d", (flag >> j) & 0x01);
			//printf("\n");
		}
	}

	for(i = 0; i < 26; i++)
		printf("%c ", letter[i]);
	printf("\n");
	return 0;
}



//实现unsigned int型数据的二进制打印
//
#include <stdio.h>

int main(void)
{
	unsigned n;
	int i = 31;

	scanf("%x", &n);

	while(!((n >> i) & 0x01))
		i--;


	//0x12345678
	for(; i >= 0; i--)
		printf("%u", (n >> i) & 0x01);
	printf("\n");
	return 0;
}



//使用位操作实现整数乘法
//
#include <stdio.h>

int main(void)
{
	int m, n, i, result = 0;;

	scanf("%d %d", &m, &n);

	for(i = 0; i < 32; i++)
		if((n >> i) & 0x01)
			result += (m << i);
	
	printf("%d * %d = %d\n", m, n, result);
	return 0;
}


//使用位操作实现整数乘法
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned shift_left(unsigned n, int bits)
{
	return (n << bits) | (n >> (32 - bits));
}

unsigned shift_right(unsigned n, int bits)
{
	return (n >> bits) | (n << (32 - bits));
}

int main(int argc, char *argv[])
{
	char *savep;

	printf("left:0x%x\n", shift_left(strtol(argv[1], &savep, 16), atoi(argv[2])));
	printf("right:0x%x\n", shift_right(strtol(argv[1], &savep, 16), atoi(argv[2])));
	return 0;
}


//求unsigned int型数据中有多少个1
//
#include <stdio.h>

int main(void)
{
	unsigned n;
	int i, count = 0;

	scanf("%x", &n);
	
	for(i = 0; i < 32; i++)
		if((n >> i) & 0x01)
			count++;

	printf("count = %d\n", count);
	return 0;
}


//通过位操作实现字母的大小写转化
//
#include <stdio.h>

char toup(char c)
{
	if(c >= 'A' && c <= 'Z')
		return c;
	return c & ~0x20;
}

char tolow(char c)
{
	if(c >= 'a' && c <= 'z')
		return c;
	return c | 0x20;
}

int main(void)
{
	int c;

	while((c = getchar()) != EOF){
		if(c == '\n')
			continue;
		printf("%c\n", c ^ 0x20);
		printf("toup:%c\n", toup(c));
		printf("tolow:%c\n", tolow(c));
	}
	return 0;
}


//通过位操作实现字母的大小写转化
//
#include <stdio.h>

char toup(char c)
{
	if(c >= 'A' && c <= 'Z')
		return c;
	return c & ~0x20;
}

char tolow(char c)
{
	if(c >= 'a' && c <= 'z')
		return c;
	return c | 0x20;
}

int main(void)
{
	int c;

	while((c = getchar()) != EOF){
		if(c == '\n')
			continue;
		printf("%c\n", c ^ 0x20);
		printf("toup:%c\n", toup(c));
		printf("tolow:%c\n", tolow(c));
	}
	return 0;
}
