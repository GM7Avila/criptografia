#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAM_MAX 1000

/**
 * Encrypts the given text using the Caesar cipher algorithm.
 *
 * Each letter in the input text is shifted by the specified key value
 * within the alphabet. Non-alphabetic characters remain unchanged.
 *
 * @param text The input string to be encrypted. It is modified in place.
 * @param key The number of positions each letter in the text is shifted.
 *            Should be a non-negative integer.
 */
void encrypt(char text[], int key) {
  for(int i=0; text[i] != '\0'; i++) {
    if(isalpha(text[i])) {
      char base = isupper(text[i]) ? 'A' : 'a';
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
