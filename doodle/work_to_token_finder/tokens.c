/* Identify  */

#include <stdio.h>
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


typedef struct {
    char token_type;
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


bool is_valid_text_inner(char c) {
    return ((c >= 0x41 && c <= 0x5A) ||
            (c >= 0x61 && c <= 0x7A) ||
            (c == 0x2D) ||
            (c >= 0x30 && c <= 0x39));
}

bool is_digit(char c) {
    return (c >= LOW_DIGIT && c <= HIGH_DIGIT);
}



int main(int argc, char **argv)
{
    char source[] = "int main(){return 0;}";

    int state_stack[] = {START_SOURCE, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int stack_end = 18;
    int stack_start = 0;
    int stack_pointer = stack_start;
    int i = 0;
    int j;
    char c;

    do  {
        c = source[i];

        switch(c) {
            case LOWER_CASE_CHAR_START ... LOWER_CASE_CHAR_END:
            case UPPER_CASE_CHAR_START ... UPPER_CASE_CHAR_END:

                while (is_valid_text_inner(c)) {
                    putchar(c);
                    c = source[++i];
                }
                printf("\n");
                c = source[--i];
                break;

            case OPEN_BRACKET:
                putchar(c);
                state_stack[++stack_pointer] = IN_BRACKETS;
                printf(" : STACK STATE NOW ");
                for (j=stack_start; j<=stack_pointer; j++) {
                    printf("(%d) ", state_stack[j]);
                }
                printf("\n");
                break;
            case CLOSE_BRACKET:
                putchar(c);
                stack_pointer--;
                printf(" : STACK STATE NOW ");
                for (j=stack_start; j<=stack_pointer; j++) {
                    printf("(%d) ", state_stack[j]);
                }
                printf("\n");
                break;
            case OPEN_CURLY_BRACKET:
                putchar(c);
                state_stack[++stack_pointer] = IN_CURLY_BRACKETS;
                state_stack[++stack_pointer] = IN_NEW_STATEMENT;
                printf(" : STACK STATE NOW ");

                for (j=stack_start; j<=stack_pointer; j++) {
                    printf("(%d) ", state_stack[j]);
                }
                printf("\n");
                break;
            case CLOSE_CURLY_BRACKET:
                putchar(c);
                stack_pointer--;
                printf(" : STACK STATE NOW ");

                for (j=stack_start; j<=stack_pointer; j++) {
                    printf("(%d) ", state_stack[j]);
                }
                printf("\n");
                break;
            case LOW_DIGIT ... HIGH_DIGIT:
                while (is_digit(c)) {
                    putchar(c);
                    c = source[++i];
                }
                c = source[--i];
                printf("\n");
            case EOF:
                putchar(c);
                stack_pointer--;
                printf(" : STACK STATE NOW ");

                for (j=stack_start; j<=stack_pointer; j++) {
                    printf("(%d) ", state_stack[j]);
                }

                printf("\n");

        }

        i++;
    } while (c != '\0');

    return 0;
}

