%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int max_length = 0;
char longest_word[100];
%}

%%
[a-zA-Z]+ {
    int len = strlen(yytext);
    if (len > max_length) {
        max_length = len;
        strcpy(longest_word, yytext);
    }
}
.|\n { /* Ignore other characters */ }
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

    yylex();

    printf("The longest word is '%s' with length %d.\n", longest_word, max_length);

    fclose(yyin);
    return 0;
}
