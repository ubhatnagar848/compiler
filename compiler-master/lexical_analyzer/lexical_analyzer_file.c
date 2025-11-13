#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isKw(char *w) {
    char *kws[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "register", "return", "short", "signed", "sizeof",
        "static", "struct", "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while", "bool"
    };
    int n = sizeof(kws) / sizeof(kws[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(w, kws[i]) == 0)
            return 1;
    }
    return 0;
}

int isOp(char c) {
    char ops[] = "+-*/=%&|<>!^~";
    for (int i = 0; i < strlen(ops); i++) {
        if (c == ops[i])
            return 1;
    }
    return 0;
}

const char* opType(char c) {
    switch (c) {
        case '+': case '-': case '*': case '/': case '%':
            return "Arithmetic";
        case '=':
            return "Assignment";
        case '<': case '>':
            return "Relational";
        case '!': case '&': case '|':
            return "Logical";
        case '^': case '~':
            return "Bitwise";
        default:
            return "Unknown";
    }
}

int isPunc(char c) {
    char puncs[] = ",;:(){}[]";
    for (int i = 0; i < strlen(puncs); i++) {
        if (c == puncs[i])
            return 1;
    }
    return 0;
}

void idOrKw(char s[], int *i) {
    char t[100];
    int j = 0;
    while (isalnum(s[*i]) || s[*i] == '_') {
        t[j++] = s[(*i)++];
    }
    t[j] = '\0';
    printf(isKw(t) ? "KEYWORD: %s\n" : "IDENTIFIER: %s\n", t);
}

void num(char s[], int *i) {
    char t[100];
    int j = 0, d = 0;
    while (isdigit(s[*i]) || (s[*i] == '.' && !d && isdigit(s[*i + 1]))) {
        if (s[*i] == '.')
            d = 1;
        t[j++] = s[(*i)++];
    }
    t[j] = '\0';
    printf("CONSTANT: %s\n", t);
}

void str(char s[], int *i) {
    char t[500];
    int j = 0;
    t[j++] = s[(*i)++];
    while (s[*i] != '"' && s[*i] != '\0') {
        t[j++] = s[(*i)++];
    }
    if (s[*i] == '"')
        t[j++] = s[(*i)++];
    t[j] = '\0';
    printf("STRING: %s\n", t);
}

int main() {
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("Error: could not open input.txt\n");
        return 1;
    }

    char s[2000];
    size_t len = fread(s, sizeof(char), sizeof(s) - 1, f);
    s[len] = '\0';
    fclose(f);

    int i = 0;
    while (s[i] != '\0') {
        if (isspace(s[i])) {
            i++;
        } else if (isalpha(s[i]) || s[i] == '_') {
            idOrKw(s, &i);
        } else if (isdigit(s[i])) {
            num(s, &i);
        } else if (s[i] == '"') {
            str(s, &i);
        } else if (isOp(s[i])) {
            printf("%s OPERATOR: %c\n", opType(s[i]), s[i]);
            i++;
        } else if (isPunc(s[i])) {
            printf("PUNCTUATION: %c\n", s[i]);
            i++;
        } else {
            i++;
        }
    }

    return 0;
}
