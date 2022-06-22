#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// #include <math.h>
// #include "NossaPaty.h"
// #include "myHash.h"
// #define maxBits 36000
#include "novaHash.h"
#include "indiceInvertido.h"

FILE *arquivoDeEntrada;
FILE *arquivos;

TipoDicionario Tabela;
TipoItem itemH;
TipoPesos peso;
TipoApontador Apontador;

TipoListaEnc listaEnc;

void minusculo(char s1[], char s2[])
{
    int i = 0;
    while (s1[i] != '\0')
    {
        s2[i] = tolower(s1[i]);
        // strcpy(s2[i], tolower(s1[i]));
        i++;
    }
    s2[i] = '\0'; // caracteer que indica o fim da string
}
// int testaSeEhNulo(char **cadaFrase, int N){
//     int i;
//     for (i = 0; i < N; i++)
//     {
//         if (cadaFrase[i] == NULL)
//         {
//             printf("\n ======= Atencao!!! =======");
//             printf("\nPrecisa ler os arquivos primeiros (DIGITE 1)\n");
//             return 0;
//         }
//     }
// }


void lerArquivosDentroDoArqPrincipal(char *nomeArquivos, char *cadaArquivo)
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
}
int lerArquivoPrincipal()
{
    int N, i;

    char nomeArquivoDeEntrada[100] = "entrada.txt";

    if ((arquivoDeEntrada = fopen(nomeArquivoDeEntrada, "r")) == NULL)
    {
        printf("Arquivo nao encontrado!");
        return 0;
    }
    fscanf(arquivoDeEntrada, "%d", &N);

    return N;
}

char *lerArquivosFrases(int N)
{
    char *linhas;
    char *cadaArquivo;

    // ler cada linha do arquivo principal (entrada.txt)
    // ou seja, cada posição é o nome dos arquivos
    linhas = malloc(sizeof(char) * 30);
    fscanf(arquivoDeEntrada, "%s", linhas);

    // cada posicao é a linha(frase) dos arquivos lidos
    cadaArquivo = malloc(sizeof(char) * 900);
    lerArquivosDentroDoArqPrincipal(linhas, cadaArquivo);
    return fgets(cadaArquivo, 899, arquivos);
}

void InsereHashEIndice(char **cadaFrase, int N)
{
    int i;
    char *t;
    for (i = 0; i < N; i++)
    {
        // t -> cada palavra do arquivo
        int num_arquivo = i + 1;
        t = strtok(cadaFrase[i], " ");
        while (t != NULL)
        {

            int tamanhoPalavra = strlen(t);
            char t_minusculo[tamanhoPalavra];
            minusculo(t, t_minusculo);
            printf("\n===========\n");
            printf("%s ", t);
            printf("%s\n", t_minusculo);
            GeraPesos(peso);

            strcpy(itemH.Chave, t_minusculo);
            // item.numArquivoHash = i + 1;
            VerificaInsere(itemH, peso, Tabela, num_arquivo);
            printf("\n-----------\n");
            // printf("\nsomafinal: %Lf", (long double)soma);
            t = strtok(NULL, " ");
        }
    }
}
void ImprimeFrasesArquivos(char **cadaFrase, int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        printf("%s\n", cadaFrase[i]);
    }
}
int main()
{
    InicializaDicionario(Tabela);
    FLVazia(&listaEnc);

    int escolha = -1;
    int i;

    int N = 0;
    char **cadaFrase;
    N = lerArquivoPrincipal();

    cadaFrase = (char** )malloc(sizeof(char) * N);

    while (escolha != 0)
    {
        printf("\n==== MENU ======\n");
        printf("\n1) LER ARQUIVOS\n");
        printf("\n2) PRINTA FRASES_ARQUIVOS\n");
        printf("\n3) INSERE TABELA HASH E INDICE\n");
        printf("\n4) IMPRIME TABELA\n");
        printf("\n5) IMPRIME INDICE\n");
        printf("\n0) SAIR\n");
        printf("\nESCOLHA: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
            case 0:
                break;
            case 1:
                lerArquivoPrincipal();
                for (i = 0; i < N; i++)
                {
                    cadaFrase[i] = lerArquivosFrases(N);
                }
                printf("Arquivos lidos com sucesso!");
                fclose(arquivoDeEntrada);
                break;
            case 2:
                ImprimeFrasesArquivos(cadaFrase, N);
                break;
            case 3:
                InsereHashEIndice(cadaFrase, N);
                break;
            case 4:
                ImprimeTabela(Tabela);
                break;
            case 5:
                ImprimeEnc(listaEnc);
                break;
        }
    }

    fclose(arquivos);
    return 0;
}