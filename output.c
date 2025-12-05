#include <stdio.h>
#include <string.h>

// ---------------- MENU FUNCTION ----------------
void display_menu()
{
    printf("\n========================================\n");
    printf("     PLAGIARISM CHECKER MENU\n");
    printf("========================================\n");
    printf("1. Check Text Files\n");
    printf("2. Check Code Files\n");
    printf("3. Exit\n");
    printf("========================================\n");
}

// ---------------- REPORT HEADER ----------------
void create_report_header()
{
    FILE *fp = fopen("report.txt", "w");  
    if (fp == NULL) {
        printf("Error creating report file!\n");
        return;
    }
    
    fprintf(fp, "================================================================\n");
    fprintf(fp, "              PLAGIARISM DETECTION REPORT\n");
    fprintf(fp, "================================================================\n");
    fprintf(fp, "================================================================\n\n");
    
    // Table 
    fprintf(fp, "+-------------------+-------------------+--------------+\n");
    fprintf(fp, "| File 1            | File 2            | Similarity %% |\n");
    fprintf(fp, "+-------------------+-------------------+--------------+\n");
    
    fclose(fp);
    printf(" Report file created successfully!\n");
}

// ---------------- COMPARISON ----------------
void write_comparison(char file1[], char file2[], float similarity)
{
    FILE *fp = fopen("report.txt", "a");  // append mode
    if (fp == NULL) {
        printf("Error opening report file!\n");
        return;
    }
    
    // Write comparison row in table format
    fprintf(fp, "| %-17s | %-17s | %11.2f%% |\n", file1, file2, similarity);
    
    fclose(fp);
}

// ---------------- MATCHING CONTENT DETAILS ----------------
void write_matching_details(float similarity, char similar[])
{
    FILE *fp = fopen("report.txt", "a");
    if (fp == NULL) {
        printf("Error opening report file!\n");
        return;
    }
    
    fprintf(fp, "+-------------------+-------------------+--------------+\n");
    fprintf(fp, "\n");
    fprintf(fp, "   Similarity Score: %.2f%%\n", similarity);
    fprintf(fp, "   Common Content:\n");
    fprintf(fp, "    \"%s\"\n\n", similar);
    fprintf(fp, "----------------------------------------------------------------\n\n");
    
    fclose(fp);
    printf(" Details added to report!\n");
}

// CLOSE REPORT  
void close_report()
{
    FILE *fp = fopen("report.txt", "a");
    if (fp == NULL) {
        printf("Error opening report file!\n");
        return;
    }
    
    fprintf(fp, "\n================================================================\n");
    fprintf(fp, "                    END OF REPORT\n");
    fprintf(fp, "================================================================\n");
    
    fclose(fp);
    printf(" Report finalized!\n");
}

// ---------------- MAIN FUNCTION ----------------
int main()
{
    
    create_report_header();
    
    
    write_comparison("file.txt", "file2.txt", 75.50);
    write_matching_details(75.50, "hello, this line is common in file 1 and file 2");
    
    write_comparison("file.txt", "file2.txt", 60.30);
    write_matching_details(60.30, "another matching section found here");
    
    write_comparison("project2.c", "project.c", 60.30);
    write_matching_details(60.30, "int main() { return 0; }");
    
    write_comparison("project2.c", "project.c", 60.30);
    write_matching_details(60.30, "printf statements are similar");
    
    
    close_report();
    
    printf("\n Full report saved in report.txt\n");
    
    return 0;
}