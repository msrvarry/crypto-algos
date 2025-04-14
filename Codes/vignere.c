#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt using Vigenère cipher
void vigenere_encrypt(char *text, char *key) {
    int text_len = strlen(text);
    int key_len = strlen(key);

    for (int i = 0, j = 0; i < text_len; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char key_char = toupper(key[j % key_len]) - 'A';
            text[i] = base + (text[i] - base + key_char) % 26;
            j++;
        }
    }
}

// Function to decrypt using Vigenère cipher
void vigenere_decrypt(char *text, char *key) {
    int text_len = strlen(text);
    int key_len = strlen(key);

    for (int i = 0, j = 0; i < text_len; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char key_char = toupper(key[j % key_len]) - 'A';
            int val = (text[i] - base - key_char + 26) % 26;
            text[i] = base + val;
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

    strcpy(cipher, text); // Copy input to preserve original for decryption

    vigenere_encrypt(cipher, key);
    printf("Encrypted: %s\n", cipher);

    vigenere_decrypt(cipher, key);
    printf("Decrypted: %s\n", cipher);

    return 0;
}
