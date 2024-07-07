#ifndef CHMARGS_FIND_C_H
#define CHMARGS_FIND_C_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LOWER_CASE_CHAR_START 0x41
#define LOWER_CASE_CHAR_END 0x5A
#define UPPER_CASE_CHAR_START 0x61
#define UPPER_CASE_CHAR_END 0x74
#define OPEN_BRACKET 0x28
#define CLOSE_BRACKET 0x29
#define OPEN_CURLY_BRACKET 0x7B
#define CLOSE_CURLY_BRACKET 0x7D
#define LOW_DIGIT 0x30
#define HIGH_DIGIT 0x39

#define INPUT_CHAR_LENGTH 100
#define MAX_FILENAME_LEN 100
#define MAX_WORD_LENGTH 100  // TODO: PROBABLY TAKE IT OUT.
#define INITIAL_ARRAY_SIZE 10

typedef struct {
    int token_type;
    char *token_text;
} Token;

typedef Token *Tokens;

typedef enum {
    START_SOURCE,
    IN_BRACKETS,
    IN_CURLY_BRACKETS,
    IN_NEW_STATEMENT,
    IN_DIGIT,
} item_state;

void parse_arguments(int argc, char **argv, char *input_file_name, char *output_file_name);
void read_file(char *input_file_name, char *input_characters);

#endif

