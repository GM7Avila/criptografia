#include <stdio.h>

// Estrutura básica de umaS-box com 16 entradas de 4 bits (0 a 15) - Ideal Block Cipher

int s_box[16] = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 9, 0, 7, 5 };

int cifrar(int entrada) {
    if (entrada < 0 || entrada > 15) {
        printf("Entrada inválida - deve ser entre 1 e 15 (4 bits)\n");
        return -1;
    }
    return s_box[entrada];
}

int main() {
    int entrada;

    printf("Digite um número de 0 a 15: ");
    scanf("%d", &entrada);

    int saida = cifrar(entrada);

    if (saida != -1) {
        printf("Saída cifrada: %04b (decimal: %d)\n", saida, saida);
    }

    return 0;
}
