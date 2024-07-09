/* silica.c: Ah hacked together c compiler */

#include "silica.h"


bool is_valid_text_inner(char c) {
    return ((c >= 0x41 && c <= 0x5A) ||
            (c >= 0x61 && c <= 0x7A) ||
            (c == 0x2D) ||
            (c >= 0x30 && c <= 0x39));
}

bool is_digit(char c) {
    return (c >= LOW_DIGIT && c <= HIGH_DIGIT);
}

bool assign_token(Token **tokens, int token_counter, char *item, unsigned int item_size) {
    if (token_counter > 0) {
        Token *tokens_update;
        tokens_update = realloc(*tokens, (token_counter + 1) * sizeof(Token));
        if (tokens_update == NULL) {
            perror("Failed to allocate memory for tokens");
            return false;
        }
        *tokens = tokens_update;
    }
    (*tokens)[token_counter].token_type = 1;  // TODO: This will get updated to types

    // TODO: malloc space for token string.

    // Next -> malloc to create heap memory for the item.
    printf("%s is %d\n", item, item_size);
    return true;
}

void free_tokens(Token *tokens, int token_counter){
    // TODO: cycle through the arrays and dealocate the memory for each item.
    free(tokens);
}

void parse_arguments(int argc, char **argv, char *input_file_name, char *output_file_name) {

    int i;
    int arglen;
    int outlen;
    int outfile_position;

    short have_input_file = 0;
    short have_output_file = 0;

    for (i = 1; i < argc; i++){
        arglen = strlen(argv[i]);

        if (arglen == 2 && argv[i][0] == '-' && argv[i][1] == 'o'){

            outfile_position = i + 1;
            if (outfile_position >= argc){
                fprintf(stderr, "No output file hane has been provided after the -o flag\n");
                exit(EXIT_FAILURE);
            }

            outlen = strlen(argv[outfile_position]);
            if (outlen > MAX_WORD_LENGTH){
                fprintf(stderr, "Output filename exceeds the maximum length");
                exit(EXIT_FAILURE);
            }

            strncpy(output_file_name, argv[outfile_position], outlen);
            output_file_name[outlen] = '\0';
            have_output_file++;
            i++;
            continue;
        }

        if (arglen > 2 && argv[i][arglen - 1] == 'c' && argv[i][arglen - 2] == '.'){

            strncpy(input_file_name, argv[i], arglen);
            input_file_name[arglen] = '\0';
            have_input_file++;
        }

        if (have_input_file > 0 && have_output_file > 0){
            break;
        }
    }

    if (have_output_file == 0) {
        strcpy(output_file_name, "a.out");
    }

    if (have_input_file == 0) {
        fprintf(stderr, "No input file has been supplied\n");
        exit(EXIT_FAILURE);
    }
}

void read_file(char *input_file_name, char **input_characters) {
    char c;
    int capacity = INITIAL_ARRAY_SIZE;
    int count = 0;
    char *padded_characters = NULL;

    *input_characters = (char *)malloc(capacity * sizeof(char));
    if (*input_characters == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }


    FILE *file = fopen(input_file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file.\n");
        exit(EXIT_FAILURE);
    }

    while ((c=fgetc(file)) != EOF) {
        if ((count + 2) >= capacity) {
            capacity *= 2;
            padded_characters = (char *)realloc(*input_characters, capacity * sizeof(char));
            if (padded_characters == NULL) {
                fprintf(stderr, "Memory reallocation failed.\n");
                fclose(file);
                exit(EXIT_FAILURE);
            }
            *input_characters = padded_characters;
        }
        (*input_characters)[count] = c;
        count++;
    }

    (*input_characters)[count] = '\0';
    fclose(file);
}

void token_parser(Token **tokens, char **input_characters) {
    int i = 0;
    char c;
    char item_container[50];  // TODO: GET RID OF MAGIC NUMBER, AND ASSIGN ON THE HEAP?
    int item_counter;

    do  {
        c = (*input_characters)[i];
        item_counter = 0;
        switch(c) {
            case LOWER_CASE_CHAR_START ... LOWER_CASE_CHAR_END:
            case UPPER_CASE_CHAR_START ... UPPER_CASE_CHAR_END:
                while (is_valid_text_inner(c)) {
                    item_container[item_counter++] = c;
                    c = (*input_characters)[++i];
                }
                printf("Found chars\n");
                break;
            case OPEN_BRACKET:
                printf("Found open brackets\n");
                break;
            case CLOSE_BRACKET:
                printf("Found close brackets\n");
                break;
            case OPEN_CURLY_BRACKET:
                printf("Found open curly brackets\n");
                break;
            case CLOSE_CURLY_BRACKET:
                printf("Found close curly brackets\n");
                break;
            case LOW_DIGIT ... HIGH_DIGIT:
                printf("Found digits\n");
                break;
            case '\0':
                printf("Found the end\n");
                break;
        }
        i++;
    } while (c != '\0');

    printf("\n\nbump: %d\n", item_counter);
}


int main(int argc, char **argv) {
    char input_file_name[MAX_FILENAME_LEN];
    char output_file_name[MAX_FILENAME_LEN];
    char *input_characters = NULL;
    Token *tokens = NULL;

    parse_arguments(argc, argv, input_file_name, output_file_name);
    read_file(input_file_name, &input_characters);
    token_parser(&tokens, &input_characters);


    free(input_characters);

    return 0;
}

