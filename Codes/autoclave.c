#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Encrypt using Autoclave Cipher
void autoclave_encrypt(char *text, char *key, char *cipher) {
    int text_len = strlen(text);
    int key_len = strlen(key);

    for (int i = 0; i < text_len; i++) {
        char base = isupper(text[i]) ? 'A' : 'a';
        char key_char;
        if (i < key_len)
            key_char = toupper(key[i]) - 'A';
        else
            key_char = toupper(text[i - key_len]) - 'A'; // use plaintext as key

        cipher[i] = base + (toupper(text[i]) - 'A' + key_char) % 26;
    }
    cipher[text_len] = '\0';
}

// Decrypt using Autoclave Cipher
void autoclave_decrypt(char *cipher, char *key, char *decrypted) {
    int text_len = strlen(cipher);
    int key_len = strlen(key);

    for (int i = 0; i < text_len; i++) {
        char base = isupper(cipher[i]) ? 'A' : 'a';
        char key_char;

        if (i < key_len)
            key_char = toupper(key[i]) - 'A';
        else
            key_char = toupper(decrypted[i - key_len]) - 'A'; // recovered plaintext as key

        decrypted[i] = base + (toupper(cipher[i]) - 'A' - key_char + 26) % 26;
    }
    decrypted[text_len] = '\0';
}

int main() {
    char text[100], key[100], cipher[100], decrypted[100];

    printf("Enter a word: ");
    scanf("%s", text);

    printf("Enter a key: ");
    scanf("%s", key);

    autoclave_encrypt(text, key, cipher);
    printf("Encrypted: %s\n", cipher);

    autoclave_decrypt(cipher, key, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
