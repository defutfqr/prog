#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 64
#define MAX_WORDS 1024

typedef struct {
    char word[MAX_WORD_LENGTH];
    int count;
} WordCount;

int compareWordCounts(const void *a, const void *b) {
    return ((WordCount *)b)->count - ((WordCount *)a)->count;
}

int let(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

char low(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}

int main(int argc, char** argv) {
    char input_file[256];
    char output_file[256];

    printf("input file: ");
    scanf("%s", input_file);
    printf("output file: ");
    scanf("%s", output_file);

    FILE *in_file = fopen(input_file, "r");
    if (in_file == NULL) {
        perror("Ошибка открытия входного файла");
        return 1;
    }

    WordCount word_counts[MAX_WORDS];
    int num_words = 0;
    char word[MAX_WORD_LENGTH];
    int found;
    int word_index = 0;

    char c;
    while ((c = fgetc(in_file)) != EOF) {
        c = low(c);
        if (let(c)) {
            if (word_index < MAX_WORD_LENGTH - 1) {
                word[word_index++] = c;
            }
        } else {
            if (word_index > 0) {
                word[word_index] = '\0';
                word_index = 0;

                found = 0;
                for (int i = 0; i < num_words; i++) {
                    if (strcmp(word_counts[i].word, word) == 0) {
                        word_counts[i].count++;
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    if (num_words < MAX_WORDS) {
                        strcpy(word_counts[num_words].word, word);
                        word_counts[num_words].count = 1;
                        num_words++;
                    } else {
                        fprintf(stderr, "Превышено максимальное количество слов (%d)\n", MAX_WORDS);
                        fclose(in_file);
                        return 1;
                    }
                }
            }
        }
    }

    if (word_index > 0) {
        word[word_index] = '\0';
        found = 0;
        for (int i = 0; i < num_words; i++) {
            if (strcmp(word_counts[i].word, word) == 0) {
                word_counts[i].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (num_words < MAX_WORDS) {
                strcpy(word_counts[num_words].word, word);
                word_counts[num_words].count = 1;
                num_words++;
            } else {
                fprintf(stderr, "Превышено максимальное количество слов (%d)\n", MAX_WORDS);
                fclose(in_file);
                return 1;
            }
        }
    }



    fclose(in_file);

    qsort(word_counts, num_words, sizeof(WordCount), compareWordCounts);

    FILE *out_file = fopen(output_file, "w");
    if (out_file == NULL) {
        perror("Ошибка открытия выходного файла");
        return 1;
    }

    for (int i = 0; i < num_words; i++) {
        fprintf(out_file, "%s: %d\n", word_counts[i].word, word_counts[i].count);
    }

    fclose(out_file);

    printf("output file '%s'.\n", output_file);
    return 0;
}
