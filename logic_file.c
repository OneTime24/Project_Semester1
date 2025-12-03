#include <stdio.h>
#include <string.h>
#include <stdlib.h>
float checkPlg(char *file1, char *file2);        //prototype for text plageirism 
float checkcode(char *file1, char *fil2);           //prototype for code plageirism 
int main(){

    printf("\n");
    printf("========================================\n");
    printf("   PLAGIARISM CHECKER SYSTEM\n");
    printf("   FAST NUCES Peshawar\n");
    printf("========================================\n");

    

    while(1){
    printf("\n========================================\n");
    printf("           MAIN MENU\n");
    printf("========================================\n");
    printf("1. Text File Plagiarism Detection\n");
    printf("2. Code File Plagiarism Detection\n");
    printf("3. Exit\n");
    printf("========================================\n");

    int ch;
    printf("Select Option: ");
    scanf(" %d",&ch);
    switch(ch){
        
        case 1:
            float similarity=checkPlg("file1.txt","file2.txt");
            printf("\nsimilarity = %.2f%%\n", similarity);
            break;
        case 2:{
            printf("Code File Plagiarism Detection\n");
            float similarity=checkcode("t1.c","t2.c");
            printf("\nSimilarity: %.3f",similarity);

            // float similarity=checkCode();                               ///CODE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            break;
        }

        case 3:{
            printf("Exiting...\n");
            return 0;
        }
        }

        }

    return 0;
}

float checkPlg(char *file1, char *file2){
            float similarity = 0;

            FILE *ptr1 = fopen(file1,"r");
            if(ptr1==NULL){
                printf("file1 not opening...\n");
                return 0;
            }

            FILE *ptr2 = fopen(file2,"r");
            if(ptr2==NULL){
                printf("file2 not opening...\n");
                fclose(ptr1);
                return 0;
            }

            // getting lengths (sir told me to use fseek)
            fseek(ptr1,0,SEEK_END);
            long len1 = ftell(ptr1);
            fseek(ptr1,0,SEEK_SET);

            fseek(ptr2,0,SEEK_END);
            long len2 = ftell(ptr2);
            fseek(ptr2,0,SEEK_SET);

            // reading file 1
            char *text1 = (char*)malloc(len1+5);
            fread(text1,1,len1,ptr1);
            text1[len1] = '\0';
            fclose(ptr1);

            // reading file 2
            char *text2 = (char*)malloc(len2+5);
            fread(text2,1,len2,ptr2);
            text2[len2] = '\0';
            fclose(ptr2);

            // token arrays (idk a better way yet)
            int max1 = 100;
            char **tokens1 = malloc(max1 * sizeof(char*));
            int t1 = 0;

            char *w1 = strtok(text1," ");
            while(w1!=NULL){
                
                if(t1>=max1){          // if array full (hope this works)
                    max1 = max1 * 2;
                    tokens1 = realloc(tokens1, max1*sizeof(char*));
                }

                tokens1[t1] = malloc(strlen(w1)+1);
                strcpy(tokens1[t1], w1);
                t1++;

                w1 = strtok(NULL," ");
            }

            // token array 2
            int max2 = 100;
            char **tokens2 = malloc(max2 * sizeof(char*));
            int t2 = 0;

            char *w2 = strtok(text2," ");
            while(w2!=NULL){
                if(t2>=max2){
                    max2 = max2 * 2;
                    tokens2 = realloc(tokens2, max2*sizeof(char*));
                }

                tokens2[t2] = malloc(strlen(w2)+1);
                strcpy(tokens2[t2], w2);
                t2++;

                w2 = strtok(NULL," ");
            }

            // just printing to see if working
            printf("Tokens from file1:\n");
            for(int i=0;i<t1;i++){
                printf("%s\n", tokens1[i]);
            }

            printf("\nTokens from file2:\n");
            for(int i=0;i<t2;i++){
                printf("%s\n", tokens2[i]);
            }


            // N-GRAM PART (3 words)
            int n = 3;

            if(t1<n || t2<n){
                printf("\nNot enough words for 3-gram \n");
            }
            else{

                int ng1 = t1 - n + 1;
                char **ngram1 = malloc(ng1 * sizeof(char*));

                for(int i=0;i<ng1;i++){
                    int size = strlen(tokens1[i])+strlen(tokens1[i+1])+strlen(tokens1[i+2])+5;
                    ngram1[i] = malloc(size);
                    sprintf(ngram1[i], "%s %s %s", tokens1[i], tokens1[i+1], tokens1[i+2]);
                }

                int ng2 = t2 - n + 1;
                char **ngram2 = malloc(ng2 * sizeof(char*));

                for(int i=0;i<ng2;i++){
                    int size = strlen(tokens2[i])+strlen(tokens2[i+1])+strlen(tokens2[i+2])+5;
                    ngram2[i] = malloc(size);
                    sprintf(ngram2[i], "%s %s %s", tokens2[i], tokens2[i+1], tokens2[i+2]);
                }

                // comparing
                int match = 0;
                for(int i=0;i<ng1;i++){
                    for(int j=0;j<ng2;j++){
                        if(strcmp(ngram1[i], ngram2[j])==0){
                            match++;
                            break;
                        }
                    }
                }

                similarity = ((float)match/ng1)*100;
                

                // freeing ngrams
                for(int i=0;i<ng1;i++) free(ngram1[i]);
                free(ngram1);

                for(int i=0;i<ng2;i++) free(ngram2[i]);
                free(ngram2);
                

            }

            // freeing tokens
            for(int i=0;i<t1;i++)
                free(tokens1[i]);
            free(tokens1);

            for(int i=0;i<t2;i++)
                free(tokens2[i]);
            free(tokens2);

            free(text1);
            free(text2);
            return similarity;

        }

float checkcode(char *file1, char *file2){                                  //CODE!!!!!!!!!!!!!!!!!!!!!
            float similarity = 0;

            FILE *ptr1 = fopen(file1,"r");
            if(ptr1==NULL){
                printf("file1 not opening...\n");
                return 0;
            }

            FILE *ptr2 = fopen(file2,"r");
            if(ptr2==NULL){
                printf("file2 not opening...\n");
                fclose(ptr1);
                return 0;
            }

            // getting lengths (sir told me to use fseek)
            fseek(ptr1,0,SEEK_END);
            long len1 = ftell(ptr1);
            fseek(ptr1,0,SEEK_SET);

            fseek(ptr2,0,SEEK_END);
            long len2 = ftell(ptr2);
            fseek(ptr2,0,SEEK_SET);

            // reading file 1
            char *text1 = (char*)malloc(len1+5);
            fread(text1,1,len1,ptr1);
            text1[len1] = '\0';
            fclose(ptr1);

            // reading file 2
            char *text2 = (char*)malloc(len2+5);
            fread(text2,1,len2,ptr2);
            text2[len2] = '\0';
            fclose(ptr2);

            // token arrays (idk a better way yet)
            int max1 = 100;
            char **tokens1 = malloc(max1 * sizeof(char*));
            int t1 = 0;

            char *w1 = strtok(text1," ");
            while(w1!=NULL){
                
                if(t1>=max1){          // if array full (hope this works)
                    max1 = max1 * 2;
                    tokens1 = realloc(tokens1, max1*sizeof(char*));
                }

                tokens1[t1] = malloc(strlen(w1)+1);
                strcpy(tokens1[t1], w1);
                t1++;

                w1 = strtok(NULL," ");
            }

            // token array 2
            int max2 = 100;
            char **tokens2 = malloc(max2 * sizeof(char*));
            int t2 = 0;

            char *w2 = strtok(text2," ");
            while(w2!=NULL){
                if(t2>=max2){
                    max2 = max2 * 2;
                    tokens2 = realloc(tokens2, max2*sizeof(char*));
                }

                tokens2[t2] = malloc(strlen(w2)+1);
                strcpy(tokens2[t2], w2);
                t2++;

                w2 = strtok(NULL," ");
            }

            // just printing to see if working
            printf("Tokens from file1:\n");
            for(int i=0;i<t1;i++){
                printf("%s\n", tokens1[i]);
            }

            printf("\nTokens from file2:\n");
            for(int i=0;i<t2;i++){
                printf("%s\n", tokens2[i]);
            }


            // N-GRAM PART (3 words)
            int n = 3;

            if(t1<n || t2<n){
                printf("\nNot enough words for 3-gram \n");
            }
            else{

                int ng1 = t1 - n + 1;
                char **ngram1 = malloc(ng1 * sizeof(char*));

                for(int i=0;i<ng1;i++){
                    int size = strlen(tokens1[i])+strlen(tokens1[i+1])+strlen(tokens1[i+2])+5;
                    ngram1[i] = malloc(size);
                    sprintf(ngram1[i], "%s %s %s", tokens1[i], tokens1[i+1], tokens1[i+2]);
                }

                int ng2 = t2 - n + 1;
                char **ngram2 = malloc(ng2 * sizeof(char*));

                for(int i=0;i<ng2;i++){
                    int size = strlen(tokens2[i])+strlen(tokens2[i+1])+strlen(tokens2[i+2])+5;
                    ngram2[i] = malloc(size);
                    sprintf(ngram2[i], "%s %s %s", tokens2[i], tokens2[i+1], tokens2[i+2]);
                }

                // comparing
                int match = 0;
                for(int i=0;i<ng1;i++){
                    for(int j=0;j<ng2;j++){
                        if(strcmp(ngram1[i], ngram2[j])==0){
                            match++;
                            break;
                        }
                    }
                }

                similarity = ((float)match/ng1)*100;
                

                // freeing ngrams
                for(int i=0;i<ng1;i++) free(ngram1[i]);
                free(ngram1);

                for(int i=0;i<ng2;i++) free(ngram2[i]);
                free(ngram2);
                

            }

            // freeing tokens
            for(int i=0;i<t1;i++)
                free(tokens1[i]);
            free(tokens1);

            for(int i=0;i<t2;i++)
                free(tokens2[i]);
            free(tokens2);

            free(text1);
            free(text2);
            return similarity;

        }
