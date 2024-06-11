/* silica.c: Ah hacked together c compiler */

#include "silica.h"


#define MAX_WORD_LENGTH 100
#define INITIAL_ARRAY_SIZE 10

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
        arglen = strlen(argv[i]);

        if (arglen == 2 && argv[i][0] == '-' && argv[i][1] == 'o'){
            if (i + 1 == argc){
                fprintf(stderr, "No output file hane has been provided after the -o flag\n");
                continue;
            }
            strncpy(output_file_name, argv[i + 1], 19);
            printf("%s\n", argv[i+1]);
            output_file_name[19] = '\0';
            (*have_output_file)++;
            i++;
        }

        if (arglen > 2 && argv[i][arglen - 1] == 'c' && argv[i][arglen - 2] == '.'){
            strncpy(input_file_name, argv[i], 19);
            input_file_name[19] = '\0';
            (*have_input_file)++;
        }

        if (*have_input_file > 0 && *have_output_file > 0){
            break;
        }
    }

    if (*have_output_file == 0) {
        strcpy(output_file_name, "a.out");
    }

    if (*have_input_file == 0) {
        fprintf(stderr, "No input file has been supplied\n");
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char **argv)
{

    short have_input_file = 0;
    short have_output_file = 0;
    char input_file_name[20] = {0};
    char output_file_name[20] = {0};

    parse_arguments(argc, argv, input_file_name, output_file_name, &have_input_file, &have_output_file);

    printf("Input file: %s\n", input_file_name);
    printf("Ouput file: %s\n", output_file_name);

    FILE *file = fopen(input_file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file.\n");
        exit(EXIT_FAILURE);
    }

    char **words = malloc(INITIAL_ARRAY_SIZE * sizeof(char *));
    if (words == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    int capacity = INITIAL_ARRAY_SIZE;
    int count = 0;
    char word[MAX_WORD_LENGTH];

    while (fscanf(file, "%s", word) == 1) {
        if (count >= capacity) {
            // Resize the array if needed
            capacity *= 2;
            words = realloc(words, capacity * sizeof(char *));
            if (words == NULL) {
                fprintf(stderr, "Memory reallocation failed.\n");
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }

        words[count] = malloc((strlen(word) + 1) * sizeof(char));
        if (words[count] == NULL) {
            fprintf(stderr, "Memory allocation for word failed.\n");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        strcpy(words[count], word);
        count++;
    }

    fclose(file);

    for (int i = 0; i < count; i++) {
        printf("%s\n", words[i]);
        free(words[i]);
    }

    free(words);

    return 0;
}

