#include "plagiarism.h"
FILE *fp_rep = NULL;
int main() {
    printf("\n--- PLAGIARISM CHECKER ---\n");
    printf("--- FAST NUCES Peshawar ---\n\n");
    
    while (1) {
        printf("1. Check Text Files\n");
        printf("2. Check Code Files\n");
        printf("3. Exit\n");
        printf("Choice: ");
        
        int opt;

        scanf("%d", &opt);
        
        if (opt == 1) {
            int n;

            printf("How many files? (2-20): ");

            scanf("%d", &n);
            
            if (n<2 || n>20) {

                printf("Number of Files Must be in between 2 - 20.\n");

                continue;
            }
            
            char fnames[20][200];
            for (int i=0;i<n;i++) {
                printf("File %d name: ",i + 1);
                scanf(" %s", fnames[i]);
            }


            // To open and conversion of file formats
            
            fp_rep = fopen("report.txt", "a");
            if(fp_rep==NULL){
                printf("FAILED TO OPEN FILE: ");
                continue;
            }
            if (fp_rep){ 
                fprintf(fp_rep, "\n--- NEW TEXT ANALYSIS ---\n");
            }
            char *data[20];
            int err = 0;
            
            for (int i=0; i<n; i++) {
                data[i] = read_f(fnames[i]);
                if (data[i]== NULL) {
                    printf("Failed to read %s\n", fnames[i]);
                    err =1;
                }
            }
            
            if (!err) {
                char processed[20][5000];
                for (int i=0; i<n; i++) {
                    clean_str(data[i], processed[i]);
                }
                
                for (int i=0; i<n; i++) {
                    for (int j=i+1;j<n;j++) {
                        printf("\nChecking %s vs %s...\n", fnames[i], fnames[j]);
                        
                        if (fp_rep){
                         fprintf(fp_rep, "File: %s vs %s\n", fnames[i], fnames[j]);
                        }
                        float res = compare_txt(processed[i], processed[j]);
                        printf("Result: %.2f%%\n", res);
                        
                        if (fp_rep)
                             fprintf(fp_rep, "Score: %.2f%%\n", res);
                    }
                }
                
                // free memory
                for (int i = 0; i < n; i++) 
                    free(data[i]);
            }
            
            if (fp_rep) {
                fclose(fp_rep);
                printf("Saved to report.txt\n");
            }
        }
        
        else if (opt==2) {
            int n;
            printf("Number of code files (2-20): ");
            scanf("%d", &n);
            
            char fnames[20][200];
            for (int i=0; i<n; i++) {
                printf("Code file %d: ", i+1);
                scanf("%s", fnames[i]);
            }
            
            fp_rep = fopen("code_report.txt", "a");
            if (fp_rep){ 
                fprintf(fp_rep, "\n--- NEW CODE ANALYSIS ---\n");
        }
            char *data[20];
            int err = 0;
            
            for (int i=0; i<n; i++) {
                data[i] = read_f(fnames[i]);
                if (!data[i]) {
                    printf("Error reading %s\n", fnames[i]);
                    err = 1;
                }
            }
            
            if (!err) {
                char temp[20][5000];
                char final[20][5000];
                
                for (int i=0; i<n; i++) {
                    rem_cmt(data[i], temp[i]);
                    rem_key(temp[i], final[i]);
                }
                
                for (int i = 0; i < n; i++) {
                    for (int j = i + 1; j < n; j++) {
                        printf("\nComparing %s and %s\n", fnames[i], fnames[j]);
                        if(fp_rep) 
                            fprintf(fp_rep, "Files: %s - %s\n", fnames[i], fnames[j]);
                        
                        code_sim(final[i], final[j]);
                    }
                }
                for(int i=0; i<n; i++) 
                    free(data[i]);
            }
            
            if (fp_rep)
                fclose(fp_rep);
        }
        
        else if (opt == 3) {
            printf("\n-----------EXITING THE PROGRAM BYE-----------");
            break;
        }
    }
    return 0;
}