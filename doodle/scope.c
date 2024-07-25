/*
 * Scope in C is a challenge
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int a = 23;
    int b = 24;

    if (b == 24){
        int a = 27;
        printf("In if: %d\n", a);
    }
    printf("back out: %d\n", a);

    return 0;
}

