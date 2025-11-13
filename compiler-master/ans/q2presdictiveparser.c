#include <stdio.h>
#include <string.h>

char s[50];
int i = 0;

void S() {
    if (s[i] == '→') {
        i++;
        S();
        if (s[i] == '←') {
            i++;
            S();
        } else {
            printf("Invalid: Missing ←\n");
            exit(0);
        }
    } else if (s[i] == '←' || s[i] == '\0') {
        return;
    } else {
        printf("Invalid symbol\n");
        exit(0);
    }
}

int main() {
    printf("Enter movement: ");
    scanf("%s", s);
    S();
    if (s[i] == '\0')
        printf("Valid movement\n");
    else
        printf("Invalid movement\n");
    return 0;
}
