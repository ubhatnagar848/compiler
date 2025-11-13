%{
#include <stdio.h>
int state = 0;
%}
%%
a   {
    if (state == 0) state = 1;
    else if (state == 1) state = 0;
    else if (state == 2) state = 3;
    else if (state == 3) state = 2;
}
b   {
    if (state == 0) state = 2;
    else if (state == 1) state = 3;
    else if (state == 2) state = 0;
    else if (state == 3) state = 1;
}
\n  {
    if (state == 1) {
        printf("ACCEPTED\n");
    } else {
        printf("REJECTED\n");
    }
    state = 0;
}
%%
int main() {
    printf("Enter strings:\n");
    yylex();
    return 0;
}
int yywrap() {
    return 1;
}
