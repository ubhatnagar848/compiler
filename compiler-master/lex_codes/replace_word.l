%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern FILE *yyin;

char old_word[100];
char new_word[100];
%}

%%

[a-zA-Z]+ {
    if (strcasecmp(yytext, old_word) == 0) {
        printf("%s", new_word);
    } else {
        printf("%s", yytext);
    }
}

.|\n {
    printf("%s", yytext);
}

%%

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <filename> <old_word> <new_word>\n", argv[0]);
        return 1;
    }

    strcpy(old_word, argv[2]);
    strcpy(new_word, argv[3]);

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error opening file");
        return 1;
    }

    yylex();

    fclose(yyin);
    return 0;
}
