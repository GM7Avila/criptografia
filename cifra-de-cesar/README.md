# Cifra de César

A Cifra de César é uma técnica de criptografia por substituição simples, na qual cada letra do texto orginal (texto claro) é substituída por outra letra, deslocada um número fixo de posições no alfabeto. A cifra utiliza aritmética modular para "girar" o alfabeto. Em sua forma mais simples, considera-se apenas letras do alfabeto latino em caixa alta.

## Definição Matemática

Ela pode ser definida pela função matemática:

$$
E(x) = (x+k) mod 26
$$

Onde

- `x` é a posição da letra no alfabeto;
- `k` é o valor do deslocamento (chave);
- `E(x)` é a letra cifrada.

Para decifrar basta fazer a operação contrária: $D(x) = (x-k) mod 26$

### Exemplo

Considere o texto claro: `ATAQUE AO AMANHECER` e um deslocamento (chave) k = 3.

Aplicando a fórmula de cifragem:

E(x) = (x + k) mod 26

Convertendo cada letra para sua posição no alfabeto (A=0, B=1, ..., Z=25):

A → (0 + 3) mod 26 = 3 → D
T → (19 + 3) mod 26 = 22 → W
A → (0 + 3) mod 26 = 3 → D
Q → (16 + 3) mod 26 = 19 → T
U → (20 + 3) mod 26 = 23 → X
E → (4 + 3) mod 26 = 7 → H

(continua o processo para as demais letras)

Resultado final: `DWDTXH DR DPDQKHFHU`

## Executando o Algoritmo

Para compilar e executar a implementação da Cifra de César em C, siga os seguintes passos em um terminal Unix-like:

1. **Abra o terminal e navegue até o diretório onde está localizado o arquivo `cifracesar.c`.**
2. **Compile o código-fonte utilizando o compilador GCC: `gcc cifracesar.c -o cifracesar`**
3. **Execute o programa compilado: `./cifracesar`**

O programa solicitará ao usuário a entrada do texto claro e o valor do deslocamento (chave). Em seguida, exibirá o texto cifrado utilizando a Cifra de César com base no deslocamento informado.
