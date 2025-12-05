/*
 * BEGINNER-FRIENDLY TEXT PREPROCESSOR
 * 
 * What this program does:
 * 1. Takes 2 to 20 text files as input
 * 2. Reads each file
 * 3. Makes all text lowercase
 * 4. Removes punctuation
 * 5. Removes extra spaces
 * 6. Creates new cleaned files with "_cleaned" added to filename
 * 
 * Compilation: gcc -o preprocessor preprocessor.c
 * Run: ./preprocessor
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Maximum number of files allowed
#define MIN_FILES 2
#define MAX_FILES 20
#define MAX_TEXT_SIZE 10000

/*
 * Function to make text lowercase
 * Example: "HELLO" becomes "hello"
 */
void make_lowercase(char text[]) {
    int i = 0;
    
    // Go through each character
    while (text[i] != '\0') {
        // Convert to lowercase
        text[i] = tolower(text[i]);
        i++;
    }
}

/*
 * Function to remove punctuation
 * Keeps only letters, numbers, and spaces
 * Example: "Hello, World!" becomes "Hello World"
 */
void remove_punctuation(char text[]) {
    int i = 0;
    int j = 0;
    char temp[MAX_TEXT_SIZE];
    
    // Go through each character
    while (text[i] != '\0') {
        // Check if character is letter, number, or space
        if (isalpha(text[i]) || isdigit(text[i]) || text[i] == ' ') {
            temp[j] = text[i];
            j++;
        }
        i++;
    }
    
    temp[j] = '\0';
    
    // Copy cleaned text back
    strcpy(text, temp);
}

/*
 * Function to remove extra spaces
 * Multiple spaces become one space
 * Example: "hello    world" becomes "hello world"
 */
void remove_extra_spaces(char text[]) {
    int i = 0;
    int j = 0;
    char temp[MAX_TEXT_SIZE];
    int space_seen = 0;
    
    // Skip spaces at the beginning
    while (text[i] == ' ') {
        i++;
    }
    
    // Go through each character
    while (text[i] != '\0') {
        if (text[i] == ' ') {
            // Only add space if we haven't seen one
            if (space_seen == 0) {
                temp[j] = ' ';
                j++;
                space_seen = 1;
            }
        } else {
            temp[j] = text[i];
            j++;
            space_seen = 0;
        }
        i++;
    }
    
    // Remove space at the end if present
    if (j > 0 && temp[j - 1] == ' ') {
        j--;
    }
    
    temp[j] = '\0';
    
    // Copy cleaned text back
    strcpy(text, temp);
}

/*
 * Function to preprocess text
 * Does all three cleaning operations:
 * 1. Lowercase
 * 2. Remove punctuation
 * 3. Remove extra spaces
 */
void preprocess_text(char text[]) {
    printf("   -> Making text lowercase...\n");
    make_lowercase(text);
    
    printf("   -> Removing punctuation...\n");
    remove_punctuation(text);
    
    printf("   -> Removing extra spaces...\n");
    remove_extra_spaces(text);
}

/*
 * Function to read file and return text
 */
int read_file(char filename[], char text[]) {
    FILE *file;
    char ch;
    int i = 0;
    
    // Open file for reading
    file = fopen(filename, "r");
    
    // Check if file opened successfully
    if (file == NULL) {
        printf("   ERROR: Cannot open file '%s'\n", filename);
        return 0; // Return 0 for failure
    }
    
    // Read file character by character
    while ((ch = fgetc(file)) != EOF && i < MAX_TEXT_SIZE - 1) {
        text[i] = ch;
        i++;
    }
    
    text[i] = '\0'; // End of string
    
    fclose(file);
    return 1; // Return 1 for success
}

/*
 * Function to create cleaned filename
 * Example: "input.txt" becomes "input_cleaned.txt"
 */
void create_output_filename(char input_filename[], char output_filename[]) {
    int i = 0;
    int dot_position = -1;
    
    // Find the position of the dot (.)
    while (input_filename[i] != '\0') {
        if (input_filename[i] == '.') {
            dot_position = i;
        }
        i++;
    }
    
    // If no dot found, just add _cleaned.txt
    if (dot_position == -1) {
        sprintf(output_filename, "%s_cleaned.txt", input_filename);
    } else {
        // Copy filename before the dot
        strncpy(output_filename, input_filename, dot_position);
        output_filename[dot_position] = '\0';
        
        // Add _cleaned and the original extension
        strcat(output_filename, "_cleaned");
        strcat(output_filename, &input_filename[dot_position]);
    }
}

/*
 * Function to write cleaned text to new file
 */
int write_file(char filename[], char text[]) {
    FILE *file;
    
    // Open file for writing
    file = fopen(filename, "w");
    
    if (file == NULL) {
        printf("   ERROR: Cannot create file '%s'\n", filename);
        return 0;
    }
    
    // Write text to file
    fprintf(file, "%s", text);
    
    fclose(file);
    return 1;
}

/*
 * MAIN FUNCTION - This is where program starts
 */
int main() {
    int number_of_files;
    char input_filename[100];
    char output_filename[100];
    char text[MAX_TEXT_SIZE];
    int successful_files = 0;
    
    printf("==========================================\n");
    printf("  TEXT PREPROCESSOR - BEGINNER VERSION\n");
    printf("==========================================\n\n");
    
    // Ask user how many files
    printf("How many files do you want to process? (2 to 20): ");
    scanf("%d", &number_of_files);
    
    // Check if number is valid
    if (number_of_files < MIN_FILES || number_of_files > MAX_FILES) {
        printf("\nERROR: Please enter a number between %d and %d\n", MIN_FILES, MAX_FILES);
        return 1;
    }
    
    printf("\nYou will process %d files.\n", number_of_files);
    printf("==========================================\n\n");
    
    // Process each file
    for (int i = 0; i < number_of_files; i++) {
        printf("FILE %d:\n", i + 1);
        printf("Enter filename (example: document.txt): ");
        scanf("%s", input_filename);
        
        printf("\n   Reading file '%s'...\n", input_filename);
        
        // Read the file
        if (read_file(input_filename, text) == 0) {
            printf("   Skipping this file.\n\n");
            continue; // Skip to next file
        }
        
        printf("   File read successfully! (%ld characters)\n", strlen(text));
        
        // Preprocess the text
        printf("   Preprocessing text...\n");
        preprocess_text(text);
        printf("   Preprocessing complete! (%ld characters after cleaning)\n", strlen(text));
        
        // Create output filename
        create_output_filename(input_filename, output_filename);
        
        // Write cleaned text to new file
        printf("   Writing cleaned text to '%s'...\n", output_filename);
        if (write_file(output_filename, text) == 1) {
            printf("   SUCCESS! File saved.\n\n");
            successful_files++;
        } else {
            printf("   FAILED to save file.\n\n");
        }
        
        printf("------------------------------------------\n\n");
    }
    
    // Show final results
    printf("==========================================\n");
    printf("         PROCESSING COMPLETE!\n");
    printf("==========================================\n");
    printf("Total files processed successfully: %d out of %d\n", successful_files, number_of_files);
    printf("\nAll cleaned files have '_cleaned' added to their names.\n");
    printf("Example: input.txt -> input_cleaned.txt\n");
    printf("==========================================\n");
    
    return 0;
}