#include <stdio.h>
#include <string.h>
#include <ctype.h>

void atbash(char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            text[i] = 'Z' - (toupper(text[i]) - 'A');
        }
    }
}

int main() {
    char text[100];
    printf("Enter a word: ");
    scanf("%s", text);

    atbash(text);
    printf("Atbash Cipher: %s\n", text);
    return 0;
}