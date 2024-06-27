#ifndef CHMARGS_FIND_C_H
#define CHMARGS_FIND_C_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void parse_arguments(
        int argc,
        char **argv,
        char *input_file_name,
        char *output_file_name,
        short *have_input_file,
        short *have_output_file);

#endif

