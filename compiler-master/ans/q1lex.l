%{
#include "y.tab.h"
%}

%%
[a-z]           { yylval = yytext[0]; return ID; }
[0-9]+          { yylval = atoi(yytext); return NUM; }
[=]             { return ASSIGN; }
[+]             { return PLUS; }
[-]             { return MINUS; }
[*]             { return MUL; }
[/]             { return DIV; }
[ \t\n]         ;
.               { return yytext[0]; }
%%
