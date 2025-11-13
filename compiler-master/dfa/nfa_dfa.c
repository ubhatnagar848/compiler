#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define N 20

int n, a, s, nf;
char st[N][10], sym[N][10];
int f[N], t[N][N][N], tc[N][N];
int dt[N][N];
char dset[N][N];
bool df[N];
int ds = 0;

void sort(char *x) {
    int l = strlen(x);
    for (int i = 0; i < l - 1; i++)
        for (int j = i + 1; j < l; j++)
            if (x[i] > x[j]) {
                char tmp = x[i];
                x[i] = x[j];
                x[j] = tmp;
            }
}

int find(char *x) {
    for (int i = 0; i < ds; i++)
        if (strcmp(dset[i], x) == 0)
            return i;
    return -1;
}

void add(char *x) {
    strcpy(dset[ds], x);
    df[ds] = false;
    for (int i = 0; i < (int)strlen(x); i++)
        if (f[x[i] - '0']) {
            df[ds] = true;
            break;
        }
    ds++;
}

void convert() {
    char q[N][N], tmp[2];
    int fr = 0, re = 0;
    tmp[0] = s + '0';
    tmp[1] = '\0';
    sort(tmp);
    add(tmp);
    strcpy(q[re++], tmp);

    while (fr < re) {
        char cur[N];
        strcpy(cur, q[fr++]);
        int ci = find(cur);

        for (int i = 0; i < a; i++) {
            char nx[N] = "";
            for (int j = 0; j < (int)strlen(cur); j++) {
                int idx = cur[j] - '0';
                for (int k = 0; k < tc[idx][i]; k++) {
                    char c = t[idx][i][k] + '0';
                    if (!strchr(nx, c)) {
                        int l = strlen(nx);
                        nx[l] = c;
                        nx[l + 1] = '\0';
                    }
                }
            }
            sort(nx);
            if (strlen(nx) == 0) {
                dt[ci][i] = -1;
            } else {
                int ex = find(nx);
                if (ex == -1) {
                    add(nx);
                    strcpy(q[re++], nx);
                    dt[ci][i] = ds - 1;
                } else {
                    dt[ci][i] = ex;
                }
            }
        }
    }
}

int getidx(char *x) {
    for (int i = 0; i < n; i++)
        if (strcmp(x, st[i]) == 0)
            return i;
    return -1;
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of symbols: ");
    scanf("%d", &a);
    printf("Enter symbols: ");
    for (int i = 0; i < a; i++) scanf("%s", sym[i]);
    printf("Enter states: ");
    for (int i = 0; i < n; i++) scanf("%s", st[i]);
    printf("Enter start state index: ");
    scanf("%d", &s);
    printf("Enter number of final states: ");
    scanf("%d", &nf);
    printf("Enter final state indices: ");
    for (int i = 0; i < nf; i++) {
        int x;
        scanf("%d", &x);
        f[x] = 1;
    }

    printf("\nEnter transition function δ:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < a; j++) {
            printf("δ[%s,%s] = ", st[i], sym[j]);
            char v[100];
            scanf("%s", v);
            if (strcmp(v, "-") != 0) {
                char *tok = strtok(v, ",");
                while (tok != NULL) {
                    int k = getidx(tok);
                    if (k != -1) t[i][j][tc[i][j]++] = k;
                    tok = strtok(NULL, ",");
                }
            }
        }

    convert();

    printf("\nDFA Transition Table:\n ");
    for (int i = 0; i < a; i++) printf("%s ", sym[i]);
    printf("\n");
    for (int i = 0; i < ds; i++) {
        printf("q%d (%s)%s ", i, dset[i], df[i] ? "*" : " ");
        for (int j = 0; j < a; j++) {
            if (dt[i][j] == -1) printf("- ");
            else printf("q%d ", dt[i][j]);
        }
        printf("\n");
    }

    char in[N];
    printf("\nEnter string: ");
    scanf("%s", in);
    printf("\nString: %s\n", in);
    int cur = 0;
    for (int i = 0; i < (int)strlen(in); i++) {
        int si = -1;
        for (int j = 0; j < a; j++) {
            if (in[i] == sym[j][0]) {
                si = j;
                break;
            }
        }
        if (si == -1 || dt[cur][si] == -1) {
            printf("δ[q%d,%c] = undefined\nREJECTED\n", cur, in[i]);
            return 0;
        } else {
            printf("δ[q%d,%c] = ", cur, in[i]);
            cur = dt[cur][si];
        }
    }
    printf("q%d\n", cur);
    if (df[cur]) printf("ACCEPTED\n");
    else printf("REJECTED\n");
    return 0;
}
