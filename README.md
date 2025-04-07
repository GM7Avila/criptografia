# Criptografia Clássica

Este repositório contém implementações de algoritmos de **criptografia clássica** utilizando a linguagem **C**, com foco educacional. O objetivo é compreender como esses algoritmos funcionam internamente, fortalecendo conceitos de segurança da informação.

1. Cifra de César
2. CIfra de Vigenère

## Objetivo

Explorar algortimos clássicos de Criptografia Simétrica de forma prática utilizando a Linguagem C.

## Conceitos Fundamentais

### Criptografia

Criptografia é o estudo e prática de técnicas para **proteger informações** de acesso não autorizado, transformando dados legíveis (texto claro) em um formato ininteligível (texto cifrado), e vice-versa.

### Chaves criptográficas

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
