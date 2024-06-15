/* Identify the start and end of the most basic character sequences
 *
 * For:
 *  int main() {return 0;}
 *
 * Stack looks like this:
 *
 * START_SOURCE (0)
 * -> START_TEXT (0) -> because we don't need to push it onto the stack
 * -> -> char "i"
 * -> -> char "n"
 * -> -> char "t"
 * -> END_TEXT (0)
 * -> START_TEXT (0)
 * -> -> char "m"
 * -> -> char "a"
 * -> -> char "i"
 * -> -> char "n"
 * -> END_TEXT (0)
 * -> START_BRACKETS (0), (1)
 * -> END_BRACKETS  (0)
 * -> START_CURLY_BRACKETS (0), (2)
 * -> -> START_STATEMENT  (0), (2), (3)
 * -> -> -> START_TEXT (0), (2), (3)
 * -> -> -> -> "r"
 * -> -> -> -> "e"
 * -> -> -> -> "t"
 * -> -> -> -> "u"
 * -> -> -> -> "r"
 * -> -> -> -> "n"
 * -> -> -> END_TEXT (0), (2), (3)
 * -> -> -> START_DIGIT (0), (2), (3)
 * -> -> -> END_DIGIT (0), (2), (3)
 * -> -> END_STATEMENT (0), (2)
 * -> END_CURLY_BRACKETS (0)
 * END_SOURCE ...
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    START_SOURCE,
    IN_BRACKETS,
    IN_CURLY_BRACKETS,
    IN_NEW_STATEMENT,
    IN_DIGIT,
} item_state;


bool is_valid_text_start(char c) {
    return ((c >= 0x41 && c <= 0x5A) || (c >= 0x61 && c <= 0x7A));
}


bool is_valid_text_inner(char c) {
    return ((c >= 0x41 && c <= 0x5A) ||
            (c >= 0x61 && c <= 0x7A) ||
            (c == 0x2D) ||
            (c >= 0x30 && c <= 0x39));
}


bool is_open_bracket(char c) {
    return (c == 0x28);
}


bool is_close_bracket(char c) {
    return (c == 0x29);
}


bool is_open_curly_brackets(char c) {
    return (c == 0x7B);
}


bool is_close_curly_bracket(char c) {
    return (c == 0x7D);
}


bool is_digit(char c) {
    return (c >= 0x30 && c <= 0x39);
}


bool is_end_statement(char c) {
    return (c == 0x3B);
}


int main(int argc, char **argv)
{
    char source[] = "int main(){return 8880;}";

    int state_stack[] = {START_SOURCE, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int stack_end = 18;
    int stack_start = 0;
    int stack_pointer = stack_start;
    int i = 0;
    int j;
    char c;

    do  {
        c = source[i];

        if (is_valid_text_start(c)) {
            while (is_valid_text_inner(c)) {
                putchar(c);
                c = source[++i];
            }
            printf("\n");
            c = source[--i];

        } else if (is_open_bracket(c)) {
            putchar(c);
            state_stack[++stack_pointer] = IN_BRACKETS;
            printf(" : STACK STATE NOW ");

            for (j=stack_start; j<=stack_pointer; j++) {
                printf("(%d) ", state_stack[j]);
            }
            printf("\n\n");

        } else if (is_close_bracket(c)) {
            putchar(c);
            stack_pointer--;
            printf(" : STACK STATE NOW ");

            for (j=stack_start; j<=stack_pointer; j++) {
                printf("(%d) ", state_stack[j]);
            }
            printf("\n");

        } else if (is_open_curly_brackets(c)) {
            putchar(c);
            state_stack[++stack_pointer] = IN_CURLY_BRACKETS;
            state_stack[++stack_pointer] = IN_NEW_STATEMENT;
            printf(" : STACK STATE NOW ");

            for (j=stack_start; j<=stack_pointer; j++) {
                printf("(%d) ", state_stack[j]);
            }
            printf("\n");

        } else if (is_close_curly_bracket(c)) {
            putchar(c);
            stack_pointer--;
            printf(" : STACK STATE NOW ");

            for (j=stack_start; j<=stack_pointer; j++) {
                printf("(%d) ", state_stack[j]);
            }
            printf("\n");

        } else if (is_digit(c)) {
            while (is_digit(c)) {
                putchar(c);
                c = source[++i];
            }
            c = source[--i];
            printf("\n");

        } else if (is_end_statement(c)) {
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

