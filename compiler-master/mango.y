/*
S  → a M b

M  → a M b | A

A  → a A | a
*/

/* cat_dog.y */

%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);

/* PDA stack simulation */
#define MAXSTACK 1000
char stack[MAXSTACK];
int sp = 0;
const char BOTTOM = '$';

int count_a = 0;
int count_b = 0;
int error_flag = 0;

/* stack operations */
void pushA() {
    if (sp >= MAXSTACK) { printf("Stack overflow\n"); exit(1); }
    stack[sp++] = 'A';
}
int popA() {
    if (sp == 0) return 0;
    if (stack[sp-1] == BOTTOM) return 0;
    sp--;
    return 1;
}
void init_stack() {
    sp = 0;
    stack[sp++] = BOTTOM;
}

void print_stack() {
    printf("  Stack (top → bottom): ");
    for (int i = sp - 1; i >= 0; i--) {
        if (stack[i] == BOTTOM) printf("[BOTTOM]");
        else printf("%c", stack[i]);
        if (i > 0) printf(" ");
    }
    printf("\n");
}

void print_config(const char *event) {
    printf("%s\n", event);
    print_stack();
}

void accept_print() {
    printf("=== RESULT: Input accepted ===\n");
}
void reject_print(const char *reason) {
    printf("=== RESULT: Input rejected: %s ===\n", reason);
}
%}

%token A_SYM B_SYM

%%

input:
      seq   
    | { reject_print("empty input"); }
    ;

seq:
      as bs {
          if (error_flag) { reject_print("parse error"); YYACCEPT; }

          if (count_a < 1) reject_print("need at least one 'a'");
          else if (count_b < 1) reject_print("need at least one 'b'");
          else if (sp <= 1) reject_print("a count is NOT greater than b count");
          else accept_print();
      }
    ;

as:
      A_SYM {
          count_a++;
          pushA();
          print_config("Read: a");
      }
    | as A_SYM {
          count_a++;
          pushA();
          print_config("Read: a");
      }
    ;

bs:
      B_SYM {
          count_b++;
          if (!popA()) {
              print_config("Read: b → stack empty (cannot pop)");
              reject_print("more b's than a's at some position");
              error_flag = 1;
          } else {
              print_config("Read: b (popped one A)");
          }
      }
    | bs B_SYM {
          count_b++;
          if (!popA()) {
              print_config("Read: b → stack empty (cannot pop)");
              reject_print("more b's than a's at some position");
              error_flag = 1;
          } else {
              print_config("Read: b (popped one A)");
          }
      }
    ;

%%

int main(void) {
    init_stack();
    printf("PDA Simulation for L = { a^n b^m | n>m>=1 }\n");
    printf("Enter sequence of symbols (a b), separated by spaces or no spaces.\n\n");
    yyparse();
    return 0;
}
