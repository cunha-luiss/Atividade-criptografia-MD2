## Atividade de Criptografia — Matemática Discreta 2

Trabalho prático em C com quatro questões envolvendo aritmética modular, fatoração, RSA, funções aritméticas e sincronização via MMC. Cada arquivo `questaoX.c` é um programa independente que solicita entradas pelo terminal e imprime um passo a passo dos cálculos realizados.

Autores: Luís Felipe Parreira Cunha (241011401) e João Pedro Lopes da Cruz (241011170)


## Estrutura do repositório

- `questao1.c`: Fatoração (Pollard Rho) de dois números compostos, geração de chaves RSA e codificação/decodificação de mensagens com explicação de cada passo (inclui uso de Fermat/Euler quando aplicável).
- `questao2.c`: Cálculo do primeiro ano de sincronização dado um conjunto de ciclos (MMC). Se o MMC > 50, informa que não é possível em até 50 anos.
- `questao3.c`: Fatoração prima de n, cálculo de τ(n) (número de divisores) e σ(n) (soma dos divisores), e a “razão de eficiência” σ(n)/τ(n), com impressão detalhada dos fatores.
- `questao4.c`: Divisão modular via inverso multiplicativo e exponenciação modular rápida. Calcula: a = H · G^{-1} (mod Z_n) e em seguida o valor final a^x (mod n1), exibindo os resultados.
- `LICENSE`: Licença do projeto.

## Detalhes de cada questão

### Questão 1 — Pollard Rho + RSA
- Solicita dois inteiros compostos N1 e N2 (100–9999) e aplica o método p de Pollard para obter um fator não trivial de cada um, resultando em p e q.
- Gera chaves RSA (n, E) e (n, D), imprime n, E, φ(n) (como z) e D, além das chaves.
- Codifica uma mensagem (alfabeto mapeado em números 11–36, espaço = 0) e depois decodifica, exibindo cada etapa da exponenciação modular. Há opção de decodificar novas mensagens com as mesmas chaves.

### Questão 2 — Sincronização por MMC
- Lê N e, em seguida, N ciclos inteiros.
- Calcula o MMC acumulado. Se o MMC for maior que 50, imprime “Não é possível em até 50 anos.”; caso contrário, imprime o primeiro ano de sincronização.

### Questão 3 — τ(n), σ(n) e razão de eficiência
- Fatora n, imprime a fatoração prima no formato p^e.
- Calcula τ(n) = ∏(e+1) e σ(n) = ∏((p^{e+1}−1)/(p−1)).
- Exibe a razão σ(n)/τ(n) com arredondamento na apresentação.

### Questão 4 — Divisão e exponenciação modular
- Lê H, G, Z_n, x e n1.
- Calcula o inverso modular de G mod Z_n (se existir) usando o algoritmo estendido de Euclides e exibe o valor do inverso.
- Faz a “divisão modular”: a = (H · G^{-1}) mod Z_n.
- Calcula o “valor final” = a^x mod n1 usando exponenciação modular rápida.

## Questão 4 — Verdadeiro ou Falso
(V) O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número. Justificativa: O código na imagem é uma implementação direta do Algoritmo de Euclides Estendido. Este algoritmo é usado para encontrar $x$ e $y$ na equação de Bézout $ax + my = \text{mdc}(a, m)$. Se $\text{mdc}(a, m) = 1$, então $ax \equiv 1 \pmod{m}$, e o valor $x$ (representado por x1 no código) é o inverso modular de $a$ módulo $m$.

(F) Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn. Justificativa: O inverso modular de $G$ em $Z_n$ (ou seja, $G^{-1} \pmod{Z_n}$) existe apenas se $G$ e $Z_n$ forem primos entre si, ou seja, $\text{mdc}(G, Z_n) = 1$. Se o $\text{mdc}$ for diferente de 1, o inverso não existe e a divisão modular não é definida.

(V) A operação (H * inverso) % Zn representa a divisão modular de H por G. Justificativa: A "divisão" no contexto da aritmética modular não é uma operação direta. Dividir $H$ por $G$ módulo $Z_n$ é, por definição, equivalente a multiplicar $H$ pelo inverso modular de $G$ módulo $Z_n$. Portanto, $(H \times G^{-1}) \pmod{Z_n}$ é a representação correta da divisão modular $H \div G \pmod{Z_n}$.

(V) Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de a^x mod n1. Justificativa: A própria descrição da questão afirma que o código "...aplica o Pequeno Teorema de Fermat ou o Teorema de Euler, conforme a natureza de n1...". O Pequeno Teorema de Fermat é o caso especial do Teorema de Euler aplicado quando o módulo ($n_1$) é um número primo. Ele permite simplificar o expoente $x$ calculando $x \pmod{n_1 - 1}$.

(F) A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas sem otimização. Justificativa: Embora a função powMod não seja mostrada, o cálculo de $a^x \pmod{n_1}$ para expoentes grandes (comuns em criptografia e teoria dos números) é computacionalmente inviável e propenso a overflow se feito por multiplicações diretas ($a \times a \times \dots \times a$). O padrão para essa operação é usar um algoritmo otimizado, como a exponenciação por quadratura (ou "método binário"), que é muito eficiente.

(V) Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0. Justificativa: O código na imagem contém exatamente essa lógica. A variável m0 armazena o módulo original. Ao final, as linhas if (x1 < 0) e x1 += m0; garantem que, se o Algoritmo de Euclides Estendido encontrar um inverso negativo, ele será convertido para seu representante positivo equivalente dentro do módulo.

(V) O cálculo de fi(n1) (função totiente de Euler) é utilizado apenas quando n1 não é primo. Justificativa: O Pequeno Teorema de Fermat (para $n_1$ primo) afirma que $a^{n_1-1} \equiv 1 \pmod{n_1}$. O Teorema de Euler (para $n_1$ composto) afirma que $a^{\phi(n_1)} \equiv 1 \pmod{n_1}$. Note que, se $n_1$ é primo, $\phi(n_1) = n_1 - 1$. Assim, o Teorema de Fermat é um caso particular do Teorema de Euler. O código escolhe a abordagem mais simples: se $n_1$ é primo, ele usa $(n_1 - 1)$; se $n_1$ não é primo, ele deve calcular o valor mais complexo $\phi(n_1)$ (a função totiente de Euler).

## Questão 4 — Exemplo dado

- Parâmetros
	- H = 7
	- G = 3
	- Z_n = 11
	- x = 10
	- n1 = 13

- Saída do programa:

```
Inverso de 3 mod 11 é 4.

Divisão modular: 7 * 4 mod 11 = 6
Valor final: 4
```


## Licença

Este projeto está licenciado sob os termos do `MIT LICENSE`.

