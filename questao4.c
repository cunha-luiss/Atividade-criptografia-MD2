#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#define CP_UTF8 65001
#endif


// Questões feitas por Luís Felipe Parreira Cunha e João Pedro Lopes da Cruz


int mdccmPassos(int a, int b) {
    int resto;
    while (b != 0) {
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);
        a = b;
        b = resto;
    }
    return a;
}

int inverseModular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;

    if (a % m == 0) return -1;

    while (m != 0) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;
    printf("\nInverso de %d mod %d é %d.\n\n", A, B, x1);
    return x1;
}

int powMod(int base, int exp, int mod) {
    long long res = 1;
    long long b = base % mod;
    while (exp > 0) {
        if (exp & 1)
            res = (res * b) % mod;
        b = (b * b) % mod;
        exp >>= 1;
    }
    return (int)res;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    printf("Alunos\nLuis Felipe Parreira Cunha - 241011401\nJoao Pedro Lopes da Cruz - 241011170\n\n");

    int H, G, Zn, x, n1;
    printf("Insira H: ");
    scanf("%d", &H);
    printf("Insira G: ");
    scanf("%d", &G);
    printf("Insira Zn: ");
    scanf("%d", &Zn);
    printf("Insira x: ");
    scanf("%d", &x);
    printf("Insira n1: ");
    scanf("%d", &n1);

    int inverse = inverseModular(G, Zn);
    int a = (H * inverse) % Zn;
    printf("Divisão modular: %d * %d mod %d = %d\n", H, inverse, Zn, a);

    int resultado = powMod(a, x, n1);
    printf("Valor final: %d\n", resultado);

    return 0;
}

/*
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
*/