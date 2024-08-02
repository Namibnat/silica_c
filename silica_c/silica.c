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
    if (!file) {
        fprintf(stderr, "Could not open file.\n");
        exit(EXIT_FAILURE);
    }

    while ((c=fgetc(file)) != EOF) {
        if ((count + 2) >= capacity) {
            capacity *= 2;
            padded_characters = (char *)realloc(*input_characters, capacity * sizeof(char));
            if (!padded_characters) {
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


void start_entry_symbol_table(char *item, Symbol **symbol_table, int symbol_table_index) {
    if (symbol_table_index > 0) {
        *symbol_table = (Symbol *)realloc(*symbol_table, sizeof(Symbol) * (symbol_table_index + 1));
        if (symbol_table == NULL) {
            perror("Failed to allocate memory for symbol table");
            exit(EXIT_FAILURE);
        }
    }
    char *symbol_name = (char *)malloc(sizeof(item));
    if (symbol_name == NULL) {
        perror("Failed to create memory for symbol name");
        exit(EXIT_FAILURE);
    }
    (*symbol_table)[symbol_table_index].symbol_name = symbol_name;

    strcpy((*symbol_table)[symbol_table_index].symbol_name, item);
}


int determin_type(char *item) {
    if (strcmp("int", item) == 0) {
        return INT;
    }
    return -1;
}


void assign_token(LinkedTokens **linked_toks, char *item, unsigned int item_size, int item_type, Symbol **symbol_table) {
    Token *new_token = (Token *)malloc(sizeof(Token));
    int symbol_table_index = 0;

    if (!new_token) {
        perror("Failed to allocate memory for tokens");
        exit(EXIT_FAILURE);
    }

    char *token_text = (char *)malloc(item_size * sizeof(char));
    if (!token_text) {
        perror("Failed to allocate memory for token text");
        exit(EXIT_FAILURE);
    }

    strcpy(token_text, item);
    new_token->token_type = item_type;

    if (item_type == IDENTIFIER) {
        start_entry_symbol_table(item, symbol_table, symbol_table_index);
        symbol_table_index++;
    }

    if (item_type == KEYWORD) {
        new_token->type = determin_type(item);
    } else {
        new_token->type = -1;
    }

    new_token->token_text = token_text;
    new_token->next = NULL;

    if ((*linked_toks)->head == NULL) {
        (*linked_toks)->head = new_token;
    } else {
        if ((*linked_toks)->tail == NULL) {
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


    for (i = 1; i < argc; i++) {
        arglen = strlen(argv[i]);

        if (arglen == 2 && argv[i][0] == '-' && argv[i][1] == 'o') {

            outfile_position = i + 1;
            if (outfile_position >= argc) {
                fprintf(stderr, "No output file hane has been provided after the -o flag\n");
                exit(EXIT_FAILURE);
            }

            outlen = strlen(argv[outfile_position]);
            if (outlen > MAX_WORD_LENGTH) {
                fprintf(stderr, "Output filename exceeds the maximum length");
                exit(EXIT_FAILURE);
            }

            strncpy(output_file_name, argv[outfile_position], outlen);
            output_file_name[outlen] = '\0';
            have_output_file++;
            i++;
            continue;
        }

        if (arglen > 2 && argv[i][arglen - 1] == 'c' && argv[i][arglen - 2] == '.') {

            strncpy(input_file_name, argv[i], arglen);
            input_file_name[arglen] = '\0';
            have_input_file++;
        }

        if (have_input_file > 0 && have_output_file > 0) {
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
    if (strcmp(text, "int") == 0) {
        return KEYWORD;
    }
    if (strcmp(text, "return") == 0) {
        return KEYWORD;
    }

    return IDENTIFIER;
}


void token_parser(LinkedTokens **linked_toks, char **input_characters, Symbol **symbol_table) {
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
                assign_token(linked_toks, item_container, item_counter, identify_code_string(item_container), symbol_table);

                token_counter++;
                i--;
                break;

            case OPEN_BRACKET:
                assign_token(linked_toks, "(", item_counter, LEFT_PARENTHESIS, NULL);
                token_counter++;
                break;

            case CLOSE_BRACKET:
                assign_token(linked_toks, ")", item_counter, RIGHT_PARENTHESIS, NULL);
                token_counter++;
                break;

            case OPEN_CURLY_BRACKET:
                assign_token(linked_toks, "{", item_counter, LEFT_BRACE, NULL);
                token_counter++;
                break;

            case CLOSE_CURLY_BRACKET:
                assign_token(linked_toks, "}", item_counter, RIGHT_BRACE, NULL);
                token_counter++;
                break;

            case LOW_DIGIT ... HIGH_DIGIT:
                do {
                    item_container[item_counter++] = c;
                    c = (*input_characters)[++i];
                } while (is_digit(c));
                item_container[item_counter++] = '\0';
                assign_token(linked_toks, item_container, item_counter, INTEGER_LITERAL, NULL);
                token_counter++;
                i--;
                break;

            case SEMICOLON:
                assign_token(linked_toks, ";", item_counter, SEMICOLON_ITEM, NULL);
                token_counter++;
                break;

            case '\0':
                break;
        }
        i++;
    } while (c != '\0');

}

void syntax_analysis(Token **token, Symbol **symbol_table) {
    /* TODO: WORKING HERE...
     *
            typedef struct Symbol {
                char *scope;
                char *symbol_name;
                int type;
                int value; // ?
            } Symbol;
     *
     */
    int symbol_table_index = 0;
    short SCOPE = SCOPE_GLB;
    int type_recorder;
    while (*token != NULL) {

        printf("Token type...%d\n", (*token)->type);
        printf("Token token_type...%d\n", (*token)->token_type);
        printf("Token text...%s\n", (*token)->token_text);

        if ((*token)->token_type == KEYWORD) {
            if ((*token)->type >= 0) {
                type_recorder = (*token)->type;
            }
            if (strcmp((*token)->token_text, "return") == 0) {
                printf("Set flag that next item is return type\n");
            }
        }
        if ((*token)->token_type == IDENTIFIER) {
            printf("Symbol: %s is of type %d\n", (*token)->token_text, type_recorder);
            (*symbol_table)[symbol_table_index].scope = SCOPE;
            type_recorder = -1;
        }
        printf("\n\n");

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

    Symbol *symbol_table = malloc(sizeof(Symbol));
    if (!symbol_table) {
        fprintf(stderr, "Memory allocation failed for symbol table\n");
        return EXIT_FAILURE;
    }


    LinkedTokens *linked_toks = malloc(sizeof(LinkedTokens));
    if (!linked_toks) {
        fprintf(stderr, "Memory allocation failed for token list\n");
        return EXIT_FAILURE;
    }

    (*linked_toks).head = NULL;
    (*linked_toks).tail = NULL;

    parse_arguments(argc, argv, input_file_name, output_file_name);
    read_file(input_file_name, &input_characters);
    token_parser(&linked_toks, &input_characters, &symbol_table);
    syntax_analysis(&linked_toks->head, &symbol_table);

    return 0;
}

