#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;

    for(i = 0; argv[1][i] == argv[2][i]; i++)
        if(argv[1][i] == '\0'){
            printf("equal!\n");
            break;
        }
    if(argv[1][i])
        printf("%s\n", (argv[1][i] > argv[2][i] ? "bigger!":"smaller!"));
    return 0;
}

