#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
#define MAX_TEXT 100

char matrix[SIZE][SIZE];

int isInMatrix(char ch, char *used) {
    for (int i = 0; used[i]; i++)
        if (used[i] == ch) return 1;
    return 0;
}

void generateMatrix(const char *key) {
    char used[26] = {0}; // letras já usadas
    int row = 0, col = 0;

    for (int i = 0; key[i]; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I'; // I/J são equivalentes

        if (isalpha(ch) && !isInMatrix(ch, used)) {
            matrix[row][col++] = ch;
            strncat(used, &ch, 1);

            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue;
        if (!isInMatrix(ch, used)) {
            matrix[row][col++] = ch;
            strncat(used, &ch, 1);

            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }
}
void findPosition(char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
}

// Prepara o texto para digramas (pares de letras)
int prepareText(const char *input, char *output) {
    int len = 0;

    for (int i = 0; input[i]; i++) {
        if (!isalpha(input[i])) continue;

        char ch = toupper(input[i]);
        if (ch == 'J') ch = 'I';

        output[len++] = ch;

        if (len > 1 && output[len - 1] == output[len - 2]) {
            output[len - 1] = 'X';
            output[len++] = ch;
        }
    }

    if (len % 2 != 0)
        output[len++] = 'X';

    output[len] = '\0';
    return len;
}

void playfairEncrypt(const char *input, char *output) {
    char prepared[MAX_TEXT];
    int len = prepareText(input, prepared);

    // percorre o texto preparado de 2 em 2 caracteres
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;

        // encontra a posição (ixj) do primeiro caractere do par
        findPosition(prepared[i], &r1, &c1);

        // encontra a posição (ixj) do segundo caractere do par
        findPosition(prepared[i+1], &r2, &c2);

        // se os caracteres estiverem na mesma linha
        if (r1 == r2) {
            // substitui cada caractere pelo da coluna à direita (wrap-around + módulo)
            output[i] = matrix[r1][(c1 + 1) % SIZE];
            output[i+1] = matrix[r2][(c2 + 1) % SIZE];
        }

        // se os caracteres estão na mesma coluna
        else if (c1 == c2) {
            // substitui cada caractere pelo da linha de baixo (wrap-around + módulo)
            output[i] = matrix[(r1 + 1) % SIZE][c1];
            output[i+1] = matrix[(r2 + 1) % SIZE][c2];
        }
        else { //se os caracteres formam um retângulo
            // substitui cada caractere pelo da mesma linha e coluna do outro caractere do par
            output[i] = matrix[r1][c2];
            output[i+1] = matrix[r2][c1];
        }
    }

    output[len] = '\0';
}

void printMatrix() {
    printf("Matriz Playfair:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }
}

int main() {
    const char *key = "MONARCHY";
    char plaintext[MAX_TEXT] = "BALLOON";
    char encrypted[MAX_TEXT];

    generateMatrix(key);
    printMatrix();

    playfairEncrypt(plaintext, encrypted);

    printf("Texto original: %s\n", plaintext);
    printf("Texto criptografado: %s\n", encrypted);

    return 0;
}
