#include <stdio.h>

// ---------------- MENU FUNCTION ----------------
void report(float percent, char* similar){
	FILE *ptr=fopen("report.txt","a");
	
	fprintf(ptr,"SIMILARIT: %f",percent);
	fprintf(ptr,"WORDS: %s",similar);
}


void display_menu()
{
    printf("\n   PLAGIARISM CHECKER MENU\n");
    printf("1. Check Text Files\n");
    printf("2. Check Code Files\n");
    printf("3. Exit\n");
}

// ---------------- REPORT FUNCTION ----------------
void write_report(char file1[], char file2[], float similarity)
{
    FILE *fp = fopen("report.txt", "a");  // open/create file in append mode

    if (fp == NULL) {
        printf("Error opening report file!\n");
        return;
    }

    fprintf(fp, "---------------------------------------------------------------\n");
    fprintf(fp, "| %-15s | %-15s | %-10.2f |\n", file1, file2, similarity);
    fprintf(fp, "---------------------------------------------------------------\n");

    fclose(fp);  // close file
    printf("? Report saved successfully in report.txt\n");
}

// ---------------- MAIN FUNCTION ----------------
int main()
{
 
 	
//    display_menu();  // show menu
//
//    int choice;
//    printf("Enter your choice: ");
//    scanf("%d", &choice);
//
//    printf("You selected: %d\n", choice);
//
//    if (choice == 1)
//    {
//        // For text files
//        char f1[50], f2[50];
//
//        printf("Enter first text file name: ");
//        scanf("%s", f1);
//
//        printf("Enter second text file name: ");
//        scanf("%s", f2);
//
        float sim = 75.5;   // dummy similarity (replace later)
		char similar[1000]="hello, this line is common in file 1 and file 2";
		
		report(sim,similar);
//		////        write_report(f1, f2, sim);
//		report(sim,similar);
//    }
//    else if (choice == 2)
//    {
//        // For code files
//        char f1[50], f2[50];
//
//        printf("Enter first code file name: ");
//        scanf("%s", f1);
//
//        printf("Enter second code file name: ");
//        scanf("%s", f2);
//
//        float sim = 60.3;   // dummy similarity (replace later)
//
//        write_report(f1, f2, sim);
//    }
//    else if (choice == 3)
//    {
//        printf("Exiting program...\n");
//    }
//    else
//    {
//        printf("Invalid choice! Try again.\n");
//    }

    return 0;
}
