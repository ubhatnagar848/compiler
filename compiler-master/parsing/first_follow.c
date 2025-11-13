#include <ctype.h>
#include <stdio.h>
#include <string.h>

void followfirst(char, int, int);
void follow(char);
void findfirst(char, int, int);

int count, n = 0;
char calc_first[10][100];
char calc_follow[10][100];
int m = 0;
char production[10][10];
char f[10], first[10];
int k;
char ck;
int e;

int main() {
    int jm = 0, km = 0, i;
    char c;
    printf("Enter number of productions: ");
    scanf("%d", &count);
    printf("Enter productions (like E->TR):\n");
    for (i = 0; i < count; i++) {
        scanf("%s", production[i]);
    }

    for (i = 0; i < count; i++) {
        char temp[10];
        int x = 0, y = 0;
        while (production[i][x] != '\0') {
            if (production[i][x] != '-' && production[i][x] != '>') {
                temp[y++] = production[i][x];
            }
            x++;
        }
        temp[y] = '\0';
        strcpy(production[i], temp);
    }

    int kay;
    char done[count];
    int ptr = -1;
    for (k = 0; k < count; k++)
        for (kay = 0; kay < 100; kay++)
            calc_first[k][kay] = '!';

    int point1 = 0, point2, xxx;

    for (k = 0; k < count; k++) {
        c = production[k][0];
        point2 = 0;
        xxx = 0;
        for (kay = 0; kay <= ptr; kay++)
            if (c == done[kay])
                xxx = 1;
        if (xxx == 1)
            continue;

        findfirst(c, 0, 1);
        ptr += 1;
        done[ptr] = c;
        printf("\nFirst(%c) = { ", c);
        calc_first[point1][point2++] = c;
        for (i = jm; i < n; i++) {
            int lark = 0, chk = 0;
            for (lark = 0; lark < point2; lark++)
                if (first[i] == calc_first[point1][lark]) {
                    chk = 1;
                    break;
                }
            if (chk == 0) {
                printf("%c ", first[i]);
                calc_first[point1][point2++] = first[i];
            }
        }
        printf("}\n");
        jm = n;
        point1++;
    }

    printf("\n-----------------------------------------------\n\n");

    char donee[count];
    ptr = -1;
    for (k = 0; k < count; k++)
        for (kay = 0; kay < 100; kay++)
            calc_follow[k][kay] = '!';

    point1 = 0;
    for (e = 0; e < count; e++) {
        ck = production[e][0];
        point2 = 0;
        xxx = 0;
        for (kay = 0; kay <= ptr; kay++)
            if (ck == donee[kay])
                xxx = 1;
        if (xxx == 1)
            continue;

        follow(ck);
        ptr += 1;
        donee[ptr] = ck;
        printf("Follow(%c) = { ", ck);
        calc_follow[point1][point2++] = ck;
        for (i = km; i < m; i++) {
            int lark = 0, chk = 0;
            for (lark = 0; lark < point2; lark++)
                if (f[i] == calc_follow[point1][lark]) {
                    chk = 1;
                    break;
                }
            if (chk == 0) {
                printf("%c ", f[i]);
                calc_follow[point1][point2++] = f[i];
            }
        }
        printf("}\n\n");
        km = m;
        point1++;
    }
    return 0;
}

void follow(char c) {
    int i, j;
    if (production[0][0] == c)
        f[m++] = '$';
    for (i = 0; i < count; i++) {
        for (j = 1; production[i][j] != '\0'; j++) {
            if (production[i][j] == c) {
                if (production[i][j + 1] != '\0')
                    followfirst(production[i][j + 1], i, j + 2);
                if (production[i][j + 1] == '\0' && c != production[i][0])
                    follow(production[i][0]);
            }
        }
    }
}

void findfirst(char c, int q1, int q2) {
    int j;
    if (!(isupper(c))) {
        first[n++] = c;
        return;
    }
    for (j = 0; j < count; j++) {
        if (production[j][0] == c) {
            if (production[j][1] == '#') {
                if (production[q1][q2] == '\0')
                    first[n++] = '#';
                else if (production[q1][q2] != '\0' && (q1 != 0 || q2 != 0))
                    findfirst(production[q1][q2], q1, q2 + 1);
                else
                    first[n++] = '#';
            } else if (!isupper(production[j][1])) {
                first[n++] = production[j][1];
            } else {
                findfirst(production[j][1], j, 2);
            }
        }
    }
}

void followfirst(char c, int c1, int c2) {
    int i = 0, j = 1;
    if (!(isupper(c))) {
        f[m++] = c;
    } else {
        for (i = 0; i < count; i++) {
            if (calc_first[i][0] == c)
                break;
        }
        while (calc_first[i][j] != '!') {
            if (calc_first[i][j] != '#')
                f[m++] = calc_first[i][j];
            else {
                if (production[c1][c2] == '\0')
                    follow(production[c1][0]);
                else
                    followfirst(production[c1][c2], c1, c2 + 1);
            }
            j++;
        }
    }
}
