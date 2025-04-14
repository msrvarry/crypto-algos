#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MOD 26

// Helper: Compute determinant of a 2x2 or 3x3 matrix
int determinant(int **matrix, int n) {
    if (n == 2)
        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];

    if (n == 3) {
        int det = 0;
        det += matrix[0][0] * (matrix[1][1]*matrix[2][2] - matrix[1][2]*matrix[2][1]);
        det -= matrix[0][1] * (matrix[1][0]*matrix[2][2] - matrix[1][2]*matrix[2][0]);
        det += matrix[0][2] * (matrix[1][0]*matrix[2][1] - matrix[1][1]*matrix[2][0]);
        return det;
    }

    return 0; // Only up to 3x3 supported
}

int mod_inverse(int a) {
    a %= MOD;
    for (int i = 1; i < MOD; i++)
        if ((a * i) % MOD == 1)
            return i;
    return -1;
}

// Helper: compute adjugate and inverse of matrix mod 26 (2x2 or 3x3)
void inverse_matrix(int **matrix, int **inverse, int n) {
    int det = determinant(matrix, n);
    int inv_det = mod_inverse((det % MOD + MOD) % MOD);
    if (inv_det == -1) {
        printf("Matrix is not invertible mod 26.\n");
        exit(1);
    }

    if (n == 2) {
        inverse[0][0] =  matrix[1][1];
        inverse[0][1] = -matrix[0][1];
        inverse[1][0] = -matrix[1][0];
        inverse[1][1] =  matrix[0][0];
    } else if (n == 3) {
        for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            int temp[2][2];
            int ti = 0, tj = 0;
            for (int r = 0; r < n; r++) {
                if (r == i) continue;
                tj = 0;
                for (int c = 0; c < n; c++) {
                    if (c == j) continue;
                    temp[ti][tj++] = matrix[r][c];
                }
                ti++;
            }
            int minor = temp[0][0]*temp[1][1] - temp[0][1]*temp[1][0];
            inverse[j][i] = ((i+j)%2==0 ? minor : -minor); // Cofactor transpose
        }
    }

    // Apply mod and inverse of determinant
    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
        inverse[i][j] = ((inverse[i][j] * inv_det) % MOD + MOD) % MOD;
    }
}

// Multiply matrix with vector mod 26
void multiply(int **matrix, int *vec, int *res, int n) {
    for (int i = 0; i < n; i++) {
        res[i] = 0;
        for (int j = 0; j < n; j++) {
            res[i] += matrix[i][j] * vec[j];
        }
        res[i] = (res[i] % MOD + MOD) % MOD;
    }
}

int main() {
    char text[256], padded[256];
    int n;

    printf("Enter the dimension of the key matrix (2 or 3): ");
    scanf("%d", &n);

    if (n < 2 || n > 3) {
        printf("Only 2x2 and 3x3 matrices are supported.\n");
        return 1;
    }

    // Allocate matrix
    int **key = malloc(n * sizeof(int *));
    int **inv = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        key[i] = malloc(n * sizeof(int));
        inv[i] = malloc(n * sizeof(int));
    }

    printf("Enter %d elements for the %dx%d key matrix:\n", n*n, n, n);
    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        scanf("%d", &key[i][j]);

    getchar(); // flush newline
    printf("Enter the plaintext (uppercase letters only): ");
    scanf("%s", text);

    // Pad with 'X' to match block size
    int len = strlen(text);
    int pad = (n - (len % n)) % n;
    strcpy(padded, text);
    for (int i = 0; i < pad; i++)
        padded[len + i] = 'X';
    padded[len + pad] = '\0';

    // Encryption
    char cipher[256] = "";
    int block[3], result[3];

    for (int i = 0; i < strlen(padded); i += n) {
        for (int j = 0; j < n; j++)
            block[j] = padded[i + j] - 'A';
        multiply(key, block, result, n);
        for (int j = 0; j < n; j++)
            cipher[i + j] = result[j] + 'A';
    }
    cipher[strlen(padded)] = '\0';
    printf("Encrypted: %s\n", cipher);

    // Decryption
    inverse_matrix(key, inv, n);

    char decrypted[256] = "";
    for (int i = 0; i < strlen(cipher); i += n) {
        for (int j = 0; j < n; j++)
            block[j] = cipher[i + j] - 'A';
        multiply(inv, block, result, n);
        for (int j = 0; j < n; j++)
            decrypted[i + j] = result[j] + 'A';
    }
    decrypted[strlen(cipher)] = '\0';
    printf("Decrypted: %s\n", decrypted);

    // Cleanup
    for (int i = 0; i < n; i++) {
        free(key[i]);
        free(inv[i]);
    }
    free(key);
    free(inv);

    return 0;
}
