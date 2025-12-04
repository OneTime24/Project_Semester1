#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// --- MODULE A FUNCTIONS ---

// 1. Read .txt and .c files into a buffer [cite: 88, 14]
char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }

    // Move to end to get size, then rewind
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory (buffer) for the text
    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    // Read the file
    fread(buffer, 1, length, file);
    buffer[length] = '\0'; // Null-terminate the string

    fclose(file);
    return buffer; // Returns the cleaned text buffer [cite: 92, 18]
}

// 2. Lowercase conversion [cite: 89, 15]
void to_lowercase(char* text) {
    if (!text) return;
    for (int i = 0; text[i]; i++) {
        text[i] = tolower((unsigned char)text[i]);
    }
}

// 3. Remove punctuation [cite: 90, 16]
void remove_punctuation(char* text) {
    if (!text) return;
    char* src = text;
    char* dst = text;

    while (*src) {
        if (!ispunct((unsigned char)*src)) {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

// 4. Remove extra spaces [cite: 91, 17]
// This turns "hello   world" into "hello world"
void remove_extra_spaces(char* text) {
    if (!text) return;
    char* src = text;
    char* dst = text;
    int space_found = 0;

    while (*src) {
        if (isspace((unsigned char)*src)) {
            if (!space_found) {
                *dst = ' ';
                dst++;
                space_found = 1;
            }
        } else {
            *dst = *src;
            dst++;
            space_found = 0;
        }
        src++;
    }
    *dst = '\0';
}
void check_t(char* content){
	printf("%s" , content);
}
// --- MAIN TEST DRIVER ---

int main() {
    // Manually create a dummy file to test
    FILE *f = fopen("test_input.txt", "w");
    if (!f) {
        printf("Failed to create test file.\n");
        return 1;
    }
    fprintf(f, "Hello,   World!  This is... a TEST.");
    fclose(f);

    printf("--- Testing Module A (Preprocessing) ---\n");

    // Test Reading
    char* content = read_file("test_input.txt");
//    if(content) {
//        printf("1. Original Read:   '%s'\n", content);
//        
//        // Test Lowercase
        to_lowercase(content);
//        printf("2. Lowercased:      '%s'\n", content);
//
//        // Test Punctuation Removal
        remove_punctuation(content);
//        printf("3. No Punctuation:  '%s'\n", content);
//
//        // Test Space Removal
        remove_extra_spaces(content);
//        printf("4. Final Cleaned:   '%s'\n", content);

        
//    } else {
//        printf("Read failed.\n");
//    }
    check_t(content);
//    return content;
}