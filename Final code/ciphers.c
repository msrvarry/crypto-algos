#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 1024

// Common helper
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// -------------------- ATBASH --------------------
void atbashCipher() {
    char text[MAX];
    printf("\nEnter text: ");
    fgets(text, MAX, stdin);

    for (int i = 0; text[i]; i++) {
        if (isupper(text[i]))
            text[i] = 'Z' - (text[i] - 'A');
        else if (islower(text[i]))
            text[i] = 'z' - (text[i] - 'a');
    }

    printf("Encrypted/Decrypted Text: %s\n", text);
}

// -------------------- CAESAR --------------------
void caesarCipher() {
    char text[MAX];
    int shift;
    printf("\nEnter text: ");
    fgets(text, MAX, stdin);
    printf("Enter shift: ");
    scanf("%d", &shift);
    clearInputBuffer();

    char encrypted[MAX];
    for (int i = 0; text[i]; i++) {
        if (isupper(text[i]))
            encrypted[i] = ((text[i] - 'A' + shift) % 26) + 'A';
        else if (islower(text[i]))
            encrypted[i] = ((text[i] - 'a' + shift) % 26) + 'a';
        else
            encrypted[i] = text[i];
    }
    encrypted[strlen(text)] = '\0';
    printf("Encrypted Text: %s", encrypted);

    // Decryption
    for (int i = 0; encrypted[i]; i++) {
        if (isupper(encrypted[i]))
            encrypted[i] = ((encrypted[i] - 'A' - shift + 26) % 26) + 'A';
        else if (islower(encrypted[i]))
            encrypted[i] = ((encrypted[i] - 'a' - shift + 26) % 26) + 'a';
    }
    printf("Decrypted Text: %s", encrypted);
}

// -------------------- AUGUST (Caesar +1) --------------------
void augustCipher() {
    char text[MAX];
    printf("\nEnter text: ");
    fgets(text, MAX, stdin);

    for (int i = 0; text[i]; i++) {
        if (isupper(text[i]))
            text[i] = ((text[i] - 'A' + 1) % 26) + 'A';
        else if (islower(text[i]))
            text[i] = ((text[i] - 'a' + 1) % 26) + 'a';
    }
    printf("Encrypted Text: %s", text);

    for (int i = 0; text[i]; i++) {
        if (isupper(text[i]))
            text[i] = ((text[i] - 'A' - 1 + 26) % 26) + 'A';
        else if (islower(text[i]))
            text[i] = ((text[i] - 'a' - 1 + 26) % 26) + 'a';
    }
    printf("Decrypted Text: %s", text);
}

// -------------------- AFFINE --------------------
int modInverse(int a) {
    for (int i = 1; i < 26; i++)
        if ((a * i) % 26 == 1) return i;
    return -1;
}

void affineCipher() {
    char text[MAX];
    int a, b;
    printf("\nEnter text: ");
    fgets(text, MAX, stdin);
    printf("Enter 'a' (coprime with 26): ");
    scanf("%d", &a);
    printf("Enter 'b': ");
    scanf("%d", &b);
    clearInputBuffer();

    int a_inv = modInverse(a);
    if (a_inv == -1) {
        printf("Invalid 'a'. No modular inverse exists!\n");
        return;
    }

    char encrypted[MAX];
    for (int i = 0; text[i]; i++) {
        if (isupper(text[i]))
            encrypted[i] = ((a * (text[i] - 'A') + b) % 26) + 'A';
        else if (islower(text[i]))
            encrypted[i] = ((a * (text[i] - 'a') + b) % 26) + 'a';
        else
            encrypted[i] = text[i];
    }
    encrypted[strlen(text)] = '\0';
    printf("Encrypted Text: %s", encrypted);

    // Decrypt
    for (int i = 0; encrypted[i]; i++) {
        if (isupper(encrypted[i]))
            encrypted[i] = (a_inv * ((encrypted[i] - 'A' - b + 26)) % 26) + 'A';
        else if (islower(encrypted[i]))
            encrypted[i] = (a_inv * ((encrypted[i] - 'a' - b + 26)) % 26) + 'a';
    }
    printf("Decrypted Text: %s", encrypted);
}

// -------------------- VIGENÈRE --------------------
void vigenereCipher() {
    char text[MAX], key[MAX];
    printf("\nEnter text: ");
    fgets(text, MAX, stdin);
    printf("Enter key: ");
    fgets(key, MAX, stdin);
    key[strcspn(key, "\n")] = 0;

    int len = strlen(text), klen = strlen(key);
    char encrypted[MAX];

    for (int i = 0, j = 0; i < len; i++) {
        char k = tolower(key[j % klen]) - 'a';
        if (isalpha(text[i])) {
            if (isupper(text[i]))
                encrypted[i] = ((text[i] - 'A' + k) % 26) + 'A';
            else
                encrypted[i] = ((text[i] - 'a' + k) % 26) + 'a';
            j++;
        } else {
            encrypted[i] = text[i];
        }
    }
    encrypted[len] = '\0';
    printf("Encrypted Text: %s", encrypted);

    // Decrypt
    for (int i = 0, j = 0; i < len; i++) {
        char k = tolower(key[j % klen]) - 'a';
        if (isalpha(encrypted[i])) {
            if (isupper(encrypted[i]))
                encrypted[i] = ((encrypted[i] - 'A' - k + 26) % 26) + 'A';
            else
                encrypted[i] = ((encrypted[i] - 'a' - k + 26) % 26) + 'a';
            j++;
        }
    }
    printf("Decrypted Text: %s", encrypted);
}

// -------------------- GRONSFELD --------------------
void gronsfeldCipher() {
    char text[MAX], key[MAX];
    printf("\nEnter text: ");
    fgets(text, MAX, stdin);
    printf("Enter numeric key: ");
    fgets(key, MAX, stdin);
    key[strcspn(key, "\n")] = 0;

    int len = strlen(text), klen = strlen(key);
    char encrypted[MAX];

    for (int i = 0, j = 0; i < len; i++) {
        int k = key[j % klen] - '0';
        if (isalpha(text[i])) {
            if (isupper(text[i]))
                encrypted[i] = ((text[i] - 'A' + k) % 26) + 'A';
            else
                encrypted[i] = ((text[i] - 'a' + k) % 26) + 'a';
            j++;
        } else {
            encrypted[i] = text[i];
        }
    }
    encrypted[len] = '\0';
    printf("Encrypted Text: %s", encrypted);

    // Decrypt
    for (int i = 0, j = 0; i < len; i++) {
        int k = key[j % klen] - '0';
        if (isalpha(encrypted[i])) {
            if (isupper(encrypted[i]))
                encrypted[i] = ((encrypted[i] - 'A' - k + 26) % 26) + 'A';
            else
                encrypted[i] = ((encrypted[i] - 'a' - k + 26) % 26) + 'a';
            j++;
        }
    }
    printf("Decrypted Text: %s", encrypted);
}

// -------------------- BEAUFORT --------------------
void beaufortCipher() {
    char text[MAX], key[MAX];
    printf("\nEnter text: ");
    fgets(text, MAX, stdin);
    printf("Enter key: ");
    fgets(key, MAX, stdin);
    key[strcspn(key, "\n")] = 0;

    int len = strlen(text), klen = strlen(key);
    char encrypted[MAX];

    for (int i = 0, j = 0; i < len; i++) {
        char k = toupper(key[j % klen]) - 'A';
        if (isalpha(text[i])) {
            if (isupper(text[i]))
                encrypted[i] = ((k - (text[i] - 'A') + 26) % 26) + 'A';
            else
                encrypted[i] = ((k - (text[i] - 'a') + 26) % 26) + 'a';
            j++;
        } else {
            encrypted[i] = text[i];
        }
    }
    encrypted[len] = '\0';
    printf("Encrypted Text: %s", encrypted);

    // Beaufort decryption = encryption
    printf("Decrypted Text: %s", encrypted);
}

// -------------------- AUTOCLAVE --------------------
void autoclaveCipher() {
    char text[MAX], key[MAX + MAX];
    printf("\nEnter text: ");
    fgets(text, MAX, stdin);
    printf("Enter key: ");
    fgets(key, MAX, stdin);
    key[strcspn(key, "\n")] = 0;

    strcat(key, text); // extend key with plaintext

    int len = strlen(text);
    char encrypted[MAX];

    for (int i = 0, j = 0; i < len; i++) {
        char k = tolower(key[j]) - 'a';
        if (isalpha(text[i])) {
            if (isupper(text[i]))
                encrypted[i] = ((text[i] - 'A' + k) % 26) + 'A';
            else
                encrypted[i] = ((text[i] - 'a' + k) % 26) + 'a';
            j++;
        } else {
            encrypted[i] = text[i];
        }
    }
    encrypted[len] = '\0';
    printf("Encrypted Text: %s", encrypted);

    // Decryption
    strcpy(key, key);  // reset key (key + plaintext known)
    for (int i = 0, j = 0; i < len; i++) {
        char k = tolower(key[j]) - 'a';
        if (isalpha(encrypted[i])) {
            if (isupper(encrypted[i]))
                encrypted[i] = ((encrypted[i] - 'A' - k + 26) % 26) + 'A';
            else
                encrypted[i] = ((encrypted[i] - 'a' - k + 26) % 26) + 'a';
            j++;
        }
    }
    printf("Decrypted Text: %s", encrypted);
}

// -------------------- RUNNING KEY --------------------
void runningKeyCipher() {
    char text[MAX], key[MAX];
    printf("\nEnter text: ");
    fgets(text, MAX, stdin);
    printf("Enter running key (same length or more): ");
    fgets(key, MAX, stdin);

    int len = strlen(text);
    char encrypted[MAX];

    for (int i = 0; i < len; i++) {
        char k = tolower(key[i]) - 'a';
        if (isalpha(text[i])) {
            if (isupper(text[i]))
                encrypted[i] = ((text[i] - 'A' + k) % 26) + 'A';
            else
                encrypted[i] = ((text[i] - 'a' + k) % 26) + 'a';
        } else {
            encrypted[i] = text[i];
        }
    }
    encrypted[len] = '\0';
    printf("Encrypted Text: %s", encrypted);

    for (int i = 0; i < len; i++) {
        char k = tolower(key[i]) - 'a';
        if (isalpha(encrypted[i])) {
            if (isupper(encrypted[i]))
                encrypted[i] = ((encrypted[i] - 'A' - k + 26) % 26) + 'A';
            else
                encrypted[i] = ((encrypted[i] - 'a' - k + 26) % 26) + 'a';
        }
    }
    printf("Decrypted Text: %s", encrypted);
}

// -------------------- HILL CIPHER --------------------
int modinverse(int a, int m) {
    for (int x = 1; x < m; x++)
        if (((a % m) * (x % m)) % m == 1)
            return x;
    return -1;
}

void hillCipher() {
    int n;
    printf("\nEnter dimension of key matrix (e.g. 2 for 2x2): ");
    scanf("%d", &n);
    getchar();

    int key[n][n];
    printf("Enter key matrix (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &key[i][j]);
    getchar();

    char msg[MAX];
    printf("Enter plaintext (only letters): ");
    fgets(msg, MAX, stdin);
    msg[strcspn(msg, "\n")] = 0;

    int len = strlen(msg), pad = n - (len % n);
    if (pad != n) {
        for (int i = 0; i < pad; i++)
            msg[len + i] = 'X';
        msg[len + pad] = '\0';
    }

    len = strlen(msg);
    char enc[MAX];
    for (int i = 0; i < len; i += n) {
        for (int row = 0; row < n; row++) {
            int sum = 0;
            for (int col = 0; col < n; col++)
                sum += key[row][col] * (toupper(msg[i + col]) - 'A');
            enc[i + row] = (sum % 26) + 'A';
        }
    }
    enc[len] = '\0';
    printf("Encrypted Text: %s\n", enc);
    printf("Note: Decryption requires matrix inverse (not implemented here).\n");
}

// -------------------- RAIL FENCE --------------------
void railFenceCipher() {
    int rails;
    printf("\nEnter number of rails: ");
    scanf("%d", &rails);
    getchar();

    char text[MAX];
    printf("Enter message: ");
    fgets(text, MAX, stdin);
    text[strcspn(text, "\n")] = 0;

    int len = strlen(text), dir_down = 0, row = 0;
    char rail[rails][MAX];
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    for (int i = 0; i < len; i++) {
        rail[row][i] = text[i];
        if (row == 0 || row == rails - 1)
            dir_down = !dir_down;
        row += dir_down ? 1 : -1;
    }

    char result[MAX];
    int k = 0;
    for (int i = 0; i < rails; i++)
        for (int j = 0; j < len; j++)
            if (rail[i][j] != '\n')
                result[k++] = rail[i][j];
    result[k] = '\0';
    printf("Encrypted Text: %s\n", result);
}

// -------------------- ROUTE CIPHER --------------------
void routeCipher() {
    int rows, cols;
    printf("\nEnter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);
    getchar();

    char msg[MAX];
    printf("Enter message (without spaces): ");
    fgets(msg, MAX, stdin);
    msg[strcspn(msg, "\n")] = 0;

    int len = strlen(msg), total = rows * cols;
    for (int i = len; i < total; i++)
        msg[i] = 'X';
    msg[total] = '\0';

    char mat[rows][cols];
    int k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            mat[i][j] = msg[k++];

    int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
    char encrypted[MAX];
    k = 0;

    while (top <= bottom && left <= right) {
        for (int i = top; i <= bottom; i++)
            encrypted[k++] = mat[i][left];
        left++;

        for (int i = left; i <= right; i++)
            encrypted[k++] = mat[bottom][i];
        bottom--;

        for (int i = bottom; i >= top; i--)
            encrypted[k++] = mat[i][right];
        right--;

        for (int i = right; i >= left; i--)
            encrypted[k++] = mat[top][i];
        top++;
    }

    encrypted[k] = '\0';
    printf("Encrypted Text: %s\n", encrypted);
}

// -------------------- MYSZKOWSKI CIPHER --------------------
int keyOrder(char ch, char key[], int keyLen) {
    int order = 1;
    for (int i = 0; i < keyLen; i++)
        if (key[i] < ch)
            order++;
    return order;
}

void myszkowskiCipher() {
    char msg[MAX], key[MAX];
    printf("\nEnter plaintext: ");
    fgets(msg, MAX, stdin);
    printf("Enter key: ");
    fgets(key, MAX, stdin);
    msg[strcspn(msg, "\n")] = 0;
    key[strcspn(key, "\n")] = 0;

    int len = strlen(msg), keyLen = strlen(key);
    int rows = (len + keyLen - 1) / keyLen;
    char matrix[rows][keyLen];

    int k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < keyLen; j++)
            matrix[i][j] = (k < len) ? msg[k++] : 'X';

    int printed[MAX] = {0};
    printf("Encrypted Text: ");
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        for (int j = 0; j < keyLen; j++) {
            if (toupper(key[j]) == ch && !printed[j]) {
                for (int i = 0; i < rows; i++)
                    printf("%c", matrix[i][j]);
                printed[j] = 1;
            }
        }
    }
    printf("\nDecryption not implemented.\n");
}


void placeholder(const char* name) {
    printf("\n%s cipher not yet included in this portion of the code.\n", name);
}

// void gronsfeldCipher() { placeholder("Gronsfeld"); }
// void beaufortCipher() { placeholder("Beaufort"); }
// void autoclaveCipher() { placeholder("Autoclave"); }
// void runningKeyCipher() { placeholder("Running Key"); }
// void hillCipher() { placeholder("Hill"); }
// void railFenceCipher() { placeholder("Rail Fence"); }
// void routeCipher() { placeholder("Route"); }
// void myszkowskiCipher() { placeholder("Myszkowski"); }

int main() {
    int choice;
    while (1) {
        printf("\n=== CLASSICAL CIPHERS MENU ===\n");
        printf("1.  Atbash Cipher\n");
        printf("2.  Caesar Cipher\n");
        printf("3.  August Cipher\n");
        printf("4.  Affine Cipher\n");
        printf("5.  Vigenère Cipher\n");
        printf("6.  Gronsfeld Cipher\n");
        printf("7.  Beaufort Cipher\n");
        printf("8.  Autoclave Cipher\n");
        printf("9.  Running Key Cipher\n");
        printf("10. Hill Cipher\n");
        printf("11. Rail Fence Cipher\n");
        printf("12. Route Cipher\n");
        printf("13. Myszkowski Cipher\n");
        printf("0.  Exit\n");
        printf("Choose a cipher: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: atbashCipher(); break;
            case 2: caesarCipher(); break;
            case 3: augustCipher(); break;
            case 4: affineCipher(); break;
            case 5: vigenereCipher(); break;
            case 6: gronsfeldCipher(); break;
            case 7: beaufortCipher(); break;
            case 8: autoclaveCipher(); break;
            case 9: runningKeyCipher(); break;
            case 10: hillCipher(); break;
            case 11: railFenceCipher(); break;
            case 12: routeCipher(); break;
            case 13: myszkowskiCipher(); break;
            case 0: printf("Goodbye!\n"); return 0;
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}