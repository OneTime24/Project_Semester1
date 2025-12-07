#ifndef PLAGIARISM_H
#define PLAGIARISM_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Tell all files that this variable exists somewhere (defined in main.c)
extern FILE *report_file;

// --- Prototypes from input.c ---
void extractTextFromPDF(const char *filename, const char *output);
void convertToText(const char *src, const char *out);
char* readFile(char *filename);

// --- Prototypes from logic.c ---
void preprocessText(char *src, char *dest);
float checkPlgText(char *txt1, char *txt2);
void removeCommentsAndHeaders(char *src, char *dest);
int isKeyword(char *word);
void removeKeywords(char *src, char *dest);
void sim_chek(char *s1, char *s2);

#endif