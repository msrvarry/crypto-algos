#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to encrypt the plaintext using Rail Fence Cipher
void encryptRailFence(char *text, int rails, char *cipher) {
    int len = strlen(text);
    char rail[rails][len];

    // Fill with nulls
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    // Build the rail pattern
    int dir_down = 0, row = 0;
    for (int i = 0; i < len; i++) {
        // Place the character
        rail[row][i] = text[i];

        // Change direction at top or bottom rail
        if (row == 0)
            dir_down = 1;
        else if (row == rails - 1)
            dir_down = 0;

        // Move up or down
        row += dir_down ? 1 : -1;
    }

    // Construct cipher by reading the rails row-wise
    int index = 0;
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] != '\n')
                cipher[index++] = rail[i][j];

    cipher[index] = '\0';
}

// Function to decrypt Rail Fence Cipher
void decryptRailFence(char *cipher, int rails, char *plain) {
    int len = strlen(cipher);
    char rail[rails][len];

    // Fill with placeholders
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    // Mark positions with '*'
    int dir_down, row = 0;
    for (int i = 0; i < len; i++) {
        if (row == 0)
            dir_down = 1;
        if (row == rails - 1)
            dir_down = 0;

        rail[row][i] = '*';
        row += dir_down ? 1 : -1;
    }

    // Fill '*' positions with ciphertext
    int index = 0;
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] == '*' && index < len)
                rail[i][j] = cipher[index++];

    // Read plaintext following the zig-zag pattern
    row = 0;
    for (int i = 0; i < len; i++) {
        if (row == 0)
            dir_down = 1;
        else if (row == rails - 1)
            dir_down = 0;

        plain[i] = rail[row][i];
        row += dir_down ? 1 : -1;
    }

    plain[len] = '\0';
}

int main() {
    char text[256], encrypted[256], decrypted[256];
    int rails;

    printf("Enter the plaintext: ");
    scanf("%s", text);

    printf("Enter the number of rails: ");
    scanf("%d", &rails);

    if (rails < 2) {
        printf("Rail count must be at least 2.\n");
        return 1;
    }

    encryptRailFence(text, rails, encrypted);
    printf("Encrypted text: %s\n", encrypted);

    decryptRailFence(encrypted, rails, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
