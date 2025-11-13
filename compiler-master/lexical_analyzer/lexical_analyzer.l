%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// List of C keywords
char *keywords[] = {
 "auto", "break", "case", "char", "const", "continue", "default", "do",
 "double", "else", "enum", "extern", "float", "for", "goto", "if",
 "int", "long", "register", "return", "short", "signed", "sizeof",
 "static", "struct", "switch", "typedef", "union", "unsigned", "void",
 "volatile", "while"
};

int is_keyword(char *word) {
 int total_keywords = sizeof(keywords) / sizeof(keywords[0]);
 for (int i = 0; i < total_keywords; i++) {
     if (strcmp(word, keywords[i]) == 0)
         return 1;
 }
 return 0;
}

void classify_operator(char *op) {
    if (strchr("+-*/%", op[0])) printf("Arithmetic OPERATOR: %s\n", op);
    else if (strchr("=<>", op[0])) printf("Relational/Assignment OPERATOR: %s\n", op);
    else if (strchr("&|!", op[0])) printf("Logical OPERATOR: %s\n", op);
    else if (strchr("^~", op[0])) printf("Bitwise OPERATOR: %s\n", op);
    else printf("Unknown OPERATOR: %s\n", op);
}
%}

DIGIT   [0-9]
LETTER  [a-zA-Z]
ID      {LETTER}({LETTER}|{DIGIT})*
NUMBER  {DIGIT}+(\.{DIGIT}+)?([eE][+-]?{DIGIT}+)?
OPERATOR [+\-*/%=<>!&|^~]
SYMBOL  [;,.:(){}[\]]

%%

"#include"|"#define"     { printf("PREPROCESSOR: %s\n", yytext); }
{ID} {
    if (is_keyword(yytext))
        printf("KEYWORD: %s\n", yytext);
    else
        printf("IDENTIFIER: %s\n", yytext);
}
{NUMBER}                 { printf("NUMBER: %s\n", yytext); }
{OPERATOR}+              { classify_operator(yytext); }
{SYMBOL}                 { printf("SYMBOL: %s\n", yytext); }
\"([^\"\n]*)\"           { printf("STRING: %s\n", yytext); }
[ \t\n]+                 { /* Ignore whitespace */ }
.                        { printf("UNKNOWN: %s\n", yytext); }

%%

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error opening file");
        return 1;
    }

    printf("Lexical Analysis Results:\n");
    printf("=========================\n");

    yylex();
    fclose(yyin);
    return 0;
}
