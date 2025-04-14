#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Beaufort cipher logic (encryption and decryption are the same)
void beaufort_cipher(char *text, char *key) {
    int text_len = strlen(text);
    int key_len = strlen(key);

    for (int i = 0, j = 0; i < text_len; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char key_char = toupper(key[j % key_len]) - 'A';
            char cipher_char = base + (26 + key_char - (toupper(text[i]) - 'A')) % 26;
            text[i] = cipher_char;
            j++;
        }
    }
}

int main() {
    char text[100], cipher[100], key[100];

    printf("Enter a word: ");
    scanf("%s", text);

    printf("Enter a key: ");
    scanf("%s", key);

    strcpy(cipher, text);

    beaufort_cipher(cipher, key);
    printf("Encrypted: %s\n", cipher);

    // Beaufort is reciprocal: same function for decryption
    beaufort_cipher(cipher, key);
    printf("Decrypted: %s\n", cipher);

    return 0;
}
