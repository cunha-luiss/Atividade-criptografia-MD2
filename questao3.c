#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *fatoracao(int n)
{
    int valor = n;
    int *resposta = (int *)calloc(30, sizeof(int));
    int ponteiroVago = 0;

    if (n == 1){
        resposta[0] = 1;
        resposta[1] = 1;
        return resposta;
    }

    for (int x = 2; x <= n; x++)
    {
        if (valor % x == 0)
        {
            resposta[ponteiroVago] = x;
            ponteiroVago++;
            resposta[ponteiroVago] = 1;

            valor = valor / x;
            while (valor % x == 0)
            {
                resposta[ponteiroVago] += 1;
                valor = valor / x;
            }
            ponteiroVago++;
        };
    };

    return resposta;
}
int funcaoTau(int *valores)
{
    int totalDivisores = 1;

    if (valores[0] == 1){
        return 1;
    }

    for (int w = 1; valores[w] != 0; w += 2)
    {
        totalDivisores *= valores[w] + 1;
    };
    return totalDivisores;
}

double funcaoSigma(int *valores)
{
    double somatorioDivisores = 1;

    // edge case do 0
    if (!valores[0])
    {
        return 0;
    }
    else if (valores[0] == 1){
        return 1;
    }
    for (int w = 0; valores[w] != 0; w += 2)
    {
        somatorioDivisores *= (pow(valores[w], valores[w + 1] + 1) - 1) / (valores[w] - 1);
    }
    return somatorioDivisores;
}

int main()
{
    printf("Alunos\nLuis Felipe Parreira Cunha - 241011401\nJoao Pedro Lopes da Cruz - 241011170\n\n");

    int valor;
    printf("Escolha um valor até 105 para calcular a razão de eficiência\n");
    scanf("%d", &valor);

    int *fatores = fatoracao(valor);
    int tau = funcaoTau(fatores);
    double sigma = funcaoSigma(fatores);

    printf("\nOs fatores do %d são\n", valor);
    for (int r = 0; fatores[r] != 0; r += 2)
    {
        printf("%d^%d", fatores[r], fatores[r + 1]);
        if (fatores[r + 2] != 0)
        {
            printf(" * ");
        };
    };
    printf("\n\nA quantidade de divisores é: %d", tau);
    printf("\nO somatório dos divisores é: %.0f\n", sigma);
    printf("\nAssim, a razão de eficiência é: %.2f", sigma / tau);

    free(fatores);
    return 0;
}