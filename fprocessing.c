#include <stdio.h>
#include <ctype.h>   // for tolower() and ispunct()
#include <string.h>

void preprocess(char text[]) {
    int i, j = 0;
    int spaceFlag = 0;
    char cleaned[1000];

    for (i = 0; text[i] != '\0'; i++) {
        char c = text[i];

        // make lowercase
        c = tolower(c);

        // remove punctuation
        if (ispunct(c)) {
            continue;
        }

        // remove extra spaces
        if (c == ' ') {
            if (spaceFlag == 1) {
                continue;  // skip if already had space
            }
            spaceFlag = 1;
        } else {
            spaceFlag = 0;
        }

        cleaned[j++] = c;
    }

    cleaned[j] = '\0';
    strcpy(text, cleaned);
}

int main() {
    int n;
    char filename[50];
    char text[1000];

    // Ask user for number of files
    printf("Enter number of text files (2 to 20): ");
    scanf("%d", &n);

    if (n < 2 || n > 20) {
        printf("Invalid number!\n");
        return 0;
    }

    // Read newline left by scanf
    getchar();

    for (int i = 0; i < n; i++) {

        printf("\nEnter file name %d: ", i + 1);
        fgets(filename, sizeof(filename), stdin);

        // remove newline from filename
        filename[strcspn(filename, "\n")] = '\0';

        FILE *fp = fopen(filename, "r");

        if (fp == NULL) {
            printf("Could not open file %s\n", filename);
            continue;
        }
        // Read line by line
        while (fgets(text, sizeof(text), fp)) {
            preprocess(text);
        }
        fclose(fp);
    }

    return 0;
}
