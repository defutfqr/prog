#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 2048

void reverseWord(char *word) {
    int len = strlen(word);
    for (int i = 0; i < len / 2; i++) {
        char temp = word[i];
        word[i] = word[len - i - 1];
        word[len - i - 1] = temp;
    }
}

void processLine(const char *line, char *output) {
    char temp[MAX_LINE_LENGTH];  
    strcpy(temp, line); 

    char *token = strtok(temp, " ");
    output[0] = '\0'; 
    while (token) {
        reverseWord(token);
        strcat(output, token);
        token = strtok(NULL, " ");
        if (token) strcat(output, " ");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen("ofile.txt", "w");
    if (!inputFile || !outputFile) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LENGTH], output[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, inputFile)) {
        line[strcspn(line, "\n")] = 0;
        processLine(line, output);
        fprintf(outputFile, "%s\n", output);
    }

    fclose(inputFile);
    fclose(outputFile);
    return EXIT_SUCCESS;
}
