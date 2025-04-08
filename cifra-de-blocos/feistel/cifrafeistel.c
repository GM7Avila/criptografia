#include <stdio.h>
#include <stdint.h>

// simplificando, o ideal é algo em torno de 16 rounds...
#define NUM_ROUNDS 4

// Função Feistel simples (substituição)
uint8_t f_function(uint8_t half_block, uint8_t round_key) {
  return (half_block ^ round_key);         // XOR simples como substituição
}

uint8_t feistel_encrypt(uint8_t plain_text, uint8_t round_keys[NUM_ROUNDS]) {
  uint8_t left_block = (plain_text >> 4) & 0X0F;            // 4 bits mais altos
  uint8_t right_block = plain_text & 0X0F;                  // 4 bits mais baixos

  // rodadas
  for (int i=0; i < NUM_ROUNDS; i++) {
    uint8_t temp = right_block;

    // aplica a Função F ao lado direito com a chave da rodada e faz XOR com o lado esquerdo
    right_block = left_block ^ f_function(right_block, round_keys[i]);

    // troca os lados: o antigo right_block vira o novo left_block
    left_block = temp;
  }

  // junta os 4 bits de left_block (shiftado << 4) com os 4 bits de right_block (permutação)
  return (left_block << 4) | right_block;
}

// operação inversa para decifragem
uint8_t feistel_decrypt(uint8_t ciphertext, uint8_t round_keys[NUM_ROUNDS]) {
    uint8_t left_block = (ciphertext >> 4) & 0x0F;
    uint8_t right_block = ciphertext & 0x0F;

    for (int i = NUM_ROUNDS - 1; i >= 0; i--) {
        uint8_t temp = left_block;
        left_block = right_block ^ f_function(left_block, round_keys[i]);
        right_block = temp;
    }

    return (left_block << 4) | right_block;
}

int main() {

  uint8_t plain_text = 0b11010110;                         // Exemplo: 214 (binario)
  uint8_t round_keys[NUM_ROUNDS] = {3, 6, 9, 12};          // Chaves das 4 rodadas (simplificado)

  uint8_t ciphertext = feistel_encrypt(plain_text, round_keys);
  uint8_t decrypted = feistel_decrypt(ciphertext, round_keys);

  printf("Plain Text: 0x%02X\n", plain_text);
  printf("Ciphertext: 0x%02X\n", ciphertext);
  printf("Decrypted: 0x%02X\n", decrypted);


  return 0;
}