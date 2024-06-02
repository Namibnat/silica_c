/* This is entirly chatGPT generated because I just wanted to be
 * careful about getting this right.
 *
 * Opens a file and reads the words and prints them out.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define INITIAL_ARRAY_SIZE 10

int main() {
    FILE *file = fopen("words.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open file.\n");
        return 1;
    }

    // Array to store pointers to the words
    char **words = malloc(INITIAL_ARRAY_SIZE * sizeof(char *));
    if (words == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(file);
        return 1;
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
                return 1;
            }
        }

        // Allocate memory for the word and store it in the array
        words[count] = malloc((strlen(word) + 1) * sizeof(char));
        if (words[count] == NULL) {
            fprintf(stderr, "Memory allocation for word failed.\n");
            fclose(file);
            return 1;
        }
        strcpy(words[count], word);
        count++;
    }

    fclose(file);

    // Print the words
    for (int i = 0; i < count; i++) {
        printf("%s\n", words[i]);
        free(words[i]);  // Free each word's memory
    }

    free(words);  // Free the array of pointers

    return 0;
}

