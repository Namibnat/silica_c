#include <stdio.h>

int main(int argc, char **argv)
{
    printf("%d args\n", argc);

    for (int i=1; i<argc; i++){
        printf("%c", argv[i][0]);
    }
    printf("\n");
    for (int i=1; i<argc; i++){
        printf("-> %s\n", argv[i]);
    }


    return 0;
}

