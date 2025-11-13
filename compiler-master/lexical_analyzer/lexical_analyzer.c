#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isKw(const char *w) {
    const char *kws[] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "union", "unsigned", "void", "volatile", "while", "bool"
    };
    int n = sizeof(kws) / sizeof(kws[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(w, kws[i]) == 0) return 1;
    }
    return 0;
}

int isOp(char c) {
    char ops[] = "+-*/=&|<>!^~";
    for (int i = 0; ops[i] != '\0'; i++) {
        if (c == ops[i]) return 1;
    }
    return 0;
}

int isPunc(char c) {
    char puncs[] = ",;:(){}[]";
    for (int i = 0; puncs[i] != '\0'; i++) {
        if (c == puncs[i]) return 1;
    }
    return 0;
}

void idOrKw(char s[], int *i) {
    char t[100];
    int j = 0;
    while (isalnum((unsigned char)s[*i]) || s[*i] == '_') {
        t[j++] = s[(*i)++];
    }
    t[j] = '\0';
    printf(isKw(t) ? "KEYWORD: %s\n" : "IDENTIFIER: %s\n", t);
}

void num(char s[], int *i) {
    char t[100];
    int j = 0, d = 0;
    while (isdigit((unsigned char)s[*i]) || (s[*i] == '.' && !d && isdigit((unsigned char)s[*i + 1]))) {
        if (s[*i] == '.') d = 1;
        t[j++] = s[(*i)++];
    }
    t[j] = '\0';
    printf("CONSTANT: %s\n", t);
}

void str(char s[], int *i) {
    char t[100];
    int j = 0;
    t[j++] = s[(*i)++]; 

    while (s[*i] != '"' && s[*i] != '\0') {
        t[j++] = s[(*i)++];
    }
    if (s[*i] == '"') t[j++] = s[(*i)++];

    t[j] = '\0';
    printf("STRING: %s\n", t);
}

void op(char s[], int *i) {
    char t[3] = {0};
    int j = 0;
    t[j++] = s[(*i)++];

    if ((t[0] == '+' && s[*i] == '+') ||
        (t[0] == '-' && s[*i] == '-') ||
        (t[0] == '=' && s[*i] == '=') ||
        (t[0] == '!' && s[*i] == '=') ||
        (t[0] == '<' && s[*i] == '=') ||
        (t[0] == '>' && s[*i] == '=') ||
        (t[0] == '&' && s[*i] == '&') ||
        (t[0] == '|' && s[*i] == '|')) {
        t[j++] = s[(*i)++];
    }
    
    const char *type = "UNKNOWN";
    if (strcmp(t, "+") == 0 || strcmp(t, "-") == 0 || strcmp(t, "*") == 0 || strcmp(t, "/") == 0) {
        type = "ARITHMETIC";
    } else if (strcmp(t, "++") == 0 || strcmp(t, "--") == 0) {
        type = "INCREMENT/DECREMENT";
    } else if (strcmp(t, "=") == 0) {
        type = "ASSIGNMENT";
    } else if (strcmp(t, "==") == 0 || strcmp(t, "!=") == 0 || strcmp(t, "<") == 0 || 
               strcmp(t, ">") == 0 || strcmp(t, "<=") == 0 || strcmp(t, ">=") == 0) {
        type = "RELATIONAL";
    } else if (strcmp(t, "&&") == 0 || strcmp(t, "||") == 0 || strcmp(t, "!") == 0) {
        type = "LOGICAL";
    } else if (strcmp(t, "&") == 0 || strcmp(t, "|") == 0 || strcmp(t, "^") == 0 || strcmp(t, "~") == 0) {
        type = "BITWISE";
    }
    
    printf("OPERATOR: %s (Type: %s)\n", t, type);
}

void punc(char s[], int *i) {
    printf("PUNCTUATOR: %c\n", s[(*i)++]);
}

int main() {
    char s[1000];
    int i = 0;
    printf("Enter statement: ");
    if (!fgets(s, sizeof(s), stdin)) return 0;

    while (s[i] != '\0') {
        if (isspace((unsigned char)s[i])) { i++; continue; }

        if (s[i] == '"') { str(s, &i); continue; }
        if (isalpha((unsigned char)s[i]) || s[i] == '_') { idOrKw(s, &i); continue; }
        if (isdigit((unsigned char)s[i]) || (s[i] == '.' && isdigit((unsigned char)s[i + 1]))) { num(s, &i); continue; }
        if (isOp(s[i])) { op(s, &i); continue; }
        if (isPunc(s[i])) { punc(s, &i); continue; }

        i++;
    }
    return 0;
}