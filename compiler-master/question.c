Table of Contents

Expt. No	Date	Name of Experiment	Page No
1	August 1, 2025	Implementation of Deterministic Finite Automaton (DFA) from regular grammar using C language. 	3
2	August 1, 2025	 Implement a C program to find a regular grammar from Deterministic Finite Automaton (DFA).	10
3	August 1, 2025	 Implementation of Deterministic Finite Automaton (DFA) from Non-deterministic Finite Automata (NFA) without ε-edges using C language.	15
4	August 1, 2025	Implement a DFA in LEX code which accepts odd number of a and even number of b’s. 
Implement a DFA in LEX code which accepts strings over {a, b, c} having bca as substring.  	28
5	August 22, 2025	Construct a lexical analyser
Identify the tokens from simple statement as input stored in a linear array Identify the tokens from small program as input stored in a text file. Identify the tokens from small program as input get it from the user and store it in a text file	35
6	August 22, 2025	Implement LEX code to:
count the frequency of the given word in a file 
replace a word with another taking input from file. 
find the length of the longest word. 
construct a lexical analyser using LEX tool.	51
7	September 5, 2025	Construct Predictive parse table using C language.	61
8	September 5, 2025	Construct precedence table for the given operator grammar and perform the parsing for the given string.	79
9	September 19, 2025	Construct Simple LR (SLR) parse table using C language and implement the LR parsing algorithm, get both parse table and input string are inputs.	106
10	September 19, 2025	Construct Canonical LR (CLR) parse table using C language implement the LR parsing algorithm, get both parse table and input string are inputs. Use C language for implementation.	129
11	September 19, 2025	Construct Look-Ahead LR (LALR) parse table using C language implement the LR parsing algorithm, get both parse table and input string are inputs. Use C language for implementation. 	161
12	October 3, 2025	Implementation of a simple calculator using LEX and YACC tools. 	193
13	October 3, 2025	Implementation of Abstract syntax tree –Infix to postfix using the LEX and YACC tools. 	196
14	October 3, 2025	Using LEX and YACC tools to recognize the strings of the following context-free languages: 
L(G) = { anbm  / m ≠ n} 
L(G) = { ab (bbaa)n bba (ba)n / n ≥ 0}	201
15	October 17, 2025	Implementation of three address codes for a simple program using LEX and YACC tools. 	206
16	October 17, 2025	Implement simple code optimization techniques.	214
17	October 17, 2025	Implement Back end of the compiler for which three address code is given as input and the 8086-assembly language is produced as output. 	222

Experiment 1:
Aim
To develop a Deterministic Finite Automaton (DFA) from a given regular grammar using the C programming language, and to verify whether a provided input string is accepted by the DFA. The program should also display the transition table and the sequence of transitions for the string.
Algorithm:
1.	Read the number of states, the labels of each state, and specify the initial state.
2.	Read the number of input symbols (alphabets) and list them.
3.	Construct the transition table by specifying transitions for each state and input symbol.
4.	Read the number of final (accepting) states and list them.
5.	For each input string:
o	Begin from the initial state.
o	Process each character in the string:
	If a character is not part of the input alphabet, reject the string.
	Follow the transition corresponding to the character; if no transition exists, reject the string.
6.	After processing the entire string, check if the resulting state is a final state:
o	If yes, accept the string.
o	Otherwise, reject it.
7.	Display the transition table and the path of transitions taken for the string.
Source Code:
#include <stdio.h>
#include <string.h>

int main() 
{
    int q, a, f, i, j, k;
    char s[100], state[10][10], alpha[10];
    char trans[10][10][10], final[10][10], cur_state[10], next_state[10], initial_state[10];
    char input, choice;
    int valid, accept, pc = 0;

    printf("No. of states: ");
    scanf("%d", &q);

    printf("Enter state names: ");
    for (i = 0; i < q; i++) {
        scanf("%s", state[i]);
    }

    printf("Enter initial state: ");
    scanf("%s", initial_state);

    printf("No. of input alphabets: ");
    scanf("%d", &a);

    printf("Enter alphabets: ");
    for (i = 0; i < a; i++) {
        scanf(" %c", &alpha[i]);
    }

    printf("Input transition table:\n");
    for (i = 0; i < q; i++) {
        for (j = 0; j < a; j++) {
            printf("D[%s,%c]: ", state[i], alpha[j]);
            scanf("%s", trans[i][j]);
        }
    }

    printf("No. of final states: ");
    scanf("%d", &f);

    printf("Enter final states: ");
    for (i = 0; i < f; i++) {
        scanf("%s", final[i]);
    }

    do {
        valid = 1;
        accept = 0;
        strcpy(cur_state, initial_state);

        printf("\nInput string: ");
        scanf("%s", s);

        printf("\nState transitions:\n%s", cur_state);

        for (i = 0; i < (int)strlen(s); i++) {
            input = s[i];

            for (j = 0; j < a; j++) {
                if (alpha[j] == input) {
                    break;
                }
            }

            if (j == a) {
                valid = 0;
                break;
            }

            for (k = 0; k < q; k++) {
                if (strcmp(cur_state, state[k]) == 0) {
                    break;
                }
            }

            if (strcmp(trans[k][j], "-") == 0) {
                valid = 0;
                break;
            }

            strcpy(next_state, trans[k][j]);
            printf(" -> %s", next_state);
            strcpy(cur_state, next_state);
        }

        for (i = 0; i < f; i++) {
            if (strcmp(cur_state, final[i]) == 0) {
                accept = 1;
                break;
            }
        }

        if (pc == 0) {
            printf("\n\nTransition Table:\nState\t");
            for (i = 0; i < a; i++) {
                printf("%c\t", alpha[i]);
            }
            printf("\n");

            for (i = 0; i < q; i++) {
                printf("%s\t", state[i]);
                for (j = 0; j < a; j++) {
                    printf("%s\t\t", trans[i][j]);
                }
                printf("\n");
            }
        }

        pc++;

        if (!valid) {
            printf("\nResult: Rejected (invalid transition)\n");
        } else if (!accept) {
            printf("\nResult: Rejected (not final state)\n");
        } else {
            printf("\nResult: Accepted\n");
        }

        printf("\nTest another string? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
Output:
 
 

 
Experiment 2:
Aim
To generate a regular grammar from a given Deterministic Finite Automaton (DFA) using the C programming language, by converting the DFA's transition table and final states into a formal grammar representation G = (N, T, P, S).
Algorithm:
1.	Input the set of states, input symbols (alphabet), initial state, transition table, and list of final states.
2.	For each transition defined as D[state, symbol] = state2:
o	If the transition leads to the same state, add the production: state → symbol
o	If it leads to a different state, add the production: state → symbol state2
3.	Do not include epsilon (empty) productions.
4.	Output the grammar in standard regular grammar format.

Source Code:
#include <stdio.h>
#include <string.h>

int main() 
{
    int q, a, f, i, j;
    char st[10][10], al[10], tbl[10][10][10], fn[10][10], S[10];

    printf("No. of states: ");
    scanf("%d", &q);

    printf("Enter state names: ");
    for (i = 0; i < q; i++) {
        scanf("%s", st[i]);
    }

    printf("Enter initial state: ");
    scanf("%s", S);

    printf("No. of input alphabets: ");
    scanf("%d", &a);

    printf("Enter alphabets: ");
    for (i = 0; i < a; i++) {
        scanf(" %c", &al[i]);
    }

    printf("Input transition table:\n");
    for (i = 0; i < q; i++) {
        for (j = 0; j < a; j++) {
            printf("D[%s,%c]: ", st[i], al[j]);
            scanf("%s", tbl[i][j]);
        }
    }

    printf("No. of final states: ");
    scanf("%d", &f);

    printf("Enter final states: ");
    for (i = 0; i < f; i++) {
        scanf("%s", fn[i]);
    }

    printf("\nGrammar:\n");

    printf("N = {");
    for (i = 0; i < q; i++) {
        printf("%s", st[i]);
        if (i < q - 1) {
            printf(", ");
        }
    }
    printf("}\n");

    printf("T = {");
    for (i = 0; i < a; i++) {
        printf("%c", al[i]);
        if (i < a - 1) {
            printf(", ");
        }
    }
    printf("}\n");

    printf("S = %s\n", S);

    printf("P:\n");
    for (i = 0; i < q; i++) {
        for (j = 0; j < a; j++) {
            if (strcmp(tbl[i][j], "-") != 0) {
                if (strcmp(tbl[i][j], st[i]) == 0) {
                    printf("%s -> %c\n", st[i], al[j]);
                } else {
                    printf("%s -> %c%s\n", st[i], al[j], tbl[i][j]);
                }
            }
        }
    }

    return 0;
}
Output:

 


 
Experiment 3:
Aim
To convert a given Nondeterministic Finite Automaton (NFA) without ε-transitions into an equivalent Deterministic Finite Automaton (DFA) using the C programming language, and to display the resulting DFA’s states and transition table.
Algorithm:
1.	Input the NFA’s states and input symbols (alphabet).
2.	Read the NFA’s transition table.
3.	Input the set of final (accepting) states of the NFA.
4.	Represent each DFA state as a set (subset) of NFA states.
5.	For each DFA state and input symbol:
o	Determine all reachable NFA states.
o	Form a new DFA state from this set if it doesn't already exist.
6.	Mark a DFA state as accepting if it includes at least one accepting NFA state.
7.	Output the DFA’s states and its complete transition table.
Source Code:
#include <stdio.h>
#include <string.h>

int isin(int arr[], int n, int val) {
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] == val) {
            return 1;
        }
    }
    return 0;
}

int find_subset(int subset[][10], int n, int arr[], int sz) {
    int i, j, found;
    for (i = 0; i < n; i++) {
        if (sz != subset[i][0]) {
            continue;
        }
        found = 1;
        for (j = 1; j <= sz; j++) {
            if (arr[j - 1] != subset[i][j]) {
                found = 0;
                break;
            }
        }
        if (found) {
            return i;
        }
    }
    return -1;
}

void build_label(char lab[], char nst[][10], int arr[], int sz) {
    int i;
    lab[0] = 0;
    for (i = 0; i < sz; i++) {
        if (i) strcat(lab, ",");
        strcat(lab, nst[arr[i]]);
    }
}

int main() {
    int nq, na, nf, i, j, k, x, m, l, ndq = 0;
    char nst[10][10], alp[10], trans[10][10][100], fns[10][10];
    int subset[100][10];
    char labels[100][200];
    int dtrans[100][10], dfinal[100] = {0};

    printf("No. of NFA states: ");
    scanf("%d", &nq);
    printf("State labels: ");
    for (i = 0; i < nq; i++) {
        scanf("%s", nst[i]);
    }

    printf("No. of input symbols: ");
    scanf("%d", &na);
    printf("Alphabets: ");
    for (i = 0; i < na; i++) {
        scanf(" %c", &alp[i]);
    }

    printf("Input transition table:\n");
    for (i = 0; i < nq; i++) {
        for (j = 0; j < na; j++) {
            printf("D[%s,%c]: ", nst[i], alp[j]);
            scanf(" %[^\n]", trans[i][j]);
            if (strlen(trans[i][j]) == 0)
                strcpy(trans[i][j], "-");
        }
    }

    printf("No. of final states: ");
    scanf("%d", &nf);
    printf("Final states: ");
    for (i = 0; i < nf; i++) {
        scanf("%s", fns[i]);
    }

    int old[10], oldsz = 0;
    old[oldsz++] = 0;
    subset[0][0] = oldsz;
    for (j = 0; j < oldsz; j++) {
        subset[0][j + 1] = old[j];
    }
    build_label(labels[0], nst, old, oldsz);
    ndq = 1;

    for (i = 0; i < ndq; i++) {
        int cursz = subset[i][0];
        int curset[10];
        for (j = 0; j < cursz; j++) {
            curset[j] = subset[i][j + 1];
        }

        for (j = 0; j < na; j++) {
            int next[10], nextsz = 0;
            for (k = 0; k < cursz; k++) {
                x = curset[k];
                if (strcmp(trans[x][j], "-") == 0) continue;

                char copy[100];
                strcpy(copy, trans[x][j]);
                char *tok = strtok(copy, " ");
                while (tok) {
                    for (l = 0; l < nq; l++) {
                        if (strcmp(tok, nst[l]) == 0)
                            break;
                    }
                    if (l < nq && !isin(next, nextsz, l)) {
                        next[nextsz++] = l;
                    }
                    tok = strtok(NULL, " ");
                }
            }

            if (nextsz == 0) {
                dtrans[i][j] = -1;
            } else {
                for (m = 0; m < nextsz - 1; m++) {
                    for (l = m + 1; l < nextsz; l++) {
                        if (next[m] > next[l]) {
                            int tmp = next[m];
                            next[m] = next[l];
                            next[l] = tmp;
                        }
                    }
                }

                int idx = find_subset(subset, ndq, next, nextsz);
                if (idx == -1) {
                    subset[ndq][0] = nextsz;
                    for (m = 0; m < nextsz; m++) {
                        subset[ndq][m + 1] = next[m];
                    }
                    build_label(labels[ndq], nst, next, nextsz);
                    dtrans[i][j] = ndq;
                    ndq++;
                } else {
                    dtrans[i][j] = idx;
                }
            }
        }
    }

    for (i = 0; i < ndq; i++) {
        int sz = subset[i][0];
        for (j = 1; j <= sz; j++) {
            for (k = 0; k < nf; k++) {
                if (strcmp(nst[subset[i][j]], fns[k]) == 0) {
                    dfinal[i] = 1;
                }
            }
        }
    }

    printf("\nDFA States:\n");
    for (i = 0; i < ndq; i++) {
        printf("%d: %s", i, labels[i]);
        if (dfinal[i]) printf(" (final)");
        printf("\n");
    }

    printf("\nDFA Transition Table:\nState\t");
    for (i = 0; i < na; i++) {
        printf("%c\t", alp[i]);
    }
    printf("\n");
    for (i = 0; i < ndq; i++) {
        printf("%s\t", labels[i]);
        for (j = 0; j < na; j++) {
            if (dtrans[i][j] != -1) {
                printf("%s\t", labels[dtrans[i][j]]);
            } else {
                printf("-\t");
            }
        }
        printf("\n");
    }
    char input[100];
    printf("\nEnter input string to check acceptance: ");
    scanf("%s", input);
    int current_states[10], current_size = 1;
    current_states[0] = 0;

    for (i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        int symbol_index = -1;
        for (j = 0; j < na; j++) {
            if (alp[j] == c) {
                symbol_index = j;
                break;
            }
        }
        if (symbol_index == -1) {
            printf("\nNFA: Input symbol '%c' not in alphabet. Rejecting.\n", c);
            current_size = 0;
            break;
        }

        int next_states[10], next_size = 0;

        for (j = 0; j < current_size; j++) {
            int st = current_states[j];
            if (strcmp(trans[st][symbol_index], "-") == 0)
                continue;

            char copy[100];
            strcpy(copy, trans[st][symbol_index]);
            char *tok = strtok(copy, " ");
            while (tok) {
                for (k = 0; k < nq; k++) {
                    if (strcmp(tok, nst[k]) == 0)
                        break;
                }
                if (k < nq && !isin(next_states, next_size, k)) {
                    next_states[next_size++] = k;
                }
                tok = strtok(NULL, " ");
            }
        }

        memcpy(current_states, next_states, sizeof(int) * next_size);
        current_size = next_size;

        if (current_size == 0)
            break;
    }

    int nfa_accept = 0;
    for (i = 0; i < current_size; i++) {
        for (j = 0; j < nf; j++) {
            if (strcmp(nst[current_states[i]], fns[j]) == 0) {
                nfa_accept = 1;
                break;
            }
        }
        if (nfa_accept)
            break;
    }

    if (nfa_accept) {
        printf("NFA accepts the string.\n");
    } else {
        printf("NFA rejects the string.\n");
    }
    int current_state = 0;
    int accepted = 1;
    for (i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        int symbol_index = -1;
        for (j = 0; j < na; j++) {
            if (alp[j] == c) {
                symbol_index = j;
                break;
            }
        }
        if (symbol_index == -1) {
            accepted = 0;
            break;
        }
        int next_state = dtrans[current_state][symbol_index];
        if (next_state == -1) {
            accepted = 0;
            break;
        }
        current_state = next_state;
    }

    if (accepted && dfinal[current_state]) {
        printf("DFA accepts the string.\n");
    } else {
        printf("DFA rejects the string.\n");
    }

    return 0;
}
Output:
 
 

 
Experiment 4:
Experiment 4a:
Aim
To implement a Deterministic Finite Automaton (DFA) using LEX that accepts all strings containing an odd number of ‘a’ characters and an even number of ‘b’ characters.
Algorithm:
1.	Start in the initial DFA state q0 (even number of 'a's and even number of 'b's).
2.	Read the input string character by character.
3.	For each character:
•	If the character is 'a', update the current state based on the DFA transition table:
o	q0 → q1, q1 → q0, q2 → q3, q3 → q2
•	If the character is 'b', update the current state based on the DFA transition table:
o	q0 → q2, q1 → q3, q2 → q0, q3 → q1
4.	After processing each character, display the current DFA state
5.	If a newline character (\n) is encountered:
•	Check the current state:
o	If the current state is q1, accept the string and display: String accepted (Final state: q1)
o	Otherwise, reject the string and display: String rejected (Final state: qX)
6.	Reset the DFA state to q0 for the next input string.
7.	Ignore any other characters that are not 'a', 'b', or newline.
Source Code
%{
#include <stdio.h>
enum State { q0, q1, q2, q3 };
enum State current_state = q0;
void update_state(char ch) {
    switch (current_state) {
        case q0:
            if (ch == 'a') current_state = q1;
            else if (ch == 'b') current_state = q2;
            break;
        case q1:
            if (ch == 'a') current_state = q0;
            else if (ch == 'b') current_state = q3;
            break;
        case q2:
            if (ch == 'a') current_state = q3;
            else if (ch == 'b') current_state = q0;
            break;
        case q3:
            if (ch == 'a') current_state = q2;
            else if (ch == 'b') current_state = q1;
            break;
    }
    printf("Read '%c' → Current state: q%d\n", ch, current_state);
}
%}
%%
[a|b]     { update_state(yytext[0]); }
\n        {
             if (current_state == q1)
                 printf("String accepted (Final state: q1)\n");
             else
                 printf("String rejected (Final state: q%d)\n", current_state);
             // Reset state for next string
             current_state = q0;
         }
.|\n      { /* Ignore other characters */ }
%%
int main() {
    printf("Enter strings (one per line)\n");
    yylex();
    return 0;
}
Output:
 

Experiment 4b:
Aim
To implement a DFA using LEX that accepts all strings containing ‘bca’ as a substring, over the alphabet {a, b, c}.
Algorithm
1.	Start in the initial DFA state q0.
2.	Read the input string character by character.
3.	For each character: After each character, display the current DFA state.
4.	If a newline character (\n) is encountered:
•	If the current state is q3, accept the string and display:
"String accepted (Final state: q3)"
•	Otherwise, reject the string and display:
"String rejected (Final state: qX)", where X is the state number.
5.	Reset the DFA state to q0 to process the next input string.
6.	Ignore any characters other than 'a', 'b', 'c', or newline.

Source Code
%{
#include <stdio.h>
enum State { q0, q1, q2, q3 };
enum State current_state = q0;
void update_state(char ch) {
    switch (current_state) {
        case q0:
            if (ch == 'b') current_state = q1;
            else current_state = q0;
            break;
        case q1:
            if (ch == 'c') current_state = q2;
            else if (ch == 'b') current_state = q1;
            else current_state = q0;
            break;
        case q2:
            if (ch == 'a') current_state = q3;
            else if (ch == 'b') current_state = q1;
            else current_state = q0;
            break;
        case q3:
            current_state = q3;
            break;
    }
    printf("Read '%c' → Current state: q%d\n", ch, current_state);
}
%}
%%
[a|b|c]    { update_state(yytext[0]); }
\n         {
             if (current_state == q3)
                 printf("String accepted (Final state: q3)\n");
             else
                 printf("String rejected (Final state: q%d)\n", current_state);
             current_state = q0;
          }
.|\n       { /* Ignore any other characters */ }
%%
int main() {
    printf("Enter strings (one per line)\n");
    yylex();
    return 0;
}
Output
 

 
Experiment 5:
Experiment 5 part 1:
1. Identify the tokens from simple statement as input stored in a linear array 
Aim
To write a C++ program that takes a stream of input data (like a small piece of code) and performs lexical analysis, classifying each token into categories such as keywords, identifiers, operators, numbers, and separators.
Algorithm
1.	Start the program.
2.	Declare the required variables and a vector to store the tokens.
3.	Prompt the user to enter a stream of data.
4.	Read the entire input line as a string.
5.	Use a stringstream to split the input string into individual words (tokens).
6.	Store each token into a vector.
7.	For each token in the vector:
a. If it matches reserved words like int, while, for, etc., classify it as a keyword.
b. If it consists of letters (A–Z or a–z), classify it as an identifier.
c. If it is "=", classify it as an assignment operator.
d. If it matches +, -, *, /, %, ++, or --, classify it as an arithmetic operator.
e. If it matches relational symbols like ==, <, <=, >, >=, or !=, classify it as a relational operator.
f. If it contains digits (0–9), classify it as a number.
g. If it matches &&, ||, or !, classify it as a logical operator.
h. If it is ";", classify it as a separator.
i. If it is (, ), {, or }, classify it as an indexing operator.
j. If it is ",", classify it as a comma operator.
k. If it matches << or >>, classify it as a stream operator.
8.	Print the token along with its classification.
9.	Repeat the process until all tokens are classified.
10.	End
 
Code:
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
 
using namespace std;
 
int main(){

    string x,y[99];

    vector<string> token;

    //

    cout<<"Enter Stream of data: ";

    getline(cin, x);

    cout<<x;

    cout<<"\n";

    cout<<"\n";

    //

    stringstream ss(x);

    string z;

    while(ss >> z){

        token.push_back(z);

    }

    for(int i=0;i<token.size();i++){

        string a = token[i];

        if(a=="int" || a=="long" || a=="string" || a=="while" || a=="do" || a=="float" || a=="if" || a=="for" || a=="switch"){

            cout<<a<<" \t\t keyword\n";

        }else if( a>="a" && a<="z" || a>="A" && a<="Z"){

            cout<<a<<" \t\t identifier\n";

        }else if(a=="="){

            cout<<a<<" \t\t assignment operator\n";

        }else if( a=="+" || a=="-" || a=="*" || a=="/" || a=="%" || a=="++" || a=="--"){

            cout<<a<<" \t\t arithmatic operator\n";

        }else if( a=="==" || a=="<" || a=="<=" || a==">" || a==">=" || a=="!="){

            cout<<a<<" \t\t relational operator\n";

        }else if( a>="0" && a<="9"){

            cout<<a<<" \t\t number\n";

        }else if( a=="&&" || a=="||" || a=="!"){

            cout<<a<<" \t\t logical operator\n";

        }else if( a==";"){

            cout<<a<<" \t\t seperator\n";

        }else if( a==")" || a=="(" || a=="{" || a=="}"){

            cout<<a<<" \t\t indexing operator\n";
        }else if(a==","){

            cout<<a<<" \t\t comma operator\n";
        }else if(a=="<<" || a==">>"){

            cout<<a<<" \t\t stream operator\n";
        }

    }

    return 0;

}
 Output:
 
Experiment 5 part 2: 
2. Identify the tokens from small program (not exceeding 5 lines) as input stored in a 
text file 
Aim
To write a C++ program that reads a stream of data from a file (input.txt) and performs lexical analysis, classifying each token into categories such as keywords, identifiers, operators, numbers, and separators.
Algorithm
1.	Start the program.
2.	Declare the required variables and a vector to store tokens.
3.	Open the input file named "input.txt".
4.	Read the contents of the file line by line and combine them into a single string.
5.	Display the complete input data on the screen.
6.	Use a stringstream to break the input string into individual words (tokens).
7.	Store each token into a vector.
8.	For each token in the vector:
a. If it matches reserved words like int, while, for, etc., classify it as a keyword.
b. If it consists of letters (A–Z or a–z), classify it as an identifier.
c. If it is "=", classify it as an assignment operator.
d. If it matches +, -, *, /, %, ++, or --, classify it as an arithmetic operator.
e. If it matches relational symbols like ==, <, <=, >, >=, or !=, classify it as a relational operator.
f. If it contains digits (0–9), classify it as a number.
g. If it matches &&, ||, or !, classify it as a logical operator.
h. If it is ";", classify it as a separator.
i. If it is (, ), {, or }, classify it as an indexing operator.
j. If it is ",", classify it as a comma operator.
k. If it matches << or >>, classify it as a stream operator.
9.	Print the token along with its classification.
10.	Repeat the process until all tokens are classified.
11.	End
Code:
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;
 
int main(){

    string x,y;

    vector<string> token;

    //

    ifstream inputFile("input.txt");
    while(getline(inputFile, y)){
        x += y + " ";
    }
    //
    cout<<x;

    cout<<"\n";

    cout<<"\n";

    //

    stringstream ss(x);

    string z;

    while(ss >> z){

        token.push_back(z);

    }

    for(int i=0;i<token.size();i++){

        string a = token[i];

        if(a=="int" || a=="long" || a=="string" || a=="while" || a=="do" || a=="float" || a=="if" || a=="for" || a=="switch"){

            cout<<a<<" \t\t keyword\n";

        }else if( a>="a" && a<="z" || a>="A" && a<="Z"){

            cout<<a<<" \t\t identifier\n";

        }else if(a=="="){

            cout<<a<<" \t\t assignment operator\n";

        }else if( a=="+" || a=="-" || a=="*" || a=="/" || a=="%" || a=="++" || a=="--"){

            cout<<a<<" \t\t arithmatic operator\n";

        }else if( a=="==" || a=="<" || a=="<=" || a==">" || a==">=" || a=="!="){

            cout<<a<<" \t\t relational operator\n";

        }else if( a>="0" && a<="9"){

            cout<<a<<" \t\t number\n";

        }else if( a=="&&" || a=="||" || a=="!"){

            cout<<a<<" \t\t logical operator\n";

        }else if( a==";"){

            cout<<a<<" \t\t seperator\n";

        }else if( a==")" || a=="(" || a=="{" || a=="}"){

            cout<<a<<" \t\t indexing operator\n";
        }else if(a==","){

            cout<<a<<" \t\t comma operator\n";
        }else if(a=="<<" || a==">>"){

            cout<<a<<" \t\t stream operator\n";
        }

    }

    return 0;

}
 Output:
 
Experiment 5 part 3: 
Aim
To write a C++ program that takes multiple lines of input from the user, performs lexical analysis to classify tokens such as keywords, identifiers, operators, and numbers, and then saves the classified output into a file named output.txt.
Algorithm
1.	Start the program.
2.	Declare the required variables and a vector to store tokens.
3.	Ask the user to enter 5 lines of input.
4.	Read each line using getline and combine all lines into a single string.
5.	Display the full input data on the screen.
6.	Use a stringstream to split the combined input string into individual tokens.
7.	Store each token into a vector.
8.	For each token in the vector:
a. If it matches reserved words like int, while, for, etc., classify it as a keyword.
b. If it consists of letters (A–Z or a–z), classify it as an identifier.
c. If it is "=", classify it as an assignment operator.
d. If it matches +, -, *, /, %, ++, or --, classify it as an arithmetic operator.
e. If it matches relational symbols like ==, <, <=, >, >=, or !=, classify it as a relational operator.
f. If it contains digits (0–9), classify it as a number.
g. If it matches &&, ||, or !, classify it as a logical operator.
h. If it is ";", classify it as a separator.
i. If it is (, ), {, or }, classify it as an indexing operator.
j. If it is ",", classify it as a comma operator.
k. If it matches << or >>, classify it as a stream operator.
9.	Store the classified tokens with their categories in a string variable.
10.	Open an output file named "output.txt".
11.	Write the classified tokens into the output file.
12.	Close the file.
13.	End
Code:
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

 
using namespace std;
 
int main(){

    string x,y;

    vector<string> token;

    //

    cout<<"Enter Stream of data (5 Lines, press enter after each line): \n";

    for(int i = 0; i < 5; ++i) {
        getline(cin, y);
        x += y + " ";
    }

    cout<<"\n";

    cout<<x;

    cout<<"\n";

    cout<<"\n";

    //

    stringstream ss(x);

    string z;

    while(ss >> z){

        token.push_back(z);

    }

    string ans;
    for(int i=0;i<token.size();i++){

        string a = token[i];

        if(a=="int" || a=="long" || a=="string" || a=="while" || a=="do" || a=="float" || a=="if" || a=="for" || a=="switch"){

            ans += a + " \t\t keyword\n";

        }else if( a>="a" && a<="z" || a>="A" && a<="Z"){
            ans += a + " \t\t identifier\n";

        }else if(a=="="){

            ans += a + " \t\t assignment operator\n";

        }else if( a=="+" || a=="-" || a=="*" || a=="/" || a=="%" || a=="++" || a=="--"){

            ans += a + " \t\t arithmatic operator\n";

        }else if( a=="==" || a=="<" || a=="<=" || a==">" || a==">=" || a=="!="){

            ans += a + " \t\t relational operator\n";

        }else if( a>="0" && a<="9"){

            ans += a + " \t\t number\n";

        }else if( a=="&&" || a=="||" || a=="!"){

            ans += a + " \t\t logical operator\n";

        }else if( a==";"){

            ans+=a+" \t\t seperator\n";

        }else if( a==")" || a=="(" || a=="{" || a=="}"){

            ans+=a+" \t\t indexing operator\n";
        }else if(a==","){

            ans+=a+" \t\t comma operator\n";
        }else if(a=="<<" || a==">>"){

            ans+=a+" \t\t stream operator\n";
        }

    }
    //
    ofstream outputFile("output.txt");
    outputFile << ans;
    outputFile.close();
    return 0;

}
 Output:
 

 
Experiment 6:
1.	Implement LEX code to count the frequency of the given word in a file  

Aim
To write a LEX program that counts the frequency of a given word in a text file.
Algorithm
1.	Include the required header files and declare global variables for the target word and count.
2.	In the LEX rules section, define a pattern to match words consisting of alphabets.
3.	For each matched word, compare it with the given target word using string comparison.
4.	If the word matches, increment the count variable.
5.	Ignore all other characters including whitespace and newline.
6.	In the main function, check command line arguments for filename and target word.
7.	Copy the target word to the global variable.
8.	Open the given file for reading and set it as input to the lexer.
9.	Call the lexical analyzer function yylex() to process the file.
10.	After scanning completes, print the frequency of the target word.
11.	Close the file and exit the program.

%{ 
#include <stdio.h> 
#include <string.h> 
 
char word[100]; 
int count = 0; 
%} 
 
%% 
[a-zA-Z]+ { 
    if (strcmp(yytext, word) == 0) 
        count++; 
} 
.|\n ; 
%% 
 
int main(int argc, char *argv[]) { 
    if (argc < 3) { 
        printf("Usage: %s <filename> <word>\n", argv[0]); 
        return 1; 
    } 
    strcpy(word, argv[2]); 
    yyin = fopen(argv[1], "r"); 
    if (!yyin) { 
        perror("File open error"); 
        return 1; 
    } 
    yylex(); 
    printf("Frequency of '%s' = %d\n", word, count); 
    fclose(yyin); 
    return 0; 
}
 

2.	Implement LEX code to replace a word with another taking input from file.  

Aim
To write a LEX program that replaces all occurrences of a given word in a text file with another specified word.
Algorithm
1.	Include the required header files and declare global variables for the old word and the new word.
2.	In the LEX rules section, define a pattern to match words consisting of alphabets.
3.	For each matched word, compare it with the old word using string comparison.
4.	If the word matches, print the new word in its place.
5.	If the word does not match, print the original word as it is.
6.	For all other characters including whitespace and newline, print them without change.
7.	In the main function, check command line arguments for filename, old word, and new word.
8.	Copy the old and new words to the global variables.
9.	Open the given file for reading and set it as input to the lexer.
10.	Call the lexical analyzer function yylex() to process the file.
11.	After scanning completes, close the file and exit
%{ 
#include <stdio.h> 
#include <string.h> 
 
char oldWord[100], newWord[100]; 
%} 
 
%% 
[a-zA-Z]+ { 
    if (strcmp(yytext, oldWord) == 0) 
        printf("%s", newWord); 
    else 
        printf("%s", yytext); 
} 
.|\n { ECHO; } 
%% 
 
int main(int argc, char *argv[]) { 
    if (argc < 4) { 
        printf("Usage: %s <filename> <oldWord> <newWord>\n", argv[0]); 
        return 1; 
    } 
    strcpy(oldWord, argv[2]); 
    strcpy(newWord, argv[3]); 
    yyin = fopen(argv[1], "r"); 
    if (!yyin) { 
        perror("File open error"); 
        return 1; 
    } 
    yylex(); 
    fclose(yyin); 
    return 0; 
}
 

3.	Implement LEX code to find the length of the longest word.  

Aim
To write a LEX program that finds the length of the longest word in a given text file.
Algorithm
1.	Include the required header files and declare a global variable to store the maximum word length.
2.	In the LEX rules section, define a pattern to match words consisting of alphabets.
3.	For each matched word, calculate its length using the string length function.
4.	Compare the length of the current word with the maximum length found so far.
5.	If the current word is longer, update the maximum length.
6.	Ignore all other characters including whitespace and newline.
7.	In the main function, check command line arguments for the filename.
8.	Open the given file for reading and set it as input to the lexer.
9.	Call the lexical analyzer function yylex() to process the file.
10.	After scanning completes, print the length of the longest word.
11.	Close the file and exit
%{ 
#include <stdio.h> 
#include <string.h> 
 
int maxLen = 0; 
%} 
 
%% 
[a-zA-Z]+ { 
    int len = strlen(yytext); 
    if (len > maxLen) 
        maxLen = len; 
} 
.|\n ; 
%% 
 
int main(int argc, char *argv[]) { 
    if (argc < 2) { 
        printf("Usage: %s <filename>\n", argv[0]); 
        return 1; 
    } 
    yyin = fopen(argv[1], "r"); 
    if (!yyin) { 
        perror("File open error"); 
        return 1; 
    } 
    yylex(); 
    printf("Length of the longest word = %d\n", maxLen); 
    fclose(yyin); 
    return 0; 
}
 

4.	Construct a lexical analyser using LEX tool.  

Aim
To write a LEX program that classifies tokens in a source code file into categories such as keywords, identifiers, numbers, operators, symbols, and unknown characters.
Algorithm
1.	Include the required header files and declare an array of keywords.
2.	Define a function to check if a given string matches any keyword.
3.	In the LEX rules section, specify token patterns and their actions:
a. Match numbers and print them as NUMBER.
b. Match identifiers; check if they are keywords. If yes, print KEYWORD, otherwise print IDENTIFIER.
c. Match arithmetic and assignment operators and print them as OPERATOR.
d. Match symbols such as semicolon, parentheses, and braces, and print them as SYMBOL.
e. Ignore whitespace characters such as space, tab, and newline.
f. For all other characters, print them as UNKNOWN.
4.	In the main function, check command line arguments for the filename.
5.	Open the file for reading and set it as input to the lexer.
6.	Call the lexical analyzer function yylex() to scan and categorize tokens.
7.	After scanning completes, close the file and exit
%{ 
#include <stdio.h> 
#include <string.h> 
 
char *keywords[] = {"int", "float", "if", "else", "while", "return"}; 
int isKeyword(char *s) { 
    for (int i = 0; i < 6; i++) { 
        if (strcmp(s, keywords[i]) == 0) return 1; 
    } 
    return 0; 
} 
%} 
%% 
[0-9]+              { printf("NUMBER: %s\n", yytext); } 
[a-zA-Z_][a-zA-Z0-9_]* { 
    if (isKeyword(yytext)) 
        printf("KEYWORD: %s\n", yytext); 
    else 
        printf("IDENTIFIER: %s\n", yytext); 
} 
"+"|"-"|"*"|"/"|"=" { printf("OPERATOR: %s\n", yytext); } 
";"|"("|")"|"{"|"}" { printf("SYMBOL: %s\n", yytext); } 
[ \t\n]             { /* Ignore whitespace */ } 
.                   { printf("UNKNOWN: %s\n", yytext); } 
%% 
int main(int argc, char *argv[]) { 
    if (argc < 2) { 
        printf("Usage: %s <filename>\n", argv[0]); 
        return 1; 
    } 
    yyin = fopen(argv[1], "r"); 
    if (!yyin) { 
        perror("File open error"); 
        return 1; 
    } 
    yylex(); 
    fclose(yyin); 
    return 0; 
}
 
 
Experiment 7:
Aim
To implement a C program that generates FIRST and FOLLOW sets, constructs an LL(1) parsing table, and parses an input string for a given grammar.
Algorithm
1.	Input the number of productions and store all grammar rules.
2.	Identify non-terminals and terminals from the productions and add $ as the end marker.
3.	Compute FIRST sets by scanning each production and adding appropriate terminals or epsilon.
4.	Compute FOLLOW sets by applying rules for terminals following non-terminals and propagating FOLLOW sets where epsilon occurs.
5.	Construct the LL(1) parsing table using the FIRST and FOLLOW sets.
6.	Display the FIRST sets, FOLLOW sets, and parsing table.
7.	Parse the input string using the LL(1) table with a stack: match terminals, expand non-terminals, and accept if the string reduces to $.
Code
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char P[40][40];
char Fi[40][40];
char Fo[40][40];
char N[40];
char T[40];
char M[40][40][40];
int np, nn, nt;

int addc(char *s, char c) 
{
    int i = 0;
    while (s[i] != '\0') {
        if (s[i] == c) {
            return 0;
        }
        i++;
    }
    s[i] = c;
    s[i + 1] = '\0';
    return 1;
}

int iN(char c) 
{
    for (int i = 0; i < nn; i++) {
        if (N[i] == c) {
            return i;
        }
    }
    return -1;
}

int iT(char c) 
{
    for (int i = 0; i < nt; i++) {
        if (T[i] == c) {
            return i;
        }
    }
    return -1;
}

void mf() 
{
    for (int i = 0; i < nn; i++) {
        Fi[i][0] = '\0';
    }

    int ch = 1;
    while (ch) {
        ch = 0;
        for (int p = 0; p < np; p++) {
            char A = P[p][0];
            char *rhs = P[p] + 2;
            int a = iN(A);

            int k = 0;
            int all_eps = 1;

            if (rhs[0] == '#') {
                if (addc(Fi[a], '#')) {
                    ch = 1;
                }
                continue;
            }

            while (rhs[k] != '\0') {
                char x = rhs[k];
                if (!isupper(x)) {
                    if (addc(Fi[a], x)) {
                        ch = 1;
                    }
                    all_eps = 0;
                    break;
                }
                int b = iN(x);
                int has_eps = 0;
                for (int j = 0; Fi[b][j] != '\0'; j++) {
                    if (Fi[b][j] == '#') {
                        has_eps = 1;
                    } else {
                        if (addc(Fi[a], Fi[b][j])) {
                            ch = 1;
                        }
                    }
                }
                if (has_eps) {
                    k++;
                } else {
                    all_eps = 0;
                    break;
                }
            }

            if (all_eps) {
                if (addc(Fi[a], '#')) {
                    ch = 1;
                }
            }
        }
    }
}

void mfo() 
{
    for (int i = 0; i < nn; i++) {
        Fo[i][0] = '\0';
    }
    addc(Fo[iN(P[0][0])], '$');

    int ch = 1;
    while (ch) {
        ch = 0;
        for (int p = 0; p < np; p++) {
            char A = P[p][0];
            char *rhs = P[p] + 2;
            int a = iN(A);
            int L = (int)strlen(rhs);

            for (int i = 0; i < L; i++) {
                char B = rhs[i];
                if (!isupper(B)) {
                    continue;
                }
                int b = iN(B);
                int j = i + 1;
                int eps_suf = 1;

                while (j < L) {
                    char y = rhs[j];
                    if (!isupper(y)) {
                        if (addc(Fo[b], y)) {
                            ch = 1;
                        }
                        eps_suf = 0;
                        break;
                    }
                    int c = iN(y);
                    int has_eps = 0;
                    for (int t = 0; Fi[c][t] != '\0'; t++) {
                        if (Fi[c][t] == '#') {
                            has_eps = 1;
                        } else {
                            if (addc(Fo[b], Fi[c][t])) {
                                ch = 1;
                            }
                        }
                    }
                    if (has_eps) {
                        j++;
                    } else {
                        eps_suf = 0;
                        break;
                    }
                }
                if (eps_suf) {
                    for (int t = 0; Fo[a][t] != '\0'; t++) {
                        if (addc(Fo[b], Fo[a][t])) {
                            ch = 1;
                        }
                    }
                }
            }
        }
    }
}

void mt() 
{
    for (int i = 0; i < nn; i++) {
        for (int j = 0; j < nt; j++) {
            strcpy(M[i][j], "-");
        }
    }

    for (int p = 0; p < np; p++) {
        char A = P[p][0];
        char *rhs = P[p] + 2;
        int a = iN(A);
        char fst[40];
        fst[0] = '\0';

        int k = 0;
        int add_eps = 1;

        if (rhs[0] == '#') {
            addc(fst, '#');
            add_eps = 1;
        } else {
            while (rhs[k] != '\0') {
                char x = rhs[k];
                if (!isupper(x)) {
                    addc(fst, x);
                    add_eps = 0;
                    break;
                }
                int b = iN(x);
                int has_eps = 0;
                for (int j = 0; Fi[b][j] != '\0'; j++) {
                    if (Fi[b][j] == '#') {
                        has_eps = 1;
                    } else {
                        addc(fst, Fi[b][j]);
                    }
                }
                if (has_eps) {
                    k++;
                } else {
                    add_eps = 0;
                    break;
                }
            }
            if (rhs[0] != '\0' && rhs[k] == '\0' && add_eps == 1) {
                addc(fst, '#');
            }
        }

        int has_eps = 0;
        for (int j = 0; fst[j] != '\0'; j++) {
            if (fst[j] == '#') {
                has_eps = 1;
            } else {
                int t = iT(fst[j]);
                if (t != -1) {
                    strcpy(M[a][t], P[p]);
                }
            }
        }
        if (has_eps) {
            for (int j = 0; Fo[a][j] != '\0'; j++) {
                int t = iT(Fo[a][j]);
                if (t != -1) {
                    strcpy(M[a][t], P[p]);
                }
            }
        }
    }
}

void parse() 
{
    char in[100];
    printf("Enter input string: ");
    scanf("%s", in);

    int L = (int)strlen(in);
    in[L] = '$';
    in[L + 1] = '\0';

    char st[200];
    int top = -1;
    st[++top] = '$';
    st[++top] = N[0];

    int ip = 0;
    printf("\n%-20s%-20s%-20s\n", "stack", "Input", "Output");

    while (top >= 0) {
        char X = st[top];
        char a = in[ip];

        char sshow[210];
        int si = 0;
        for (int i = 0; i <= top; i++) {
            sshow[si++] = st[i];
        }
        sshow[si] = '\0';

        char ishow[110];
        int ii = 0;
        int rem = ip;
        while (in[rem] != '\0') {
            ishow[ii++] = in[rem++];
        }
        ishow[ii] = '\0';

        if (X == '$' && a == '$') {
            printf("%-20s%-20s%-20s\n", sshow, ishow, "Accept");
            return;
        }

        if (!isupper(X)) {
            if (X == a) {
                printf("%-20s%-20s%-20s\n", sshow, ishow, "Match");
                top--;
                ip++;
            } else {
                printf("%-20s%-20s%-20s\n", sshow, ishow, "Reject: mismatch");
                return;
            }
        } else {
            int r = iN(X);
            int c = iT(a);
            if (c == -1) {
                printf("%-20s%-20s%-20s\n", sshow, ishow, "Reject: no col");
                return;
            }
            if (strcmp(M[r][c], "-") == 0) {
                printf("%-20s%-20s%-20s\n", sshow, ishow, "Reject: no rule");
                return;
            }

            char *prod = M[r][c];
            char *rhs = prod + 2;
            top--;

            if (rhs[0] == '#' && rhs[1] == '\0') {
                printf("%-20s%-20s%-20s\n", sshow, ishow, prod);
            } else {
                int len = (int)strlen(rhs);
                for (int i = len - 1; i >= 0; i--) {
                    st[++top] = rhs[i];
                }
                printf("%-20s%-20s%-20s\n", sshow, ishow, prod);
            }
        }
    }
    printf("%-20s%-20s%-20s\n", "-", "-", "Reject: stack empty");
}

int main() 
{
    printf("Enter number of productions: ");
    scanf("%d", &np);

    printf("Enter productions:\n");
    for (int i = 0; i < np; i++) {
        scanf("%s", P[i]);
    }

    N[0] = '\0';
    T[0] = '\0';

    for (int i = 0; i < np; i++) {
        addc(N, P[i][0]);
    }
    nn = (int)strlen(N);

    for (int i = 0; i < np; i++) {
        for (int j = 2; P[i][j] != '\0'; j++) {
            if (!isupper(P[i][j]) && P[i][j] != '#') {
                addc(T, P[i][j]);
            }
        }
    }
    addc(T, '$');
    nt = (int)strlen(T);

    mf();
    mfo();
    mt();

    printf("\nFIRST Sets:\n");
    for (int i = 0; i < nn; i++) {
        printf("FIRST(%c) = { %s }\n", N[i], Fi[i]);
    }

    printf("\nFOLLOW Sets:\n");
    for (int i = 0; i < nn; i++) {
        printf("FOLLOW(%c) = { %s }\n", N[i], Fo[i]);
    }

    printf("\nLL(1) Parse Table:\n");
    printf("%-8s", "");
    for (int j = 0; j < nt; j++) {
        printf("%-8c", T[j]);
    }
    printf("\n");

    for (int i = 0; i < nn; i++) {
        printf("%-8c", N[i]);
        for (int j = 0; j < nt; j++) {
            printf("%-8s", M[i][j]);
        }
        printf("\n");
    }
    parse();
    return 0;
}
Output:
 
 
 

Experiment 8:
Aim
To write a C program that computes the LEADING and TRAILING sets of a grammar, constructs the operator precedence table, and displays the results for operator precedence parsing.
Algorithm
1.	Input the grammar productions and store them.
2.	Extract operators from the right-hand side of productions and include # as the end marker.
3.	Initialize data structures for LEADING and TRAILING sets.
4.	Compute LEADING sets:
a. For each production, scan symbols from left to right.
b. If a terminal or epsilon occurs, add it directly.
c. If a non-terminal occurs, inherit its LEADING set until epsilon is absent.
5.	Compute TRAILING sets:
a. For each production, scan symbols from right to left.
b. If a terminal or epsilon occurs, add it directly.
c. If a non-terminal occurs, inherit its TRAILING set until epsilon is absent.
6.	Build the operator precedence table:
a. Assign “=” between consecutive operators.
b. Use LEADING sets to assign “<” relations between an operator and the next non-terminal.
c. Use TRAILING sets to assign “>” relations between a non-terminal and the following operator.
d. Handle non-terminal to non-terminal relations using their TRAILING and LEADING sets.
7.	Display the computed LEADING and TRAILING sets.
8.	Display the operator precedence table.
Code
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char operators[MAX];
int numOps = 0;

char productions[MAX][MAX];
int numProds = 0;

int precTable[MAX][MAX];

char leading[MAX][MAX];
int leadingCount[MAX];

char trailing[MAX][MAX];
int trailingCount[MAX];

int isNonTerminal(char c) {
    return (c >= 'A' && c <= 'Z');
}

int isOperator(char c) {
    return (c != '=' && c != '\0');
}

int indexOf(char c, char arr[], int sz) {
    for (int i = 0; i < sz; i++) {
        if (arr[i] == c) {
            return i;
        }
    }
    return -1;
}

int addChar(char arr[], int *count, char c) {
    if (indexOf(c, arr, *count) == -1) {
        arr[(*count)++] = c;
        return 1;
    }
    return 0;
}

void inputProductions() {
    printf("Enter number of productions: ");
    scanf("%d", &numProds);

    printf("Enter productions in form E=E+T (use # for epsilon):\n");
    for (int i = 0; i < numProds; i++) {
        scanf("%s", productions[i]);
    }
}

void extractOperators() {
    for (int i = 0; i < numProds; i++) {
        int len = strlen(productions[i]);
        for (int j = 0; j < len; j++) {
            char c = productions[i][j];
            if (c == '=') continue;
            if (isOperator(c)) {
                addChar(operators, &numOps, c);
            }
        }
    }
    addChar(operators, &numOps, '#');
}

void initLeadingTrailing() {
    for (int i = 0; i < 26; i++) {
        leadingCount[i] = 0;
        trailingCount[i] = 0;
    }
}

int ntIndex(char c) {
    return c - 'A';
}

void computeLeading() {
    int changed;
    do {
        changed = 0;
        for (int p = 0; p < numProds; p++) {
            char lhs = productions[p][0];
            int lhsIdx = ntIndex(lhs);
            int len = strlen(productions[p]);

            for (int i = 2; i < len; i++) {
                char c = productions[p][i];

                if (c == '#') {
                    changed |= addChar(leading[lhsIdx], &leadingCount[lhsIdx], '#');
                    break;
                } else if (!isNonTerminal(c)) {
                    changed |= addChar(leading[lhsIdx], &leadingCount[lhsIdx], c);
                    break;
                } else {
                    int cIdx = ntIndex(c);
                    for (int k = 0; k < leadingCount[cIdx]; k++) {
                        changed |= addChar(leading[lhsIdx], &leadingCount[lhsIdx], leading[cIdx][k]);
                    }
                    int hasEpsilon = (indexOf('#', leading[cIdx], leadingCount[cIdx]) != -1);
                    if (!hasEpsilon) break;
                }
            }
        }
    } while (changed);
}

void computeTrailing() {
    int changed;
    do {
        changed = 0;
        for (int p = 0; p < numProds; p++) {
            char lhs = productions[p][0];
            int lhsIdx = ntIndex(lhs);
            int len = strlen(productions[p]);

            for (int i = len - 1; i >= 2; i--) {
                char c = productions[p][i];

                if (c == '#') {
                    changed |= addChar(trailing[lhsIdx], &trailingCount[lhsIdx], '#');
                    break;
                } else if (!isNonTerminal(c)) {
                    changed |= addChar(trailing[lhsIdx], &trailingCount[lhsIdx], c);
                    break;
                } else {
                    int cIdx = ntIndex(c);
                    for (int k = 0; k < trailingCount[cIdx]; k++) {
                        changed |= addChar(trailing[lhsIdx], &trailingCount[lhsIdx], trailing[cIdx][k]);
                    }
                    int hasEpsilon = (indexOf('#', trailing[cIdx], trailingCount[cIdx]) != -1);
                    if (!hasEpsilon) break;
                }
            }
        }
    } while (changed);
}

void initPrecedenceTable() {
    for (int i = 0; i < numOps; i++) {
        for (int j = 0; j < numOps; j++) {
            precTable[i][j] = 99;
        }
    }
}

void buildPrecedenceTable() {
    initPrecedenceTable();

    for (int p = 0; p < numProds; p++) {
        int len = strlen(productions[p]);
        for (int i = 2; i < len - 1; i++) {
            char a = productions[p][i];
            char b = productions[p][i + 1];

            if (!isOperator(a) || !isOperator(b)) continue;

            int ai = indexOf(a, operators, numOps);
            int bi = indexOf(b, operators, numOps);
            if (ai == -1 || bi == -1) continue;

            precTable[ai][bi] = 0;

            if (isOperator(a) && isNonTerminal(b)) {
                int bIdx = ntIndex(b);
                for (int k = 0; k < leadingCount[bIdx]; k++) {
                    int lk = indexOf(leading[bIdx][k], operators, numOps);
                    if (lk != -1) precTable[ai][lk] = -1;
                }
            }

            if (isNonTerminal(a) && isOperator(b)) {
                int aIdx = ntIndex(a);
                for (int k = 0; k < trailingCount[aIdx]; k++) {
                    int tk = indexOf(trailing[aIdx][k], operators, numOps);
                    if (tk != -1) precTable[tk][bi] = 1;
                }
            }

            if (isNonTerminal(a) && isNonTerminal(b)) {
                int aIdx = ntIndex(a);
                int bIdx = ntIndex(b);
                for (int ta = 0; ta < trailingCount[aIdx]; ta++) {
                    int tIndex = indexOf(trailing[aIdx][ta], operators, numOps);
                    if (tIndex == -1) continue;
                    for (int lb = 0; lb < leadingCount[bIdx]; lb++) {
                        int lIndex = indexOf(leading[bIdx][lb], operators, numOps);
                        if (lIndex == -1) continue;
                        precTable[tIndex][lIndex] = 1;
                    }
                }
            }
        }
    }
}

void printLeadingTrailing() {
    printf("\nLEADING sets:\n");
    for (int i = 0; i < numProds; i++) {
        char nt = productions[i][0];
        int idx = ntIndex(nt);
        printf("LEADING(%c) = { ", nt);
        for (int j = 0; j < leadingCount[idx]; j++) {
            printf("%c ", leading[idx][j]);
        }
        printf("}\n");
    }

    printf("\nTRAILING sets:\n");
    for (int i = 0; i < numProds; i++) {
        char nt = productions[i][0];
        int idx = ntIndex(nt);
        printf("TRAILING(%c) = { ", nt);
        for (int j = 0; j < trailingCount[idx]; j++) {
            printf("%c ", trailing[idx][j]);
        }
        printf("}\n");
    }
}

void printPrecedenceTable() {
    printf("\nOperator Precedence Table:\n\t");
    for (int i = 0; i < numOps; i++) {
        printf("%c\t", operators[i]);
    }
    printf("\n");

    for (int i = 0; i < numOps; i++) {
        printf("%c\t", operators[i]);
        for (int j = 0; j < numOps; j++) {
            if (precTable[i][j] == -1) printf("<\t");
            else if (precTable[i][j] == 1) printf(">\t");
            else if (precTable[i][j] == 0) printf("=\t");
            else printf("-\t");
        }
        printf("\n");
    }
}

int main() {
    inputProductions();
    extractOperators();
    initLeadingTrailing();

    computeLeading();
    computeTrailing();
    printLeadingTrailing();

    buildPrecedenceTable();
    printPrecedenceTable();

    return 0;
}
Output
 
Aim
To implement a C program that computes LEADING and TRAILING sets, constructs an operator precedence table, and parses an input string using operator precedence parsing.
Algorithm
1.	Input the number of productions and store all grammar rules.
2.	Extract non-terminals from the left-hand side of productions.
3.	Extract terminals from the right-hand side of productions and add # as an end marker.
4.	Compute LEADING sets for each non-terminal by scanning the first symbols of right-hand sides and propagating results through non-terminals.
5.	Compute TRAILING sets for each non-terminal by scanning the last symbols of right-hand sides and propagating results through non-terminals.
6.	Construct the operator precedence table by:
a. Setting relations (=) between consecutive terminals in productions.
b. Using LEADING sets to assign (<) relations between terminal and following non-terminal.
c. Using TRAILING sets to assign (>) relations between non-terminal and following terminal.
d. Adding precedence relations with #.
7.	Display the operator precedence table.
8.	Perform operator precedence parsing:
a. Initialize stack with #.
b. Scan input from left to right.
c. Shift operands and immediately reduce them to E.
d. Use the precedence table to decide shift or reduce for operators.
e. Continue until input and stack reduce to E#.
f. Accept if parsing is successful; otherwise reject.
Code
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

char productions[MAX][MAX];
int numProds = 0;

char nonTerminals[MAX];
int numNT = 0;

char terminals[MAX];
int numT = 0;

char leading[MAX][MAX];
int leadCount[MAX];
char trailing[MAX][MAX];
int trailCount[MAX];

int precTable[MAX][MAX];

int isNonTerminal(char c) {
    return (c >= 'A' && c <= 'Z');
}

int isTerminal(char c) {
    return (!isNonTerminal(c));
}

int addToSet(char c, char set[][MAX], int idx, int *count) {
    for (int i = 0; i < *count; i++) {
        if (set[idx][i] == c) {
            return 0;
        }
    }
    set[idx][(*count)++] = c;
    return 1;
}

int indexOf(char c, char arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == c) {
            return i;
        }
    }
    return -1;
}

void extractNonTerminals() {
    for (int i = 0; i < numProds; i++) {
        char nt = productions[i][0];
        if (indexOf(nt, nonTerminals, numNT) == -1) {
            nonTerminals[numNT++] = nt;
        }
    }
}

void extractTerminals() {
    for (int i = 0; i < numProds; i++) {
        int len = strlen(productions[i]);
        for (int j = 2; j < len; j++) {
            char c = productions[i][j];
            if (!isNonTerminal(c) && indexOf(c, terminals, numT) == -1) {
                terminals[numT++] = c;
            }
        }
    }
    if (indexOf('#', terminals, numT) == -1) {
        terminals[numT++] = '#';
    }
}

void computeLeading() {
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < numProds; i++) {
            char A = productions[i][0];
            int idxA = indexOf(A, nonTerminals, numNT);
            char *rhs = productions[i] + 2;

            if (rhs[0] != '\0') {
                if (isTerminal(rhs[0])) {
                    changed |= addToSet(rhs[0], leading, idxA, &leadCount[idxA]);
                } else if (isNonTerminal(rhs[0])) {
                    int idxB = indexOf(rhs[0], nonTerminals, numNT);
                    for (int k = 0; k < leadCount[idxB]; k++) {
                        changed |= addToSet(leading[idxB][k], leading, idxA, &leadCount[idxA]);
                    }
                }
                if (rhs[0] && rhs[1]) {
                    if (isTerminal(rhs[1])) {
                        changed |= addToSet(rhs[1], leading, idxA, &leadCount[idxA]);
                    }
                }
            }
        }
    } while (changed);
}

void computeTrailing() {
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < numProds; i++) {
            char A = productions[i][0];
            int idxA = indexOf(A, nonTerminals, numNT);
            char *rhs = productions[i] + 2;
            int len = strlen(rhs);

            if (len > 0) {
                char last = rhs[len - 1];
                if (isTerminal(last)) {
                    changed |= addToSet(last, trailing, idxA, &trailCount[idxA]);
                } else if (isNonTerminal(last)) {
                    int idxB = indexOf(last, nonTerminals, numNT);
                    for (int k = 0; k < trailCount[idxB]; k++) {
                        changed |= addToSet(trailing[idxB][k], trailing, idxA, &trailCount[idxA]);
                    }
                }
                if (len > 1) {
                    char secondLast = rhs[len - 2];
                    if (isTerminal(secondLast)) {
                        changed |= addToSet(secondLast, trailing, idxA, &trailCount[idxA]);
                    }
                }
            }
        }
    } while (changed);
}

void buildPrecedenceTable() {
    for (int i = 0; i < numT; i++) {
        for (int j = 0; j < numT; j++) {
            precTable[i][j] = 99;
        }
    }

    for (int i = 0; i < numProds; i++) {
        char *rhs = productions[i] + 2;
        int len = strlen(rhs);

        for (int j = 0; j < len - 1; j++) {
            char a = rhs[j];
            char b = rhs[j + 1];

            if (isTerminal(a) && isTerminal(b)) {
                int ai = indexOf(a, terminals, numT);
                int bi = indexOf(b, terminals, numT);
                precTable[ai][bi] = 0;
            }

            if (isTerminal(a) && isNonTerminal(b)) {
                int ai = indexOf(a, terminals, numT);
                int bi = indexOf(b, nonTerminals, numNT);
                for (int k = 0; k < leadCount[bi]; k++) {
                    int tk = indexOf(leading[bi][k], terminals, numT);
                    if (tk != -1 && precTable[ai][tk] == 99) {
                        precTable[ai][tk] = -1;
                    }
                }
            }

            if (isNonTerminal(a) && isTerminal(b)) {
                int ai = indexOf(a, nonTerminals, numNT);
                int bi = indexOf(b, terminals, numT);
                for (int k = 0; k < trailCount[ai]; k++) {
                    int tk = indexOf(trailing[ai][k], terminals, numT);
                    if (tk != -1 && precTable[tk][bi] == 99) {
                        precTable[tk][bi] = 1;
                    }
                }
            }
        }
    }

    int hashIndex = indexOf('#', terminals, numT);
    for (int i = 0; i < numT; i++) {
        if (i != hashIndex) {
            precTable[hashIndex][i] = -1;
            precTable[i][hashIndex] = 1;
        } else {
            precTable[hashIndex][hashIndex] = 0;
        }
    }
}

void printPrecedenceTable() {
    printf("\nOperator Precedence Table:\n\t");
    for (int i = 0; i < numT; i++) {
        printf("%c\t", terminals[i]);
    }
    printf("\n");

    for (int i = 0; i < numT; i++) {
        printf("%c\t", terminals[i]);
        for (int j = 0; j < numT; j++) {
            if (precTable[i][j] == -1) {
                printf("<\t");
            } else if (precTable[i][j] == 0) {
                printf("=\t");
            } else if (precTable[i][j] == 1) {
                printf(">\t");
            } else {
                printf("-\t");
            }
        }
        printf("\n");
    }
}

int getPrecedence(char a, char b) {
    int i = indexOf(a, terminals, numT);
    int j = indexOf(b, terminals, numT);
    if (i == -1 || j == -1) {
        return 99;
    }
    return precTable[i][j];
}

int findTopTerminal(char stack[], int top) {
    for (int i = top; i >= 0; i--) {
        if (indexOf(stack[i], terminals, numT) != -1) {
            return i;
        }
    }
    return -1;
}

int canReduce(char stack[], int top) {
    if (top < 2) {
        return 0;
    }
    if (stack[top] == 'E' && stack[top - 2] == 'E' &&
        indexOf(stack[top - 1], terminals, numT) != -1) {
        return 1;
    }
    return 0;
}

void operatorPrecedenceParse(char input[]) {
    char stack[MAX];
    int top = -1;
    int i = 0;

    stack[++top] = '#';

    printf("\nOperator Precedence Parsing Steps:\n");
    printf("Stack\tInput\tAction\n");

    while (1) {
        for (int k = 0; k <= top; k++) {
            printf("%c", stack[k]);
        }
        printf("\t");

        printf("%s\t", &input[i]);

        char curr = input[i];

        if (top == 1 && stack[top] == 'E' && curr == '#') {
            printf("Accept (Parsing successful)\n");
            break;
        }

        if (isalnum(curr) && islower(curr)) {
            stack[++top] = curr;
            i++;
            printf("Shift operand %c\n", curr);
            stack[top] = 'E';
            printf("Reduce operand %c to E\n", curr);
            continue;
        }

        if (isalnum(curr) && isupper(curr)) {
            stack[++top] = curr;
            i++;
            printf("Shift operand %c\n", curr);
            stack[top] = 'E';
            printf("Reduce operand %c to E\n", curr);
            continue;
        }

        if (canReduce(stack, top)) {
            char op = stack[top - 1];
            printf("Reduce E%cE to E\n", op);
            top -= 2;
            stack[top] = 'E';
            continue;
        }

        int topTermIndex = findTopTerminal(stack, top);
        if (topTermIndex == -1) {
            printf("Error: No terminal in stack for precedence\n");
            break;
        }

        char topTerm = stack[topTermIndex];
        int prec = getPrecedence(topTerm, curr);

        if (prec == -1 || prec == 0) {
            stack[++top] = curr;
            i++;
            printf("Shift operator %c\n", curr);
        } else if (prec == 1) {
            printf("Error: Can't reduce operator %c without E operands\n", topTerm);
            break;
        } else {
            printf("Error: No precedence relation between %c and %c\n", topTerm, curr);
            break;
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &numProds);
    printf("Enter productions:\n");
    for (int i = 0; i < numProds; i++) {
        scanf("%s", productions[i]);
    }

    extractNonTerminals();
    extractTerminals();

    memset(leadCount, 0, sizeof(leadCount));
    memset(trailCount, 0, sizeof(trailCount));

    computeLeading();
    computeTrailing();

    buildPrecedenceTable();

    printPrecedenceTable();

    char inputStr[MAX];
    printf("\nEnter input string: ");
    scanf("%s", inputStr);

    operatorPrecedenceParse(inputStr);

    return 0;
}
Output
 

 
Experiment 9:
Aim
To write a C program that constructs the canonical collection of LR(0) items, computes FOLLOW sets, generates the SLR(1) parsing table, and parses a given input string.
Algorithm
1.	Input grammar productions and augment with a new start production Z -> S.
2.	Identify terminals and non-terminals, add $ as end marker.
3.	Compute FOLLOW sets for all non-terminals using grammar rules.
4.	Construct canonical collection of LR(0) items:
a. Initialize with augmented production and apply closure.
b. For each state and grammar symbol, compute GOTO to form new states.
c. Store states uniquely in the state collection.
5.	Build the SLR(1) parsing table:
a. If an item has a terminal after the dot, assign “Shift” action.
b. If an item is complete, assign “Reduce” action using FOLLOW sets.
c. For augmented production completion, assign “Accept”.
d. For non-terminals after the dot, record “Goto” transitions.
6.	Display FOLLOW sets and the parsing table.
7.	Parse input string:
a. Initialize stack with state 0 and symbol $.
b. At each step, consult parsing table using current state and input symbol.
c. Perform Shift, Reduce, or Accept based on the table entry.
d. Reject if no valid action exists.
Code:
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 

#define MAX_PRODUCTIONS 20 
#define MAX_SYMBOLS 25 
#define MAX_STATES 50 

typedef struct 
{ 
    char left_side; 
    char right_side[10]; 
} Production; 

typedef struct 
{ 
    int production_index; 
    int dot_position; 
} Item; 

typedef struct 
{ 
    Item item_list[MAX_PRODUCTIONS * 2]; 
    int item_count; 
} State; 

Production grammar_rules[MAX_PRODUCTIONS]; 
int total_productions; 
char non_terminal_symbols[MAX_SYMBOLS]; 
char terminal_symbols[MAX_SYMBOLS]; 
int non_terminal_count; 
int terminal_count; 
char follow_symbol_sets[MAX_SYMBOLS][MAX_SYMBOLS]; 
State state_collection[MAX_STATES]; 
int total_states; 
int goto_transition_table[MAX_STATES][MAX_SYMBOLS]; 
char parsing_table[MAX_STATES][MAX_SYMBOLS][10]; 
 
int parsing_state_stack[100]; 
char parsing_symbol_stack[100]; 
int stack_top = -1; 
 
int find_symbol_index(char symbol, const char *symbol_array, int array_size) 
{ 
    for (int index = 0; index < array_size; index++) 
        if (symbol_array[index] == symbol) return index; 
    return -1; 
} 
 
int add_symbol_to_set(char *symbol_set, char symbol) 
{ 
    int set_length = strlen(symbol_set); 
    for (int index = 0; index < set_length; index++) 
        if (symbol_set[index] == symbol) return 0; 
    symbol_set[set_length] = symbol; 
    symbol_set[set_length + 1] = '\0'; 
    return 1; 
} 
 
void compute_follow_sets() 
{ 
    int start_symbol_index = find_symbol_index(grammar_rules[1].left_side, non_terminal_symbols, non_terminal_count); 
    add_symbol_to_set(follow_symbol_sets[start_symbol_index], '$'); 
    int has_changed = 1; 
    while (has_changed) 
    { 
        has_changed = 0; 
        for (int production_num = 0; production_num < total_productions; production_num++) 
        { 
            if (grammar_rules[production_num].left_side == 'Z') continue; 
            char left_hand_side = grammar_rules[production_num].left_side; 
            char *right_hand_side = grammar_rules[production_num].right_side; 
            int lhs_index = find_symbol_index(left_hand_side, non_terminal_symbols, non_terminal_count); 
            for (int position = 0; position < strlen(right_hand_side); position++) 
            { 
                char current_symbol = right_hand_side[position]; 
                int symbol_index = find_symbol_index(current_symbol, non_terminal_symbols, non_terminal_count); 
                if (symbol_index == -1) continue; 
                int should_continue = 1; 
                for (int next_pos = position + 1; next_pos < strlen(right_hand_side) && should_continue; next_pos++) 
                { 
                    should_continue = 0; 
                    char next_symbol = right_hand_side[next_pos]; 
                    if (find_symbol_index(next_symbol, terminal_symbols, terminal_count) != -1) 
                    { 
                        if (add_symbol_to_set(follow_symbol_sets[symbol_index], next_symbol)) has_changed = 1; 
                    } 
                    else 
                    { 
                        int next_nt_index = find_symbol_index(next_symbol, non_terminal_symbols, non_terminal_count); 
                        char *first_set = follow_symbol_sets[next_nt_index]; 
                        for (int first_index = 0; first_index < strlen(first_set); first_index++) 
                        { 
                            if (first_set[first_index] == '#') should_continue = 1; 
                            else if (add_symbol_to_set(follow_symbol_sets[symbol_index], first_set[first_index])) has_changed = 1; 
                        } 
                    } 
                    if (!should_continue) break; 
                } 
                if (should_continue) 
                { 
                    char *lhs_follow_set = follow_symbol_sets[lhs_index]; 
                    for (int follow_index = 0; follow_index < strlen(lhs_follow_set); follow_index++) 
                        if (add_symbol_to_set(follow_symbol_sets[symbol_index], lhs_follow_set[follow_index])) has_changed = 1; 
                } 
            } 
        } 
    } 
} 
 
int item_exists_in_state(const State *current_state, const Item *target_item) 
{ 
    for (int item_index = 0; item_index < current_state->item_count; item_index++) 
        if (current_state->item_list[item_index].production_index == target_item->production_index && 
            current_state->item_list[item_index].dot_position == target_item->dot_position) return 1; 
    return 0; 
} 
 
void add_item_to_state(State *current_state, const Item *new_item) 
{ 
    if (!item_exists_in_state(current_state, new_item)) 
        current_state->item_list[current_state->item_count++] = *new_item; 
} 
 
void compute_closure(State *current_state) 
{ 
    int has_changed = 1; 
    while (has_changed) 
    { 
        has_changed = 0; 
        for (int item_index = 0; item_index < current_state->item_count; item_index++) 
        { 
            Item current_item = current_state->item_list[item_index]; 
            char *production_right_side = grammar_rules[current_item.production_index].right_side; 
            if (current_item.dot_position < strlen(production_right_side)) 
            { 
                char symbol_after_dot = production_right_side[current_item.dot_position]; 
                if (find_symbol_index(symbol_after_dot, non_terminal_symbols, non_terminal_count) != -1) 
                { 
                    for (int prod_index = 0; prod_index < total_productions; prod_index++) 
                    { 
                        if (grammar_rules[prod_index].left_side == symbol_after_dot) 
                        { 
                            Item new_item = {prod_index, 0}; 
                            if (!item_exists_in_state(current_state, &new_item)) 
                            { 
                                add_item_to_state(current_state, &new_item); 
                                has_changed = 1; 
                            } 
                        } 
                    } 
                } 
            } 
        } 
    } 
} 
 
int state_already_exists(const State *target_state) 
{ 
    for (int state_index = 0; state_index < total_states; state_index++) 
    { 
        if (state_collection[state_index].item_count == target_state->item_count) 
        { 
            int states_match = 1; 
            for (int item_index = 0; item_index < target_state->item_count; item_index++) 
                if (!item_exists_in_state(&state_collection[state_index], &target_state->item_list[item_index])) { 
                    states_match = 0; 
                    break; 
                } 
            if (states_match) return state_index; 
        } 
    } 
    return -1; 
} 
 
void perform_goto_operation(int current_state_index, char transition_symbol, State *next_state) 
{ 
    next_state->item_count = 0; 
    State *current_state = &state_collection[current_state_index]; 
    for (int item_index = 0; item_index < current_state->item_count; item_index++) 
    { 
        Item current_item = current_state->item_list[item_index]; 
        char *production_right_side = grammar_rules[current_item.production_index].right_side; 
        if (current_item.dot_position < strlen(production_right_side) && 
            production_right_side[current_item.dot_position] == transition_symbol) 
        { 
            Item new_item = {current_item.production_index, current_item.dot_position + 1}; 
            add_item_to_state(next_state, &new_item); 
        } 
    } 
    if (next_state->item_count > 0) compute_closure(next_state); 
} 
 
void build_canonical_collection() 
{ 
    State initial_state; 
    initial_state.item_count = 0; 
    Item start_item = {0, 0}; 
    add_item_to_state(&initial_state, &start_item); 
    compute_closure(&initial_state); 
    state_collection[total_states++] = initial_state; 
    
    for (int state_index = 0; state_index < total_states; state_index++) 
    { 
        for (int nt_index = 0; nt_index < non_terminal_count; nt_index++) 
        { 
            char non_terminal = non_terminal_symbols[nt_index]; 
            State next_state; 
            perform_goto_operation(state_index, non_terminal, &next_state); 
            if (next_state.item_count > 0) 
            { 
                int existing_state_index = state_already_exists(&next_state); 
                if (existing_state_index == -1) { 
                    state_collection[total_states] = next_state; 
                    existing_state_index = total_states++; 
                } 
                int symbol_index = find_symbol_index(non_terminal, non_terminal_symbols, non_terminal_count); 
                goto_transition_table[state_index][terminal_count + symbol_index] = existing_state_index; 
            } 
        } 
        for (int term_index = 0; term_index < terminal_count; term_index++) 
        { 
            char terminal = terminal_symbols[term_index]; 
            if (terminal == '$') continue; 
            State next_state; 
            perform_goto_operation(state_index, terminal, &next_state); 
            if (next_state.item_count > 0) 
            { 
                int existing_state_index = state_already_exists(&next_state); 
                if (existing_state_index == -1) { 
                    state_collection[total_states] = next_state; 
                    existing_state_index = total_states++; 
                } 
                int symbol_index = find_symbol_index(terminal, terminal_symbols, terminal_count); 
                goto_transition_table[state_index][symbol_index] = existing_state_index; 
            } 
        } 
    } 
} 
 
void set_parse_table_entry(int row, int column, const char *action) 
{ 
    strcpy(parsing_table[row][column], action); 
} 
 
void create_parse_table() 
{ 
    for (int state_index = 0; state_index < total_states; state_index++) 
    { 
        for (int item_index = 0; item_index < state_collection[state_index].item_count; item_index++) 
        { 
            Item current_item = state_collection[state_index].item_list[item_index]; 
            char *production_right_side = grammar_rules[current_item.production_index].right_side; 
            int production_length = (production_right_side[0] == '#') ? 0 : strlen(production_right_side); 
            
            if (current_item.dot_position < production_length) 
            { 
                char symbol_after_dot = production_right_side[current_item.dot_position]; 
                int terminal_index = find_symbol_index(symbol_after_dot, terminal_symbols, terminal_count); 
                if (terminal_index != -1) 
                { 
                    int next_state = goto_transition_table[state_index][terminal_index]; 
                    if (next_state != -1) 
                    { 
                        char action[10]; 
                        sprintf(action, "S%d", next_state); 
                        set_parse_table_entry(state_index, terminal_index, action); 
                    } 
                } 
            } 
            else 
            { 
                if (current_item.production_index == 0) 
                { 
                    int dollar_index = find_symbol_index('$', terminal_symbols, terminal_count); 
                    set_parse_table_entry(state_index, dollar_index, "Acc"); 
                } 
                else 
                { 
                    char left_hand_side = grammar_rules[current_item.production_index].left_side; 
                    int nt_index = find_symbol_index(left_hand_side, non_terminal_symbols, non_terminal_count); 
                    char *follow_set = follow_symbol_sets[nt_index]; 
                    for (int follow_index = 0; follow_index < strlen(follow_set); follow_index++) 
                    { 
                        int terminal_index = find_symbol_index(follow_set[follow_index], terminal_symbols, terminal_count); 
                        if (terminal_index != -1) 
                        { 
                            char action[10]; 
                            sprintf(action, "R%d", current_item.production_index); 
                            set_parse_table_entry(state_index, terminal_index, action); 
                        } 
                    } 
                } 
            } 
        } 
        for (int nt_index = 0; nt_index < non_terminal_count; nt_index++) 
        { 
            int column = terminal_count + nt_index; 
            int next_state = goto_transition_table[state_index][column]; 
            if (next_state != -1) 
            { 
                char action[10]; 
                sprintf(action, "%d", next_state); 
                set_parse_table_entry(state_index, column, action); 
            } 
        } 
    } 
} 
 
void print_follow_sets() 
{ 
    printf("\nFOLLOW sets:\n"); 
    for (int nt_index = 0; nt_index < non_terminal_count; nt_index++) 
        if (non_terminal_symbols[nt_index] != 'Z') 
            printf("FOLLOW(%c): %s\n", non_terminal_symbols[nt_index], follow_symbol_sets[nt_index]); 
} 
 
void print_parse_table() 
{ 
    printf("\n--- SLR PARSE TABLE ---\n\n"); 
    printf("%-5s|", "STATE"); 
    for (int term_index = 0; term_index < terminal_count; term_index++) 
        printf(" %-4c|", terminal_symbols[term_index]); 
    printf("|"); 
    for (int nt_index = 0; nt_index < non_terminal_count; nt_index++) 
        if(non_terminal_symbols[nt_index] != 'Z') 
            printf(" %-4c|", non_terminal_symbols[nt_index]); 
    printf("\n"); 
    
    for (int dash_index = 0; dash_index < 6 + (terminal_count * 6) + 1 + (non_terminal_count-1)*6; dash_index++) 
        printf("-"); 
    printf("\n"); 
    
    for (int state_index = 0; state_index < total_states; state_index++) 
    { 
        printf("%-5d|", state_index); 
        for (int term_index = 0; term_index < terminal_count; term_index++) 
            printf(" %-4s|", parsing_table[state_index][term_index]); 
        printf("|"); 
        for (int nt_index = 0; nt_index < non_terminal_count; nt_index++) 
            if(non_terminal_symbols[nt_index] != 'Z') 
                printf(" %-4s|", parsing_table[state_index][terminal_count+nt_index]); 
        printf("\n"); 
    } 
} 
 
void parse_input_string(char input_string[]) 
{ 
    int input_pointer = 0; 
    stack_top = -1; 
    parsing_state_stack[++stack_top] = 0; 
    parsing_symbol_stack[stack_top] = '$'; 
    printf("\nParsing Steps:\n"); 
    
    while (1) 
    { 
        int current_state = parsing_state_stack[stack_top]; 
        int current_symbol_index = find_symbol_index(input_string[input_pointer], terminal_symbols, terminal_count); 
        if (current_symbol_index == -1) { 
            printf("Error\n"); 
            return; 
        } 
        char *action = parsing_table[current_state][current_symbol_index]; 
        printf("StackTopState=%d, Symbol=%c, Action=%s\n", current_state, input_string[input_pointer], action); 
        
        if (action[0] == 'S') 
        { 
            int next_state = atoi(action + 1); 
            stack_top++; 
            parsing_symbol_stack[stack_top] = input_string[input_pointer]; 
            parsing_state_stack[stack_top] = next_state; 
            input_pointer++; 
        } 
        else if (action[0] == 'R') 
        { 
            int production_num = atoi(action + 1); 
            int production_length = strlen(grammar_rules[production_num].right_side); 
            if (grammar_rules[production_num].right_side[0] == '#') production_length = 0; 
            stack_top -= production_length; 
            char left_hand_side = grammar_rules[production_num].left_side; 
            int previous_state = parsing_state_stack[stack_top]; 
            int lhs_index = find_symbol_index(left_hand_side, non_terminal_symbols, non_terminal_count); 
            int column = terminal_count + lhs_index; 
            int next_state = atoi(parsing_table[previous_state][column]); 
            stack_top++; 
            parsing_symbol_stack[stack_top] = left_hand_side; 
            parsing_state_stack[stack_top] = next_state; 
        } 
        else if (strcmp(action, "Acc") == 0) 
        { 
            printf("String Accepted\n"); 
            return; 
        } 
        else 
        { 
            printf("Rejected\n"); 
            return; 
        } 
    } 
} 
 
int main() 
{ 
    total_productions = 0; 
    non_terminal_count = 0; 
    terminal_count = 0; 
    total_states = 0; 
    
    printf("Enter number of productions: "); 
    int number_of_productions;  
    scanf("%d", &number_of_productions); 
    
    Production temporary_productions[MAX_PRODUCTIONS]; 
    for (int prod_index = 0; prod_index < number_of_productions; prod_index++) 
    { 
        char production_string[20]; 
        scanf("%s", production_string); 
        temporary_productions[prod_index].left_side = production_string[0]; 
        strcpy(temporary_productions[prod_index].right_side, production_string + 2); 
    } 
    
    grammar_rules[0].left_side = 'Z'; 
    grammar_rules[0].right_side[0] = temporary_productions[0].left_side; 
    grammar_rules[0].right_side[1] = '\0'; 
    
    for (int prod_index = 0; prod_index < number_of_productions; prod_index++) 
        grammar_rules[prod_index+1] = temporary_productions[prod_index]; 
    
    total_productions = number_of_productions + 1; 
    non_terminal_symbols[non_terminal_count++] = 'Z'; 
    
    for (int prod_index = 0; prod_index < total_productions; prod_index++) 
    { 
        if (find_symbol_index(grammar_rules[prod_index].left_side, non_terminal_symbols, non_terminal_count) == -1) 
            non_terminal_symbols[non_terminal_count++] = grammar_rules[prod_index].left_side; 
        for (int char_index = 0; char_index < strlen(grammar_rules[prod_index].right_side); char_index++) 
        { 
            char current_char = grammar_rules[prod_index].right_side[char_index]; 
            if (isupper(current_char)) 
            { 
                if (find_symbol_index(current_char, non_terminal_symbols, non_terminal_count) == -1) 
                    non_terminal_symbols[non_terminal_count++] = current_char; 
            } 
            else if (current_char != '#') 
            { 
                if (find_symbol_index(current_char, terminal_symbols, terminal_count) == -1) 
                    terminal_symbols[terminal_count++] = current_char; 
            } 
        } 
    } 
    terminal_symbols[terminal_count++] = '$'; 
    
    compute_follow_sets(); 
    build_canonical_collection(); 
    create_parse_table(); 
    print_follow_sets(); 
    print_parse_table(); 
    
    char input_string[50]; 
    printf("\nEnter input string ending with $: "); 
    scanf("%s", input_string); 
    parse_input_string(input_string); 
    
    return 0; 
}
Output:
 
 

 
Experiment 10:
Aim
To implement a C program that constructs CLR(1) parsing tables by generating LR(1) items, building the canonical collection of states, computing FIRST and FOLLOW sets, and parsing an input string using ACTION and GOTO tables.
Algorithm
1.	Input grammar productions and augment with new start symbol Z->S.
2.	Identify terminals and non-terminals, then compute FIRST and FOLLOW sets iteratively.
3.	Generate LR(1) items with dot position and lookahead.
4.	Compute closure by adding items for non-terminals after the dot with appropriate lookaheads.
5.	Apply GOTO operation to build new states from existing ones, forming the canonical collection of LR(1) item sets.
6.	Construct parsing tables:
– If dot precedes a terminal, enter shift action.
– If item is complete, enter reduce using FOLLOW of LHS.
– If augmented item is complete, mark accept.
– Non-terminal transitions fill GOTO table.
7.	Display CLR(1) states, FOLLOW sets, and ACTION/GOTO table.
8.	Parse input string using stack operations: shift, reduce, goto, or accept.
Code:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTIONS 30
#define MAX_SYMBOLS 30
#define MAX_STATES 200
#define MAX_RHS 30
#define MAX_ITEMS (MAX_PRODUCTIONS * MAX_RHS)

typedef struct
{
    char left;
    char right[MAX_RHS];
} Production;

Production productions[MAX_PRODUCTIONS];
int production_count = 0;

char nonterminals[MAX_SYMBOLS];
char terminals[MAX_SYMBOLS];
int nonterminal_count = 0;
int terminal_count = 0;

char first_sets[MAX_SYMBOLS][MAX_SYMBOLS];
char follow_sets[MAX_SYMBOLS][MAX_SYMBOLS];

typedef struct
{
    int prod_index;
    int dot;
    char lookahead;
} LRItem;

typedef struct
{
    LRItem items[MAX_ITEMS];
    int count;
} LRItemSet;

LRItemSet canonical_sets[MAX_STATES];
int state_count = 0;

int goto_table[MAX_STATES][MAX_SYMBOLS];
char action_table[MAX_STATES][MAX_SYMBOLS][10];

int index_of(char c, char arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == c)
        {
            return i;
        }
    }
    return -1;
}

int add_symbol(char c, char arr[], int *n)
{
    if (index_of(c, arr, *n) == -1)
    {
        arr[(*n)++] = c;
        return 1;
    }
    return 0;
}

int set_add(char set[], char c)
{
    if (strchr(set, c) == NULL)
    {
        int l = strlen(set);
        set[l] = c;
        set[l + 1] = '\0';
        return 1;
    }
    return 0;
}

void compute_first_sets()
{
    for (int i = 0; i < nonterminal_count + terminal_count; i++)
    {
        first_sets[i][0] = '\0';
    }
    for (int i = 0; i < terminal_count; i++)
    {
        int idx = nonterminal_count + i;
        first_sets[idx][0] = terminals[i];
        first_sets[idx][1] = '\0';
    }

    int changed = 1;
    while (changed)
    {
        changed = 0;
        for (int i = 0; i < production_count; i++)
        {
            char A = productions[i].left;
            int Ai = index_of(A, nonterminals, nonterminal_count);
            char *rhs = productions[i].right;

            if (rhs[0] == '#')
            {
                if (set_add(first_sets[Ai], '#'))
                {
                    changed = 1;
                }
                continue;
            }

            int k = 0;
            int cont = 1;
            while (rhs[k] != '\0' && cont)
            {
                cont = 0;
                char X = rhs[k];
                int idx;
                if (isupper(X))
                {
                    idx = index_of(X, nonterminals, nonterminal_count);
                }
                else
                {
                    idx = nonterminal_count + index_of(X, terminals, terminal_count);
                }

                for (int p = 0; p < strlen(first_sets[idx]); p++)
                {
                    char fc = first_sets[idx][p];
                    if (fc != '#')
                    {
                        if (set_add(first_sets[Ai], fc))
                        {
                            changed = 1;
                        }
                    }
                    else
                    {
                        cont = 1;
                    }
                }

                if (cont && rhs[k + 1] == '\0')
                {
                    if (set_add(first_sets[Ai], '#'))
                    {
                        changed = 1;
                    }
                }
                k++;
            }
        }
    }
}

void compute_follow_sets()
{
    for (int i = 0; i < nonterminal_count; i++)
    {
        follow_sets[i][0] = '\0';
    }
    set_add(follow_sets[0], '$');

    int changed = 1;
    while (changed)
    {
        changed = 0;
        for (int i = 0; i < production_count; i++)
        {
            char A = productions[i].left;
            int Ai = index_of(A, nonterminals, nonterminal_count);
            char *rhs = productions[i].right;
            int len = strlen(rhs);

            for (int j = 0; j < len; j++)
            {
                char B = rhs[j];
                if (!isupper(B))
                {
                    continue;
                }
                int Bi = index_of(B, nonterminals, nonterminal_count);
                int cont = 1;
                for (int k = j + 1; k < len && cont; k++)
                {
                    cont = 0;
                    char Y = rhs[k];
                    int Yi;
                    if (isupper(Y))
                    {
                        Yi = index_of(Y, nonterminals, nonterminal_count);
                    }
                    else
                    {
                        Yi = nonterminal_count + index_of(Y, terminals, terminal_count);
                    }
                    for (int p = 0; p < strlen(first_sets[Yi]); p++)
                    {
                        char fc = first_sets[Yi][p];
                        if (fc != '#')
                        {
                            if (set_add(follow_sets[Bi], fc))
                            {
                                changed = 1;
                            }
                        }
                        else
                        {
                            cont = 1;
                        }
                    }
                }
                if (cont)
                {
                    for (int p = 0; p < strlen(follow_sets[Ai]); p++)
                    {
                        if (set_add(follow_sets[Bi], follow_sets[Ai][p]))
                        {
                            changed = 1;
                        }
                    }
                }
            }
        }
    }
}

int item_equals(const LRItem *a, const LRItem *b)
{
    return a->prod_index == b->prod_index && a->dot == b->dot && a->lookahead == b->lookahead;
}

int item_in_set(const LRItemSet *s, const LRItem *it)
{
    for (int i = 0; i < s->count; i++)
    {
        if (item_equals(&s->items[i], it))
        {
            return 1;
        }
    }
    return 0;
}

void add_item_to_set(LRItemSet *s, const LRItem *it)
{
    if (!item_in_set(s, it))
    {
        s->items[s->count++] = *it;
    }
}

void closure_itemset(LRItemSet *s)
{
    int changed = 1;
    while (changed)
    {
        changed = 0;
        for (int i = 0; i < s->count; i++)
        {
            LRItem it = s->items[i];
            char *rhs = productions[it.prod_index].right;
            if (it.dot < (int)strlen(rhs))
            {
                char B = rhs[it.dot];
                if (isupper(B))
                {
                    for (int p = 0; p < production_count; p++)
                    {
                        if (productions[p].left != B)
                        {
                            continue;
                        }
                        char lookahead_candidates[MAX_SYMBOLS];
                        lookahead_candidates[0] = it.lookahead;
                        lookahead_candidates[1] = '\0';
                        LRItem nit;
                        nit.prod_index = p;
                        nit.dot = 0;
                        for (int q = 0; lookahead_candidates[q] != '\0'; q++)
                        {
                            nit.lookahead = lookahead_candidates[q];
                            if (!item_in_set(s, &nit))
                            {
                                add_item_to_set(s, &nit);
                                changed = 1;
                            }
                        }
                    }
                }
            }
        }
    }
}

void goto_operation(const LRItemSet *cur, char X, LRItemSet *out)
{
    out->count = 0;
    for (int i = 0; i < cur->count; i++)
    {
        LRItem it = cur->items[i];
        char *rhs = productions[it.prod_index].right;
        if (it.dot < (int)strlen(rhs) && rhs[it.dot] == X)
        {
            LRItem nit;
            nit.prod_index = it.prod_index;
            nit.dot = it.dot + 1;
            nit.lookahead = it.lookahead;
            add_item_to_set(out, &nit);
        }
    }
    if (out->count > 0)
    {
        closure_itemset(out);
    }
}

int state_equal(const LRItemSet *a, const LRItemSet *b)
{
    if (a->count != b->count)
    {
        return 0;
    }
    for (int i = 0; i < a->count; i++)
    {
        int found = 0;
        for (int j = 0; j < b->count; j++)
        {
            if (item_equals(&a->items[i], &b->items[j]))
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            return 0;
        }
    }
    return 1;
}

int find_state_index(const LRItemSet *s)
{
    for (int i = 0; i < state_count; i++)
    {
        if (state_equal(s, &canonical_sets[i]))
        {
            return i;
        }
    }
    return -1;
}

void build_clr_states()
{
    for (int i = 0; i < MAX_STATES; i++)
    {
        for (int j = 0; j < MAX_SYMBOLS; j++)
        {
            goto_table[i][j] = -1;
            action_table[i][j][0] = '\0';
        }
    }

    state_count = 0;

    LRItemSet I0;
    I0.count = 0;
    LRItem it0;
    it0.prod_index = 0;
    it0.dot = 0;
    it0.lookahead = '$';
    add_item_to_set(&I0, &it0);
    closure_itemset(&I0);
    canonical_sets[state_count++] = I0;

    int changed = 1;
    while (changed)
    {
        changed = 0;
        for (int i = 0; i < state_count; i++)
        {
            LRItemSet cur = canonical_sets[i];
            char symbols[MAX_SYMBOLS];
            int sym_n = 0;

            for (int j = 0; j < cur.count; j++)
            {
                LRItem it = cur.items[j];
                char *rhs = productions[it.prod_index].right;
                if (it.dot < (int)strlen(rhs))
                {
                    char X = rhs[it.dot];
                    if (index_of(X, symbols, sym_n) == -1)
                    {
                        symbols[sym_n++] = X;
                    }
                }
            }

            for (int s = 0; s < sym_n; s++)
            {
                char X = symbols[s];
                LRItemSet gotoS;
                gotoS.count = 0;
                goto_operation(&cur, X, &gotoS);
                if (gotoS.count == 0)
                {
                    continue;
                }
                int found = find_state_index(&gotoS);
                if (found == -1)
                {
                    canonical_sets[state_count] = gotoS;
                    found = state_count;
                    state_count++;
                    changed = 1;
                }
                int idxsym;
                if (isupper(X))
                {
                    idxsym = index_of(X, nonterminals, nonterminal_count);
                    goto_table[i][terminal_count + idxsym] = found;
                }
                else
                {
                    idxsym = index_of(X, terminals, terminal_count);
                    goto_table[i][idxsym] = found;
                }
            }
        }
    }

    for (int i = 0; i < state_count; i++)
    {
        for (int j = 0; j < canonical_sets[i].count; j++)
        {
            LRItem it = canonical_sets[i].items[j];
            char *rhs = productions[it.prod_index].right;
            if (it.dot < (int)strlen(rhs))
            {
                char a = rhs[it.dot];
                if (!isupper(a))
                {
                    int col = index_of(a, terminals, terminal_count);
                    int g = goto_table[i][col];
                    if (g != -1)
                    {
                        sprintf(action_table[i][col], "S%d", g);
                    }
                }
            }
            else
            {
                if (it.prod_index == 0)
                {
                    int col = index_of('$', terminals, terminal_count);
                    strcpy(action_table[i][col], "acc");
                }
                else
                {
                    char A = productions[it.prod_index].left;
                    int Ai = index_of(A, nonterminals, nonterminal_count);
                    for (int p = 0; p < strlen(follow_sets[Ai]); p++)
                    {
                        char a = follow_sets[Ai][p];
                        int col = index_of(a, terminals, terminal_count);
                        if (col != -1)
                        {
                            sprintf(action_table[i][col], "R%d", it.prod_index);
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < state_count; i++)
    {
        for (int j = 0; j < nonterminal_count; j++)
        {
            int g = goto_table[i][terminal_count + j];
            if (g != -1)
            {
                char buf[10];
                sprintf(buf, "%d", g);
                strcpy(action_table[i][terminal_count + j], buf);
            }
        }
    }
}

void print_follow_sets()
{
    printf("\nFOLLOW sets\n");
    for (int i = 0; i < nonterminal_count; i++)
    {
        if (nonterminals[i] == 'Z')
        {
            continue;
        }
        printf("FOLLOW(%c) = ", nonterminals[i]);
        if (follow_sets[i][0] != '\0')
        {
            for (int j = 0; j < strlen(follow_sets[i]); j++)
            {
                printf("%c", follow_sets[i][j]);
            }
        }
        printf("\n");
    }
}

void print_states()
{
    for (int i = 0; i < state_count; i++)
    {
        printf("\nState %d\n", i);
        for (int j = 0; j < canonical_sets[i].count; j++)
        {
            LRItem it = canonical_sets[i].items[j];
            printf("[%c->", productions[it.prod_index].left);
            char *rhs = productions[it.prod_index].right;
            for (int k = 0; k < (int)strlen(rhs); k++)
            {
                if (k == it.dot)
                {
                    printf(".");
                }
                printf("%c", rhs[k]);
            }
            if (it.dot == (int)strlen(rhs))
            {
                printf(".");
            }
            printf(",%c]\n", it.lookahead);
        }
    }
}

void print_action_goto()
{
    printf("\nACTION and GOTO Table\n\t");
    for (int i = 0; i < terminal_count; i++)
    {
        printf("%c\t", terminals[i]);
    }
    for (int i = 0; i < nonterminal_count; i++)
    {
        printf("%c\t", nonterminals[i]);
    }
    printf("\n");

    for (int i = 0; i < state_count; i++)
    {
        printf("%d\t", i);
        for (int j = 0; j < terminal_count + nonterminal_count; j++)
        {
            if (action_table[i][j][0] != '\0')
            {
                printf("%s\t", action_table[i][j]);
            }
            else
            {
                printf("-\t");
            }
        }
        printf("\n");
    }
}

void lr_parse(char input[])
{
    int st_stack[200];
    char sym_stack[200];
    int top = -1;
    st_stack[++top] = 0;
    sym_stack[top] = '$';
    int ip = 0;
    printf("\nParsing steps\nStack\tInput\tAction\n");
    while (1)
    {
        for (int i = 0; i <= top; i++)
        {
            if (i > 0)
            {
                printf("%c%d", sym_stack[i], st_stack[i]);
            }
            else
            {
                printf("%c%d", sym_stack[i], st_stack[i]);
            }
        }
        printf("\t%s\t", input + ip);
        char a = input[ip];
        int col = index_of(a, terminals, terminal_count);
        if (col == -1)
        {
            printf("Error\n");
            return;
        }
        char action[10];
        strcpy(action, action_table[st_stack[top]][col]);
        if (action[0] == '\0')
        {
            printf("Error\n");
            return;
        }
        if (action[0] == 'S')
        {
            int s;
            sscanf(action + 1, "%d", &s);
            printf("Shift %c and go %d\n", a, s);
            st_stack[++top] = s;
            sym_stack[top] = a;
            ip++;
        }
        else if (action[0] == 'R')
        {
            int r;
            sscanf(action + 1, "%d", &r);
            Production pr = productions[r];
            int rlen = strlen(pr.right);
            if (rlen == 1 && pr.right[0] == '#')
            {
                printf("Reduce by %c->#\n", pr.left);
                int cur = st_stack[top];
                int col2 = index_of(pr.left, nonterminals, nonterminal_count);
                int goto_st = goto_table[cur][terminal_count + col2];
                st_stack[++top] = goto_st;
                sym_stack[top] = pr.left;
            }
            else
            {
                printf("Reduce by %c->%s\n", pr.left, pr.right);
                for (int k = 0; k < rlen; k++)
                {
                    top--;
                }
                int cur = st_stack[top];
                int col2 = index_of(pr.left, nonterminals, nonterminal_count);
                int goto_st = goto_table[cur][terminal_count + col2];
                st_stack[++top] = goto_st;
                sym_stack[top] = pr.left;
            }
        }
        else
        {
            if (strcmp(action, "acc") == 0)
            {
                printf("Accept\n");
                return;
            }
            else
            {
                printf("Error\n");
                return;
            }
        }
    }
}

int main()
{
    printf("Enter number of productions: ");
    int n;
    scanf("%d", &n);
    production_count = 0;
    for (int i = 0; i < n; i++)
    {
        char tmp[80];
        scanf("%s", tmp);
        productions[production_count].left = tmp[0];
        strcpy(productions[production_count].right, tmp + 2);
        production_count++;
    }

    char start = productions[0].left;
    for (int i = production_count; i >= 1; i--)
    {
        productions[i] = productions[i - 1];
    }
    productions[0].left = 'Z';
    productions[0].right[0] = start;
    productions[0].right[1] = '\0';
    production_count++;

    nonterminal_count = 0;
    terminal_count = 0;

    for (int i = 0; i < production_count; i++)
    {
        add_symbol(productions[i].left, nonterminals, &nonterminal_count);
    }
    for (int i = 0; i < production_count; i++)
    {
        for (int j = 0; productions[i].right[j] != '\0'; j++)
        {
            char c = productions[i].right[j];
            if (!isupper(c) && c != '#')
            {
                add_symbol(c, terminals, &terminal_count);
            }
        }
    }

    add_symbol('$', terminals, &terminal_count);

    for (int i = 0; i < nonterminal_count + terminal_count; i++)
    {
        first_sets[i][0] = '\0';
    }
    for (int i = 0; i < nonterminal_count; i++)
    {
        follow_sets[i][0] = '\0';
    }

    compute_first_sets();
    compute_follow_sets();
    build_clr_states();

    printf("\nProductions\n");
    for (int i = 0; i < production_count; i++)
    {
        printf("%d: %c=%s\n", i, productions[i].left, productions[i].right);
    }

    print_follow_sets();
    print_states();
    print_action_goto();

    char inp[200];
    printf("\nEnter input string ending with $: ");
    scanf("%s", inp);
    lr_parse(inp);

    return 0;
}
Output:
 
 

 
Experiment 11:
Aim:
To implement an LALR(1) parser that constructs the parse table and parses a given input string.
Algorithm Steps
1.	Input Grammar
o	Read number of productions from the user.
o	Insert an augmented production Z -> S (where S is the start symbol).
o	Store grammar productions in an array.
2.	Identify Grammar Symbols
o	Extract non-terminals (uppercase letters) from production left-hand sides.
o	Extract terminals (lowercase and special characters except #) from right-hand sides.
o	Add end marker symbol $ to terminal list.
3.	Compute FIRST Sets
o	Initialize FIRST for all terminals with themselves.
o	Iteratively update FIRST of non-terminals:
	If RHS starts with a terminal -> add it.
	If RHS starts with a non-terminal -> add its FIRST (except epsilon).
	If epsilon (#) is possible, propagate it.
4.	Construct Canonical LR(1) Collection (CLR)
o	Create initial item [Z -> •S, $].
o	Apply closure:
	If dot is before a non-terminal, add productions of that non-terminal with lookaheads from FIRST of the suffix.
o	Apply goto for each grammar symbol to form new states.
o	Repeat until no new states are generated.
5.	Merge States (CLR -> LALR)
o	Identify states with identical cores (production number + dot position).
o	Merge them into a single LALR state by combining lookaheads.
o	Update transitions accordingly.
6.	Build ACTION and GOTO Table
o	For each item in each LALR state:
	If item is [A -> α • a β, x] and a is a terminal -> add Shift action.
	If item is [A -> α •, x] and production is not augmented -> add Reduce action.
	If item is [Z -> S •, $] -> add Accept action.
o	For non-terminals after reduction -> update GOTO table.
7.	Display Parse Table
o	Print ACTION (terminals) and GOTO (non-terminals) table in tabular form with states as rows.
8.	Parsing the Input String
o	Initialize stack with state 0.
o	Repeat:
	Look at top state and current input symbol.
	Fetch action from parse table.
	If Shift -> push symbol and new state, advance input.
	If reduce -> pop RHS length, push LHS, follow GOTO, and push new state.
	If accept -> parsing successful.
	If no valid action -> report error.
9.	Output
o	Display step-by-step stack contents, input, and action.
o	Show whether the input string is accepted or rejected.
Code:
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 

#define MAX_PROD 25 
#define MAX_SYMBOLS 25 
#define MAX_STATES 100 
#define MAX_RHS_LEN 15 

typedef struct  
{ 
    char lhs; 
    char rhs[MAX_RHS_LEN]; 
} Grammar; 

typedef struct  
{ 
    int production_num; 
    int position; 
    char next_symbol; 
} LR_Item; 

typedef struct  
{ 
    LR_Item elements[MAX_PROD * 5]; 
    int count; 
} ItemSet; 

typedef struct  
{ 
    int production_num; 
    int position; 
} CoreItem; 

Grammar rules[MAX_PROD]; 
int total_productions = 0; 
char nonterminals[MAX_SYMBOLS]; 
char symbols[MAX_SYMBOLS]; 
int nonterminal_count = 0; 
int symbol_count = 0; 
char first_collection[MAX_SYMBOLS][MAX_SYMBOLS]; 
ItemSet clr_itemsets[MAX_STATES]; 
int clr_count = 0; 
int clr_transitions[MAX_STATES][MAX_SYMBOLS]; 
ItemSet lalr_itemsets[MAX_STATES]; 
int lalr_count = 0; 
int lalr_labels[MAX_STATES]; 
int mapping[MAX_STATES]; 
int lalr_transitions[MAX_STATES][MAX_SYMBOLS]; 
char action_goto[MAX_STATES][MAX_SYMBOLS][10]; 
int parser_stack[100]; 
char stack_symbols[100]; 
int stack_top = -1; 

int locate_symbol(char sym, const char* array, int size)  
{ 
    for (int i = 0; i < size; i++) 
        if (array[i] == sym) return i; 
    return -1; 
}

int insert_symbol(char* collection, char sym)  
{ 
    int length = strlen(collection); 
    for (int i = 0; i < length; i++) 
        if (collection[i] == sym) return 0; 
    collection[length] = sym; 
    collection[length + 1] = '\0'; 
    return 1; 
}

void calculate_first()  
{ 
    for (int i = 0; i < symbol_count; i++)  
    { 
        int pos = locate_symbol(symbols[i], symbols, symbol_count); 
        insert_symbol(first_collection[nonterminal_count + pos], symbols[i]); 
    } 
    
    int modified = 1; 
    while (modified)  
    { 
        modified = 0; 
        for (int i = 0; i < total_productions; i++)  
        { 
            char head = rules[i].lhs; 
            char* body = rules[i].rhs; 
            int head_pos = locate_symbol(head, nonterminals, nonterminal_count); 
            
            if (body[0] == '#')  
            { 
                if (insert_symbol(first_collection[head_pos], '#')) modified = 1; 
                continue; 
            } 
            
            int nullable = 1; 
            for (int k = 0; k < strlen(body) && nullable; k++)  
            { 
                nullable = 0; 
                char current = body[k]; 
                int nt_pos = locate_symbol(current, nonterminals, nonterminal_count); 
                int t_pos = locate_symbol(current, symbols, symbol_count); 
                char* current_first = (nt_pos != -1) ? first_collection[nt_pos] :  
                                     first_collection[nonterminal_count + t_pos]; 
                
                for(int j = 0; j < strlen(current_first); j++)  
                { 
                    if (current_first[j] == '#')  
                    { 
                        nullable = 1; 
                    }  
                    else  
                    { 
                        if (insert_symbol(first_collection[head_pos], current_first[j])) modified = 1; 
                    } 
                } 
            } 
            
            if (nullable)  
            { 
                if (insert_symbol(first_collection[head_pos], '#')) modified = 1; 
            } 
        } 
    } 
} 
 
void get_first_of_sequence(const char* sequence, char* output)  
{ 
    output[0] = '\0'; 
    if (strlen(sequence) == 0)  
    { 
        insert_symbol(output, '#'); 
        return; 
    } 
    
    int epsilon_possible = 1; 
    for (int i = 0; i < strlen(sequence); i++)  
    { 
        char current = sequence[i]; 
        char current_first[MAX_SYMBOLS] = {0}; 
        int epsilon_found = 0; 
        
        int nt_pos = locate_symbol(current, nonterminals, nonterminal_count); 
        if (nt_pos != -1)  
        { 
            strcpy(current_first, first_collection[nt_pos]); 
        }  
        else  
        { 
            int t_pos = locate_symbol(current, symbols, symbol_count); 
            if(t_pos != -1) strcpy(current_first, first_collection[nonterminal_count + t_pos]); 
        } 
        
        for (int j = 0; j < strlen(current_first); j++)  
        { 
            if (current_first[j] == '#')  
            { 
                epsilon_found = 1; 
            }  
            else  
            { 
                insert_symbol(output, current_first[j]); 
            } 
        } 
        
        if (!epsilon_found)  
        { 
            epsilon_possible = 0; 
            break; 
        } 
    } 
    
    if (epsilon_possible)  
    { 
        insert_symbol(output, '#'); 
    } 
} 
 
int item_present(const ItemSet* set, const LR_Item* item)  
{ 
    for (int i = 0; i < set->count; i++)  
    { 
        if (set->elements[i].production_num == item->production_num &&  
            set->elements[i].position == item->position &&  
            set->elements[i].next_symbol == item->next_symbol)  
        { 
            return 1; 
        } 
    } 
    return 0; 
} 
 
void add_item_to_set(ItemSet* set, const LR_Item* item)  
{ 
    if (!item_present(set, item))  
    { 
        set->elements[set->count++] = *item; 
    } 
} 
 
void compute_closure(ItemSet* set)  
{ 
    int changed = 1; 
    while (changed)  
    { 
        changed = 0; 
        for (int i = 0; i < set->count; i++)  
        { 
            LR_Item current = set->elements[i]; 
            char* body = rules[current.production_num].rhs; 
            
            if (current.position < strlen(body))  
            { 
                char after_dot = body[current.position]; 
                if (locate_symbol(after_dot, nonterminals, nonterminal_count) != -1)  
                { 
                    char remaining[MAX_RHS_LEN + 2]; 
                    strcpy(remaining, body + current.position + 1); 
                    int length = strlen(remaining); 
                    remaining[length] = current.next_symbol; 
                    remaining[length + 1] = '\0'; 
                    
                    char first_remaining[MAX_SYMBOLS] = {0}; 
                    get_first_of_sequence(remaining, first_remaining); 
                    
                    for (int j = 0; j < total_productions; j++)  
                    { 
                        if (rules[j].lhs == after_dot)  
                        { 
                            for(int k=0; k < strlen(first_remaining); k++) 
                            { 
                                LR_Item new_item = {j, 0, first_remaining[k]}; 
                                if (!item_present(set, &new_item))  
                                { 
                                    add_item_to_set(set, &new_item); 
                                    changed = 1; 
                                } 
                            } 
                        } 
                    } 
                } 
            } 
        } 
    } 
} 
 
int itemset_exists(const ItemSet* set)  
{ 
    for (int i = 0; i < clr_count; i++)  
    { 
        if (clr_itemsets[i].count == set->count)  
        { 
            int identical = 1; 
            for (int j = 0; j < set->count; j++)  
            { 
                if (!item_present(&clr_itemsets[i], &set->elements[j]))  
                { 
                    identical = 0; 
                    break; 
                } 
            } 
            if(identical)  
            { 
                for (int j = 0; j < clr_itemsets[i].count; j++)  
                { 
                    if (!item_present(set, &clr_itemsets[i].elements[j]))  
                    { 
                        identical = 0; 
                        break; 
                    } 
                } 
            } 
            if (identical) return i; 
        } 
    } 
    return -1; 
} 
 
void compute_goto(int state_num, char symbol, ItemSet* result)  
{ 
    result->count = 0; 
    ItemSet* current = &clr_itemsets[state_num]; 
    
    for (int i = 0; i < current->count; i++)  
    { 
        LR_Item item = current->elements[i]; 
        char* body = rules[item.production_num].rhs; 
        if (item.position < strlen(body) && body[item.position] == symbol)  
        { 
            LR_Item next_item = {item.production_num, item.position + 1, item.next_symbol}; 
            add_item_to_set(result, &next_item); 
        } 
    } 
    
    if (result->count > 0)  
    { 
        compute_closure(result); 
    } 
} 
 
void build_clr_collection()  
{ 
    ItemSet start_set; 
    start_set.count = 0; 
    LR_Item initial = {0, 0, '$'}; 
    add_item_to_set(&start_set, &initial); 
    compute_closure(&start_set); 
    clr_itemsets[clr_count++] = start_set; 
    
    for (int i = 0; i < clr_count; i++)  
    { 
        char all_symbols[MAX_SYMBOLS * 2] = {0}; 
        strcpy(all_symbols, nonterminals); 
        strcat(all_symbols, symbols); 
        
        for (int j = 0; j < strlen(all_symbols); j++)  
        { 
            char symbol = all_symbols[j]; 
            if (symbol == '$' || symbol == '#') continue; 
            
            ItemSet next_set; 
            compute_goto(i, symbol, &next_set); 
            
            if (next_set.count > 0)  
            { 
                int existing = itemset_exists(&next_set); 
                if (existing == -1)  
                { 
                    clr_itemsets[clr_count] = next_set; 
                    existing = clr_count; 
                    clr_count++; 
                } 
                
                int symbol_pos; 
                if((symbol_pos = locate_symbol(symbol, nonterminals, nonterminal_count)) != -1)  
                { 
                    clr_transitions[i][symbol_count + symbol_pos] = existing; 
                }  
                else  
                { 
                    symbol_pos = locate_symbol(symbol, symbols, symbol_count); 
                    clr_transitions[i][symbol_pos] = existing; 
                } 
            } 
        } 
    } 
} 
 
int cores_identical(const ItemSet* s1, const ItemSet* s2)  
{ 
    CoreItem cores1[MAX_PROD * 5]; 
    int count1 = 0; 
    
    for (int i = 0; i < s1->count; i++)  
    { 
        int exists = 0; 
        for (int j = 0; j < count1; j++)  
        { 
            if (cores1[j].production_num == s1->elements[i].production_num &&  
                cores1[j].position == s1->elements[i].position)  
            { 
                exists = 1; 
                break; 
            } 
        } 
        if (!exists)  
        { 
            cores1[count1].production_num = s1->elements[i].production_num; 
            cores1[count1].position = s1->elements[i].position; 
            count1++; 
        } 
    } 
    
    CoreItem cores2[MAX_PROD * 5]; 
    int count2 = 0; 
    for (int i = 0; i < s2->count; i++)  
    { 
        int exists = 0; 
        for (int j = 0; j < count2; j++)  
        { 
            if (cores2[j].production_num == s2->elements[i].production_num &&  
                cores2[j].position == s2->elements[i].position)  
            { 
                exists = 1; 
                break; 
            } 
        } 
        if (!exists)  
        { 
            cores2[count2].production_num = s2->elements[i].production_num; 
            cores2[count2].position = s2->elements[i].position; 
            count2++; 
        } 
    } 
    
    if (count1 != count2) return 0; 
    
    for (int i = 0; i < count1; i++)  
    { 
        int found = 0; 
        for (int j = 0; j < count2; j++)  
        { 
            if (cores1[i].production_num == cores2[j].production_num &&  
                cores1[i].position == cores2[j].position)  
            { 
                found = 1; 
                break; 
            } 
        } 
        if (!found) return 0; 
    } 
    return 1; 
} 
 
void merge_states()  
{ 
    int processed[MAX_STATES] = {0}; 
    for(int i=0; i < MAX_STATES; i++) mapping[i] = -1; 
    
    for (int i = 0; i < clr_count; i++)  
    { 
        if (processed[i]) continue; 
        
        char label_string[MAX_STATES * 3] = {0}, temp[5]; 
        sprintf(label_string, "%d", i); 
        lalr_itemsets[lalr_count].count = 0; 
        
        for (int k = 0; k < clr_itemsets[i].count; k++)  
        { 
            add_item_to_set(&lalr_itemsets[lalr_count], &clr_itemsets[i].elements[k]); 
        } 
        
        processed[i] = 1; 
        mapping[i] = lalr_count; 
        
        for (int j = i + 1; j < clr_count; j++)  
        { 
            if (!processed[j] && cores_identical(&clr_itemsets[i], &clr_itemsets[j]))  
            { 
                for (int k = 0; k < clr_itemsets[j].count; k++)  
                { 
                    add_item_to_set(&lalr_itemsets[lalr_count], &clr_itemsets[j].elements[k]); 
                } 
                processed[j] = 1; 
                mapping[j] = lalr_count; 
                sprintf(temp, "%d", j); 
                strcat(label_string, temp); 
            } 
        } 
        lalr_labels[lalr_count] = atoi(label_string); 
        lalr_count++; 
    } 
    
    for(int i=0; i<MAX_STATES; i++) 
        for(int j=0; j<MAX_SYMBOLS; j++) 
            lalr_transitions[i][j] = -1; 
    
    for (int i = 0; i < clr_count; i++)  
    { 
        for (int j = 0; j < symbol_count + nonterminal_count; j++)  
        { 
            if (clr_transitions[i][j] != -1)  
            { 
                int source = mapping[i]; 
                int target = mapping[clr_transitions[i][j]]; 
                lalr_transitions[source][j] = target; 
            } 
        } 
    } 
} 
 
void create_table()  
{ 
    for (int i = 0; i < lalr_count; i++)  
    { 
        for (int j = 0; j < lalr_itemsets[i].count; j++)  
        { 
            LR_Item item = lalr_itemsets[i].elements[j]; 
            char* body = rules[item.production_num].rhs; 
            int body_len = (strcmp(body, "#") == 0) ? 0 : strlen(body); 
            
            if (item.position < body_len)  
            { 
                char symbol = body[item.position]; 
                int symbol_pos = locate_symbol(symbol, symbols, symbol_count); 
                if (symbol_pos != -1)  
                { 
                    int next_state = lalr_transitions[i][symbol_pos]; 
                    if (next_state != -1)  
                    { 
                        sprintf(action_goto[i][symbol_pos], "S%d", lalr_labels[next_state]); 
                    } 
                } 
            }  
            else  
            { 
                if (item.production_num == 0)  
                { 
                    int dollar_pos = locate_symbol('$', symbols, symbol_count); 
                    strcpy(action_goto[i][dollar_pos], "Acc"); 
                }  
                else  
                { 
                    int symbol_pos = locate_symbol(item.next_symbol, symbols, symbol_count); 
                    if (symbol_pos != -1)  
                    { 
                        sprintf(action_goto[i][symbol_pos], "R%d", item.production_num); 
                    } 
                } 
            } 
        } 
        
        for (int j = 0; j < nonterminal_count; j++)  
        { 
            int table_col = symbol_count + j; 
            int state_index = lalr_transitions[i][table_col]; 
            if (state_index != -1)  
            { 
                sprintf(action_goto[i][table_col], "%d", lalr_labels[state_index]); 
            } 
        } 
    } 
} 
 
int locate_state(int label)  
{ 
    for (int i = 0; i < lalr_count; i++)  
    { 
        if (lalr_labels[i] == label) return i; 
    } 
    return -1; 
} 

void push_state(int index)  
{ 
    parser_stack[++stack_top] = index; 
}

void push_symbol(char sym)  
{ 
    stack_symbols[stack_top] = sym; 
}

void pop_stack()  
{ 
    if (stack_top >= 0)  
    { 
        stack_top--; 
    }
}

void print_stack_contents()  
{ 
    for (int i = 0; i <= stack_top; i++)  
    { 
        printf("%c%d", stack_symbols[i], lalr_labels[parser_stack[i]]); 
    }
}

void parse_string(char input[])  
{ 
    int pointer = 0; 
    push_state(0); 
    push_symbol(' '); 
    
    printf("\n%-20s %-15s %-15s\n", "STACK", "INPUT", "ACTION"); 
    printf("----------------------------------------------------\n"); 
    
    while (1)  
    { 
        print_stack_contents(); 
        printf("%-20.20s ", ""); 
        printf("%-15.15s ", input + pointer); 
        
        int current_state = parser_stack[stack_top]; 
        char current_symbol = input[pointer]; 
        int symbol_index = locate_symbol(current_symbol, symbols, symbol_count); 
        
        if (symbol_index == -1)  
        { 
            printf("\nError: Invalid input symbol '%c'\n", current_symbol); 
            break; 
        } 
        
        char* action = action_goto[current_state][symbol_index]; 
        
        if (strcmp(action, " ") == 0)  
        { 
            printf("\nError: No action in parse table\n"); 
            break; 
        } 
        
        if (action[0] == 'S')  
        { 
            int next_state_label, next_state_index; 
            sscanf(action, "S%d", &next_state_label); 
            next_state_index = locate_state(next_state_label); 
            printf("Shift to %d\n", next_state_label); 
            
            if (next_state_index == -1)  
            { 
                printf("\nError: Invalid state %d in shift action.\n", next_state_label); 
                break; 
            } 
            
            push_state(next_state_index); 
            push_symbol(current_symbol); 
            pointer++; 
        }  
        else if (action[0] == 'R')  
        { 
            int rule_number; 
            sscanf(action, "R%d", &rule_number); 
            Grammar rule = rules[rule_number]; 
            printf("Reduce by %c -> %s\n", rule.lhs,  
                   (strcmp(rule.rhs, "#") == 0) ? "epsilon" : rule.rhs); 
            
            int rule_length = (strcmp(rule.rhs, "#") == 0) ? 0 : strlen(rule.rhs); 
            for (int i = 0; i < rule_length; i++)  
            { 
                pop_stack(); 
            } 
            
            int state_after_pop = parser_stack[stack_top]; 
            int nt_index = locate_symbol(rule.lhs, nonterminals, nonterminal_count); 
            int next_state_index = lalr_transitions[state_after_pop][symbol_count + nt_index]; 
            
            if (next_state_index == -1)  
            { 
                printf("\nError: Invalid GOTO.\n"); 
                break; 
            } 
            
            push_state(next_state_index); 
            push_symbol(rule.lhs); 
        }  
        else if (strcmp(action, "Acc") == 0)  
        { 
            printf("Accept\n"); 
            printf("\n--- Input string accepted ---\n"); 
            break; 
        }  
        else  
        { 
            printf("\nError: Unknown action '%s' in parse table\n", action); 
            break; 
        } 
    } 
} 
 
int main()  
{ 
    for(int i=0; i<MAX_STATES; i++) 
        for(int j=0; j<MAX_SYMBOLS; j++) 
            clr_transitions[i][j] = -1; 
    
    for(int i=0; i<MAX_STATES; i++) 
        for(int j=0; j<MAX_SYMBOLS; j++) 
            strcpy(action_goto[i][j], " "); 
     
    printf("Enter number of productions: "); 
    scanf("%d", &total_productions); 
    printf("Enter productions:\n"); 
    
    rules[0].lhs = 'Z'; 
    scanf(" %c=", &rules[1].lhs); 
    rules[0].rhs[0] = rules[1].lhs; 
    rules[0].rhs[1] = '\0'; 
    scanf("%s", rules[1].rhs); 
    
    for (int i = 2; i <= total_productions; i++)  
    { 
        scanf(" %c=%s", &rules[i].lhs, rules[i].rhs); 
    } 
    total_productions++; 
     
    nonterminals[nonterminal_count++] = rules[0].lhs; 
    for (int i=0; i<total_productions; i++)  
        if(locate_symbol(rules[i].lhs, nonterminals, nonterminal_count) == -1)  
            nonterminals[nonterminal_count++] = rules[i].lhs; 
     
    for (int i=0; i<total_productions; i++)  
        for(int j=0; j<strlen(rules[i].rhs); j++)  
        { 
            char sym = rules[i].rhs[j]; 
            if(!isupper(sym) && sym != '#' && locate_symbol(sym, symbols, symbol_count) == -1) 
                symbols[symbol_count++] = sym; 
        } 
    symbols[symbol_count++] = '$'; 
     
    calculate_first(); 
    build_clr_collection(); 
    merge_states(); 
    create_table(); 
     
    printf("\n--- LALR(1) PARSE TABLE ---\n\n"); 
    printf("%-5s|", "STATE"); 
    for (int i = 0; i < symbol_count; i++) printf(" %-4c|", symbols[i]); 
    printf("|"); 
    for (int i = 0; i < nonterminal_count; i++)  
        if(nonterminals[i] != rules[0].lhs)  
            printf(" %-4c|", nonterminals[i]); 
    printf("\n"); 
     
    for (int i = 0; i < lalr_count; i++)  
    { 
        printf("%-5d|", lalr_labels[i]); 
        for (int j = 0; j < symbol_count; j++)  
            printf(" %-4s|", action_goto[i][j]); 
        printf("|"); 
        for (int j = 0; j < nonterminal_count; j++)  
        { 
            if(nonterminals[j] != rules[0].lhs)  
            { 
                int col_index = symbol_count + locate_symbol(nonterminals[j], nonterminals, nonterminal_count); 
                printf(" %-4s|", action_goto[i][col_index]); 
            } 
        } 
        printf("\n"); 
    } 
    
    char input_string[100]; 
    printf("\nEnter input string to parse: "); 
    scanf("%s", input_string); 
    strcat(input_string, "$"); 
    parse_string(input_string); 
    
    return 0; 
}
Output:
 

 
Experiment 12:
Aim:
Implementation of a simple calculator using LEX and YACC tools. 
Algorithm
1.	Define tokens for numbers, operators, parentheses, and newline in Lex.
2.	Ignore whitespace and handle invalid characters.
3.	In Yacc, define grammar rules for expressions with precedence.
4.	Perform arithmetic operations in semantic actions during parsing.
5.	Check division by zero and report errors.
6.	Continuously parse user input and print results until EOF.
Code:
calc.l
%{
#include "y.tab.h"
#include <stdlib.h>
%}
 
%%
[0-9]+        { yylval = atoi(yytext); return NUMBER; }
[\n]          { return EOL; }
[+\-*/()]     { return yytext[0]; }
[ \t]         ; // Ignore whitespace
.             { printf("Invalid character: %s\n", yytext); }
 
%%
int yywrap(void) {
    return 1;
}
calc.y
%{
#include <stdio.h>
#include <stdlib.h>
 
int yylex(void);
int yyerror(char *s);
%}
 
%token NUMBER
%token EOL
 
%left '+' '-'
%left '*' '/'
%left '(' ')'
 
%%
input:
    | input line
    ;
 
line:
    expr EOL   { printf("Result = %d\n", $1); }
    ;
 
expr:
    NUMBER             { $$ = $1; }
    | expr '+' expr    { $$ = $1 + $3; }
    | expr '-' expr    { $$ = $1 - $3; }
    | expr '*' expr    { $$ = $1 * $3; }
    | expr '/' expr    { 
                          if ($3 == 0) {
                              yyerror("Division by zero");
                              $$ = 0;
                          } else {
                              $$ = $1 / $3;
                          }
                        }
    | '(' expr ')'     { $$ = $2; }
    ;
%%
int main() {
    printf("Enter expressions (Ctrl+D to exit):\n");
    yyparse();
    return 0;
}
 
int yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}
Output:
 

 
Experiment 13:
Aim:
To convert infix expressions into postfix using Lex and Yacc by constructing and traversing an expression tree.
Algorithm
1.	Lex identifies numbers, identifiers, operators, and parentheses.
2.	Lex creates nodes for operands and returns tokens to Yacc.
3.	Yacc defines grammar rules with operator precedence.
4.	For each operator, Yacc builds expression tree nodes.
5.	Unary minus is handled with %prec UMINUS.
6.	Post-order traversal of the tree prints postfix expression.
7.	Program accepts infix input, parses, builds tree, and outputs postfix.
Code:
q13.y
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *token;
    struct node *left, *right;
} node;

node* createNode(char *token, node *left, node *right);
void printPostfix(node *tree);
int yylex(void);
void yyerror(char *s);
%}

%union {
    struct node *node;
}

%token <node> ID NUMBER
%type <node> expr

%left '+' '-'
%left '*' '/'
%right UMINUS

%%
start: expr { 
    printf("\nPostfix Expression: ");
    printPostfix($1);
    printf("\n");
    return 0;
};

expr: expr '+' expr   { $$ = createNode("+", $1, $3); }
    | expr '-' expr   { $$ = createNode("-", $1, $3); }
    | expr '*' expr   { $$ = createNode("*", $1, $3); }
    | expr '/' expr   { $$ = createNode("/", $1, $3); }
    | '(' expr ')'    { $$ = $2; }
    | '-' expr %prec UMINUS { $$ = createNode("-", $2, NULL); }
    | ID              { $$ = $1; }
    | NUMBER          { $$ = $1; }
    ;

%%

node* createNode(char *token, node *left, node *right) {
    node *newNode = (node*)malloc(sizeof(node));
    newNode->token = token;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

void printPostfix(node *tree) {
    if (tree) {
        printPostfix(tree->left);
        printPostfix(tree->right);
        printf("%s ", tree->token);
    }
}

int main() {
    printf("Enter infix expression:\n");
    yyparse();
    return 0;
}

void yyerror(char *s) {
    printf("Error: %s\n", s);
}
q13.l
%{
#include "y.tab.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node {
    char *token;
    struct node *left, *right;
} node;

extern YYSTYPE yylval;
node* createNode(char *token, node *left, node *right);
%}

%%
[0-9]+      { yylval.node = createNode(strdup(yytext), NULL, NULL); return NUMBER; }
[a-zA-Z]    { yylval.node = createNode(strdup(yytext), NULL, NULL); return ID; }
[+\-*/()]   { return yytext[0]; }
\n          { return 0; }
[ \t]       ;
.           { printf("Invalid character: %s\n", yytext); }
%%

int yywrap() { return 1; }
Output:
 

 
Experiment 14:
Aim:
Using LEX and YACC tools to recognize the strings of the following context-free languages: 
1.	L(G) = { anbm  /  m ≠ n} 
2.	L(G) =  { ab (bbaa)n bba (ba)n  /  n ≥ 0} 

Algorithm:
1) Algorithm
1.	Lex identifies characters a and b and returns tokens A and B.
2.	Yacc grammar accepts a sequence of a’s and b’s.
3.	Counters aCount and bCount are incremented for each token.
4.	After parsing, compare counts of a and b.
5.	If counts differ, print string accepted; else reject.
2) Algorithm
1.	Lex identifies characters a and b and returns tokens A and B.
2.	Yacc grammar enforces starting with A B.
3.	mid allows repetitions of the pattern B B A A.
4.	end ensures the sequence B B A followed by tail.
5.	tail allows zero or more B A pairs.
6.	If the input matches the grammar, print accepted; otherwise reject.

Code:
1)
q14a.l
%{
#include "y.tab.h"
%}

%%
a   { return A; }
b   { return B; }
\n  { return 0; }
.   ;
%%
int yywrap() { return 1; }

q14a.y
%{
#include <stdio.h>

int yylex(void);
void yyerror(char *s);
int aCount = 0, bCount = 0;
%}

%token A B

%%
start: str {
    if (aCount != bCount)
        printf("String accepted: m != n\n");
    else
        printf("String rejected: m = n\n");
};

str: str A { aCount++; }
   | str B { bCount++; }
   | /* empty */
   ;
%%

int main() {
    printf("Enter string (a's and b's): ");
    yyparse();
    return 0;
}

void yyerror(char *s) {
    // Just suppress error message for clean output
}

Output:
 

Code:
2)
q14b.l
%{
#include "y.tab.h"
%}

%%
a   { return A; }
b   { return B; }
\n  { return 0; }
.   ;
%%

int yywrap() { return 1; }

q14b.y
%{
#include <stdio.h>

int yylex(void);
void yyerror(char *s);
%}

%token A B

%%
start: A B mid end { 
        printf("String accepted\n"); 
        return 0; 
     }
     ;

mid: /* epsilon */
   | mid B B A A
   ;

end: B B A tail
   ;

tail: /* epsilon */
    | tail B A
    ;
%%

int main() {
    printf("Enter string: ");
    yyparse();
    return 0;
}

void yyerror(char *s) {
    printf("String not accepted\n");
}

Output:
 


 
Experiment 15:
Aim:
To generate three-address, quadruple, and triple code representations for arithmetic expressions using Lex and Yacc.
Algorithm:
1.	Lex identifies identifiers and numbers as tokens and sends them to Yacc.
2.	Yacc parses the arithmetic expressions based on grammar rules.
3.	For each operation, AddToTable stores operands and operators in a table.
4.	After parsing, ThreeAddressCode() prints the intermediate code using temporary variables.
5.	quadraple() displays operator, operands, and result as quadruples.
6.	triple() prints compact triples without result fields.
Code:
file.l 
%{ 
 #include "y.tab.h"  
 %} 
  
%% 
  
[0-9]+  { yylval.sym = (char)yytext[0]; return NUMBER; } 
 [a-zA-Z]+  { yylval.sym = (char)yytext[0]; return LETTER; } 
  
\n  { return 0; }   
 .  { return yytext[0]; }   
 %% 
  
int yywrap() { 
  return 1;  // Return 1 to indicate EOF 
 } 
file.y 
%{ 
 #include<stdio.h> 
 #include<string.h> 
 #include<stdlib.h> 
 #include <ctype.h>  // Include ctype.h for isalpha 
  
extern int yylex(void);  // Declare yylex 
 extern void yyerror(const char *s);  // Declare yyerror 
  
void ThreeAddressCode(); 
 void quadraple(); 
 void triple(); 
 char AddToTable(char ,char, char); 
  
int ind=0;  // count number of lines 
 char temp = '1';  // for t1,t2,t3..... 
 struct incod { 
  char opd1; 
  char opd2; 
  char opr; 
 }; 
 %} 
  
%union { 
  char sym;  // char for letter and number tokens 
 } 
  
%token <sym> LETTER NUMBER 
 %type <sym> expr statement  // Declare that expr and statement use the 'sym' type 
  
%left '+' '-' 
 %left '*' '/' 
 %% 
  
statement: 
  LETTER '=' expr ';' { AddToTable((char)$1, (char)$3, '='); } 
  | expr ';'  
 ; 
  
expr: 
  expr '+' expr   { $$ = AddToTable((char)$1, (char)$3, '+'); } 
  | expr '-' expr   { $$ = AddToTable((char)$1, (char)$3, '-'); } 
  | expr '*' expr   { $$ = AddToTable((char)$1, (char)$3, '*'); } 
  | expr '/' expr   { $$ = AddToTable((char)$1, (char)$3, '/'); } 
  | '(' expr ')' { $$ = (char)$2; } 
  | NUMBER       { $$ = (char)$1; } 
  | LETTER       { $$ = (char)$1; } 
  | '-' expr     { $$ = AddToTable((char)$2, (char)'\t', '-'); } 
 ; 
  
%% 
  
void yyerror(const char *s) { 
  printf("%s\n", s); 
  exit(1);  // Exit on error 
 } 
  
struct incod code[20]; 
  
char AddToTable(char opd1, char opd2, char opr) { 
  code[ind].opd1 = opd1; 
  code[ind].opd2 = opd2; 
  code[ind].opr = opr; 
  ind++; 
  return temp++; 
 } 
  
void ThreeAddressCode() { 
  int cnt = 0; 
  char temp = '1'; 
  printf("\n\n\t THREE ADDRESS CODE\n\n"); 
  while (cnt < ind) { 
      if (code[cnt].opr != '=') 
          printf("t%c : = \t", temp++); 
      if (isalpha(code[cnt].opd1)) 
          printf(" %c\t", code[cnt].opd1); 
      else if (code[cnt].opd1 >= '1' && code[cnt].opd1 <= '9') 
          printf("t%c\t", code[cnt].opd1); 
      printf(" %c\t", code[cnt].opr); 
      if (isalpha(code[cnt].opd2)) 
          printf(" %c\n", code[cnt].opd2); 
      else if (code[cnt].opd2 >= '1' && code[cnt].opd2 <= '9') 
          printf("t%c\n", code[cnt].opd2); 
      cnt++; 
  } 
 } 
  
void quadraple() { 
  int cnt = 0; 
  char temp = '1'; 
  printf("\n\n\t QUADRAPLE CODE\n\n"); 
  while (cnt < ind) { 
      printf(" %c\t", code[cnt].opr); 
      if (code[cnt].opr == '=') { 
          if (isalpha(code[cnt].opd2)) 
              printf(" %c\t \t", code[cnt].opd2); 
          else if (code[cnt].opd2 >= '1' && code[cnt].opd2 <= '9') 
              printf("t%c\t \t", code[cnt].opd2); 
          printf(" %c\n", code[cnt].opd1); 
          cnt++; 
          continue; 
      } 
      if (isalpha(code[cnt].opd1)) 
          printf(" %c\t", code[cnt].opd1); 
      else if (code[cnt].opd1 >= '1' && code[cnt].opd1 <= '9') 
          printf("t%c\t", code[cnt].opd1); 
      if (isalpha(code[cnt].opd2)) 
          printf(" %c\t", code[cnt].opd2); 
      else if (code[cnt].opd2 >= '1' && code[cnt].opd2 <= '9') 
          printf("t%c\t", code[cnt].opd2); 
      printf("  t%c\n", temp++); 
      cnt++; 
  } 
 } 
  
void triple() { 
  int cnt = 0; 
  char temp = '1'; 
  printf("\n\n\t TRIPLE CODE\n\n"); 
  while (cnt < ind) { 
      printf("(%c) \t", temp); 
      printf(" %c\t", code[cnt].opr); 
      if (code[cnt].opr == '=') { 
          if (isalpha(code[cnt].opd2)) 
              printf(" %c \t \t", code[cnt].opd2); 
          else if (code[cnt].opd2 >= '1' && code[cnt].opd2 <= '9') 
              printf("(%c)\n", code[cnt].opd2); 
          cnt++; 
          temp++; 
          continue; 
      } 
      if (isalpha(code[cnt].opd1)) 
          printf(" %c \t", code[cnt].opd1); 
      else if (code[cnt].opd1 >= '1' && code[cnt].opd1 <= '9') 
          printf("(%c)\t", code[cnt].opd1); 
      if (isalpha(code[cnt].opd2)) 
          printf(" %c \n", code[cnt].opd2); 
      else if (code[cnt].opd2 >= '1' && code[cnt].opd2 <= '9') 
          printf("(%c)\n", code[cnt].opd2); 
      else 
          printf("  %c\n", code[cnt].opd2); 
      cnt++; 
      temp++; 
  } 
 } 
  
int main() { 
  printf("\n Enter the Expression : "); 
  yyparse(); 
  ThreeAddressCode(); 
  quadraple(); 
  triple(); 
  return 0; 
 }
 

 
Experiment 16:
Aim:
To perform optimization on three-address code using constant folding, strength reduction, and algebraic transformations.
Algorithm:
1.	Input a set of three-address code instructions.
2.	For each instruction, check if both operands are constants — evaluate them directly (constant folding).
3.	Replace multiplications by powers of 2 with equivalent left-shift operations (strength reduction).
4.	Simplify expressions using algebraic rules like x*1 = x and x+0 = x.
5.	Display the optimized code alongside the original code.
Code:
#include <stdio.h> 
 
#include <string.h> 
 
#include <stdlib.h> 
  
typedef struct { 
 
    char op[10]; 
 
    char arg1[20]; 
 
    char arg2[20]; 
 
    char result[20]; 
 
} TAC; 
  
int isNumber(char *str) { 
 
    for (int i = 0; i < (int)strlen(str); i++) { 
 
        if (str[i] < '0' || str[i] > '9') return 0; 
 
    } 
 
    return 1; 
 
} 
  
int toInt(char *str) { 
 
    return atoi(str); 
 
} 
  
void optimize(TAC *tac) { 
 
    // Constant Folding 
 
    if (isNumber(tac->arg1) && isNumber(tac->arg2)) { 
 
        int a = toInt(tac->arg1); 
 
        int b = toInt(tac->arg2); 
 
        int val = 0; 
 
        if (strcmp(tac->op, "+") == 0) val = a + b; 
 
        else if (strcmp(tac->op, "-") == 0) val = a - b; 
 
        else if (strcmp(tac->op, "*") == 0) val = a * b; 
 
        else if (strcmp(tac->op, "/") == 0 && b != 0) val = a / b; 
 
        else return; 
  
        sprintf(tac->op, "="); 
 
        sprintf(tac->arg1, "%d", val); 
 
        tac->arg2[0] = '\0'; 
 
    } 
  
    // Strength Reduction 
 
    if (strcmp(tac->op, "*") == 0 && isNumber(tac->arg2)) { 
 
        int b = toInt(tac->arg2); 
 
        if (b == 2 || b == 4 || b == 8 || b == 16) { 
 
            int shift = 0; 
 
            while (b > 1) { 
 
                b = b / 2; 
 
                shift++; 
 
            } 
 
            sprintf(tac->op, "<<"); 
 
            sprintf(tac->arg2, "%d", shift); 
 
        } 
 
    } 
  
    // Algebraic transformations 
 
    if ((strcmp(tac->op, "*") == 0) && (strcmp(tac->arg2, "1") == 0)) { 
 
        sprintf(tac->op, "="); 
 
        strcpy(tac->arg1, tac->arg1); 
 
        tac->arg2[0] = '\0'; 
 
    } 
  
    if ((strcmp(tac->op, "+") == 0) && (strcmp(tac->arg2, "0") == 0)) { 
 
        sprintf(tac->op, "="); 
 
        strcpy(tac->arg1, tac->arg1); 
 
        tac->arg2[0] = '\0'; 
 
    } 
 
} 
  
void printTAC(TAC tac) { 
 
    if (strlen(tac.arg2) > 0) 
 
        printf("%s = %s %s %s\n", tac.result, tac.arg1, tac.op, tac.arg2); 
 
    else 
 
        printf("%s = %s %s\n", tac.result, tac.op, tac.arg1); 
 
} 
  
int main() { 
 
    int n; 
 
    printf("Enter number of three-address code instructions: "); 
 
    scanf("%d", &n); 
 
    getchar();  // consume newline after number input 
  
    TAC *code = (TAC *)malloc(n * sizeof(TAC)); 
 
    if (!code) { 
 
        printf("Memory allocation failed.\n"); 
 
        return 1; 
 
    } 
  
    for (int i = 0; i < n; i++) { 
 
        printf("Enter instruction %d\n", i + 1); 
 
        printf("Operator (+, -, *, /, =, <<): "); 
 
        fgets(code[i].op, sizeof(code[i].op), stdin); 
 
        code[i].op[strcspn(code[i].op, "\n")] = 0; // remove newline 
  
        printf("Argument 1: "); 
 
        fgets(code[i].arg1, sizeof(code[i].arg1), stdin); 
 
        code[i].arg1[strcspn(code[i].arg1, "\n")] = 0; 
  
        printf("Argument 2 (leave blank if none): "); 
 
        fgets(code[i].arg2, sizeof(code[i].arg2), stdin); 
 
        code[i].arg2[strcspn(code[i].arg2, "\n")] = 0; 
  
        printf("Result: "); 
 
        fgets(code[i].result, sizeof(code[i].result), stdin); 
 
        code[i].result[strcspn(code[i].result, "\n")] = 0; 
  
        printf("\n"); 
 
    } 
  
    printf("\nBefore Optimization:\n"); 
 
    for (int i = 0; i < n; i++) printTAC(code[i]); 
  
    for (int i = 0; i < n; i++) optimize(&code[i]); 
  
    printf("\nAfter Optimization:\n"); 
 
    for (int i = 0; i < n; i++) printTAC(code[i]); 
  
    free(code); 
 
    return 0; 
 
}
 

 
Experiment 17:
Aim:
To generate equivalent 8086 assembly code from given three-address code operations.
Algorithm:
1.	Input the number of three-address code instructions.
2.	For each instruction, read operator, operands, and result.
3.	If the operator is arithmetic (+, -, *, /), generate corresponding MOV, ADD, SUB, MUL, or DIV instructions.
4.	If the operator is assignment (=), generate MOV instruction.
5.	If the operator is left shift (<<), generate SHL instruction.
6.	Display all the generated 8086 assembly code instructions.
Code:
#include <stdio.h> 
 
#include <string.h> 
  
void generateAssembly(char *op, char *arg1, char *arg2, char *result) { 
 
    if (strcmp(op, "+") == 0) { 
 
        printf("MOV AX, %s\n", arg1); 
 
        printf("ADD AX, %s\n", arg2); 
 
        printf("MOV %s, AX\n", result); 
 
    } else if (strcmp(op, "-") == 0) { 
 
        printf("MOV AX, %s\n", arg1); 
 
        printf("SUB AX, %s\n", arg2); 
 
        printf("MOV %s, AX\n", result); 
 
    } else if (strcmp(op, "*") == 0) { 
 
        printf("MOV AX, %s\n", arg1); 
 
        printf("MOV BX, %s\n", arg2); 
 
        printf("MUL AX, BX\n"); 
 
        printf("MOV %s, AX\n", result); 
 
    } else if (strcmp(op, "/") == 0) { 
 
        printf("MOV AX, %s\n", arg1); 
 
        printf("MOV BX, %s\n", arg2); 
 
        printf("DIV AX, BX\n"); 
 
        printf("MOV %s, AX\n", result); 
 
    } else if (strcmp(op, "=") == 0) { 
 
        printf("MOV %s, %s\n", result, arg1); 
 
    } else if (strcmp(op, "<<") == 0) { 
 
        printf("MOV AX, %s\n", arg1); 
 
        printf("SHL AX, %s\n", arg2); 
 
        printf("MOV %s, AX\n", result); 
 
    } else { 
 
        printf("; Unsupported operation: %s\n", op); 
 
    } 
 
} 
  
int main() { 
 
    int n; 
 
    printf("Enter number of three-address code instructions: "); 
 
    scanf("%d", &n); 
 
    getchar();  // consume newline 
  
    char op[20], arg1[20], arg2[20], result[20]; 
  
    printf("\n"); 
 
    printf("; 8086 Assembly generated from three-address code\n\n"); 
  
    for (int i = 0; i < n; i++) { 
 
        printf("Instruction %d\n", i + 1); 
 
        printf("Operator (+, -, *, /, =, <<): "); 
 
        fgets(op, sizeof(op), stdin); 
 
        op[strcspn(op, "\n")] = 0; 
  
        printf("Argument 1: "); 
 
        fgets(arg1, sizeof(arg1), stdin); 
 
        arg1[strcspn(arg1, "\n")] = 0; 
  
        printf("Argument 2 (leave blank if none): "); 
 
        fgets(arg2, sizeof(arg2), stdin); 
 
        arg2[strcspn(arg2, "\n")] = 0; 
  
        printf("Result: "); 
 
        fgets(result, sizeof(result), stdin); 
 
        result[strcspn(result, "\n")] = 0; 
  
        printf("\n"); 
  
        generateAssembly(op, arg1, arg2, result); 
 
        printf("\n"); 
 
    } 
 
    return 0; 
 
}

/*

S = rA | e
A = rAA | lS

*/