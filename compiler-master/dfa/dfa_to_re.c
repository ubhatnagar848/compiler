#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char s[10];
char q[10][10];
char t[10][10][10];
int f[10];
int nq, ns, nf, start;

int findQ(char* n) {
    for (int i = 0; i < nq; i++) {
        if (strcmp(q[i], n) == 0) {
            return i;
        }
    }
    return -1;
}

int findS(char c) {
    for (int i = 0; i < ns; i++) {
        if (s[i] == c) {
            return i;
        }
    }
    return -1;
}

int isFinal(int i) {
    for (int j = 0; j < nf; j++) {
        if (f[j] == i) {
            return 1;
        }
    }
    return 0;
}

void printTable() {
    printf("\nTransition Table:\n");
    printf("  ");
    for (int j = 0; j < ns; j++) {
        printf("%c ", s[j]);
    }
    printf("\n");
    for (int i = 0; i < nq; i++) {
        printf("%s ", q[i]);
        for (int j = 0; j < ns; j++) {
            printf("%s ", t[i][j]);
            if (strlen(t[i][j]) == 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void genGrammar() {
    printf("\n=== REGULAR GRAMMAR FROM DFA ===\n");
    printf("\nNon-terminals (N): {");
    for (int i = 0; i < nq; i++) {
        printf("%s", q[i]);
        if (i < nq - 1) printf(", ");
    }
    printf("}\n");

    printf("Terminals (T): {");
    for (int i = 0; i < ns; i++) {
        printf("%c", s[i]);
        if (i < ns - 1) printf(", ");
    }
    printf("}\n");

    printf("Start Symbol (S): %s\n", q[start]);
    printf("\nProductions (P):\n");

    for (int i = 0; i < nq; i++) {
        for (int j = 0; j < ns; j++) {
            char* next = t[i][j];
            if (strcmp(next, "-") != 0) {
                int ni = findQ(next);
                printf(" %s -> %c%s\n", q[i], s[j], next);
                if (ni != -1 && isFinal(ni)) {
                    printf(" %s -> %c\n", q[i], s[j]);
                }
            }
        }
        if (isFinal(i)) {
            printf(" %s -> ε\n", q[i]);
        }
    }

    printf("\nGrammar G = (N, T, P, S) where:\n");
    printf(" N = Non-terminals\n");
    printf(" T = Terminals\n");
    printf(" P = Productions\n");
    printf(" S = Start Symbol\n");
}

int sim(char* str) {
    int cur = start;
    int len = strlen(str);
    printf("\n=== STRING SIMULATION ===\n");
    printf("String: %s\n", str);
    for (int i = 0; i < len; i++) {
        char c = str[i];
        int si = findS(c);
        if (si == -1) {
            printf("Symbol '%c' not found in alphabet\n", c);
            return 0;
        }
        char* next = t[cur][si];
        if (strcmp(next, "-") == 0) {
            printf("δ[%s,%c] = REJECTED (no transition)\n", q[cur], c);
            return 0;
        }
        int ni = findQ(next);
        if (ni == -1) {
            printf("Invalid state: %s\n", next);
            return 0;
        }
        printf("δ[%s,%c] = %s\n", q[cur], c, next);
        cur = ni;
    }
    printf("Final state: %s\n", q[cur]);
    if (isFinal(cur)) {
        printf("Result: ACCEPTED\n");
        return 1;
    } else {
        printf("Result: REJECTED\n");
        return 0;
    }
}

int main() {
    printf("=== DFA TO REGULAR GRAMMAR CONVERTER ===\n\n");
    printf("Enter number of states: ");
    if (scanf("%d", &nq) != 1) return 1;
    printf("Enter number of symbols: ");
    if (scanf("%d", &ns) != 1) return 1;
    printf("Enter symbols: ");
    for (int i = 0; i < ns; i++) {
        scanf(" %c", &s[i]);
    }
    printf("Enter states: ");
    for (int i = 0; i < nq; i++) {
        scanf("%9s", q[i]);
    }
    printf("Enter start state index (0 to %d): ", nq - 1);
    scanf("%d", &start);
    printf("Enter number of final states: ");
    scanf("%d", &nf);
    printf("Enter final state indices: ");
    for (int i = 0; i < nf; i++) {
        scanf("%d", &f[i]);
    }
    for (int i = 0; i < nq; i++) {
        for (int j = 0; j < ns; j++) {
            strcpy(t[i][j], "-");
        }
    }
    printf("\nEnter transition function δ:\n");
    printf("(Enter '-' for no transition)\n");
    for (int i = 0; i < nq; i++) {
        for (int j = 0; j < ns; j++) {
            printf("δ[%s,%c] = ", q[i], s[j]);
            scanf("%9s", t[i][j]);
        }
    }
    printTable();
    genGrammar();

    char input[100];
    printf("\nEnter string to test: ");
    if (scanf("%99s", input) == 1) {
        sim(input);
    }
    return 0;
}