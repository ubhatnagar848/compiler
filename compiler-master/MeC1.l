%{
#include <stdio.h>
#include <string.h>

/* States:
   S0 : 0 chars
   S1 : 1 char
   S2 : 2 chars
   S3 : 3 chars
   S4 : 4 chars
   S5 : >=5 chars (start tracking last 5 symbols)
*/

char win[6];   // sliding window of last 5 characters
int len = 0;   // total characters seen

void print_state(int st){
    printf("State: S%d\n", st);
}
%}

%%
[a|b]  {
        char c = yytext[0];
        len++;

        /* slide window */
        if(len <= 5){
            win[len-1] = c;
        } else {
            for(int i=0;i<4;i++) win[i] = win[i+1];
            win[4] = c;
        }

        /* Determine state */
        if(len == 1) print_state(1);
        else if(len == 2) print_state(2);
        else if(len == 3) print_state(3);
        else if(len == 4) print_state(4);
        else print_state(5);
      }

\n      {
        /* End of input: decide ACCEPT/REJECT */

        if(len < 5){
            printf("Result: REJECT (length < 5)\n");
        } else {
            if(win[0] == 'b')
                printf("Result: ACCEPT\n");
            else
                printf("Result: REJECT\n");
        }

        len = 0;  // reset
      }

.       ;  /* ignore anything else */
%%

int main() {
    yylex();
    return 0;
}
