/* Just practice to get the mem thing working for tokens */

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    LEFTBRACKET,
    RIGHTBRACKET,
} TokenType;

typedef struc {
    tokentype TokenType;
    const char *text;
}

int main(int argc, char **argv)
{
    int i;
    const char code_chunck[] = "int main(){}";

    for (i=0,
