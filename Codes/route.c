#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Pad with 'X' to fill matrix
void padText(char *text, int rows, int cols) {
    int len = strlen(text);
    int total = rows * cols;
    for (int i = len; i < total; i++) {
        text[i] = 'X';
    }
    text[total] = '\0';
}

// Encrypt: fill row-wise, read column-wise
void encryptRoute(char *plain, int rows, int cols, char *cipher) {
    char matrix[rows][cols];
    int len = strlen(plain);
    int k = 0;

    // Fill matrix row-wise
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = plain[k++];

    // Read column-wise (top to bottom)
    k = 0;
    for (int j = 0; j < cols; j++)
        for (int i = 0; i < rows; i++)
            cipher[k++] = matrix[i][j];

    cipher[k] = '\0';
}

// Decrypt: fill column-wise, read row-wise
void decryptRoute(char *cipher, int rows, int cols, char *plain) {
    char matrix[rows][cols];
    int len = strlen(cipher);
    int k = 0;

    // Fill matrix column-wise
    for (int j = 0; j < cols; j++)
        for (int i = 0; i < rows; i++)
            matrix[i][j] = cipher[k++];

    // Read matrix row-wise
    k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            plain[k++] = matrix[i][j];

    plain[k] = '\0';
}

int main() {
    char text[256], padded[256], encrypted[256], decrypted[256];
    int rows, cols;

    printf("Enter the plaintext (uppercase letters only): ");
    scanf("%s", text);

    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    if (rows < 1 || cols < 1) {
        printf("Matrix size must be at least 1x1.\n");
        return 1;
    }

    strcpy(padded, text);
    padText(padded, rows, cols);

    encryptRoute(padded, rows, cols, encrypted);
    printf("Encrypted text: %s\n", encrypted);

    decryptRoute(encrypted, rows, cols, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
