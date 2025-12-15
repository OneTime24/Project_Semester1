#include "plagiarism.h"

// clean text: lowercase and remove weird chars
void clean_str(char *s, char *d) {
    int i=0,j=0;
    while (s[i]!='\0') {
        char c=s[i];
        if (c>='A'&&c<='Z'){ 
            c = c + 32; // manual tolower
        }
        if((c >='a'&&c<= 'z') ||(c>='0'&&c<= '9') || c == ' '){
            d[j++] = c;
        }else{ 
            d[j++] = ' ';
        }
        i++;
    }
    d[j] = '\0';
    
    // fix spaces
    char temp[5000]; // temp buffer
    int x=0, y=0;
    int sp=0;  
    // copying to temp first to handle spaces
    strcpy(temp, d);
    
    while (temp[x]!='\0') {
        if (temp[x]!=' ') {
            d[y++] = temp[x];
            sp = 0;
        } else {
            if (sp == 0) {
                d[y++] = ' ';
                sp = 1;
            }
        }
        x++;
    }
    if (y>0 && d[y-1] == ' ') 
    {
        y--;
    }
    d[y] = '\0';
}

// text compare logic
float compare_txt(char *t1, char *t2) {
    // duplicating strings so strtok doesn't mess up original
    char *c1 = strdup(t1);
    char *c2 = strdup(t2);
    
    char *toks1[2000]; // fixed array is simpler for students
    int cnt1 = 0;
    


    char *p = strtok(c1, " ");
    while (p != NULL && cnt1 < 2000) {
        toks1[cnt1++] = p;
        p = strtok(NULL, " ");
    }
    
    char *toks2[2000];
    int cnt2 = 0;
    
    p = strtok(c2, " ");
    while (p != NULL && cnt2 < 2000) {
        toks2[cnt2++] = p;
        p = strtok(NULL, " ");
    }
    
    // 3-gram logic
    int n=3;
    float ans=0;
    
    if (cnt1>=n && cnt2>=n) {
        int g1 = cnt1-n+1;
        int g2 = cnt2-n+1;
        
        int match = 0;
        int used[2000] = {0}; // to mark matches
        
        for (int i=0; i<g1; i++) {
            // build phrase 1
            char ph1[100]; 
            sprintf(ph1, "%s %s %s", toks1[i], toks1[i+1], toks1[i+2]);
            
            for (int j=0; j<g2; j++) {
                if (used[j])      
                    continue;

                char ph2[100];
                sprintf(ph2, "%s %s %s", toks2[j], toks2[j+1], toks2[j+2]);
                
                if (strcmp(ph1, ph2) == 0) {
                    match++;
                    used[j] = 1;
                    if(fp_rep) 
                        fprintf(fp_rep, "  Found: \"%s\"\n", ph1);
                    break;
                }
            }
        }
        
        // formula
        ans = (2.0 * match) / (g1 + g2) * 100.0;
    }
    
    free(c1);
    free(c2);
    return ans;
}

// remove comments
void rem_cmt(char *s, char *d) {
    int i = 0, k = 0;
    while (s[i]) {
        if (s[i]=='/' && s[i+1] =='/') { // line comment
            while(s[i]!='\n'&&s[i]!='\0') 
                i++;
        }
        else if (s[i] == '/' && s[i+1] == '*') { // block comment
            i += 2;
            while (!(s[i] == '*' && s[i+1] == '/') && s[i]) 
                i++;
            if (s[i]) 
                i += 2;
        }
        else if (s[i] == '#') { // include header
            while (s[i] != '\n' && s[i] != '\0') 
                i++;
        }
        else {
            d[k++] = s[i++];
        }
    }
    d[k] = '\0';
}

// manual check instead of loop looks more natural for beginners
int is_key(char *w) {
    if (strcmp(w, "int") == 0 || strcmp(w, "float") == 0 || strcmp(w, "double") == 0 || 
        strcmp(w, "char") == 0 || strcmp(w, "void") == 0 || strcmp(w, "if") == 0 || 
        strcmp(w, "else") == 0 || strcmp(w, "while") == 0 || strcmp(w, "for") == 0 || 
        strcmp(w, "return") == 0) {
        return 1;
    }
    return 0;
}

void rem_key(char *s, char *d) {
    int i=0, j=0;
    char temp[100];
    int t = 0;
    
    while (s[i] != '\0') {
        if (isalpha(s[i])) {
            temp[t++] = s[i];
        } else {
            temp[t] = '\0';
            if (t > 0 && !is_key(temp)) {
                // copy word if not keyword
                for (int x = 0; x < t; x++) 
                    d[j++] = temp[x];
            }
            t = 0;
            d[j++] = s[i];
        }
        i++;
    }
    d[j] = '\0';
}

// code similarity
void code_sim(char *s1, char *s2) {
    char *c1 = strdup(s1);
    char *c2 = strdup(s2);
    
    char *list1[1000], *list2[1000];
    int n1 = 0, n2 = 0;
    
    char *t = strtok(c1, " \n\t(){};,"); // extra delimiters
    while (t && n1 < 1000) {
        if (strlen(t) > 0)
            list1[n1++] = t;
        t = strtok(NULL, " \n\t(){};,");
    }
    
    t = strtok(c2, " \n\t(){};,");
    while (t && n2 < 1000) {
        if (strlen(t) > 0)
            list2[n2++] = t;
        t = strtok(NULL, " \n\t(){};,");
    }
    
    if (n1 == 0 || n2 == 0) {
        printf("No code tokens.\n");
        free(c1);
        free(c2);
        return;
    }
    
    int matched[1000] = {0};
    int m = 0;
    
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (!matched[j] && strcmp(list1[i], list2[j]) == 0) {
                if(fp_rep) 
                fprintf(fp_rep, "  Match: %s\n", list1[i]);
                matched[j] = 1;
                m++;
                break;
            }
        }
    }
    
    float res = (2.0 * m) / (n1 + n2) * 100.0;
    
    printf("Matches: %d\n", m);
    printf("Similarity: %.2f%%\n", res);
    
    if (fp_rep) {
        fprintf(fp_rep, "\nTotal Matches: %d\nSimilarity: %.2f%%\n", m, res);
        fprintf(fp_rep, "--------------------------------\n");
    }
    
    free(c1);
    free(c2);
}
