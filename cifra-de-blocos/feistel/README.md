# Cifra de Feistel

## Introdução

A Cifra de Feistel é uma construção fundamental utilizada no deisgn de cifradores de bloco. Ela fornece um arcabouço seguro e flexível para desenvolver para desenvolver algoritmos cripográficos simétricos, incluindo o famoso DES (Data Encrpytion Standard). Seu funcionamento é baseado n divisão do bloco de dadosem duas metadas (esquerda e direita), e na aplicação de uma função repetida a cada rodada chamada Função F.

## Limitações na Cifra de Bloco Ideal

Uma cifra de bloco ideal simula uma permutação aleatória segura para cada chave. No entanto, é impraticável implementá-la diretamente devido ao enorme espaço de chaves e transformações possíveis. A cifra de Feistel aproxima esse comportamento de maneira eficiente.

A estrutura de Feistel corrige limitações de cifradores simples que não possuem reversibilidade direta. Cada operação do processo de cifragem pode ser invertida facilmente, desde que as mesmas chaves sejam usadas em ordem inversa. Ela realiza um **produto de cifras**, combina várias operações simples (como **XOR**, substituições e permutações) em múltiplas rodadas para aumentar a segurança do sistema.

## Confusão e Difusão

- **Confusão**: A relação entre a chave e o texto cifrado é obscurecida. Isso é geralmente obtido com operações de substituição, como as aplicadas na Função F.
- **Difusão**: Cada bit da entrada afeta muitos bits da saída. Isso é promovido por permulações e pela troca de lados a cada rodada.

## Princípios Básicos e Fundamentos

- Opera com blocos fixos de dados (ex.: 64 bits)
- Usa uma chave mestra, da qual derivam sub-chaves a cada rodada.
- Divide o bloco em duas metades: L (left) e R (right).
- Aplica várias rodadas que utilizam a Função F (que por sua vez recebe Ki como parâmetro).

## Funcionamento da Cifragem de Feistel

1. **Input**: bloco de dados - plaintext, que será dividido em duas metades L e R.
2. Para cada rodada:

- $L_i$ = $R_{i-1}$
- $R_i$ = $L_{i-1}$ ⊕ $F(R_{i-1}, K_i)$

> Ou seja, o lado esquerdo recebe o lado direito da rodada anterior;
> E o lado direito recebe a operação XOR do Lado Esquerdo anterior + Resultado da Função F.
> A Função F tem a mesma estrutura geral, mas é parametrizada com um subchave $k_i$ a cada rodada.

<img src="https://p1-jj.byteimg.com/tos-cn-i-t2oaga2asx/gold-user-assets/2018/2/27/161d69ad479cbd3e~tplv-t2oaga2asx-jj-mark:3024:0:0:0:q75.awebp" width="450">

No código em C em questão temos, para criptografia:

```c
uint8_t feistel_encrypt(uint8_t plain_text, uint8_t round_keys[NUM_ROUNDS]) {
  uint8_t left_block = (plain_text >> 4) & 0X0F;
  uint8_t right_block = plain_text & 0X0F;

  for (int i=0; i < NUM_ROUNDS; i++) {
    uint8_t temp = right_block;
    right_block = left_block ^ f_function(right_block, round_keys[i]);
    left_block = temp;
  }

  return (left_block << 4) | right_block;
}
```

### Entrada do Algoritmo

A entrada é um bloco de tamanho fixo (ex: 8 bits, 64 bits) e uma chave principal. O bloco é dividido em duas metades, e a chave principal é expandida em subchaves para cada rodada.

### Rodadas

As rodadas repetem a mesma operação com subchaves diferentes. O número de rodadas depende da implementação; DES, por exemplo, usa 16.

### Função F

A função F é o coração da cifra. Ela é aplicada sobre metade do bloco (geralmente o lado direito) e uma subchave da rodada. Pode incluir operações como:

- Expansão
- XOR com subchave
- Substituição (via S-Boxes)
- Permutação

### Chaves

A chave mestre é dividida ou manipulada para gerar subchaves, uma para cada rodada. A segurança depende da qualidade dessas subchaves.

### XOR e o Princípio da Reversibilidade

<img src="https://www.electronicshub.org/wp-content/smush-webp/2015/07/exor-equivalent-circuit.jpg.webp" width="250">

- Opera de forma rápida e relativamente barata nas operações bit a bit.
- É reversível: A ⊕ B = C implica que A = B ⊕ C
- Essa propriedade é chamada de **reversibilidade de XOR**.
- Por exemplo, se tivermos $A ⊕ B = C$, então podemos recuperar A fazendo C ⊕ B.
- Na cifra de Feistel, isso permite reverter o processo de cifragem durante a decifragem.
- Suponha que $F(R, K) = 5$ e $L = 3$; então $R_n = L ⊕ F(R, K) = 3 ⊕ 5 = 6$.
- Na decifragem, temos $R_n e F(R, K)$, logo podemos recuperar $L$ como $6 ⊕ 5 = 3$.

## Decifragem

A decifragem é feita aplicando o mesmo algoritmo, mas com as subchaves em ordem inversa:

- Inverte-se a sequência de subchaves
- Aplica-se o mesmo esquema de troca e XOR
