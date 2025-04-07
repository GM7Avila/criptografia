#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAM_MAX 1000

/**
 * Criptografa o texto fornecido utilizando o algoritmo da Cifra de César.
 *
 * Cada letra no texto de entrada é deslocada, dentro do alfabeto, por um valor
 * determinado pela chave (key). Caracteres não alfabéticos permanecem inalterados.
 *
 * @param text Texto de entrada a ser criptografado. É modificado diretamente.
 * @param key Número de posições que cada letra do texto será deslocada.
 *            Deve ser um número inteiro não negativo.
 */

void encrypt(char text[], int key) {
  for(int i=0; text[i] != '\0'; i++) {
    
    // se for um caracter alfabetico
    if(isalpha(text[i])) {
      // verifica se é maiusculo ou minusculo
      char base = isupper(text[i]) ? 'A' : 'a'; // base recebe: 'a' (ASCII: 97) ou 'A' (ASCII: 65)
      
      /*
        Aplica a cifra de César à letra text[i]:

        1. Subtrai a base ('A' ou 'a') para converter a letra em um valor entre 0 e 25.
          Exemplo: 'Z' - 'A' = 90 - 65 = 25

        2. Soma a chave de deslocamento (key).
          Exemplo: 25 + 3 = 28

        3. Aplica módulo 26 para garantir que o valor continue no intervalo do alfabeto.
          Exemplo: 28 % 26 = 2

        4. Soma novamente a base para converter o valor numérico de volta para caractere.
          Exemplo: 2 + 'A' = 67 → 'C'

        Resultado: 'Z' se torna 'C' com deslocamento 3
      */
      text[i] = (text[i] - base + key) % 26 + base;
 
    }
  }
}

int main() {
  char text[TAM_MAX]; // Tamanho máximo do texto claro
  int key; // Chave: valor do deslocamento

  printf("Digite o texto claro: ");
  fgets(text, TAM_MAX, stdin);

  text[strcspn(text, "\n")] = '\0'; // Remover o caractere de nova linha

  printf("Digite o valor da chave: ");
  scanf("%d", &key);

  key = key % 26; // Passa o valor para módulo 26 (garante key entre 0 a 25)

  encrypt(text, key);

  printf("Texto cifrado: %s\n", text);

  return 0;
}
