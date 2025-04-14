#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 256

// Helper: assign numerical values to keyword letters (handling duplicates)
void assignKeyOrder(char *key, int *order) {
    int len = strlen(key);
    int used[MAX] = {0};

    for (int i = 0; i < len; i++) {
        int count = 1;
        for (int j = 0; j < len; j++) {
            if (key[j] < key[i]) count++;
        }
        order[i] = count;
    }

    // handle duplicates (assign same number to same letters)
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (i != j && key[i] == key[j]) {
                order[j] = order[i];
            }
        }
    }
}

// Encryption function
void encryptMyszkowski(char *text, char *key, char *cipher) {
    int keylen = strlen(key);
    int textlen = strlen(text);

    // Calculate number of rows in matrix
    int rows = (textlen + keylen - 1) / keylen;

    // Pad text
    int paddedLen = rows * keylen;
    for (int i = textlen; i < paddedLen; i++) {
        text[i] = 'X';
    }
    text[paddedLen] = '\0';

    // Fill matrix row-wise
    char matrix[rows][keylen];
    int k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < keylen; j++)
            matrix[i][j] = text[k++];

    // Assign key order numbers
    int order[keylen];
    assignKeyOrder(key, order);

    // Print columns based on order
    int used[MAX] = {0}, index = 0;
    for (int num = 1; num <= keylen; num++) {
        for (int i = 0; i < keylen; i++) {
            if (order[i] == num && !used[i]) {
                // If this number is duplicated, print all such columns in order
                for (int j = 0; j < keylen; j++) {
                    if (order[j] == num) {
                        for (int r = 0; r < rows; r++)
                            cipher[index++] = matrix[r][j];
                        used[j] = 1;
                    }
                }
                break;
            }
        }
    }
    cipher[index] = '\0';
}

// Decryption function
void decryptMyszkowski(char *cipher, char *key, char *plain) {
    int keylen = strlen(key);
    int cipherlen = strlen(cipher);
    int rows = cipherlen / keylen;

    char matrix[rows][keylen];

    // Assign order
    int order[keylen];
    assignKeyOrder(key, order);

    // Read columns into matrix
    int index = 0, used[MAX] = {0};
    for (int num = 1; num <= keylen; num++) {
        for (int i = 0; i < keylen; i++) {
            if (order[i] == num && !used[i]) {
                for (int j = 0; j < keylen; j++) {
                    if (order[j] == num) {
                        for (int r = 0; r < rows; r++)
                            matrix[r][j] = cipher[index++];
                        used[j] = 1;
                    }
                }
                break;
            }
        }
    }

    // Read row-wise
    index = 0;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < keylen; c++)
            plain[index++] = matrix[r][c];
    plain[index] = '\0';
}

int main() {
    char text[MAX], key[MAX], cipher[MAX], decrypted[MAX];

    printf("Enter the plaintext (uppercase letters only): ");
    scanf("%s", text);

    printf("Enter the keyword (with possible duplicate letters): ");
    scanf("%s", key);

    // Convert to uppercase
    for (int i = 0; text[i]; i++) text[i] = toupper(text[i]);
    for (int i = 0; key[i]; i++) key[i] = toupper(key[i]);

    encryptMyszkowski(text, key, cipher);
    printf("Encrypted text: %s\n", cipher);

    decryptMyszkowski(cipher, key, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
