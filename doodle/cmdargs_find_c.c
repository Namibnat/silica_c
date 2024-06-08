/* This was my play around.  I threw it into chatGPT for feedback, and there is an updated version */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_args(int argc, char **argv, char *input_file_name, char *output_file_name, short *have_input_file, short *have_output_file)
{

    int I;
    int arglen = 0;

    for(I=1; I < argc; I++){
        // get the length of the arg
        arglen = strlen(argv[I]);

        // find the -o flag
        if (arglen == 2 && argv[I][0] == '-' && argv[I][1] == 'o'){
            // next arg is the output file
            if (I+1 == argc){
                perror("No output file has been provided after -o flag\n");
                exit(EXIT_FAILURE);
            }
            strncpy(output_file_name, argv[I+1]);
            have_output_file++;
        }
        if (arglen > 2 && argv[I][arglen - 1] == 'c' && argv[I][arglen - 2] == '.'){
            strncpy(input_file_name, argv[I]);
            have_input_file++;
        }
    }

}

int main(int argc, char **argv)
{
    short have_input_file = 0;
    short have_output_file = 0;

    char input_file_name[20];
    char output_file_name[20];

    parse_args(argc, argv, input_file_name, output_file_name, &have_input_file, &have_output_file);

    if (have_output_file == 0){
        strncpy(output_file_name, "a.out");
    }
    if (have_input_file == 0){
        perror("No input file has been supplied\n");
        exit(EXIT_FAILURE);
    }


    return 0;
}

