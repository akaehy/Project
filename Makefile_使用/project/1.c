#include <stdio.h>

int main(int argc, char *argv[])
{
    int len = 0;

    for(len = 0; argv[1][len]; len++)
        ;
    printf("len = %d\n", len);
    return 0;
}
