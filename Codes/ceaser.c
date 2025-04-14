#include <stdio.h>
#include <string.h>
#include <ctype.h>

void caesar(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = base + (text[i] - base + shift) % 26;
        }
    }
}

int main() {
    char text[100];
    printf("Enter a word: ");
    scanf("%s", text);

    caesar(text, 3);
    printf("Caesar Cipher: %s\n", text);
    return 0;
}
