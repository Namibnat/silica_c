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


void assign_token(LinkedTokens **linked_toks, char *item, unsigned int item_size, int item_type) {
    Token *new_token = (Token *)malloc(sizeof(Token));
    if (new_token == NULL) {
        perror("Failed to allocate memory for tokens");
        exit(EXIT_FAILURE);
    }
    char *token_text = (char *)malloc(item_size * sizeof(char));
    if (token_text == NULL) {
        perror("Failed to allocate memory for token text");
        exit(EXIT_FAILURE);
    }
    strcpy(token_text, item);
    new_token->token_type = item_type;
    new_token->token_text = token_text;
    new_token->next = NULL;

    if ((*linked_toks)->head == NULL){
        (*linked_toks)->head = new_token;
    } else {
        if ((*linked_toks)->tail == NULL){
            (*linked_toks)->head->next = new_token;
            (*linked_toks)->tail = new_token;
        } else {
            (*linked_toks)->tail->next = new_token;
            (*linked_toks)->tail = new_token;
        }
    }

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


void token_parser(LinkedTokens **linked_toks, char **input_characters) {
    int i = 0;
    char c;
    char item_container[50];
    int item_counter;
    int token_counter = 0;

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
                assign_token(linked_toks, item_container, item_counter, identify_code_string(item_container));

                token_counter++;
                i--;
                break;

            case OPEN_BRACKET:
                assign_token(linked_toks, "(", item_counter, LEFT_PARENTHESIS);
                token_counter++;
                break;

            case CLOSE_BRACKET:
                assign_token(linked_toks, ")", item_counter, RIGHT_PARENTHESIS);
                token_counter++;
                break;

            case OPEN_CURLY_BRACKET:
                assign_token(linked_toks, "{", item_counter, LEFT_BRACE);
                token_counter++;
                break;

            case CLOSE_CURLY_BRACKET:
                assign_token(linked_toks, "}", item_counter, RIGHT_BRACE);
                token_counter++;
                break;

            case LOW_DIGIT ... HIGH_DIGIT:
                do {
                    item_container[item_counter++] = c;
                    c = (*input_characters)[++i];
                } while (is_digit(c));
                item_container[item_counter++] = '\0';
                assign_token(linked_toks, item_container, item_counter, INTEGER_LITERAL);
                token_counter++;
                i--;
                break;

            case SEMICOLON:
                assign_token(linked_toks, ";", item_counter, SEMICOLON_ITEM);
                token_counter++;
                break;

            case '\0':
                break;
        }
        i++;
    } while (c != '\0');

}


void syntax_analysis(Token **token) {
    short state_stack[100];
    /*
     * The next step here is for me to figoure out how
     * to build out a tree structure, etc.
     */
    while ((*token)->next != NULL) {
        printf("%s\n", (*token)->token_text);
        *token = (*token)->next;
    }
}


int main(int argc, char **argv) {
    /*
     * TODO:
     *  - Start on syntax analysis of the basic input
     */

    char input_file_name[MAX_FILENAME_LEN];
    char output_file_name[MAX_FILENAME_LEN];
    char *input_characters = NULL;

    LinkedTokens *linked_toks = malloc(sizeof(LinkedTokens));
    if (!linked_toks) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    (*linked_toks).head = NULL;
    (*linked_toks).tail = NULL;

    parse_arguments(argc, argv, input_file_name, output_file_name);
    read_file(input_file_name, &input_characters);
    token_parser(&linked_toks, &input_characters);
    syntax_analysis(&linked_toks->head);

    return 0;
}

