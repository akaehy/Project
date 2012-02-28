//分别用指针强制类型转换、共用体知识,判断计算机
//是大端还是小端系统。
//
#include <stdio.h>

typedef union{
	char c;
	unsigned short sn;
}un_t;

int main(void)
{
	un_t u;
	char *snp = (char *)&u.sn;

	unsigned short sn = 0x1234;
	unsigned short *p = &sn;

	u.sn = sn;
	printf("&u:%p, &u.c:%p, &u.sn:%p\n", &u, &u.c, &u.sn);
	printf("&sn:%p, snp:%p\n", &sn, snp);
	
	printf("snp + 1:%p, *(snp + 1):0x%x\n", snp + 1, *(snp + 1));

	u.sn = 0x1234;
	if(u.c == 0x34)
		printf("little endian!\n");
	else
		printf("big endian!\n");

	if(*((char *)p) == 0x34)
		printf("little endian!\n");
	else
		printf("big endian!\n");
	return 0;
}
