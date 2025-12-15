#include "plagiarism.h"

// check if file is ok
int check_f(const char *fn) {
    FILE *f = fopen(fn, "r");
    if (!f){ 
    return 0;
    }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fclose(f);
    if (sz>0){
    return 1;
    }
    return 0;
}

// convert pdf or docx
void to_txt(const char *s, const char *d) {
    char cmd[512];
    int ret = -1;

    // simple check for extension
    if (strstr(s, ".pdf")) {
        // command to run pdftotext
        #ifdef _WIN32
            sprintf(cmd, "pdftotext \"%s\" \"%s\" > NUL 2>&1", s, d);
        #else
            sprintf(cmd, "pdftotext \"%s\" \"%s\" > /dev/null 2>&1", s, d);
        #endif
        
        ret = system(cmd);
        
        if (ret != 0 || !check_f(d)) {
            printf("Error: PDF convert fail for %s\n", s);
        }
    }
    else if (strstr(s, ".docx")) {
        #ifdef _WIN32
            sprintf(cmd, "docx2txt \"%s\" \"%s\" > NUL 2>&1", s, d);
        #else
            sprintf(cmd, "docx2txt < \"%s\" > \"%s\" 2> /dev/null", s, d);
        #endif

        ret = system(cmd);
        
        if (ret != 0 || !check_f(d)) {
             printf("Error: DOCX convert fail for %s\n", s);
        }
    }
}

// main read function
char* read_f(char *fname) {
    char tmp[] = "temp_conv.txt";
    char *target = fname;
    int conv = 0;

    // check if we need conversion
    if (strstr(fname, ".pdf") || strstr(fname, ".docx")) {
        remove(tmp); // delete old temp
        to_txt(fname, tmp);
        
        if (check_f(tmp)) {
            target = tmp;
            conv = 1;
        } else {
            return NULL; 
        }
    }
    
    FILE *fp = fopen(target, "r");
    if (!fp) {
        printf("Cannot open %s\n", target);
        return NULL;
    }
    
    fseek(fp, 0, SEEK_END);
    long l = ftell(fp);
    rewind(fp);
    
    // simple malloc, no extensive error check
    char *buf = (char*)malloc(l + 10);
    fread(buf, 1, l, fp);
    buf[l] = '\0';
    
    fclose(fp);
    
    if (conv) {
        remove(tmp);
    }
    
    return buf;
}