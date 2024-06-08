#include <stdio.h>

int main(int argc, char **argv)
{

    // cast a char to short where number is positive
    char ch = 'A';
    short s = ch;

    printf("%d\n", s);

    // cast a char to short where number is negative (this works)
    ch = -65;
    s = ch;

    printf("%d\n", s);

    // cast 2049 (which is 2**11 + 1), which punts all the bits it doesn't have room for.
    // so, becomes a 1 since 2**11 is out of bounds for a char
    s = 2049;
    char ch1 = s;
    printf("%d\n", ch1);


    return 0;
}

