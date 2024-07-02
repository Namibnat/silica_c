#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int thingi;
    char *word_to_yo_moma;
} Xs;


int main(int argc, char **argv) {
    int i = 0;

    Xs *xses;

    xses = realloc(xses, 2*sizeof(Xs));
    if (xses == NULL) {
        perror("bad");
        exit(1);
    }

    xses[0].thingi = 291;
    xses[0].word_to_yo_moma = malloc(sizeof(char)*10);

    xses[0].word_to_yo_moma[0] = 'Y';
    xses[1].thingi - 100;


    printf("Done\n");

    free(xses[0].word_to_yo_moma);
    free(xses);

    return 0;
}
