#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

long int mdc(long int n1, long int n2)
{
    if (!n1)
    {
        return n2;
    }
    else if (!n2)
    {
        return n1;
    }
    if (n1 == n2)
    {
        return n1;
    }
    long int x = 0;
    if (n1 > n2)
    {
        long int q = n1 / n2;
        long int r = n1 - (n2 * q);

        if (r == 0)
        {
            return n2;
        }
        else
        {
            x = mdc(n2, r);
        }
    }
    else if (n1 < n2)
    {
        long int q = n2 / n1;
        long int r = n2 - (n1 * q);

        if (r == 0)
        {
            return n1;
        }

        x = mdc(n1, r);
    }
    return x;
}

long int funcGeradoraRho(long int n, long int x)
{
    return (((x * x) + 1) % n);
}

// Etapa 1 Metodo p de Pollard
long int rhoPollard(int N)
{
    long int x0 = 2;
    long int x1 = funcGeradoraRho(N, x0);
    long int temp;
    long int mdcP = mdc(labs(x0 - x1), N);
    int p;

    x0 = x1;
    int pos = 1;
    printf("\nx%d = %ld e o mdc(|x%d - x%d|, %d) = %ld\n", pos, x0, pos, pos - 1, N, mdcP);
    while (mdcP == 1)
    {
        p = pos;
        temp = x0;
        for (int y = p; y < 2 * p; y++)
        {
            x1 = funcGeradoraRho(N, x0);
            x0 = x1;
            pos++;
        }
        mdcP = mdc(labs(x0 - temp), N); // lembrar que esse e o novo x0
        printf("\nx%d = %ld e o mdc(|x%d - x%d|, %d) = %ld\n", pos, x0, pos, pos - p, N, mdcP);
    }
    printf("\n\nO fator não trivial encontrado foi %ld\n", mdcP);
    printf("---------------------------------------------------------------\n\n\n");
    return mdcP;
}

// metodo para achar o inverso modular
long int mdcEstendido(long int a, long int b, long int *x, long int *y)
{
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    long int x1, y1;
    long int mdc = mdcEstendido(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return mdc;
}

long int inversoModular(long int E, long int Z)
{
    long int x, y;
    long int mdc = mdcEstendido(E, Z, &x, &y);

    if (mdc != 1)
    {
        return 0;
    }

    long int D = (x % Z + Z) % Z;
    return D;
}

// Etapa 2 Geracao das chaves RSA
long int *RSA(long int p, long int q)
{
    long int n = p * q;
    long int z = (p - 1) * (q - 1);

    long int E = 1;

    do
    {
        E++;
    } while (mdc(E, z) != 1);

    long int D = inversoModular(E, z);
    printf("n = %ld\nE = %ld\nz = %ld\nD = %ld", n, E, z, D);

    long int *resultado = (long int *)malloc(3 * sizeof(long int));
    resultado[0] = n;
    resultado[1] = E;
    resultado[2] = D;
    return resultado; // retorna um vetor com {n,E,D}
}

long int letraParaNumero(char c)
{
    if (c == ' ')
    {
        return 0;
    }
    if (c >= 'a' && c <= 'z')
    {
        c -= 'a' - 'A';
    }
    if (c >= 'A' && c <= 'Z')
    {
        return 11 + (c - 'A');
    }
    return 0; // se for outro caracter ele será ignorado
}

char numeroParaLetra(long int num)
{
    if (num == 0)
    {
        return ' ';
    }
    if (num >= 11 && num <= 36)
    {
        return 'A' + (num - 11);
    }
    return '?'; // Retorna '?' para números inválidos
}

// necessaria para o teorema de fernet
int ehPrimo(long int n)
{
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;

    for (long int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    }
    return 1;
}

// necessario para o teorema de euler
long int funcaoFi(long int n)
{
    long int resultado = n;

    for (long int p = 2; p * p <= n; p++)
    {
        if (n % p == 0)
        {
            while (n % p == 0)
            {
                // Remove todas as ocorrencias do fator primo
                n = n / p;
            }
            resultado -= resultado / p;
        }
    }

    if (n > 1)
    {
        resultado -= resultado / n;
    }

    return resultado;
}

// funcao para calcular o C codificado
// ou para decodificar o C através do mod
long int potenciaModular(long int base, long int exp, long int mod)
{
    long int expAntigo = exp;

    if (ehPrimo(mod) && base % mod != 0 && exp >= mod - 1)
    {
        printf("\nTeorema de fermat será utilizado na resolução da exponenciação modular:\n");
        // Reduz o expoente usando o Teorema de Fermat
        exp = exp % (mod - 1);
        printf("Expoente reduzido de %ld para: %ld\n\n", expAntigo, exp);
    }
    else if (mdc(base, mod) == 1)
    {
        printf("\nTeorema de euler será utilizado na resolução da exponenciação modular\n");
        // Teorema de euler: Se mdc(a,n) = 1, então a^totiente(n) ≡ 1 mod n
        // Logo: a^k ≡ [a^(k mod totiente(n))] mod n
        long int phi = funcaoFi(mod);
        exp = exp % phi;
        printf("totiente(%ld) = %ld, expoente reduzido de %ld para: %ld\n\n", mod, phi, expAntigo, exp);
    }
    else
    {
        printf("\nTeorema da divisão euclidiana será utilizado na resolução da exponenciação modular\n\n");
    }
    long int resultado = 1;
    base = base % mod;

    while (exp > 0)
    {
        printf("%ld^%ld * %ld mod %ld = ", base, exp, resultado, mod);
        // Se exp e impar, multiplica base com resultado
        if (exp % 2 == 1)
        {
            resultado = (resultado * base) % mod;
        }

        // exp deve ser par agora
        exp = exp / 2;
        base = (base * base) % mod;
        printf("%ld^%ld * %ld mod %ld\n", base, exp, resultado, mod);
    }

    return resultado;
}

char *codificar(long int n, long int E, char *mensagem)
{
    long int codificado[100];
    int i = 0;
    while (mensagem[i] != '\0')
    {
        printf("%c", mensagem[i]);
        long int c = letraParaNumero(mensagem[i]);
        c = potenciaModular(c, E, n);

        codificado[i] = c;
        printf("\nA letra %c foi convertida no valor %ld\n", mensagem[i], codificado[i]);
        printf("---------------------------------------------------------------\n\n\n");
        i++;
    }
    char *resultado = (char *)malloc(i * 20 * sizeof(char));
    resultado[0] = '\0';

    for (int j = 0; j < i; j++)
    {
        char temp[20];
        if (j == 0)
        {
            sprintf(temp, "%ld", codificado[j]); // Primeiro numero sem hifen
        }
        else
        {
            sprintf(temp, "-%ld", codificado[j]); // Demais com hifen antes
        }
        strcat(resultado, temp);
    }

    return resultado;
}

char *decodificar(long int n, long int D, char *mensagemCodificada)
{
    char *copia = (char *)malloc(strlen(mensagemCodificada) + 1);
    strcpy(copia, mensagemCodificada);

    char *resultado = (char *)malloc(100 * sizeof(char));
    resultado[0] = '\0';

    char *token = strtok(copia, "-");
    while (token != NULL)
    {
        long int numero = atol(token); // Converte string para número
        long int decodificado = potenciaModular(numero, D, n);
        char letra = numeroParaLetra(decodificado);

        // Adiciona letra ao resultado
        char temp[2] = {letra, '\0'};
        strcat(resultado, temp); // Lida automaticamente com os \0

        token = strtok(NULL, "-");

        printf("\nO número %ld foi convertido na letra %c\n\n", numero, temp[0]);
        printf("---------------------------------------------------------------\n\n\n");
    }

    free(copia);
    return resultado;
}

int main()
{

    printf("Alunos\nLuis Felipe Parreira Cunha - 241011401\nJoao Pedro Lopes da Cruz - 241011170\n\n");

    // Etapa 1
    printf("Para o método de Pollard vamos definir inteiros e compostos distintos N1, N2 (para maior eficiência defina N1 e N2 com fatores primos diferentes)\n");

    int n1 = 0;
    int n2 = 0;

    while (!n1)
    {
        printf("\nDetermine o N1:\n");
        scanf("%d", &n1);
        if (n1 > 9999 || n1 < 100)
        {
            printf("Escolha valores entre 100 e 9999");
            n1 = 0;
        }
        else if (ehPrimo(n1))
        {
            printf("Escolha um número não primo");
            n1 = 0;
        }
    }
    while (!n2)
    {
        printf("\nDetermine o N2:\n");
        scanf("%d", &n2);
        if (n2 > 9999 || n2 < 100)
        {
            printf("Escolha valores entre 100 e 9999");
            n2 = 0;
        }
        else if (ehPrimo(n2))
        {
            printf("Escolha um número não primo");
            n2 = 0;
        }
    }

    printf("\n\nFazendo o método p de Pollard em N1:\n\n");

    long int p = rhoPollard(n1);

    printf("\nFazendo o método p de Pollard em N2:\n\n");

    long int q = rhoPollard(n2);

    // Etapa 2

    printf("\nAssim, para rsa temos:\np=%ld\nq=%ld\n\n", p, q);

    int pPrimo = ehPrimo(p);
    int qPrimo = ehPrimo(q);

    if (!pPrimo || !qPrimo)
    {
        printf("O adequado seria que as chaves fossem ambas números primos, mas continuaremos a resolução mesmo assim ");
        if (!pPrimo)
        {
            printf("(p não é primo)");
        }
        if (!qPrimo)
        {
            printf("(q não é primo)");
        }
        printf(")\n\n");
    }

    long int *chaves = RSA(p, q); //{n,E,D}

    if (chaves[0] > 10 && chaves[0] < 37)
    {
        printf("\n\nO n está no intervalo de 11 a 37 o qual nossas letras estão codificadas, o processo de decodificação não funcionará");
    }

    printf("\n\nChave pública: (%ld,%ld)\n", chaves[0], chaves[1]);
    printf("Chave privada: (%ld,%ld)\n\n", chaves[0], chaves[2]);

    // Etapa 3
    char mensagem[100];
    int c;
    printf("Determine a mensagem a ser codificada (utilize apenas maiúsculas):\n");
    while ((c = getchar()) != '\n' && c != EOF);
    scanf("%99[^\n]", mensagem);
    printf("\n\n");

    char *mensagemCodificada = codificar(chaves[0], chaves[1], mensagem);

    printf("\n\nA mensagem codificada é\n%s\n\n", mensagemCodificada);

    char *continuar[10];
    printf("Aperte ENTER para decodificar a mensagem");
    getchar();
    getchar();

    printf("\n\nAgora a mensagem será decodificada:\n");

    char *mensagemDecodificada = decodificar(chaves[0], chaves[2], mensagemCodificada);

    printf("\n\nA mensagem decodificada é\n%s\n\n", mensagemDecodificada);

    if (strcmp(mensagem, mensagemDecodificada) == 0)
    {
        printf("A mensagem foi codificada e decodificada corretamente!\n\nmensagem: %s\ncodificada: %sdecodificada: %s\n", mensagem, mensagemCodificada, mensagemDecodificada);
    }
    else
    {
        printf("Houve falha na decodificação da mensagem\nmensagem: %s\ndecodificada: %s", mensagem, mensagemDecodificada);
    }

    int novo = 0;
    char *novaMensagemDecodificada;
    do
    {
        printf("Gostaria de decodificar outra mensagem?\n\n1.sim\n0.nao\n");
        scanf("%d", &novo);
        if (novo)
        {
            printf("As mesamas chaves anteriores serão usadas!\n\n");
            printf("Qual mensagem vc gostaria de decodificar?\n(formato: bloco1-bloco2-...-blocox) sendo cada bloco um caracter\n");
            char novaMensagem[100];
            scanf("%s", novaMensagem);

            printf("\n\nAgora a mensagem será decodificada:");

            novaMensagemDecodificada = decodificar(chaves[0], chaves[2], novaMensagem);

            printf("\n\nA mensagem decodificada é\n%s\n\n", novaMensagemDecodificada);

            novo = 0;
        }
    } while (novo);

    return 0;
}