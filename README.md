## Atividade de Criptografia — Matemática Discreta 2

Trabalho prático em C com quatro questões envolvendo aritmética modular, fatoração, RSA, funções aritméticas e sincronização via MMC. Cada arquivo `questaoX.c` é um programa independente que solicita entradas pelo terminal e imprime um passo a passo dos cálculos realizados.

Autores: Luís Felipe Parreira Cunha (241011401) e João Pedro Lopes da Cruz (241011170)


## Estrutura do repositório

- `questao1.c`: Fatoração (Pollard Rho) de dois números compostos, geração de chaves RSA e codificação/decodificação de mensagens com explicação de cada passo (inclui uso de Fermat/Euler quando aplicável).
- `questao2.c`: Cálculo do primeiro ano de sincronização dado um conjunto de ciclos (MMC). Se o MMC > 50, informa que não é possível em até 50 anos.
- `questao3.c`: Fatoração prima de n, cálculo de τ(n) (número de divisores) e σ(n) (soma dos divisores), e a “razão de eficiência” σ(n)/τ(n), com impressão detalhada dos fatores.
- `questao4.c`: Divisão modular via inverso multiplicativo e exponenciação modular rápida. Calcula: a = H · G^{-1} (mod Z_n) e em seguida o valor final a^x (mod n1), exibindo os resultados.
- `LICENSE`: Licença do projeto.


## Pré-requisitos

- Windows com PowerShell (você está usando PowerShell 5.1)
- Um compilador C:
	- GCC (MinGW-w64) recomendado; ou
	- MSVC (Developer Command Prompt) — exemplos fornecidos com GCC.

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

## Dicas e validação

- Se o inverso modular não existir (mdc(G, Z_n) ≠ 1), o programa reporta que não há inverso e não há “divisão modular” válida.
- Em Q1 e Q3, quando aplicável, o código reduz expoentes usando Fermat/Euler e imprime as reduções para tornar os passos auditáveis.


## Licença

Este projeto está licenciado sob os termos do `MIT LICENSE`.

