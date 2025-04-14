#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to compute GCD (for coprime check)
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to find modular inverse of a mod m
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // inverse doesn't exist
}

// Encrypt using Affine Cipher
void affine_encrypt(char *text, int a, int b) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = base + (a * (text[i] - base) + b) % 26;
        }
    }
}

// Decrypt using Affine Cipher
void affine_decrypt(char *text, int a, int b) {
    int a_inv = modInverse(a, 26);
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            int val = text[i] - base - b;
            if (val < 0) val += 26;
            text[i] = base + (a_inv * val) % 26;
        }
    }
}

int main() {
    char text[100], cipher[100];
    int a, b;

    printf("Enter a word: ");
    scanf("%s", text);

    printf("Enter value for 'a': ");
    scanf("%d", &a);
    printf("Enter value for 'b': ");
    scanf("%d", &b);

    if (gcd(a, 26) != 1) {
        printf("Error: 'a' must be coprime with 26.\n");
        return 1;
    }

    strcpy(cipher, text);
    affine_encrypt(cipher, a, b);
    printf("Encrypted: %s\n", cipher);

    affine_decrypt(cipher, a, b);
    printf("Decrypted: %s\n", cipher);

    return 0;
}
