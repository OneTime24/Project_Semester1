#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// =========================
// MODULE A CODE
// =========================

void preprocess(char text[]) {
    char cleaned[50000];
    int i, j = 0;
    int spaceFlag = 0;

    for (i = 0; text[i] != '\0'; i++) {
        char c = tolower(text[i]);

        if (ispunct(c))
            continue;

        if (c == ' ') {
            if (spaceFlag) continue;
            spaceFlag = 1;
        } else {
            spaceFlag = 0;
        }

        cleaned[j++] = c;
    }

    cleaned[j] = '\0';
    strcpy(text, cleaned);
}

void convertToText(const char *src, const char *out) {
    char cmd[200];

    if (strstr(src, ".pdf")) {
        sprintf(cmd, "pdftotext \"%s\" \"%s\"", src, out);
        system(cmd);
    }
    else if (strstr(src, ".docx")) {
        sprintf(cmd, "docx2txt \"%s\" \"%s\"", src, out);
        system(cmd);
    }
}

int loadFile(const char *filename, char buffer[], int max) {

    char tempFile[] = "temp_output.txt";

    // convert PDF or DOCX to text first
    if (strstr(filename, ".pdf") || strstr(filename, ".docx")) {
        convertToText(filename, tempFile);
        filename = tempFile; // now load the converted text file
    }

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: cannot open file %s\n", filename);
        return 0;
    }

    int i = 0;
    char c;

    while ((c = fgetc(fp)) != EOF && i < max - 1) {
        buffer[i++] = c;
    }
    buffer[i] = '\0';

    fclose(fp);
    return 1;
}

// =========================
// SIMPLE MAIN FOR TESTING
// =========================

int main() {

    char filename[100];
    char buffer[50000];

    printf("Enter file name (.txt .c .pdf .docx): ");
    scanf("%s", filename);

    // Step 1 — Load raw text
    if (!loadFile(filename, buffer, sizeof(buffer))) {
        printf("File loading failed.\n");
        return 1;
    }

    printf("\n--- RAW TEXT LOADED ---\n");
    printf("%s\n", buffer);

    // Step 2 — Preprocess (cleaning)
    preprocess(buffer);

    printf("\n--- CLEANED TEXT ---\n");
    printf("%s\n", buffer);

    printf("\nModule A test complete.\n");

    return 0;
}
