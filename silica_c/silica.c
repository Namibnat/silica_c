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

void assign_token(Token **tokens, int token_counter, char *item, unsigned int item_size, int item_type) {
    if (token_counter > 0) {
        Token *tokens_update;
        tokens_update = realloc(*tokens, (token_counter + 1) * sizeof(Token));
        if (tokens_update == NULL) {
            perror("Failed to allocate memory for tokens");
            exit(EXIT_FAILURE);
        }
        *tokens = tokens_update;
    }
    (*tokens)[token_counter].token_type = item_type;
    char *token_text = (char *)malloc(item_size * sizeof(char));
    if (token_text == NULL) {
        perror("Failed to allocate memory for token text");
        exit(EXIT_FAILURE);
    }
    (*tokens)[token_counter].token_text = token_text;
    strcpy((*tokens)[token_counter].token_text, item);
}

void free_tokens(Token *tokens, int token_counter){
    for (int i = 0; i < token_counter; i++) {
        free(tokens[i].token_text);
    }
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

int identify_code_string(char *text) {
    // TODO: do logic to sort keywords form identifiers.
    if (strcmp(text, "int")) {
        return KEYWORD;
    }
    if (strcmp(text, "return")) {
        return KEYWORD;
    }

    return IDENTIFIER;
}

int token_parser(Token **tokens, char **input_characters) {
    int i = 0;
    char c;
    char item_container[50];
    int item_counter;
    int token_counter = 0;

    *tokens = (Token *)malloc(sizeof(Token));
    if (tokens == NULL) {
        perror("Failed to allocate memory for tokens");
        exit(EXIT_FAILURE);
    }

    do  {
        c = (*input_characters)[i];
        item_counter = 0;
        switch(c) {
            case LOWER_CASE_CHAR_START ... LOWER_CASE_CHAR_END:
            case UPPER_CASE_CHAR_START ... UPPER_CASE_CHAR_END:
                do {
                    item_container[item_counter++] = c;
                    c = (*input_characters)[++i];
                } while (is_valid_text_inner(c));
                item_container[item_counter++] = '\0';

                assign_token(tokens, token_counter, item_container, item_counter, identify_code_string(item_container));
                token_counter++;
                i--;
                break;

            case OPEN_BRACKET:
                assign_token(tokens, token_counter, "(", item_counter, LEFT_PARENTHESIS);
                token_counter++;
                break;

            case CLOSE_BRACKET:
                assign_token(tokens, token_counter, ")", item_counter, RIGHT_PARENTHESIS);
                token_counter++;
                break;

            case OPEN_CURLY_BRACKET:
                assign_token(tokens, token_counter, "{", item_counter, LEFT_BRACE);
                token_counter++;
                break;

            case CLOSE_CURLY_BRACKET:
                assign_token(tokens, token_counter, "}", item_counter, RIGHT_BRACE);
                token_counter++;
                break;

            case LOW_DIGIT ... HIGH_DIGIT:
                do {
                    item_container[item_counter++] = c;
                    c = (*input_characters)[++i];
                } while (is_digit(c));
                item_container[item_counter++] = '\0';
                assign_token(tokens, token_counter, item_container, item_counter, INTEGER_LITERAL);
                token_counter++;
                i--;
                break;
            case SEMICOLON:
                assign_token(tokens, token_counter, ";", item_counter, SEMICOLON_ITEM);
                token_counter++;
                break;

            case '\0':
                break;
        }
        i++;
    } while (c != '\0');

    return token_counter;
}


int main(int argc, char **argv) {
    /*
     * TODO:
     *  - Make tokens into a linked list.
     *  - Then start on the next section
     */

    int token_counter;
    char input_file_name[MAX_FILENAME_LEN];
    char output_file_name[MAX_FILENAME_LEN];
    char *input_characters = NULL;
    Token *tokens = NULL;
    // TODO: Working towards changing to linked list -> use linked tokens to keep track of tail to add
    // to the end of the linked list.
    LinkedTokens linked_toks = {NULL, NULL};

    parse_arguments(argc, argv, input_file_name, output_file_name);
    read_file(input_file_name, &input_characters);
    token_counter = token_parser(&tokens, &input_characters);

    printf("token_counter: %d\n", token_counter);
    for (int i = 0; i < token_counter; i++) {
        printf("%s\n", tokens[i].token_text);
    }


    free(input_characters);
    free_tokens(tokens, token_counter);

    return 0;
}

