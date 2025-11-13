/* three_addr.y: Yacc parser for 3-Address Code Generation */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(char *);
int temp_count = 0;

char* new_temp() {
    char* temp = (char*)malloc(sizeof(char)*4);
    sprintf(temp, "t%d", temp_count++);
    return temp;
}
%}

/* --- Yacc Declarations --- */
%union {
    char* str;
}

%token <str> ID NUM
%type <str> stmt expr term factor

%left '+' '-'
%left '*' '/'

%%
/* --- CORRECTED GRAMMAR RULES --- */

program:
    /* A program can be empty or a list of statements */
    | stmt_list
    ;

stmt_list:
    stmt                 /* A list can be a single statement */
    | stmt_list stmt     /* or a list followed by another statement */
    ;

stmt:
    ID '=' expr ';'   { printf("%s = %s\n", $1, $3); }
    ;

expr:
    expr '+' term     { $$ = new_temp(); printf("%s = %s + %s\n", $$, $1, $3); }
    | expr '-' term     { $$ = new_temp(); printf("%s = %s - %s\n", $$, $1, $3); }
    | term              { $$ = $1; }
    ;

term:
    term '*' factor   { $$ = new_temp(); printf("%s = %s * %s\n", $$, $1, $3); }
    | term '/' factor   { $$ = new_temp(); printf("%s = %s / %s\n", $$, $1, $3); }
    | factor            { $$ = $1; }
    ;

factor:
    '(' expr ')'      { $$ = $2; }
    | ID                { $$ = $1; }
    | NUM               { $$ = $1; }
    ;

%%
/* --- C Code Section --- */

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("--- Three Address Code ---\n");
    yyparse();
    return 0;
}