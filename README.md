# Criptografia Clássica

Este repositório contém implementações de **algoritmos clássicos de criptografia simétrica** , escritas em **linguagem C** , com fins **educacionais** . O objetivo é explorar os fundamentos da criptografia através de implementações práticas e didáticas, reforçando conceitos de segurança da informação.Algoritmos Clássicos de Criptografia Simétrica

## Estrutura do Repositório

Os algoritmos estão organizados em **pastas e subpastas** temáticas:

### 1. [Algoritmos Clássicos de Criptografia Simétrica](algoritmos-classicos)

- [1.1. Cifra de César](algoritmos-classicos/cifra-de-cesar)
- [1.2. Cifra de Vigenère](algoritmos-classicos/cifra-de-vigenere)
- [1.3. Cifra de Playfair](algoritmos-classicos/cifra-de-playfair)

### 2. [Cifras de Bloco](cifra-de-blocos/README.md)

- [2.1. Simple S-box](cifra-de-blocos/simple-s-box)
- [2.2. Cifra de Feistel](cifra-de-blocos/feistel)

## Objetivo

Explorar algoritmos clássicos de **criptografia simétrica** por meio de **implementações em linguagem C** , com foco em:

- Entendimento de como os algoritmos operam internamente
- Fortalecimento de conceitos fundamentais de segurança
- Visualização da lógica de cifragem/decifragem passo a passo

## Conceitos Fundamentais

### Criptografia

A criptografia é o estudo e aplicação de técnicas para **proteger informações** de acessos não autorizados. Ela transforma dados legíveis (texto claro) em dados ininteligíveis (texto cifrado), e vice-versa.

#### Chaves criptográficas

A **chave** é um elemento essencial na criptografia. Ela define como a informação será cifrada e decifrada.

- Em criptografia **simétrica**, a **mesma chave** é usada para criptografar e descriptografar os dados.
- Em criptografia **assimétrica**, são usadas **duas chaves diferentes**: uma **pública** (para cifrar) e uma **privada** (para decifrar).

> **Este repositório foca exclusivamente em criptografia simétrica.**

A criptografia simétrica pode ser representada matematicamente como:

$$
C = E(K, M)
$$

Onde:

- C: texto cifrado (ciphertext)
- E: função de criptografia
- K: chave
- M: mensagem original (plaintext)

### Obeservações

- Os conteúdos desse repositório são códigos dos algoritmos acompanhado de arquivos README, que detalha o funcionamento e os princípios teóricos dos algoritmos.
