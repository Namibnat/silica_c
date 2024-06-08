/* This is a version that ChatGPT produced for me as feedback */

#include <stdio.h>   // For standard input/output functions
#include <stdlib.h>  // For standard library functions like exit()
#include <string.h>  // For string handling functions like strlen() and strcpy()

int main(int argc, char **argv)
{
    int i; // Corrected: Changed from 'I' to 'i' for convention
    short have_input_file = 0;  // Flag to check if input file is provided
    short have_output_file = 0; // Flag to check if output file is provided

    int arglen = 0;  // Variable to store the length of the current argument
    char input_file_name[20];  // Array to store the input file name (limited to 19 characters + null terminator)
    char output_file_name[20]; // Array to store the output file name (limited to 19 characters + null terminator)

    // Loop through all command-line arguments
    for(i = 1; i < argc; i++) {
        // Get the length of the current argument
        arglen = strlen(argv[i]);

        // Check for the '-o' flag for output file
        if (arglen == 2 && argv[i][0] == '-' && argv[i][1] == 'o') {
            // Ensure there is a next argument for the output file name
            if (i + 1 == argc) {
                fprintf(stderr, "No output file has been provided after -o flag\n");  // Use fprintf for better error message formatting
                exit(EXIT_FAILURE);
            }
            // Copy the next argument as the output file name
            strncpy(output_file_name, argv[i + 1], sizeof(output_file_name) - 1); // Use strncpy to avoid buffer overflow
            output_file_name[sizeof(output_file_name) - 1] = '\0'; // Ensure null termination
            have_output_file++;
            i++; // Skip the next argument as it is the output file name
        }

        // Check if the argument is an input file with .c extension
        if (arglen > 2 && argv[i][arglen - 1] == 'c' && argv[i][arglen - 2] == '.') {
            // Copy the argument as the input file name
            strncpy(input_file_name, argv[i], sizeof(input_file_name) - 1); // Use strncpy to avoid buffer overflow
            input_file_name[sizeof(input_file_name) - 1] = '\0'; // Ensure null termination
            have_input_file++;
        }
    }

    // If no output file specified, use the default name "a.out"
    if (have_output_file == 0) {
        strcpy(output_file_name, "a.out");
    }

    // If no input file provided, print an error message and exit
    if (have_input_file == 0) {
        fprintf(stderr, "No input file has been supplied\n");  // Use fprintf for better error message formatting
        exit(EXIT_FAILURE);
    }

    // Print the identified input and output files for verification (Optional)
    printf("Input file: %s\n", input_file_name);
    printf("Output file: %s\n", output_file_name);

    return 0;
}
