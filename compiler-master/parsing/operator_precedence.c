#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD 50
#define MAX_SYMBOLS 50
#define MAX_STR 100
#define MAX_STACK 100

typedef struct {
    char non_terminal[10];
    char production[MAX_STR];
} Production;

typedef struct {
    char symbols[MAX_SYMBOLS];
    int count;
} Set;

typedef struct {
    char stack[MAX_STACK];
    int top;
} Stack;

Production grammar[MAX_PROD];
int prod_count = 0;
Set leading_sets[MAX_SYMBOLS];
Set trailing_sets[MAX_SYMBOLS];
char precedence_table[MAX_SYMBOLS][MAX_SYMBOLS];
char terminals[MAX_SYMBOLS];
char non_terminals[MAX_SYMBOLS][10];
int term_count = 0, non_term_count = 0;
char start_symbol[10];

void add_to_set(Set *set, char c);
int set_contains(Set set, char c);
void compute_leading();
void compute_trailing();
void construct_precedence_table();
void print_sets(const char *name, Set sets[]);
void print_precedence_table();
void push(Stack *s, char symbol);
char pop(Stack *s);
char peek_terminal(Stack *s);
void operator_precedence_parse(char *input);
int find_non_terminal_index(const char *symbol);
int find_terminal_index(char c);
void process_grammar_symbols();

int main() {
    int i;
    printf("=== Operator Precedence Parser ===\n");
    printf("NOTE: Assumes a valid operator grammar (no adjacent non-terminals, no epsilon productions).\n\n");

    int num_rules;
    printf("Enter number of production rules (e.g., E->E+T|T is one rule): ");
    if (scanf("%d", &num_rules) != 1) return 1;
    getchar();

    printf("Enter productions (e.g., E->E+T|T or F->id):\n");
    for (i = 0; i < num_rules; i++) {
        char line[MAX_STR];
        if (!fgets(line, MAX_STR, stdin)) break;
        line[strcspn(line, "\n")] = 0;
        char *arrow = strstr(line, "->");
        if (!arrow) {
            printf("Invalid production format (missing '->'): %s\n", line);
            i--;
            continue;
        }
        char non_terminal[10];
        strncpy(non_terminal, line, arrow - line);
        non_terminal[arrow - line] = '\0';
        sscanf(non_terminal, " %s ", non_terminal);
        char *productions = arrow + 2;
        char *prod_token = strtok(productions, "|");
        while (prod_token != NULL) {
            if (prod_count >= MAX_PROD) {
                printf("Exceeded maximum production limit.\n");
                break;
            }
            strcpy(grammar[prod_count].non_terminal, non_terminal);
            char *start = prod_token;
            while (*start && isspace((unsigned char)*start)) start++;
            char *end = start + strlen(start) - 1;
            while (end > start && isspace((unsigned char)*end)) {
                *end = '\0';
                end--;
            }
            strcpy(grammar[prod_count].production, start);
            prod_count++;
            prod_token = strtok(NULL, "|");
        }
    }

    if (prod_count == 0) {
        printf("No productions provided.\n");
        return 1;
    }

    strcpy(start_symbol, grammar[0].non_terminal);
    process_grammar_symbols();

    int is_defined[MAX_SYMBOLS] = {0};
    for (i = 0; i < prod_count; i++) {
        int nt_index = find_non_terminal_index(grammar[i].non_terminal);
        if (nt_index != -1) {
            is_defined[nt_index] = 1;
        }
    }
    int grammar_ok = 1;
    for (i = 0; i < non_term_count; i++) {
        if (!is_defined[i]) {
            if (grammar_ok) {
                printf("\n--- Grammar Warnings ---\n");
            }
            printf("Warning: Non-terminal '%s' is used but has no productions.\n", non_terminals[i]);
            grammar_ok = 0;
        }
    }
    if (!grammar_ok) {
        printf("Please check your grammar. The results below may be incorrect.\n");
    }

    terminals[term_count++] = '$';
    compute_leading();
    compute_trailing();
    construct_precedence_table();

    printf("\n--- LEADING Sets ---\n");
    print_sets("LEADING", leading_sets);
    printf("\n--- TRAILING Sets ---\n");
    print_sets("TRAILING", trailing_sets);
    printf("\n--- Operator Precedence Table ---\n");
    print_precedence_table();

    char input[MAX_STR];
    printf("\nEnter input string to parse (end with $): ");
    if (scanf(" %[^\n]", input) != 1) return 1;

    printf("\n--- Parsing Steps ---\n");
    printf("%-25s %-20s %s\n", "Stack", "Input", "Action");
    printf("------------------------------------------------------------------\n");
    operator_precedence_parse(input);
    return 0;
}

void process_grammar_symbols() {
    for (int i = 0; i < prod_count; i++) {
        int found_nt = 0;
        for (int j = 0; j < non_term_count; j++) {
            if (strcmp(non_terminals[j], grammar[i].non_terminal) == 0) {
                found_nt = 1;
                break;
            }
        }
        if (!found_nt) {
            strcpy(non_terminals[non_term_count++], grammar[i].non_terminal);
        }
        char *prod = grammar[i].production;
        for (int j = 0; j < (int)strlen(prod);) {
            char c = prod[j];
            if (isupper((unsigned char)c)) {
                char current_nt_str[2] = {c, '\0'};
                int found = 0;
                for (int k = 0; k < non_term_count; k++) {
                    if (strcmp(non_terminals[k], current_nt_str) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(non_terminals[non_term_count++], current_nt_str);
                }
                j++;
            } else if (j + 1 < (int)strlen(prod) && ((c == 'i' && prod[j+1] == 'd') || (c == 'I' && prod[j+1] == 'D'))) {
                int found_t = 0;
                for (int k = 0; k < term_count; k++) {
                    if (terminals[k] == 'i') { found_t = 1; break; }
                }
                if (!found_t) { terminals[term_count++] = 'i'; }
                j += 2;
            } else {
                int found_t = 0;
                for (int k = 0; k < term_count; k++) {
                    if (terminals[k] == c) {
                        found_t = 1;
                        break;
                    }
                }
                if (!found_t) {
                    terminals[term_count++] = c;
                }
                j++;
            }
        }
    }
}

void add_to_set(Set *set, char c) {
    if (!set_contains(*set, c)) {
        set->symbols[set->count++] = c;
    }
}

int set_contains(Set set, char c) {
    for (int i = 0; i < set.count; i++) {
        if (set.symbols[i] == c) return 1;
    }
    return 0;
}

int find_non_terminal_index(const char *symbol) {
    for (int i = 0; i < non_term_count; i++) {
        if (strcmp(non_terminals[i], symbol) == 0) return i;
    }
    return -1;
}

int find_terminal_index(char c) {
    for (int i = 0; i < term_count; i++) {
        if (terminals[i] == c) return i;
    }
    return -1;
}

void compute_leading() {
    int changed;
    for (int i = 0; i < prod_count; i++) {
        int nt_index = find_non_terminal_index(grammar[i].non_terminal);
        if (nt_index == -1) continue;
        char *prod = grammar[i].production;
        if (strlen(prod) >= 2 && ((prod[0] == 'i' && prod[1] == 'd') || (prod[0] == 'I' && prod[1] == 'D'))) {
            add_to_set(&leading_sets[nt_index], 'i');
        } else if (!isupper((unsigned char)prod[0]) && prod[0] != '\0') {
            add_to_set(&leading_sets[nt_index], prod[0]);
        } else if (strlen(prod) > 1 && !isupper((unsigned char)prod[1])) {
            add_to_set(&leading_sets[nt_index], prod[1]);
        }
    }
    do {
        changed = 0;
        for (int i = 0; i < prod_count; i++) {
            int lhs_index = find_non_terminal_index(grammar[i].non_terminal);
            char *prod = grammar[i].production;
            if (strlen(prod) > 0 && isupper((unsigned char)prod[0])) {
                char rhs_nt_str[2] = {prod[0], '\0'};
                int rhs_index = find_non_terminal_index(rhs_nt_str);
                if (rhs_index == -1) continue;
                int old_count = leading_sets[lhs_index].count;
                for (int j = 0; j < leading_sets[rhs_index].count; j++) {
                    add_to_set(&leading_sets[lhs_index], leading_sets[rhs_index].symbols[j]);
                }
                if (leading_sets[lhs_index].count != old_count) {
                    changed = 1;
                }
            }
        }
    } while (changed);
}

void compute_trailing() {
    int changed;
    for (int i = 0; i < prod_count; i++) {
        int nt_index = find_non_terminal_index(grammar[i].non_terminal);
        if (nt_index == -1) continue;
        char *prod = grammar[i].production;
        int len = strlen(prod);
        if (len == 0) continue;
        if (len >= 2 && ((prod[len-2] == 'i' && prod[len-1] == 'd') || (prod[len-2] == 'I' && prod[len-1] == 'D'))) {
            add_to_set(&trailing_sets[nt_index], 'i');
        } else if (!isupper((unsigned char)prod[len - 1])) {
            add_to_set(&trailing_sets[nt_index], prod[len - 1]);
        } else if (len > 1 && !isupper((unsigned char)prod[len - 2])) {
            add_to_set(&trailing_sets[nt_index], prod[len - 2]);
        }
    }
    do {
        changed = 0;
        for (int i = 0; i < prod_count; i++) {
            int lhs_index = find_non_terminal_index(grammar[i].non_terminal);
            char *prod = grammar[i].production;
            int len = strlen(prod);
            if (len > 0 && isupper((unsigned char)prod[len - 1])) {
                char rhs_nt_str[2] = {prod[len - 1], '\0'};
                int rhs_index = find_non_terminal_index(rhs_nt_str);
                if (rhs_index == -1) continue;
                int old_count = trailing_sets[lhs_index].count;
                for (int j = 0; j < trailing_sets[rhs_index].count; j++) {
                    add_to_set(&trailing_sets[lhs_index], trailing_sets[rhs_index].symbols[j]);
                }
                if (trailing_sets[lhs_index].count != old_count) {
                    changed = 1;
                }
            }
        }
    } while (changed);
}

void construct_precedence_table() {
    for (int i = 0; i < term_count; i++) {
        for (int j = 0; j < term_count; j++) {
            precedence_table[i][j] = ' ';
        }
    }

    for (int i = 0; i < prod_count; i++) {
        char *prod = grammar[i].production;
        char symbols[MAX_STR][10];
        int sym_count = 0;
        for (int j = 0; j < (int)strlen(prod);) {
            if (j + 1 < (int)strlen(prod) && ((prod[j] == 'i' && prod[j + 1] == 'd') || (prod[j] == 'I' && prod[j + 1] == 'D'))) {
                strcpy(symbols[sym_count++], "i");
                j += 2;
            } else if (isupper((unsigned char)prod[j])) {
                symbols[sym_count][0] = prod[j];
                symbols[sym_count][1] = '\0';
                sym_count++;
                j++;
            } else if (!isspace((unsigned char)prod[j])) {
                symbols[sym_count][0] = prod[j];
                symbols[sym_count][1] = '\0';
                sym_count++;
                j++;
            } else {
                j++;
            }
        }

        for (int k = 0; k < sym_count - 1; k++) {
            char *s1 = symbols[k];
            char *s2 = symbols[k + 1];
            int s1_is_nt = find_non_terminal_index(s1) != -1;
            int s2_is_nt = find_non_terminal_index(s2) != -1;

            if (!s1_is_nt && !s2_is_nt) {
                int r = find_terminal_index(s1[0]);
                int c = find_terminal_index(s2[0]);
                if (r != -1 && c != -1)
                    precedence_table[r][c] = '=';
            }

            if (k < sym_count - 2) {
                char *s3 = symbols[k + 2];
                if (!s1_is_nt && find_non_terminal_index(s3) == -1 && s2_is_nt) {
                    int r = find_terminal_index(s1[0]);
                    int c = find_terminal_index(s3[0]);
                    if (r != -1 && c != -1)
                        precedence_table[r][c] = '=';
                }
            }

            if (!s1_is_nt && s2_is_nt) {
                int nt_index = find_non_terminal_index(s2);
                if (nt_index == -1) continue;
                int r = find_terminal_index(s1[0]);
                if (r == -1) continue;
                for (int l = 0; l < leading_sets[nt_index].count; l++) {
                    int c = find_terminal_index(leading_sets[nt_index].symbols[l]);
                    if (c != -1)
                        precedence_table[r][c] = '<';
                }
            }

            if (s1_is_nt && !s2_is_nt) {
                int nt_index = find_non_terminal_index(s1);
                if (nt_index == -1) continue;
                int c = find_terminal_index(s2[0]);
                if (c == -1) continue;
                for (int l = 0; l < trailing_sets[nt_index].count; l++) {
                    int r = find_terminal_index(trailing_sets[nt_index].symbols[l]);
                    if (r != -1)
                        precedence_table[r][c] = '>';
                }
            }
        }
    }

    int dollar_idx = find_terminal_index('$');
    if (dollar_idx == -1) return;
    int start_idx = find_non_terminal_index(start_symbol);
    if (start_idx == -1) return;
    for (int j = 0; j < leading_sets[start_idx].count; j++) {
        int c = find_terminal_index(leading_sets[start_idx].symbols[j]);
        if (c != -1) precedence_table[dollar_idx][c] = '<';
    }
    for (int j = 0; j < trailing_sets[start_idx].count; j++) {
        int r = find_terminal_index(trailing_sets[start_idx].symbols[j]);
        if (r != -1) precedence_table[r][dollar_idx] = '>';
    }
}

void print_sets(const char *name, Set sets[]) {
    for (int i = 0; i < non_term_count; i++) {
        printf("%s(%s): { ", name, non_terminals[i]);
        int nt_index = find_non_terminal_index(non_terminals[i]);
        if (nt_index == -1) continue;
        for (int j = 0; j < sets[nt_index].count; j++) {
            printf("%c ", sets[nt_index].symbols[j]);
        }
        printf("}\n");
    }
}

void print_precedence_table() {
    printf("%-4c", ' ');
    for (int i = 0; i < term_count; i++) {
        printf("%-4c", terminals[i]);
    }
    printf("\n");
    for (int i = 0; i < term_count; i++) {
        printf("%-4c", terminals[i]);
        for (int j = 0; j < term_count; j++) {
            printf("%-4c", precedence_table[i][j]);
        }
        printf("\n");
    }
}

void push(Stack *s, char symbol) {
    if (s->top < MAX_STACK - 1) {
        s->stack[++s->top] = symbol;
    }
}

char pop(Stack *s) {
    if (s->top >= 0) return s->stack[s->top--];
    return '\0';
}

char peek_terminal(Stack *s) {
    for (int i = s->top; i >= 0; i--) {
        if (find_terminal_index(s->stack[i]) != -1) {
            return s->stack[i];
        }
    }
    return '\0';
}

void operator_precedence_parse(char *input) {
    Stack s;
    s.top = -1;
    push(&s, '$');

    char processed_input[MAX_STR] = "";
    int p_idx = 0;
    for (int i = 0; i < (int)strlen(input);) {
        if (isspace((unsigned char)input[i])) { i++; continue; }
        if (i + 1 < (int)strlen(input) && ((input[i] == 'I' && input[i+1] == 'D') || (input[i] == 'i' && input[i+1] == 'd'))) {
            processed_input[p_idx++] = 'i';
            i += 2;
        } else {
            processed_input[p_idx++] = input[i++];
        }
    }
    processed_input[p_idx] = '\0';

    int input_idx = 0;
    int accepted = 0;
    while (1) {
        char stack_str[MAX_STR] = "";
        for (int i = 0; i <= s.top; i++) {
            stack_str[i] = s.stack[i];
        }
        stack_str[s.top + 1] = '\0';

        char current_input_char = processed_input[input_idx];
        if (current_input_char == '\0') {
            current_input_char = '$';
        }
        printf("%-25s %-20s ", stack_str, processed_input + input_idx);

        char stack_top_term = peek_terminal(&s);

        if (stack_top_term == '$' && current_input_char == '$') {
            printf("Accept\n");
            accepted = 1;
            break;
        }

        int row = find_terminal_index(stack_top_term);
        int col = find_terminal_index(current_input_char);
        if (row == -1 || col == -1 || stack_top_term == '\0') {
            printf("Error: Invalid parsing state (Stack: '%c', Input: '%c').\n", stack_top_term, current_input_char);
            break;
        }

        char relation = precedence_table[row][col];
        if (relation == '<' || relation == '=') {
            printf("Shift %c\n", current_input_char);
            push(&s, current_input_char);
            if (input_idx < (int)strlen(processed_input)) {
                input_idx++;
            }
        } else if (relation == '>') {
            printf("Reduce\n");
            char last_popped;
            do {
                last_popped = pop(&s);
                if (last_popped == '\0') break;
            } while (peek_terminal(&s) != '\0' &&
                     (find_terminal_index(last_popped) == -1 ||
                      precedence_table[find_terminal_index(peek_terminal(&s))][find_terminal_index(last_popped)] != '<'));
        } else {
            printf("Error: No relation between %c and %c\n", stack_top_term, current_input_char);
            break;
        }
    }

    printf("\n");
    if (accepted) {
        printf("Input string is ACCEPTED.\n");
    } else {
        printf("Input string is REJECTED.\n");
    }
}