#include "plagiarism.h"

// simple pdf to text converter (fallback if pdftotext not available)
void extractTextFromPDF(const char *filename, const char *output) {
    FILE *pdf = fopen(filename, "rb");
    FILE *txt = fopen(output, "w");
    
    if (!pdf || !txt) {
        printf("Error: Cannot process PDF file\n");
        if(pdf) fclose(pdf);
        if(txt) fclose(txt);
        return;
        
    }
    
    // simple text extraction - just get readable characters
    int c;
    int space_added = 0;
    while ((c = fgetc(pdf)) != EOF) {
        if (isprint(c) && c != '\r') {
            fprintf(txt, "%c", c);
            space_added = 0;
        } else if (!space_added && c != '\r') {
            fprintf(txt, " ");
            space_added = 1;
        }
    }
    
    fclose(pdf);
    fclose(txt);
}

// converts pdf/docx to text file
void convertToText(const char *src, const char *out) {
    if (strstr(src, ".pdf")) {
        // try pdftotext first, if fails use fallback
        char cmd[200];
        sprintf(cmd, "pdftotext \"%s\" \"%s\" 2>/dev/null", src, out);
        int result = system(cmd);
        
        if (result != 0) {
            // pdftotext not available, use basic extraction
            printf("Note: Using basic PDF text extraction\n");
            extractTextFromPDF(src, out);
    
        }
    }
    else if (strstr(src, ".docx")) {
        char cmd[200];
        sprintf(cmd, "docx2txt \"%s\" \"%s\" 2>/dev/null", src, out);
        int result = system(cmd);
        
        if (result != 0) {
            printf("Warning: docx2txt not installed, trying to read as text\n");
        }
    }
}

// reads file and handles pdf/docx conversion
char* readFile(char *filename) {
    char tempFile[] = "temp_converted.txt";
    char *actualFile = filename;
    
    // if pdf or docx, convert it first
    if (strstr(filename, ".pdf") || strstr(filename, ".docx")) {
        convertToText(filename, tempFile);
        actualFile = tempFile;
    }
    
    FILE *fp = fopen(actualFile, "r");
    
    if (!fp) {
        printf("cant open file %s\n", filename);
        return NULL;
    }
    
    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    char *text = (char*)malloc(len + 10);
    fread(text, 1, len, fp);
    text[len] = '\0';
    
    fclose(fp);
    return text;
}