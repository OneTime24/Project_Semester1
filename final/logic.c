#include "plagiarism.h"

// makes text lowercase and removes punctuation stuff
void preprocessText(char *src, char *dest) {
    int i = 0, j = 0;
    
    while (src[i] != '\0') {
        char c = src[i];
        if (isupper(c)) c = tolower(c);
        
        // keep only letters numbers and spaces
        if (isalnum(c) || c == ' ') 
            dest[j++] = c;
        else 
            dest[j++] = ' ';
        
        i++;
    }
    dest[j] = '\0';
    
    // remove multiple spaces
    i = 0; j = 0;
    int space_flag = 0;
    while (dest[i] != '\0') {
        if (dest[i] != ' ') {
            dest[j++] = dest[i];
            space_flag = 0;
        } else {
            if (!space_flag) {
                dest[j++] = ' ';
                space_flag = 1;
            }
        }
        i++;
    }
    
    if (j > 0 && dest[j - 1] == ' ') j--;
    dest[j] = '\0';
}

// FIXED: checking plagiarism - compares 3 word chunks with proper similarity calculation
float checkPlgText(char *txt1, char *txt2) {
    // make copies because strtok destroys strings
    char *copy1 = (char*)malloc(strlen(txt1) + 1);
    char *copy2 = (char*)malloc(strlen(txt2) + 1);
    strcpy(copy1, txt1);
    strcpy(copy2, txt2);
    
    int max1 = 100, max2 = 100;
    
    char **tokens1 = (char**)malloc(max1 * sizeof(char*));
    int t1 = 0;
    
    char *w1 = strtok(copy1, " ");
    while (w1 != NULL) {
        if (t1 >= max1) {
            max1 = max1 * 2;
            tokens1 = realloc(tokens1, max1 * sizeof(char*));
        }
        tokens1[t1] = (char*)malloc(strlen(w1) + 1);
        strcpy(tokens1[t1], w1);
        t1++;
        w1 = strtok(NULL, " ");
    }
    
    char **tokens2 = malloc(max2 * sizeof(char*));
    int t2 = 0;
    
    char *w2 = strtok(copy2, " ");
    while (w2 != NULL) {
        if (t2 >= max2) {
            max2 = max2 * 2;
            tokens2 = realloc(tokens2, max2 * sizeof(char*));
        }
        tokens2[t2] = malloc(strlen(w2) + 1);
        strcpy(tokens2[t2], w2);
        t2++;
        w2 = strtok(NULL, " ");
    }
    
    free(copy1);
    free(copy2);
    
    int n = 3;
    float similarity = 0;
    
    if (t1 >= n && t2 >= n) {
        int ng1 = t1 - n + 1;
        char **ngram1 = malloc(ng1 * sizeof(char*));
        
        int i;
        for (i = 0; i < ng1; i++) {
            int size = strlen(tokens1[i])+strlen(tokens1[i+1])+strlen(tokens1[i+2])+5;
            ngram1[i] = malloc(size);
            sprintf(ngram1[i], "%s %s %s", tokens1[i], tokens1[i+1], tokens1[i+2]);
        }
        
        int ng2 = t2 - n + 1;
        char **ngram2 = malloc(ng2 * sizeof(char*));
        
        for (i = 0; i < ng2; i++) {
            int size = strlen(tokens2[i])+strlen(tokens2[i+1])+strlen(tokens2[i+2])+5;
            ngram2[i] = malloc(size);
            sprintf(ngram2[i], "%s %s %s", tokens2[i], tokens2[i+1], tokens2[i+2]);
        }
        
        // Track which ngrams in file2 are already matched
        int *matched2 = (int*)calloc(ng2, sizeof(int));
        int match = 0;
        
        for (i = 0; i < ng1; i++) {
            int j;
            for (j = 0; j < ng2; j++) {
                if (!matched2[j] && strcmp(ngram1[i], ngram2[j]) == 0) {
                    match++;
                    matched2[j] = 1;
                    
                    // write matched 3-grams to report
                    if(report_file != NULL) {
                        fprintf(report_file, "  - \"%s\"\n", ngram1[i]);
                    }
                    
                    break;
                }
            }
        }
        
        // FIXED: Use Jaccard similarity or average-based similarity
        // Jaccard: matches / (total_unique_ngrams)
        // We'll use: (2 * matches) / (ng1 + ng2) for better balance
        similarity = (2.0 * match) / (ng1 + ng2) * 100;
        
        free(matched2);
        
        for (i = 0; i < ng1; i++) free(ngram1[i]);
        free(ngram1);
        for (i = 0; i < ng2; i++) free(ngram2[i]);
        free(ngram2);
    }
    
    int i;
    for (i = 0; i < t1; i++) free(tokens1[i]);
    free(tokens1);
    for (i = 0; i < t2; i++) free(tokens2[i]);
    free(tokens2);
    
    return similarity;
}

// removes comments and include statements from code
void removeCommentsAndHeaders(char *src, char *dest) {
    int i = 0, j = 0;
    
    while (src[i] != '\0') {
        if (src[i] == '#') {
            while (src[i] != '\n' && src[i] != '\0') i++;
            continue;
        }
        
        if (src[i] == '/' && src[i + 1] == '/') {
            i = i + 2;
            while (src[i] != '\n' && src[i] != '\0') i++;
            continue;
        }
        
        if (src[i] == '/' && src[i + 1] == '*') {
            i = i + 2;
            while (!(src[i] == '*' && src[i + 1] == '/') && src[i] != '\0') i++;
            if (src[i] != '\0') i = i + 2;
            continue;
        }
        
        dest[j++] = src[i++];
    }
    dest[j] = '\0';
}

int isKeyword(char *word) {
    char *keywords[] = {"int","float","double","char","void","if","else","while","for","return"};
    int i;
    for (i = 0; i < 10; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

void removeKeywords(char *src, char *dest) {
    int i = 0, j = 0;
    char word[50];
    int w = 0;
    
    while (src[i] != '\0') {
        if (isalpha(src[i])) {
            word[w++] = src[i];
        } else {
            word[w] = '\0';
            if (w > 0 && !isKeyword(word)) {
                int x;
                for (x = 0; word[x] != '\0'; x++)
                    dest[j++] = word[x];
            }
            w = 0;
            dest[j++] = src[i];
        }
        i++;
    }
    dest[j] = '\0';
}

// FIXED: compares code files with proper similarity calculation
void sim_chek(char *s1, char *s2) {
    char *copy1 = (char*)malloc(strlen(s1) + 1);
    char *copy2 = (char*)malloc(strlen(s2) + 1);
    strcpy(copy1, s1);
    strcpy(copy2, s2);
    
    // tokenize first file
    int max_tokens = 1000;
    char **tokens1 = (char**)malloc(max_tokens * sizeof(char*));
    int count1 = 0;
    
    char *tok = strtok(copy1, " \n\t");
    while (tok != NULL && count1 < max_tokens) {
        // skip very short tokens (single chars like braces)
        if(strlen(tok) > 1) {
            tokens1[count1] = (char*)malloc(strlen(tok) + 1);
            strcpy(tokens1[count1], tok);
            count1++;
        }
        tok = strtok(NULL, " \n\t");
    }
    
    // tokenize second file
    char **tokens2 = (char**)malloc(max_tokens * sizeof(char*));
    int count2 = 0;
    
    tok = strtok(copy2, " \n\t");
    while (tok != NULL && count2 < max_tokens) {
        // skip very short tokens
        if(strlen(tok) > 1) {
            tokens2[count2] = (char*)malloc(strlen(tok) + 1);
            strcpy(tokens2[count2], tok);
            count2++;
        }
        tok = strtok(NULL, " \n\t");
    }
    
    free(copy1);
    free(copy2);
    
    if(count1 == 0 || count2 == 0) {
        printf("No tokens found!\n");
        // free memory
        int i;
        for(i = 0; i < count1; i++) free(tokens1[i]);
        for(i = 0; i < count2; i++) free(tokens2[i]);
        free(tokens1);
        free(tokens2);
        return;
    }
    
    // track which tokens from file2 are already matched
    int *matched = (int*)calloc(count2, sizeof(int));
    int total_matches = 0;
    
    // compare tokens
    int i, j;
    for (i = 0; i < count1; i++) {
        for (j = 0; j < count2; j++) {
            // only match if not already matched
            if (!matched[j] && strcmp(tokens1[i], tokens2[j]) == 0) {
                printf("Matched: %s\n", tokens1[i]);
                
                // write to report file if open
                if(report_file != NULL) {
                    fprintf(report_file, "  - %s\n", tokens1[i]);
                }
                
                matched[j] = 1; // mark as matched
                total_matches++;
                break;
            }
        }
    }
    
    printf("\nTOTAL MATCHED: %d\n", total_matches);
    
    // FIXED: Use proper similarity calculation
    // Using: (2 * matches) / (count1 + count2) * 100
    // This gives balanced similarity considering both files
    float perc = (2.0 * total_matches) / (count1 + count2) * 100;
    printf("SIMILARITY PERCENTAGE: %.2f%%\n", perc);
    printf("(File1 tokens: %d, File2 tokens: %d)\n", count1, count2);
    
    // write summary to report
    if(report_file != NULL) {
        fprintf(report_file, "\nTotal Matches: %d\n", total_matches);
        fprintf(report_file, "File1 tokens: %d, File2 tokens: %d\n", count1, count2);
        fprintf(report_file, "Similarity: %.2f%%\n", perc);
        fprintf(report_file, "========================================\n\n");
    }
    
    // cleanup
    for(i = 0; i < count1; i++) free(tokens1[i]);
    for(i = 0; i < count2; i++) free(tokens2[i]);
    free(tokens1);
    free(tokens2);
    free(matched);
}