#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *arquivoDeEntrada;
FILE *arquivos;
void lerArquivos(char *nomeArquivos, int N, char *cadaArquivo, int i)
{
    // printf("%s\n", &nomeArquivos[0]);
    char nomepasta[100] = "./arquivos/";
    strcat(nomepasta, &nomeArquivos[0]);
    arquivos = fopen(nomepasta, "r");
    if (arquivos == NULL)
    {
        printf("Arquivo nao encontrado!\n");
        return;
    }
    else
    {
        printf("leu arquivo: %s\n", nomeArquivos);
    }
}
void lerArquivoPrincipal()
{
    int N, i;

    char nomeArquivoDeEntrada[100] = "entrada.txt";

    if ((arquivoDeEntrada = fopen(nomeArquivoDeEntrada, "r")) == NULL)
    {
        printf("Arquivo nao encontrado!");
        return;
    }
    fscanf(arquivoDeEntrada, "%d", &N);

    char *linhas[N];
    char *cadaArquivo[N];

    for (i = 0; i < N; i++)
    {
        linhas[i] = malloc(sizeof(char) * 30);
        fscanf(arquivoDeEntrada, "%s", linhas[i]);
    }
    printf("\n==== Arquivo principal ===== \n");
    printf("Quantidade de arquivos a serem lidos = %d\n", N);
    for (i = 0; i < N; i++)
    {

        printf("%s\n", linhas[i]);
    }
    printf("\n==== Lendo cada arquivo dentro do arquivo principal ===== \n");
    char *testeArq[N];
    for (i = 0; i < N; i++)
    {
        cadaArquivo[i] = malloc(sizeof(char) * 800);
        lerArquivos(linhas[i], N, cadaArquivo[i], i);
        fgets(cadaArquivo[i], 799, arquivos);
    }
    printf("\n==== /////// ===== \n");
    for (i = 0; i < N; i++)
    {

        printf("\n%s\n", cadaArquivo[i]);
    }
}

int main()
{
    int escolha = -1;

    while (escolha != 0)
    {
        printf("\n==== MENU ======");
        printf("\n1) LER ARQUIVOS\n");
        printf("\n0) SAIR\n");
        printf("\nESCOLHA: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 0:
            break;
        case 1:
            lerArquivoPrincipal();
            fclose(arquivoDeEntrada);
            break;
        }
    }

    // fclose(arquivos);
    return 0;
}