/* Write some binary stuff to a file */

#include <stdio.h>
#include <stdlib.h>

#define ONE_SECTION 1

int main(int argc, char **argv)
{
    FILE* bin_file = fopen("binary.bin", "wb");

    if (bin_file == NULL){
        printf("Could not open file\n");
        exit(-1);
    }

    int num = 32;
    fwrite(&num, sizeof(num), ONE_SECTION, bin_file);

    num = 16;
    fwrite(&num, sizeof(num), ONE_SECTION, bin_file);

    num = 1;
    fwrite(&num, sizeof(num), ONE_SECTION, bin_file);

    num = 15;
    fwrite(&num, sizeof(num), ONE_SECTION, bin_file);


    fclose(bin_file);

    return 0;
}

