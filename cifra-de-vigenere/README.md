# Cifra de Vigenère

A Cifra de Vigenère é um método de criptografia por substituição polialfabética, na qual cada letra do texto claro é cifrada utilizando uma chave composta por uma sequência de letras. Cada letra da chave define um deslocamento distinto, aplicando a Cifra de César com diferentes valores ao longo do texto. Quando a chave é mais curta que o texto, ela é repetida ciclicamente.

## Definição Matemática

- **Criptografia**: $Ei=(Pi+Ki) mod  26$
- **Descriptografia**: $Pi=(Ei−Ki+26) mod  26$

Onde:

- `Pi` é a posição da i-ésima letra do texto claro no alfabeto;
- `Ki` é a posição da i-ésima letra da chave no alfabeto (a chave é repetida se necessário);
- `Ei` é a posição da letra cifrada;

### Exemplo

Considere o texto claro `ATAQUEAOAMANHECER` e a chave `CHAVE`.

Primeiro, repetimos a chave para cobrir o tamanho do texto:

```
Texto:  A T A Q U E A O A M A N H E C E R
Chave:  C H A V E C H A V E C H A V E C H
```

Convertendo as letras para posições (A=0,B=1,..., Z=25) e aplicando a fórmula $Ei=(Pi + Ki) mod26%$:

```
A (0) + C (2)  = 2  → C
T (19) + H (7) = 26 → 0 → A
A (0) + A (0)  = 0  → A
Q (16) + V (21) = 37 → 11 → L
U (20) + E (4) = 24 → Y
...
```

Resultado final: `CAALYGHOVQCUHZGGY`

## Executando o Algoritmo

Para compilar e executar a implementação da Cifra de Vigenère em C, siga os seguintes passos em um terminal Unix-like:

1. Abra o terminal e navegue até o diretório onde está localizado o arquivo `cifravigenere.c`.
2. Compile o código-fonte utilizando o compilador GCC: `gcc vigenere.c -o cifravigenere`

Execute o programa compilado: `./cifravigenere`

Durante a execução, o programa solicitará:

- O texto claro a ser criptografado.

  A chave utilizada para a cifra.

O programa exibirá então o texto cifrado utilizando a Cifra de Vigenère. Também poderá permitir a operação inversa (descriptografar) utilizando a mesma chave fornecida.
