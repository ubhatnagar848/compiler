%{
#include <stdio.h>
#include <stdlib.h>

int t = 1;

void tac(char op, char a, char b, char c) {
    printf("t%d = %c %c %c\n", t++, a, op, b);
}
%}

%token ID NUM ASSIGN PLUS MINUS MUL DIV

%%
stmt: ID ASSIGN expr { printf("%c = t%d\n", $1, t-1); }
    ;

expr: expr PLUS term { tac('+', $1, $3, 0); }
    | expr MINUS term { tac('-', $1, $3, 0); }
    | term
    ;

term: term MUL factor { tac('*', $1, $3, 0); }
    | term DIV factor { tac('/', $1, $3, 0); }
    | factor
    ;

factor: ID
      | NUM
      ;
%%

int main() {
    printf("Enter expression: ");
    yyparse();
    return 0;
}

int yyerror() {
    printf("Invalid expression\n");
    return 0;
}
