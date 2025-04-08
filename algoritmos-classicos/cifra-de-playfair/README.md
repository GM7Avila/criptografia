# Cifra de Playfair

A Cifra de Playfair é uma cifra de substituição digráfica (baseada em pares de letras), desenvolvida no século XIX. Ao invés de substituir letras individuais, ela substitui pares de letras (digramas), tornando-a mais resistente à análise de frequência simples.

A cifra utiliza uma matriz 5x5 construída a partir de uma palavra-chave (key), onde letras repetidas são removidas e a letra J é geralmente tratada como equivalente a I.

## Algoritmo de Criptografia

1. Geração da Matriz 5x5:

- A matriz é preenchida com os caracteres da chave (sem repetições).
- Depois, as demais letras do alfabeto (exceto J) completam a matriz.

2. Preparação do Texto

- O texto é convertido para letras maiúsculas.
- Letras J são substituídas por I.
- Se dois caracteres idênticos aparecerem em um par, o segundo é substituído por X.
- Se o número de letras for ímpar, um X é adicionado ao final.

3. Criptografia: Para cada par de letras:

- Se estiverem na mesma linha, substitua cada letra pela letra à sua direita (com wrap-around).
- Se estiverem na mesma coluna, substitua cada letra pela letra abaixo dela (com wrap-around).
- Caso contrário (formam um retângulo), cada letra é substituída pela letra na mesma linha e coluna da outra.

## Exemplo

Chave: `MONARCHY`
Texto claro: `BALLOON`

- Após a preparação do texto: BALXLOON
- Matriz gerada (sem a letra J):

```
M O N A R
C H Y B D
E F G I K
L P Q S T
U V W X Z
```

- Resultado: `IBSUPMNA`
