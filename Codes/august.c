#include <stdio.h>
#include <string.h>
#include <ctype.h>

void august_cipher(char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = base + (text[i] - base + 1) % 26;
        }
    }
}

int main() {
    char text[100];
    printf("Enter a word: ");
    scanf("%s", text);

    august_cipher(text);
    printf("August Cipher: %s\n", text);
    return 0;
}