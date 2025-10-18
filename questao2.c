#include <stdio.h>

//Calcular o MMC entre os ciclos. Se for maior que 50, tchau

int mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mmc(int a, int b) {
    return a / mdc(a, b) * b;
}

int main() {
    printf("Alunos\nLuis Felipe Parreira Cunha - 241011401\nJoao Pedro Lopes da Cruz - 241011170\n\n");

    int N;
    printf("Digite o numero de chaves: ");
    scanf("%d", &N);
    int cycles[10];
    printf("Digite os ciclos: ");
    for (int i = 0; i < N; i++) {
        scanf("%d", &cycles[i]);
    }

    int result = cycles[0];
    for (int i = 1; i < N; i++) {
        result = mmc(result, cycles[i]);
    }

    if (result > 50) {
        printf("Não é possível em até 50 anos.\n");
    } else {
        printf("Primeiro ano de sincronizacao: %d\n", result);
    }

    return 0;
}