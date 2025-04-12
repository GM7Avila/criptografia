# Data Encryption Standard (DES)

O Data Encryption Standard (DES) é um algoritmo de criptografia simétrica amplamente estudado no campo da segurança da informação. Ele pertence à classe das cifras de blocos, nas quais os dados são processados em blocos fixos — no caso do DES, blocos de 64 bits — utilizando uma chave de 56 bits efetivos (com 8 bits adicionais de paridade). A principal característica desse tipo de cifra é que ela transforma um bloco de texto claro em um bloco de texto cifrado de mesmo tamanho, de maneira determinística, a partir de uma chave.

## Funcionamento Básico

A arquitetura do DES é baseada na estrutura Feistel, um modelo conceitual de cifragem que permite tanto a encriptação quanto a decriptação com algoritmos semelhantes, utilizando operações iterativas em várias rodadas.

<img src="https://marioseguridad.wordpress.com/wp-content/uploads/2012/09/algoritmo-des2.png">

No DES, essa estrutura é composta por 16 rodadas idênticas de processamento, onde o bloco de entrada é dividido em duas metades (esquerda e direita), sendo que apenas uma delas é transformada a cada rodada com o uso de uma função de confusão e difusão, combinada com a subchave da rodada. Ao final das rodadas, ocorre uma troca final das metades e uma permutação inversa, resultando no bloco cifrado.

### 1. Entrada

- **Texto claro**: bloco de 64 bits
- **Chave**: 64 bits (sendo 56 usados efetivamente)

### 2. Permutação Inicial (IP)

Reorganiza os bits do bloco de entrada segundo uma tabela pré-definida.

### 3. Geração de Subchaves

- Usa permutações PC-1 e PC-2
- Executa rotações à esquerda em blocos C e D
- Gera 16 subchaves de 48 bits

### 4. Rodadas Feistel (16 rodadas)

Para cada rodada:

- Expansão do lado direito (32 → 48 bits)
- XOR com subchave
- Substituição usando S-boxes (48 → 32 bits)
- Permutação (P)
- Troca entre lado esquerdo e direito

### 5. Permutação Final (IP⁻¹)

Aplica a permutação inversa à combinação final dos blocos.

## Segurança

- **Confusão**: obtida pelas S-boxes
- **Difusão**: promovida pelas permutações
- **Uso** de subchaves distintas em cada rodada

## Observações Técnicas e de Segurança

- **Segurança do DES**: Embora o DES tenha sido amplamente utilizado e estudado, o aumento do poder computacional e o avanço em técnicas de criptoanálise tornaram o DES atualmente considerado **inseguro** para muitas aplicações. A chave efetiva de 56 bits é suscetível a ataques de força bruta.
- **Triple DES (3DES)**: Para mitigar as vulnerabilidades do DES, foi desenvolvido o Triple DES, que aplica o algoritmo DES três vezes em cada bloco de dados. Essa técnica aumenta a complexidade e o tamanho efetivo da chave, proporcionando maior segurança, embora com impacto na performance.
- **RSA**: Em contraste com o DES e o Triple DES, o RSA é um algoritmo de criptografia de chave pública. O RSA se baseia na dificuldade de fatoração de grandes números primos e é utilizado para a troca segura de chaves e assinaturas digitais, sendo uma alternativa fundamental em sistemas de criptografia híbrida.
