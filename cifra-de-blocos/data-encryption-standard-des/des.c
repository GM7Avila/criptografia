/* ====================== DATA ENCRYPTION STANDARD (DES) ======================

1. Entrada: Bloco de 64 bits + Chave de 64 bits (56 bits efetivos + 8 bits de paridade)

2. Permutação Inicial (IP):
   - Reorganiza os bits do bloco usando a tabela IP
   - Exemplo: bit 1 do texto claro vai para posição 58

3. Geração de Subchaves:
   - PC-1 remove bits de paridade (64->56 bits)
   - Divide em C0 (28 bits) e D0 (28 bits)
   - 16 rodadas de rotações:
     * Rodadas 1,2,9,16: rotação simples (1 bit)
     * Demais: rotação dupla (2 bits)
   - PC-2 seleciona 48 bits para cada subchave

4. Rodadas Feistel (16 iterações):
   a) Expansão:
      - R(n-1) de 32 para 48 bits usando tabela E
   b) Mistura com chave:
      - XOR entre R expandido e subchave
   c) Substituição S-box:
      - 8 blocos de 6 bits -> 8 blocos de 4 bits
      - Cada S-box tem tabela 4x16 específica
   d) Permutação P:
      - Reorganização final de 32 bits

5. Pós-processamento:
   - Troca final L16/R16
   - Permutação Final (IP⁻¹)
   - Produz bloco cifrado de 64 bits

6. Segurança:
   - Confusão (S-boxes)
   - Difusão (permutações)
   - Chave de 56 bits efetivos
   - 16 rodadas de transformação

7. Observações:
   - Implementação mostra apenas cifração
   - Decifração usa mesma estrutura com subchaves invertidas
   - Não inclui modos de operação (ECB, CBC, etc)
   - Otimizações possíveis (lookup tables, operações bit a bit)
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>

// ====================== TABELAS DES ======================

// Tabela IP: Permutação inicial (64 bits para 64 bits)
int IP[] = {
  58, 50, 42, 34, 26, 18, 10,  2,
  60, 52, 44, 36, 28, 20, 12,  4,
  62, 54, 46, 38, 30, 22, 14,  6,
  64, 56, 48, 40, 32, 24, 16,  8,
  57, 49, 41, 33, 25, 17,  9,  1,
  59, 51, 43, 35, 27, 19, 11,  3,
  61, 53, 45, 37, 29, 21, 13,  5,
  63, 55, 47, 39, 31, 23, 15,  7
};

// Tabela IP-1: Permutação inversa (64 bits para 64 bits)
int IP_INV[] = {
  40,  8, 48, 16, 56, 24, 64, 32,
  39,  7, 47, 15, 55, 23, 63, 31,
  38,  6, 46, 14, 54, 22, 62, 30,
  37,  5, 45, 13, 53, 21, 61, 29,
  36,  4, 44, 12, 52, 20, 60, 28,
  35,  3, 43, 11, 51, 19, 59, 27,
  34,  2, 42, 10, 50, 18, 58, 26,
  33,  1, 41,  9, 49, 17, 57, 25
};

// Tabela PC-1 (Escolha Permutada 1): Permutação de 64 bits para 56 bits
int PC1[] = {
  57,49,41,33,25,17,9,
  1,58,50,42,34,26,18,
  10,2,59,51,43,35,27,
  19,11,3,60,52,44,36,
  63,55,47,39,31,23,15,
  7,62,54,46,38,30,22,
  14,6,61,53,45,37,29,
  21,13,5,28,20,12,4
};

// Tabela PC-2 (Escolha Permutada 2): Permutação de 56 bits para 48 bits
int PC2[] = {
  14,17,11,24,1,5,
  3,28,15,6,21,10,
  23,19,12,4,26,8,
  16,7,27,20,13,2,
  41,52,31,37,47,55,
  30,40,51,45,33,48,
  44,49,39,56,34,53,
  46,42,50,36,29,32
};

// Tabela de Left Shift: Quantidade de bits a serem deslocados por rodada (16 ao total)
int SHIFT_SCHEDULE[] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

// Tabela de expansão: Permutação de 32 bits para 48 bits
// Antes de RE0 entrar na Função F é preciso realizar uma expansão de bits
// RE0: Permutação de 32 bits para 48 bits (tamanho da subchave)
int EXPANSION[] = {
    32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1
};

// Tabela P: Permutação de 32 bits para 32 bits
// Último passo da Função F: recebe a saida das s-boxes concatenadas
int P[] = {
    16,7,20,21,
    29,12,28,17,
    1,15,23,26,
    5,18,31,10,
    2,8,24,14,
    32,27,3,9,
    19,13,30,6,
    22,11,4,25
};

// S-boxes: Usamos 8 s-boxes com 4x16, com valores de 0-15
// 1. Primeiro + Último bit = linha
// 2. Bits do meio = coluna
int S_BOXES[8][4][16] = {
    // S-box 1
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    // S-box 2
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    // S-box 3
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    // S-box 4
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    // S-box 5
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    // S-box 6
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    // S-box 7
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    // S-box 8
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

// Função de permutação
/**
 * Realiza uma permutação de bits usando uma tabela específica
 * @param input: Dado de entrada (64 ou 56 bits)
 * @param table: Tabela de permutação a ser usada
 * @param n: Número de elementos na tabela (tamanho da saída)
 * @return Dado permutado
 */
uint64_t permute(uint64_t input, int *table, int n) {
    uint64_t output = 0;
    for (int i = 0; i < n; i++) {
        output <<= 1;
        output |= (input >> (64 - table[i])) & 1;
    }
    return output;
}

// Função Feistel (F): aplica expansão, XOR com subchave, S-boxes e permutação final (P)
/**
 * Função Feistel: Realiza a operação principal de cada rodada
 * @param R: Bloco de 32 bits direito
 * @param k: Subchave de 48 bits para a rodada
 * @return Resultado de 32 bits após as operações
 */
uint32_t feistel(uint32_t R, uint64_t k) {
    
    // Expansão de 32 para 48 bits
    uint64_t expandedR = permute((uint64_t)R << 32, EXPANSION, 48);
    
    // XOR com a subchave
    uint64_t temp = expandedR ^ k;

    // Processamento pelas S-boxes (8 boxes de 6 para 4 bits)
    uint32_t out = 0; // no final de todas as S-boxes, vamos obter 32 bits
    for (int i = 0; i < 8; i++) {
        // calcula a linha (bits 1 e 6) e a coluna (bits 2 até 5)
        int row = ((temp >> (42 - 6*i)) & 0x20) | ((temp >> (42 - 6*i + 5)) & 1);
        int col = (temp >> (43 - 6*i + 1)) & 0xF;
        
        // busca valor na S-box correspondente (cada S-box mapeia 6 bits para 4 bits)
        int s_val = S_BOXES[i][row >> 4][col];

        // concatena os resultados das S-boxes (8x4 bits = 32 bits)
        out = (out << 4) | s_val;
    }

    // Permutação final na tabela P (32 bits -> 32 bits)
    return permute((uint64_t)out << 32, P, 32);
}

/**
 * Gera as 16 subchaves de 48 bits a partir da chave principal
 * @param key: Chave principal de 64 bits (com bits de paridade)
 * @param subkeys: Array para armazenar as 16 subchaves geradas
 */
void generate_subkeys(uint64_t key, uint64_t subkeys[16]) {
    // Permutação inicial PC-1 (64 bits -> 56 bits)
    uint64_t permuted_key = permute(key, PC1, 56);

    // Divide em metades C e D (28 bits cada)
    uint32_t C = (permuted_key >> 28) & 0xFFFFFFF;
    uint32_t D = permuted_key & 0xFFFFFFF;

    // Gera as 16 subchaves
    for (int i = 0; i < 16; i++) {
        
        // rotaciona as metades conforme o cronograma de Left Shifts (SHIFT_SCHEDULE)
        C = ((C << SHIFT_SCHEDULE[i]) | (C >> (28 - SHIFT_SCHEDULE[i]))) & 0xFFFFFFF;
        D = ((D << SHIFT_SCHEDULE[i]) | (D >> (28 - SHIFT_SCHEDULE[i]))) & 0xFFFFFFF;

        // Combinando C e D e aplica PC-2 (Escolha Permutada 2)
        uint64_t CD = (((uint64_t)C) << 28) | (uint64_t)D;
        subkeys[i] = permute(CD << 8, PC2, 48); // shift adicional para alinhamento
    }
}

/**
 * Função principal de cifragem DES
 * @param plaintext: Bloco de 64 bits a ser cifrado
 * @param key: Chave de 64 bits (com bits de paridade)
 * @return Bloco cifrado de 64 bits
 */
uint64_t des_encrypt(uint64_t plaintext, uint64_t key) {

    // 1. Permutação Inicial (IP)
    plaintext = permute(plaintext, IP, 64);

    // 2. Divide em blocos L e R de 32 bits                       
    uint32_t L = (plaintext >> 32) & 0xFFFFFFFF;
    uint32_t R = plaintext & 0xFFFFFFFF;

    // 3. Gera todas as subchaves (antecipadamente)
    uint64_t subkeys[16];
    generate_subkeys(key, subkeys);


    // 4. Realiza as 16 rodadas Feistel
    for (int i = 0; i < 16; i++) {
        uint32_t temp = R;
        R = L ^ feistel(R, subkeys[i]);
        L = temp;
    }

    // 5. Concatenação final (troca L e R)
    uint64_t preoutput = ((uint64_t)R << 32) | L;

    // 6. Permutação Final (IP⁻¹)
    return permute(preoutput, IP_INV, 64);
}

int main() {
    uint64_t plaintext = 0x0123456789ABCDEF;
    uint64_t key = 0x133457799BBCDFF1;

    uint64_t ciphertext = des_encrypt(plaintext, key);
    printf("Ciphertext: %016lX\n", ciphertext);

    return 0;
}
