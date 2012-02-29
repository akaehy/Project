//实现一个功能较完整的printf,能够处理%c、%s、
//%d(对应参数是int型, 以八进制打印)、%o (对
//应参数是unsigned int型, 以八进制打印)、 %x(对
//应参数是unsigned int型, 以十六进制打印)、%f
//(对应参数是double型, 打印到小数点后6位)、
//%%(打印一个%)等转换说明,在实现中不能调用
//printf一族的函数
//
//
//
#include <stdio.h>
#include <stdarg.h>

#define LEN 30

void myitoa(int n, char *str, int radix)
{
	int i = 0, j,  remain;
	char tmp;
	
	do{
		remain = n % radix;
		if(remain > 10){
			str[i++] = remain - 10 + 'A';
		}else{
			str[i++] = remain + '0';
		}
	}while(n /= radix);
	str[i] = '\0';
	
	for(i--, j = 0; j <= i; i--, j++){
		tmp = str[j];
		str[j] = str[i];
		str[i] = tmp;
	}
}

void myprintf(const char *format, ...)
{
	va_list ap;
	int n;
	char c, ch, str[LEN];
	double f_num;

	va_start(ap, format);
	while((c = *format)){
		switch(c){
		case '%':{
			ch = *(++format);
			switch(ch){
			case 'd':{
				n = va_arg(ap, int);
				myitoa(n, str, 10);
				fputs(str, stdout);
				break;
				}
			case 'o':{
				n = va_arg(ap, int);
				myitoa(n, str, 8);
				fputs(str, stdout);
				break;
				}
			case 'x':{
				n = va_arg(ap, int);
				myitoa(n, str, 16);
				fputs(str, stdout);
				break;
				}
			case 'c':{
				putchar(va_arg(ap, int));
				break;
				}
			case 's':{
				fputs(va_arg(ap, char *), stdout);
				break;
				}
			case 'f':{
				f_num = va_arg(ap, double);
				n = f_num;
				myitoa(n, str, 10);
				fputs(str, stdout);
				putchar('.');
				n = (f_num - n) * 1000000;
				myitoa(n, str, 10);
				fputs(str, stdout);
				break;
				}
			case '%':{
				putchar('%');
				break;
				}
			}
			break;
			}
		default:putchar(c);
			break;
		}
		format++;
	}
	
	va_end(ap);
	
}

int main(void)
{
	myprintf("%d, %o, %x, %c, %s, %%, %f\n", 1248, 8, 15, 'A', "abcd", 3.14159);
	return 0;
}
