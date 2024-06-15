/* Just print source-code char by char */

#include <stdio.h>

int main(int argc, char **argv)
{
    char source[] = "int main(){return 0;}";

    int i = 0;
    char c;

    do  {
        c = source[i];
        printf("(\"");
        putchar(c);
        printf("\",%d)\n", c);
        i++;
    } while (c != '\0');

    return 0;
}


