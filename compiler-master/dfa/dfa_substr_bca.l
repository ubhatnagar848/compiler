%{
#include <stdio.h>
int state = 0;
%}
%%
a {
 if(state == 2) state = 3;
 else state = 0;
}

b {
 if(state == 0 || state == 1 || state == 2) state = 1;
 else if(state == 3) state = 1;
}

c {
 if(state == 1) state = 2;
 else if(state == 3) state = 0;
 else state = 0;
}

\n {
 if(state == 3) {
 printf("ACCEPTED\n");
 } else {
 printf("REJECTED\n");
29

}
 state = 0; }
. {
 state = 0; }
%%

int main() {
 yylex();
 return 0; }

int yywrap() {
 return 1; }