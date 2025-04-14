#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Validate if key only contains digits
int is_valid_key(char *key) {
    for (int i = 0; key[i] != '\0'; i++) {
        if (!isdigit(key[i])) return 0;
    }
    return 1;
}

// Encrypt using Gronsfeld Cipher
void gronsfeld_encrypt(char *text, char *key) {
    int key_len = strlen(key);

    for (int i = 0, j = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            int shift = key[j % key_len] - '0';
            text[i] = base + (text[i] - base + shift) % 26;
            j++;
        }
    }
}

// Decrypt using Gronsfeld Cipher
void gronsfeld_decrypt(char *text, char *key) {
    int key_len = strlen(key);

    for (int i = 0, j = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            int shift = key[j % key_len] - '0';
            int val = (text[i] - base - shift + 26) % 26;
            text[i] = base + val;
            j++;
        }
    }
}

int main() {
    char text[100], cipher[100], key[100];

    printf("Enter a word: ");
    scanf("%s", text);

    printf("Enter a numeric key (e.g. 31415): ");
    scanf("%s", key);

    if (!is_valid_key(key)) {
        printf("Error: Gronsfeld key must be numeric digits only.\n");
        return 1;
    }

    strcpy(cipher, text);

    gronsfeld_encrypt(cipher, key);
    printf("Encrypted: %s\n", cipher);

    gronsfeld_decrypt(cipher, key);
    printf("Decrypted: %s\n", cipher);

    return 0;
}
