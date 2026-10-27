#include <stdio.h>
#include <string.h>

void divide(char *t, char *g) {
    int n = strlen(t), gl = strlen(g), i, j;
    for (i = 0; i <= n - gl; i++)
        if (t[i] == '1')
            for (j = 0; j < gl; j++)
                t[i + j] = (t[i + j] == g[j]) ? '0' : '1';   // XOR
}

int main() {
    char d[50], g[20], t[70], r[70];
    int i, dl, gl;

    printf("Enter data: ");
    scanf("%s", d);
    printf("Enter generator: ");
    scanf("%s", g);
    dl = strlen(d);
    gl = strlen(g);

    strcpy(t, d);
    for (i = 0; i < gl - 1; i++)
        strcat(t, "0");                 // append zeros

    divide(t, g);                       // t now holds the remainder at the end
    printf("CRC = %s\n", t + dl);       // last gl-1 bits

    strcpy(t + dl, t + dl);             // (remainder stays in t)
    printf("Transmitted = %s%s\n", d, t + dl);

    printf("Enter received data: ");
    scanf("%s", r);
    divide(r, g);

    if (strchr(r, '1') == NULL)         // remainder all zeros
        printf("Data is correct\n");
    else
        printf("Data is corrupted\n");

    return 0;
}
