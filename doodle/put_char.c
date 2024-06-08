/* put what I read */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *file;
    char c;
    char spacethingi = '|';

    file = fopen("words.txt", "r");

    if (file == NULL){
        perror("File could not be read\n");
        exit(EXIT_FAILURE);
    }

    while ((c = fgetc(file)) != EOF){
        putchar(c);
        putchar(spacethingi);
    }
    fclose(file);
    printf("\n");

    return 0;
}

