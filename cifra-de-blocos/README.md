# Cifras de Blocos

Cifras de bloco são algoritmos de criptografia simétrica que operam sobre blocos de dados de tamanho fixo, tipicamente 64 ou 128 bits. Cada bloco é transformado por meio de operações que envolvem substituição, permutação e mistura com uma chave secreta. Este modelo de cifra é amplamente empregado em sistemas de segurança da informação, incluindo padrões como AES (Advanced Encryption Standard) e DES (Data Encryption Standard).

## Princípios Fundamentais

As cifras de bloco seguem os princípios estabelecidos por Claude Shannon: **difusão** e **confusão**.

- **Difusão**: Um pequeno número de bits modificados no texto claro deve provocar alterações significativas no texto cifrado. Isso é geralmente implementado por operações de permutação ou transposição.
- **Confusão**: A relação entre o texto cifrado e a chave deve ser o mais complexa possível, dificultando a dedução da chave mesmo com conhecimento parcial da entrada ou da saída. A confusão é frequentemente obtida com funções de substituição não lineares.

## Funcionamento

Uma cifra de bloco normalmente utiliza uma estrutura iterativa, com múltiplas rodadas de operações básicas:

1. Divisão do texto claro em blocos.
2. Aplicação de substituições e permutações.
3. Mistura com a chave (tipicamente via XOR).
4. Repetição em rodadas subsequentes.

A saída de cada rodada serve como entrada para a próxima. Após a última rodada, o bloco resultante é o texto cifrado.

## Diferença em relação às Cifras de Fluxo

| Característica       | Cifra de Bloco               | Cifra de Fluxo                 |
| -------------------- | ---------------------------- | ------------------------------ |
| Unidade de operação  | Bloco de bits (ex: 128 bits) | Bit a bit ou byte a byte       |
| Adequação            | Dados em repouso             | Dados em transmissão contínua  |
| Repetição de padrões | Requer modos de operação     | Menor risco de padrão repetido |
| Exemplos             | AES, DES, Blowfish           | RC4, ChaCha20                  |

## S-box (Substitution Box)

A S-box é um componente essencial para prover confusão. Trata-se de uma função de substituição não linear que transforma um conjunto fixo de bits de entrada em outro conjunto de bits de saída.

### Características de uma S-box segura

- **Não linearidade**: Minimiza a correlação entre entrada e saída.
- **Avalanche**: Alterações mínimas na entrada provocam mudanças significativas na saída.
- **Balanceamento**: Saídas uniformemente distribuídas.
- **Resistência à análise diferencial**: Pequenas diferenças em entradas próximas não devem produzir diferenças previsíveis nas saídas.

<img src="https://morf.lv/images//blowfish/03fig01.jpg" alt="simple-s-box" width="400">

### Vulnerabilidades

- **Projetos fracos**: S-boxes mal construídas permitem ataques como análise diferencial ou linear.
- **Backdoors criptográficos**: Possibilidade de inserir mapeamentos previsíveis de forma intencional.
- **Falta de aleatoriedade**: S-boxes fixas e públicas podem ser alvos de otimizações por atacantes.

## Modos de Operação

Cifras de bloco por si só não garantem segurança para textos maiores que o tamanho do bloco. Por isso, são utilizados modos de operação:

- **ECB (Electronic Codebook)**: Cada bloco é cifrado de forma independente. Inseguro para dados repetitivos.
- **CBC (Cipher Block Chaining)**: Cada bloco é cifrado em função do bloco anterior.
- **CFB, OFB, CTR**: Transformam a cifra de bloco em cifra de fluxo.

## Exemplos de Cifras de Bloco

- **AES** (Rijndael): 128, 192 ou 256 bits de chave.
- **DES**: Considerado inseguro devido ao tamanho da chave (56 bits).
- **Triple DES (3DES)**: Três aplicações de DES com chaves diferentes.
- **Blowfish, Twofish, Serpent**: Alternativas robustas em diversos contextos.

## Conclusão

As cifras de bloco são fundamentais para a segurança moderna em criptografia simétrica. Quando corretamente implementadas, especialmente com S-boxes robustas e modos de operação adequados, fornecem confidencialidade eficaz contra ataques estatísticos e estruturais.
