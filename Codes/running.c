#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Encrypt using Running Key Cipher
void running_key_encrypt(char *text, char *key, char *cipher) {
    int len = strlen(text);

    for (int i = 0; i < len; i++) {
        if (!isalpha(text[i]) || !isalpha(key[i])) {
            cipher[i] = text[i]; // copy as-is (not expected for this version)
            continue;
        }
        char base = isupper(text[i]) ? 'A' : 'a';
        int key_shift = toupper(key[i]) - 'A';
        cipher[i] = base + (toupper(text[i]) - 'A' + key_shift) % 26;
    }
    cipher[len] = '\0';
}

// Decrypt using Running Key Cipher
void running_key_decrypt(char *cipher, char *key, char *plain) {
    int len = strlen(cipher);

    for (int i = 0; i < len; i++) {
        if (!isalpha(cipher[i]) || !isalpha(key[i])) {
            plain[i] = cipher[i]; // copy as-is (not expected for this version)
            continue;
        }
        char base = isupper(cipher[i]) ? 'A' : 'a';
        int key_shift = toupper(key[i]) - 'A';
        plain[i] = base + (toupper(cipher[i]) - 'A' - key_shift + 26) % 26;
    }
    plain[len] = '\0';
}

int main() {
    char text[100], key[100], cipher[100], decrypted[100];

    printf("Enter a word: ");
    scanf("%s", text);

    printf("Enter a key (at least as long as the word): ");
    scanf("%s", key);

    if (strlen(key) < strlen(text)) {
        printf("Error: Key must be at least as long as the text.\n");
        return 1;
    }

    running_key_encrypt(text, key, cipher);
    printf("Encrypted: %s\n", cipher);

    running_key_decrypt(cipher, key, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
