%{
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

extern FILE *yyin;
char target_word[100];
int word_count = 0;
%}

%%
[a-zA-Z]+ {
    if (strcasecmp(yytext, target_word) == 0) {
        word_count++;
    }
}
.|\n   { /* ignore other characters */ }
%%

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <filename> <word>\n", argv[0]);
        return 1;
    }

    strncpy(target_word, argv[2], sizeof(target_word) - 1);
    target_word[sizeof(target_word) - 1] = '\0';

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error opening file");
        return 1;
    }

    yylex();

    printf("The word '%s' appears %d times in the file.\n", target_word, word_count);

    fclose(yyin);
    return 0;
}
