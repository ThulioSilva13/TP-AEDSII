#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NossaPaty.h"
#include "time.h"

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
    time_t startPatricia, endPatricia, startHash, endHash;

    char palavra[100];
    TipoArvoreApontador* arvore;
    //Criar uma variavel do tipo tabela hash
    for(int i = 0; i < 2; i++)
    {
        if(i==0)//faz o procedimento para a ARVORE PATRICIA
        {
            time(&startPatricia);
            InicializaArvorePatricia(arvore);
            //inserir texto na arvore 
            ResultadoPatricia(arvore);
            time(&endPatricia);
            double tempoPatricia = (endPatricia - startPatricia);
            printf("o tempo de execução da arvore PATRICIA foi: %d",tempoPatricia);
        
        }
        else if(i==1)
        {
            time(&startHash);
            //Inicializa tabela Hash
            //Inserir texto na tabela Hash
            //ResultadoHash
            time(&endHash);
            double tempoHash = (endHash - startHash);
            printf("O tempo de execução da tabela Hash foi: %d", tempoHash);
        }
    }
}
void lerArquivoPrincipal()
{
    int N;
    int i;
    
    char nomeArquivoDeEntrada[100] = "entrada.txt";

    if ((arquivoDeEntrada = fopen(nomeArquivoDeEntrada, "r")) == NULL)
    {
        printf("Arquivo nao encontrado!");
        return;
    }
    fscanf(arquivoDeEntrada, "%d", &N);

    char *linhas;
    char *cadaArquivo;

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
    char *testeArq;
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
void ResultadoPatricia(TipoArvoreApontador *arvore)//pode precisar de mais parâmetros aqui, arquivos por exemplo
{
    //ADICIONAR QUANTIDADE DE ARQUIVOS NA VARIÁVEL QUANTARQUIVOS 
    int quantArquivos;
    for(int i = 0; i < quantArquivos; i++){
        //CÓDIGO DA TÁSSIA QUE PEGA CADA PALAVRA DO ARQUIVO E SALVA NESSA VARIÁVEL PALAVRA
        char *palavra;
        for(int j = 0; j < strlen(palavra); j++){
            int contador = ContarPalavras(arvore, palavra);
            printf("a palavra: %s, apareceu %d vezes no documento %d", palavra, contador, i+1);
        }
    }
}

int main()
{
    //FAZER UMA CONDIÇÃO PARA SABER SE VAI SER PATRICIA OU HASH
    TipoArvoreApontador *arvorePatricia;
    int escolha = -1;
    int escolhaEstrutura = -1; 
    InicializaArvorePatricia(arvorePatricia);
    
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
    //double time_taken = (endPatricia - startPatricia);
    //printf("tempo gasto pela Patricia foi %d", time_taken);
    return 0;
}