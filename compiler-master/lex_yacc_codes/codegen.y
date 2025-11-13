/* codegen.y: The yacc parser file */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(char const *s);
int yylex(void);
%}

/* Define the type of data associated with tokens */
%union {
    char *var;
}

/* Declare tokens and their types */
%token <var> ID
%token ASSIGN

%%

/* The grammar rules start here */
program: /* An empty program is valid */
       | program statement
       ;

statement: ID ASSIGN ID '+' ID '\n' { 
             printf("\tMOV AX, %s\n", $3);   /* Move first operand to AX register */
             printf("\tADD AX, %s\n", $5);   /* Add second operand to AX */
             printf("\tMOV %s, AX\n\n", $1); /* Store result from AX to variable */
             free($1); free($3); free($5); /* Free allocated memory */
           }
         | ID ASSIGN ID '-' ID '\n' {
             printf("\tMOV AX, %s\n", $3);
             printf("\tSUB AX, %s\n", $5);
             printf("\tMOV %s, AX\n\n", $1);
             free($1); free($3); free($5);
           }
         | ID ASSIGN ID '*' ID '\n' {
             printf("\tMOV AX, %s\n", $3);   /* MUL implicitly uses AX */
             printf("\tMOV BX, %s\n", $5);   /* Move second operand to BX */
             printf("\tMUL BX\n");           /* Multiply AX by BX, result in AX */
             printf("\tMOV %s, AX\n\n", $1);
             free($1); free($3); free($5);
           }
         | ID ASSIGN ID '/' ID '\n' {
             printf("\tMOV AX, %s\n", $3);   /* DIV implicitly uses AX */
             printf("\tMOV BX, %s\n", $5);   /* Move divisor to BX */
             printf("\tDIV BX\n");           /* Divide AX by BX, quotient in AX */
             printf("\tMOV %s, AX\n\n", $1);
             free($1); free($3); free($5);
           }
         | '\n' { /* Ignore blank lines */ }
         | error '\n' { yyerrok; } /* Simple error recovery */
         ;

%%

/* Main function and error reporting */
int main() {
    printf("Enter Three Address Code (e.g., res := op1 + op2).\n");
    printf("Press Ctrl+D (Linux/macOS) or Ctrl+Z (Windows) when done.\n\n");
    printf("--- Generated 8086 Assembly ---\n");
    yyparse();
    printf("--- End of Assembly ---\n");
    return 0;
}

void yyerror(char const *s) {
    fprintf(stderr, "Syntax Error: '%s'. Invalid statement format.\n", s);
}