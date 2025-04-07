#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * Criptografa um texto usando a Cifra de Vigenère.
 *
 * Cada caractere alfabético do texto é deslocado com base na letra correspondente da chave.
 * Caracteres não alfabéticos permanecem inalterados.
 *
 * @param text Texto a ser criptografado (modificado in-place).
 * @param key Palavra-chave usada para cifrar o texto.
 */
void encrypt(char *text, const char *key) {
    int text_len = strlen(text);
    int key_len = strlen(key);
    int key_index = 0;

    for (int i = 0; i < text_len; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            
            // key_char recebe o valor em modulo do key_len atual (ciclo enquanto percorre o text)
            char key_char = toupper(key[key_index % key_len]) - 'A';
            text[i] = (text[i] - base + key_char) % 26 + base;
            key_index++;
        }
    }
}

/**
 * Descriptografa um texto cifrado com a Cifra de Vigenère.
 *
 * Reverte o processo de criptografia usando a mesma chave.
 *
 * @param text Texto cifrado a ser descriptografado (modificado in-place).
 * @param key Palavra-chave usada para decifrar o texto.
 */
void decrypt(char *text, const char *key) {
    int text_len = strlen(text);
    int key_len = strlen(key);
    int key_index = 0;

    for (int i = 0; i < text_len; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char key_char = toupper(key[key_index % key_len]) - 'A';
            text[i] = (text[i] - base - key_char + 26) % 26 + base;
            key_index++;
        }
    }
}

int main() {
    char text[] = "ATAQUEAOAMANHECER";
    char key[] = "CHAVE";

    printf("Texto original: %s\n", text);
    encrypt(text, key);
    printf("Texto criptografado: %s\n", text);
    decrypt(text, key);
    printf("Texto descriptografado: %s\n", text);

    return 0;
}
