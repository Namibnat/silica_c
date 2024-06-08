#include <stdio.h>

int main(int argc, char **argv)
{
    /*
     * On this machine:
     * Size of char: 1 byte(s)
     * Size of short: 2 byte(s)
     * Size of int: 4 byte(s)
     * Size of long: 8 byte(s)
     * Size of long long: 8 byte(s)
     * Size of float: 4 byte(s)
     * Size of double: 8 byte(s)
     * Size of long double: 16 byte(s)
    */

    double d = 3.1416;
    char ch2 = *(char *)&d;
    int i2 = ch2;
    printf("%d\n", i2);

    // 1 byte per char
    char ch[] = {4, 5, 1, 3, 2};

    // This is how I understand the array ch to look in memory:
    // 00000100|00000101|00000001|00000011|00000010
    //
    // If I do a cast to an int, I expect the int to grab the first four bytes
    // 00000100 00000101 00000001 00000011
    // And turn that into some huge number
    //
    // But works...
    int i = *(int *)&ch;
    printf("%d\n", i);

    // Lets try an easy number, just to see that it really does what I expect
    char ch1[] = {0, 0, 0, 3, 0, 0, 0};

    // I think that casting this will give me a 1
    // (int *)ch -> gives me a pointer to an int
    // *(int *)ch -> dereference the int
    int i1 = *(int *)&ch1;
    printf("%d\n", i1);


    return 0;
}
