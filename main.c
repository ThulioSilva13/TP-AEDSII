#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paty.h"

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
    // else
    // {
    //     char palavra[100];
    //     TipoArvore arvore;
    //     int *compara;
    //     InicializarPat(&arvore);
    //     while(feof(arquivos))
    //     {
    //         strcpy(palavra, fgetc(arquivos));
    //         InserePat(palavra, &arvore, compara);
    //         printf("leu arquivo: %s\n", nomeArquivos);
    //     }
    // }
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
    char *t;
    int tamanhoString = strlen(cadaArquivo[0]);
    int count = 0;
    printf("%d ", tamanhoString);
    t = strtok(cadaArquivo[0], " ");

    while ( t != NULL )
    {
        
        printf("%s\n", t);
        t = strtok(NULL, " ");
        count++;
    }
    
}

int main()
{
    TipoArvoreApontador *arvorePatricia;
    int escolha = -1;
    InicializaArvorePatricia(&arvorePatricia);

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