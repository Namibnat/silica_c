/* parse cmdline args */

#include "cmdargs.h"

void parse_arguments(
        int argc,
        char **argv,
        char *input_file_name,
        char *output_file_name,
        short *have_input_file,
        short *have_output_file)
{
    int i;
    int arglen;

    for (i = 1; i < argc; i++){
        // Get the length of the current arg
        arglen = strlen(argv[i]);

        // Check for the '-o' flag for output file
        if (arglen == 2 && argv[i][0] == '-' && argv[i][1] == 'o'){
            // Ensure there is a next argument for the output file name
            if (i + 1 == argc){
                fprintf(stderr, "No output file hane has been provided after the -o flag\n");
                continue;
            }
            // Copy the next argument as the ouput file name
            strncpy(output_file_name, argv[i + 1], 19);
            printf("%s\n", argv[i+1]);
            output_file_name[19] = '\0';
            (*have_output_file)++;
            i++; // Skip the next arg as it's the input file name
        }

        // Check if the arg is an input file with the .c exstension
        if (arglen > 2 && argv[i][arglen - 1] == 'c' && argv[i][arglen - 2] == '.'){
            // Copy the argument as the input file name
            strncpy(input_file_name, argv[i], 19);
            input_file_name[19] = '\0';
            (*have_input_file)++;
        }

        // For now, just bail if we have what we need
        if (*have_input_file > 0 && *have_output_file > 0){
            break;
        }
    }

    // If no output file specified, use the default name "a.out"
    if (*have_output_file == 0) {
        strcpy(output_file_name, "a.out");
    }

    // If no input file provided, print an error message and exit
    if (*have_input_file == 0) {
        fprintf(stderr, "No input file has been supplied\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {
    short have_input_file = 0;
    short have_output_file = 0;
    char input_file_name[20] = {0};
    char output_file_name[20] = {0};

    // Call the func to parse the cmd line args
    parse_arguments(argc, argv, input_file_name, output_file_name, &have_input_file, &have_output_file);

    printf("Input file: %s\n", input_file_name);
    printf("Ouput file: %s\n", output_file_name);

    return 0;
}

