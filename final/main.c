#include "plagiarism.h"

// Define the global variable here
FILE *report_file = NULL;

int main() {
    
    printf("\n========================================\n");
    printf("   PLAGIARISM CHECKER SYSTEM\n");
    printf("   FAST NUCES Peshawar\n");
    printf("========================================\n");
    
    while (1) {
        printf("\n========================================\n");
        printf("           MAIN MENU\n");
        printf("========================================\n");
        printf("1. Text File Plagiarism Detection\n");
        printf("2. Code File Plagiarism Detection\n");
        printf("3. Exit\n");
        printf("========================================\n");
        
        int ch;
        printf("Select Option: ");
        scanf("%d", &ch);
        
        if (ch == 1) {
            int n;
            printf("Enter number of text files (2-20): ");
            printf("(supports .txt .pdf .docx)\n");
            scanf("%d", &n);
            
            if (n < 2 || n > 20) {
                printf("Invalid number of files.\n");
                continue;
            }
            
            char filenames[20][100];
            int i;
            for (i = 0; i < n; i++) {
                printf("Enter filename %d: ", i + 1);
                scanf("%s", filenames[i]);
            }
            
            // open report file
            report_file = fopen("plagiarism_report.txt", "a");
            if(report_file != NULL) {
                fprintf(report_file, "========================================\n");
                fprintf(report_file, "   PLAGIARISM DETECTION REPORT\n");
                fprintf(report_file, "   Text File Analysis\n");
                fprintf(report_file, "========================================\n\n");
            }
            
            char *raw[20];
            int files_loaded = 0;
            for (i = 0; i < n; i++) {
                raw[i] = readFile(filenames[i]);
                if (raw[i] == NULL) {
                    printf("Error reading %s\n", filenames[i]);
                    // free already loaded files
                    int k;
                    for (k = 0; k < i; k++) free(raw[k]);
                    files_loaded = -1;
                    break;
                }
            }
            
            if(files_loaded == -1) {
                if(report_file != NULL) fclose(report_file);
                continue;
            }
            
            char pre1[20][5000];
            for (i = 0; i < n; i++) {
                preprocessText(raw[i], pre1[i]);
            }
            
            // comparing all files
            for (i = 0; i < n; i++) {
                int j;
                for (j = i + 1; j < n; j++) {
                    printf("\n--- Comparing %s and %s ---\n", filenames[i], filenames[j]);
                    
                    // write to report
                    if(report_file != NULL) {
                        fprintf(report_file, "Comparing: %s vs %s\n", filenames[i], filenames[j]);
                        fprintf(report_file, "Matched 3-word phrases:\n");
                    }
                    
                    // pass copies to checkPlgText
                    char copy1[5000], copy2[5000];
                    strcpy(copy1, pre1[i]);
                    strcpy(copy2, pre1[j]);
                    
                    float sim = checkPlgText(copy1, copy2);
                    printf("Similarity = %.2f%%\n", sim);
                    
                    // write summary
                    if(report_file != NULL) {
                        fprintf(report_file, "\nSimilarity Score: %.2f%%\n", sim);
                        fprintf(report_file, "========================================\n\n");
                    }
                }
            }
            
            for (i = 0; i < n; i++) free(raw[i]);
            
            // close report
            if(report_file != NULL) {
                fclose(report_file);
                report_file = NULL;
                printf("\nReport saved to: plagiarism_report.txt\n");
            }
        }
        
        else if (ch == 2) {
            int n;
            printf("Enter number of code files (2-20): ");
            scanf("%d", &n);
            
            if (n < 2 || n > 20) {
                printf("Invalid number of files.\n");
                continue;
            }
            
            char filenames[20][100];
            int i;
            for (i = 0; i < n; i++) {
                printf("Enter code filename %d: ", i + 1);
                scanf("%s", filenames[i]);
            }
            
            // open report file
            report_file = fopen("code_plagiarism_report.txt", "a");
            if(report_file != NULL) {
                fprintf(report_file, "========================================\n");
                fprintf(report_file, "   PLAGIARISM DETECTION REPORT\n");
                fprintf(report_file, "   Code File Analysis\n");
                fprintf(report_file, "========================================\n\n");
            }
            
            char *raw[20];
            int files_loaded = 0;
            for (i = 0; i < n; i++) {
                raw[i] = readFile(filenames[i]);
                if (raw[i] == NULL) {
                    printf("Error reading %s\n", filenames[i]);
                    int k;
                    for (k = 0; k < i; k++) free(raw[k]);
                    files_loaded = -1;
                    break;
                }
            }
            
            if(files_loaded == -1) {
                if(report_file != NULL) fclose(report_file);
                continue;
            }
            
            char step[20][5000], final[20][5000];
            for (i = 0; i < n; i++) {
                removeCommentsAndHeaders(raw[i], step[i]);
                removeKeywords(step[i], final[i]);
            }
            
            for (i = 0; i < n; i++) {
                int j;
                for (j = i + 1; j < n; j++) {
                    printf("\n----- COMPARING %s and %s -----\n", filenames[i], filenames[j]);
                    
                    // write to report
                    if(report_file != NULL) {
                        fprintf(report_file, "Comparing: %s vs %s\n", filenames[i], filenames[j]);
                        fprintf(report_file, "Matched tokens:\n");
                    }
                    
                    // pass copies because sim_chek uses strtok which destroys strings
                    char copy_final1[5000], copy_final2[5000];
                    strcpy(copy_final1, final[i]);
                    strcpy(copy_final2, final[j]);
                    
                    sim_chek(copy_final1, copy_final2);
                }
            }
            
            for (i = 0; i < n; i++) free(raw[i]);
            
            // close report
            if(report_file != NULL) {
                fclose(report_file);
                report_file = NULL;
                printf("\nReport saved to: code_plagiarism_report.txt\n");
            }
        }
        
        else if (ch == 3) {
            printf("Exiting...\n");
            break;
        }
        
        else {
            printf("Invalid option! Try again.\n");
        }
    }
    
    return 0;
}