#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main() {
    printf("Momina Ahmad 25P-0503\n");

    char sentence[1000];
    printf("Enter a sentence:\n");
    fgets(sentence, sizeof(sentence), stdin);

    int length = strlen(sentence);
    if(sentence[length - 1] == '\n') sentence[length - 1] = '\0';

    // Count words
    int wordCount = 0;
    int inWord = 0;
    for(int i = 0; *(sentence + i) != '\0'; i++){
        if(!isspace(*(sentence + i))) {
            if(!inWord) {
                wordCount++;
                inWord = 1;
            }
        } else {
            inWord = 0;
        }
    }

    // Allocate array of char pointers for words
    char **words = (char**)malloc(wordCount * sizeof(char*));
    if(words == NULL) return 1;

    int index = 0;
    int i = 0;
    while(*(sentence + i) != '\0') {
        while(isspace(*(sentence + i))) i++; // skip spaces
        if(*(sentence + i) == '\0') break;

        int start = i;
        while(*(sentence + i) != '\0' && !isspace(*(sentence + i))) i++;
        int wordLength = i - start;

        *(words + index) = (char*)malloc((wordLength + 1) * sizeof(char));
        if(*(words + index) == NULL) return 1;

        char *p = *(words + index);
        for(int j = 0; j < wordLength; j++)
            *(p + j) = *(sentence + start + j);
        *(p + wordLength) = '\0';

        index++;
    }
    printf("2D Array Output:\n");
	for(int k = 0; k < wordCount; k++)
        printf("%s\n", *(words + k));

    // Free memory
    for(int k = 0; k < wordCount; k++)
        free(*(words + k));
    free(words);

    return 0;
}
