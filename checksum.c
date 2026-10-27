#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add(char *s) {
    char h[9] = "";
    strncpy(h, s, 8);                                   // first 8 bits
    int sum = strtol(h, NULL, 2) + strtol(s + 8, NULL, 2);  // + last 8 bits
    if (sum > 255)
        sum = (sum & 255) + 1;                          // wrap the carry
    return sum;
}

int main() {
    char s[17], r[17];
    int i;

    printf("Enter 16 bit data: ");
    scanf("%s", s);

    int checksum = ~add(s) & 255;                       // 1's complement

    printf("Checksum = ");
    for (i = 7; i >= 0; i--)
        printf("%d", (checksum >> i) & 1);

    printf("\nEnter received data: ");
    scanf("%s", r);

    if (add(r) + checksum == 255)                       // all 1s
        printf("Data is correct\n");
    else
        printf("Data is corrupted\n");

    return 0;
}
