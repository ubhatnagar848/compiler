#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROD 50
#define MAX_SYMBOLS 50
#define MAX_STR 100
#define MAX_STACK 100
#define EPSILON 'e'

typedef struct {
    char non_terminal[10];
    char production[MAX_STR];
} Production;

typedef struct {
    char symbols[MAX_SYMBOLS];
    int count;
} Set;

typedef struct {
    char stack[MAX_STACK][10];
    int top;
} Stack;

Production grammar[MAX_PROD];
int prod_count = 0;
Set first_sets[MAX_SYMBOLS];
Set follow_sets[MAX_SYMBOLS];
char parse_table[MAX_SYMBOLS][MAX_SYMBOLS][MAX_STR];
char terminals[MAX_SYMBOLS];
char non_terminals[MAX_SYMBOLS][10];
int term_count = 0, non_term_count = 0;
char start_symbol[10];

int is_non_terminal_char(char c);
void add_to_set(Set *set, char c);
int set_contains(Set set, char c);
void compute_first_of_string(char *str, Set *result_set);
void compute_all_first();
void compute_follow();
void construct_parse_table();
void print_sets(const char *name, Set sets[]);
void print_parse_table();
void push(Stack *s, const char *symbol);
char* pop(Stack *s);
char* peek(Stack *s);
void predictive_parse(char *input);
int find_non_terminal_index(const char *symbol);
int find_terminal_index(char c);
void process_grammar_terminals();

int main() {
    int i;
    printf("=== Predictive Parser ===\n\n");
    printf("Enter number of productions: ");
    scanf("%d", &prod_count);
    getchar();

    printf("Enter productions (format: A->aB|c, use 'e' for epsilon):\n");
    for (i = 0; i < prod_count; i++) {
        char line[MAX_STR];
        fgets(line, MAX_STR, stdin);
        line[strcspn(line, "\n")] = 0;

        char *arrow = strstr(line, "->");
        if (!arrow) {
            printf("Invalid production format (missing '->'): %s\n", line);
            i--;
            continue;
        }

        char nt_buffer[MAX_STR];
        strncpy(nt_buffer, line, arrow - line);
        nt_buffer[arrow - line] = '\0';
        sscanf(nt_buffer, "%s", grammar[i].non_terminal);

        char *prod_start = arrow + 2;
        while (*prod_start && isspace((unsigned char)*prod_start))
            prod_start++;
        strcpy(grammar[i].production, prod_start);

        int found = 0;
        for (int j = 0; j < non_term_count; j++) {
            if (strcmp(non_terminals[j], grammar[i].non_terminal) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(non_terminals[non_term_count++], grammar[i].non_terminal);
        }
    }

    strcpy(start_symbol, grammar[0].non_terminal);

    for (i = 0; i < MAX_SYMBOLS; i++) {
        first_sets[i].count = 0;
        follow_sets[i].count = 0;
    }

    process_grammar_terminals();
    terminals[term_count++] = '$';
    compute_all_first();

    int start_symbol_index = find_non_terminal_index(start_symbol);
    if (start_symbol_index != -1) {
        add_to_set(&follow_sets[start_symbol_index], '$');
    }

    compute_follow();
    construct_parse_table();

    printf("\n--- FIRST Sets ---\n");
    print_sets("FIRST", first_sets);
    printf("\n--- FOLLOW Sets ---\n");
    print_sets("FOLLOW", follow_sets);
    printf("\n--- Predictive Parse Table ---\n");
    print_parse_table();

    char input[MAX_STR];
    printf("\nEnter input string to parse (end with $): ");
    scanf(" %[^\n]", input);

    printf("\n--- Parsing Steps ---\n");
    printf("%-25s %-20s %s\n", "Stack", "Input", "Action");
    printf("------------------------------------------------------------------\n");

    predictive_parse(input);
    return 0;
}

int is_non_terminal_char(char c) {
    return isupper(c);
}

void process_grammar_terminals() {
    for (int i = 0; i < prod_count; i++) {
        for (int j = 0; j < (int)strlen(grammar[i].production); j++) {
            char c = grammar[i].production[j];

            if (j + 1 < (int)strlen(grammar[i].production) && c == 'i' &&
                grammar[i].production[j + 1] == 'd') {
                int found = 0;
                for (int k = 0; k < term_count; k++) {
                    if (terminals[k] == 'i') {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    terminals[term_count++] = 'i';
                }
                j++;
            } else if (c != EPSILON && c != '|' &&
                       !is_non_terminal_char(c) && c != '\'' && !isspace(c)) {
                int found = 0;
                for (int k = 0; k < term_count; k++) {
                    if (terminals[k] == c) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    terminals[term_count++] = c;
                }
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

void compute_first_of_string(char *str, Set *result_set) {
    result_set->count = 0;
    int all_derive_epsilon = 1;

    for (int i = 0; i < (int)strlen(str); ) {
        if (i + 1 < (int)strlen(str) && str[i] == 'i' && str[i + 1] == 'd') {
            add_to_set(result_set, 'i');
            all_derive_epsilon = 0;
            break;
        }
        if (!is_non_terminal_char(str[i])) {
            add_to_set(result_set, str[i]);
            all_derive_epsilon = 0;
            break;
        }

        char nt_symbol[10] = {str[i], '\0'};
        if (i + 1 < (int)strlen(str) && str[i + 1] == '\'') {
            nt_symbol[1] = '\'';
            nt_symbol[2] = '\0';
            i += 2;
        } else {
            i++;
        }

        int nt_index = find_non_terminal_index(nt_symbol);
        if (nt_index == -1) continue;

        int has_epsilon = 0;
        for (int j = 0; j < first_sets[nt_index].count; j++) {
            char symbol = first_sets[nt_index].symbols[j];
            if (symbol == EPSILON) {
                has_epsilon = 1;
            } else {
                add_to_set(result_set, symbol);
            }
        }
        if (!has_epsilon) {
            all_derive_epsilon = 0;
            break;
        }
    }

    if (all_derive_epsilon) {
        add_to_set(result_set, EPSILON);
    }
}

void compute_all_first() {
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < prod_count; i++) {
            char *nt = grammar[i].non_terminal;
            int nt_index = find_non_terminal_index(nt);
            if (nt_index == -1) continue;
            int old_count = first_sets[nt_index].count;

            char prod_copy[MAX_STR];
            strcpy(prod_copy, grammar[i].production);
            char *alt = strtok(prod_copy, "|");
            while (alt != NULL) {
                while (*alt && isspace((unsigned char)*alt)) alt++;
                char *end = alt + strlen(alt) - 1;
                while (end >= alt && isspace((unsigned char)*end)) {
                    *end = '\0';
                    end--;
                }

                if (strcmp(alt, "e") == 0) {
                    add_to_set(&first_sets[nt_index], EPSILON);
                } else if (*alt != '\0') {
                    Set first_of_alt;
                    compute_first_of_string(alt, &first_of_alt);
                    for (int j = 0; j < first_of_alt.count; j++) {
                        add_to_set(&first_sets[nt_index], first_of_alt.symbols[j]);
                    }
                }
                alt = strtok(NULL, "|");
            }

            if (first_sets[nt_index].count != old_count) {
                changed = 1;
            }
        }
    } while (changed);
}

void compute_follow() {
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < prod_count; i++) {
            char *lhs_nt = grammar[i].non_terminal;
            int lhs_nt_index = find_non_terminal_index(lhs_nt);
            if (lhs_nt_index == -1) continue;

            char prod_copy[MAX_STR];
            strcpy(prod_copy, grammar[i].production);

            char *alt = strtok(prod_copy, "|");
            while (alt != NULL) {
                for (int j = 0; j < (int)strlen(alt); ) {
                    if (is_non_terminal_char(alt[j])) {
                        char current_nt[10] = {alt[j], '\0'};
                        int sym_len = 1;
                        if (j + 1 < (int)strlen(alt) && alt[j + 1] == '\'') {
                            current_nt[1] = '\'';
                            current_nt[2] = '\0';
                            sym_len = 2;
                        }

                        int current_nt_index = find_non_terminal_index(current_nt);
                        if (current_nt_index == -1) {
                            j += sym_len;
                            continue;
                        }

                        int old_count = follow_sets[current_nt_index].count;
                        char *beta = alt + j + sym_len;
                        Set first_of_beta;
                        compute_first_of_string(beta, &first_of_beta);

                        int beta_has_epsilon = 0;
                        for (int k = 0; k < first_of_beta.count; k++) {
                            if (first_of_beta.symbols[k] == EPSILON) {
                                beta_has_epsilon = 1;
                            } else {
                                add_to_set(&follow_sets[current_nt_index], first_of_beta.symbols[k]);
                            }
                        }

                        if (beta_has_epsilon || strlen(beta) == 0) {
                            for (int k = 0; k < follow_sets[lhs_nt_index].count; k++) {
                                add_to_set(&follow_sets[current_nt_index], follow_sets[lhs_nt_index].symbols[k]);
                            }
                        }

                        if (follow_sets[current_nt_index].count != old_count) {
                            changed = 1;
                        }
                        j += sym_len;
                    } else {
                        j++;
                    }
                }
                alt = strtok(NULL, "|");
            }
        }
    } while (changed);
}

void construct_parse_table() {
    for (int i = 0; i < non_term_count; i++) {
        for (int j = 0; j < term_count; j++) {
            strcpy(parse_table[i][j], "-");
        }
    }

    for (int i = 0; i < prod_count; i++) {
        char *nt = grammar[i].non_terminal;
        int row = find_non_terminal_index(nt);
        if (row == -1) continue;

        char prod_copy[MAX_STR];
        strcpy(prod_copy, grammar[i].production);
        char *alt = strtok(prod_copy, "|");
        while (alt != NULL) {
            while (*alt && isspace((unsigned char)*alt)) alt++;
            char *end = alt + strlen(alt) - 1;
            while (end >= alt && isspace((unsigned char)*end)) {
                *end = '\0';
                end--;
            }

            Set first_of_alt;
            compute_first_of_string(alt, &first_of_alt);
            for (int j = 0; j < first_of_alt.count; j++) {
                if (first_of_alt.symbols[j] != EPSILON) {
                    int col = find_terminal_index(first_of_alt.symbols[j]);
                    if (col != -1) {
                        sprintf(parse_table[row][col], "%s->%s", nt, alt);
                    }
                }
            }

            if (set_contains(first_of_alt, EPSILON)) {
                int nt_index = find_non_terminal_index(nt);
                for (int j = 0; j < follow_sets[nt_index].count; j++) {
                    char terminal = follow_sets[nt_index].symbols[j];
                    int col = find_terminal_index(terminal);
                    if (col != -1) {
                        sprintf(parse_table[row][col], "%s->%s", nt, alt);
                    }
                }
            }
            alt = strtok(NULL, "|");
        }
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

void print_parse_table() {
    printf("\t");
    for (int i = 0; i < term_count; i++) {
        printf("%-8c", terminals[i]);
    }
    printf("\n");
    for (int i = 0; i < non_term_count; i++) {
        printf("%-8s", non_terminals[i]);
        for (int j = 0; j < term_count; j++) {
            printf("%-8s", parse_table[i][j]);
        }
        printf("\n");
    }
}

void push(Stack *s, const char *symbol) {
    if (s->top < MAX_STACK - 1) {
        strcpy(s->stack[++s->top], symbol);
    }
}

char* pop(Stack *s) {
    if (s->top >= 0) return s->stack[s->top--];
    return NULL;
}

char* peek(Stack *s) {
    if (s->top >= 0) return s->stack[s->top];
    return NULL;
}

void predictive_parse(char *input) {
    Stack s;
    s.top = -1;
    push(&s, "$");
    push(&s, start_symbol);

    char processed_input[MAX_STR] = "";
    int p_idx = 0;
    for (int i = 0; i < (int)strlen(input); i++) {
        if (isspace((unsigned char)input[i])) continue;
        if (i + 1 < (int)strlen(input) && input[i] == 'i' && input[i + 1] == 'd') {
            processed_input[p_idx++] = 'i';
            i++;
        } else {
            processed_input[p_idx++] = input[i];
        }
    }
    processed_input[p_idx] = '\0';

    int input_idx = 0;
    while (s.top >= 0) {
        char stack_str[MAX_STR * 2] = "";
        for (int i = s.top; i >= 0; i--) {
            strcat(stack_str, s.stack[i]);
            strcat(stack_str, " ");
        }

        printf("%-25s %-20s ", stack_str, processed_input + input_idx);
        char *stack_top = peek(&s);
        char current_input = processed_input[input_idx];

        if (strcmp(stack_top, "$") == 0 && current_input == '$') {
            printf("Accept");
            break;
        }

        if (strcmp(stack_top, "id") == 0 && current_input == 'i') {
            printf("Match 'id'");
            pop(&s);
            input_idx++;
        } else if (strlen(stack_top) == 1 && stack_top[0] == current_input) {
            printf("Match '%c'", current_input);
            pop(&s);
            input_idx++;
        } else if (is_non_terminal_char(stack_top[0])) {
            int row = find_non_terminal_index(stack_top);
            int col = find_terminal_index(current_input);
            if (row == -1 || col == -1 || strcmp(parse_table[row][col], "-") == 0) {
                printf("Error: No rule for M[%s, %c]", stack_top, current_input);
                break;
            }

            char* production_rule = parse_table[row][col];
            printf("Apply %s", production_rule);
            pop(&s);
            char *rhs = strchr(production_rule, '>') + 1;
            if (strcmp(rhs, "e") != 0) {
                char symbols[20][10];
                int sym_count = 0;
                for (int k = 0; k < (int)strlen(rhs); ) {
                    if (k + 1 < (int)strlen(rhs) && rhs[k] == 'i' && rhs[k + 1] == 'd') {
                        strcpy(symbols[sym_count++], "id");
                        k += 2;
                    } else if (is_non_terminal_char(rhs[k])) {
                        symbols[sym_count][0] = rhs[k];
                        if (k + 1 < (int)strlen(rhs) && rhs[k + 1] == '\'') {
                            symbols[sym_count][1] = '\'';
                            symbols[sym_count][2] = '\0';
                            k += 2;
                        } else {
                            symbols[sym_count][1] = '\0';
                            k++;
                        }
                        sym_count++;
                    } else {
                        symbols[sym_count][0] = rhs[k];
                        symbols[sym_count][1] = '\0';
                        sym_count++;
                        k++;
                    }
                }
                for (int k = sym_count - 1; k >= 0; k--) {
                    push(&s, symbols[k]);
                }
            }
        } else {
            printf("Error: Mismatch. Stack: %s, Input: %c", stack_top, current_input);
            break;
        }
        printf("\n");
    }

    printf("\n");
    if (peek(&s) && strcmp(peek(&s), "$") == 0 && processed_input[strlen(processed_input) ? strlen(processed_input) - 1 : 0] == '$') {
        /* If input ended with '$' and stack only has '$' */
        if (processed_input[0] != '\0' && processed_input[strlen(processed_input)-1] == '$') {
            printf("\nInput string is ACCEPTED.\n");
            return;
        }
    }

    printf("\nInput string is REJECTED.\n");
}
