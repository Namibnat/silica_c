/*
 * 	•	Keywords: Reserved words in C, such as int, return, if, else, while, for, void, char, float, double, static, struct, etc.
	•	Identifiers: Names given to variables, functions, arrays, etc., such as main, x, myFunction, data, etc.
	•	Operators:
	•	Arithmetic Operators: +, -, *, /, %
	•	Assignment Operators: =, +=, -=, *=, /=, %=
	•	Comparison Operators: ==, !=, <, >, <=, >=
	•	Logical Operators: &&, ||, !
	•	Bitwise Operators: &, |, ^, ~, <<, >>
	•	Increment/Decrement Operators: ++, --
	•	Pointer Operators: *, &
	•	Punctuation:
	•	Parentheses: (, )
	•	Braces: {, }
	•	Brackets: [, ]
	•	Comma: ,
	•	Semicolon: ;
	•	Colon: :
	•	Period: .
	•	Ellipsis: ... (used in variadic functions)
	•	Literals:
	•	Integer Literals: 0, 1, 2, 110, etc.
	•	Floating-point Literals: 0.0, 3.14, 2.718, etc.
	•	Character Literals: 'a', 'b', '\n', etc.
	•	String Literals: "hello", "world", "sample", etc.
	•	Boolean Literals: true, false (from <stdbool.h>)
*/

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
#define SEMICOLON 0x3B

#define INPUT_CHAR_LENGTH 100
#define MAX_FILENAME_LEN 100
#define MAX_WORD_LENGTH 100
#define INITIAL_ARRAY_SIZE 10

typedef struct Token{
    int token_type;
    char *token_text;
    struct Token *next;
} Token;

typedef struct LinkedTokens {
    Token *head;
    Token *tail;
} LinkedTokens;


enum item_state{
    START_SOURCE,
    IN_BRACKETS,
    IN_CURLY_BRACKETS,
    IN_NEW_STATEMENT,
    IN_DIGIT,
};

enum c_types{
    KEYWORD,
    IDENTIFIER,
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    LEFT_BRACE,
    RIGHT_BRACE,
    INTEGER_LITERAL,
    SEMICOLON_ITEM,
};

/* Starting to add in details to work towards syntax analysis */

// Define types of nodes
typedef enum { NODE_TYPE_OPERATOR, NODE_TYPE_NUMBER } NodeType;

// Struct for a node in the parse tree
typedef struct Node {
    NodeType type;
    union {
        struct {
            char operator;
            struct Node *left;
            struct Node *right;
        } operator;
        int number;
    } data;
} Node;

bool is_valid_text_inner(char c);
int identify_code_string(char *text);
void assign_token(LinkedTokens **linked_toks, char *item, unsigned int item_size, int item_type);
void parse_arguments(int argc, char **argv, char *input_file_name, char *output_file_name);
void read_file(char *input_file_name, char **input_characters);
void token_parser(LinkedTokens **linked_toks, char **input_characters);

#endif

