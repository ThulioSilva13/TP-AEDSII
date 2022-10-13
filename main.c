#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "NossaPaty.h"
#include "novaHash.h"
#include <time.h>

FILE *arquivoDeEntrada;
FILE *arquivos;

TipoDicionario Tabela;
TipoItem itemHash;
TipoPesos peso;
TipoApontador Apontador;

// TipoListaEnc listaEnc;
// TipoListaQntd listaQnd;

TipoArvoreApontador arvore;
ListaIndicePat listaPat;

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
char *TirarPontuacao(char *t_minusculo)
{
    char *replace = "";
    int i = 0, count = 0;
    while (t_minusculo[i])
    {
        if (ispunct(t_minusculo[i]))
            t_minusculo[i] = *replace;
        i++;
    }
    return t_minusculo;
}
void InsereHashEIndice(char **cadaFrase, int N)
{
    clock_t tempoInsereHash = clock();
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
            char palavraSemPontuacao[tamanhoPalavra];
            minusculo(t, t_minusculo);
            strcpy(palavraSemPontuacao, TirarPontuacao(t_minusculo));

            GeraPesos(peso);
            VerificaInsere(num_arquivo, palavraSemPontuacao, peso, Tabela);

            t = strtok(NULL, " ");
        }
    }
    tempoInsereHash = clock() - tempoInsereHash;
    printf("Tempo de execucao para inserir na Hash: %lf milisegundos",((double)tempoInsereHash)/((CLOCKS_PER_SEC/1000)));
}
void ImprimePatriciaMenu(TipoArvoreApontador *arvore){
    clock_t tempoLePatricia = clock();
    ImprimePatricia(*arvore);
    tempoLePatricia = clock() - tempoLePatricia;
    printf("Tempo de execucao para ler a arvore Patricia: %lf milisegundos",((double)tempoLePatricia)/((CLOCKS_PER_SEC/1000)));
}

void ImprimeTabelaMenu(TipoDicionario *Tabela){
    clock_t tempoImprimeTabela = clock();
    ImprimeTabela(*Tabela);
    tempoImprimeTabela = clock() - tempoImprimeTabela;
    printf("Tempo de execucao para imprimir a Hash: %lf milisegundos",((double)tempoImprimeTabela)/((CLOCKS_PER_SEC/1000)));
}
void ImprimeFrasesArquivos(char **cadaFrase, int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        printf("%s\n", cadaFrase[i]);
    }
}

void InserePatriciaMenu(char **cadaFrase, int N, TipoArvoreApontador *arvore)
{
    clock_t tempoInserePatricia = clock();
    int i;
    char *t;  
    TipoArvoreApontador *aux = arvore;

    for (i = 0; i < N; i++)
    {
        // t -> cada palavra do arquivo
        int num_arquivo = i + 1;
        t = strtok(cadaFrase[i], " ");
        while (t != NULL)
        {
            int tamanhoPalavra = strlen(t);
            char t_minusculo[tamanhoPalavra];
            char palavraSemPontuacao[tamanhoPalavra];

            minusculo(t, t_minusculo);
            strcpy(palavraSemPontuacao, TirarPontuacao(t_minusculo));

            *aux = InserePatricia(arvore, palavraSemPontuacao, num_arquivo);

            t = strtok(NULL, " ");
        }
    }
    tempoInserePatricia = clock() - tempoInserePatricia;
    printf("Inserido com sucesso!\n");
    printf("Tempo de execucao para inserir na arvore Patricia: %lf milisegundos",((double)tempoInserePatricia)/((CLOCKS_PER_SEC/1000)));
}

void MenuBusca(TipoArvoreApontador arvore){
    char buscaPalavra[Y];
    int opcaoPesquisa = 1;

    while (opcaoPesquisa == 1)
    {
        printf("---> BUSCAR PALAVRA: ");
        scanf("%s", buscaPalavra);
        BuscaPatiEIndice(arvore, buscaPalavra);

        printf("\n-> DIGITE 1 PARA CONTINUAR");
        printf("\n-> DIGITE 0 PARA SAIR DA BUSCA\n");
        printf("\n DESEJA CONTINUAR? ESCOLHA: ");
        scanf("%d", &opcaoPesquisa);
        printf("\n");
    }
}
void MenuBuscaHash(TipoDicionario table)
{
    char buscaPalavra[Y];
    int opcaoPesquisa = 1;
    
    while (opcaoPesquisa == 1)
    {
        printf("---> BUSCAR PALAVRA: ");
        scanf("%s", buscaPalavra);
        BuscaPesquisa(Tabela, buscaPalavra);

        printf("\n-> DIGITE 1 PARA CONTINUAR");
        printf("\n-> DIGITE 0 PARA SAIR DA BUSCA\n");
        printf("\n DESEJA CONTINUAR? ESCOLHA: ");
        scanf("%d", &opcaoPesquisa);
        printf("\n");
    }
}

int main()
{
    InicializaDicionario(Tabela);
    // FLVaziaQntd(&listaQnd);

    int escolha = -1;
    int i;
    
    int N = 0;
    char **cadaFrase;
    N = lerArquivoPrincipal();
    

    cadaFrase = (char **)malloc(sizeof(char*) * N);

    while (escolha != 0)
    {
        printf("\n==== MENU ======\n");

        printf("\n1) Receber o arquivo de entrada com os textos a serem indexados;\n");
        printf("\n2) PRINTA FRASES_ARQUIVOS\n");

        printf("\n====== HASH =======\n");

        printf("\n3) CONSTRUIR TABELA HASH E INDICE INVERTIDO\n");
        printf("\n4) IMPRIME TABELA\n");
        printf("\n5) BUSCAR PALAVRAS\n");

        printf("\n====== PATRICIA =======\n");
        printf("\n6) CONSTRUIR ARVORE PATRICIA E INDICE INVERTIDO\n");
        printf("\n7) IMPRIMIR A PARTIR DO INDICE\n");
        printf("\n8) BUSCAR PALAVRAS\n");

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
                printf("Arquivos lidos com sucesso!\n");
                fclose(arquivoDeEntrada);
                
                break;
            case 2:
                ImprimeFrasesArquivos(cadaFrase, N);
                break;
            case 3:
                InsereHashEIndice(cadaFrase, N);
                break;
            case 4:
                ImprimeTabelaMenu(&Tabela);
                break;
            case 5:
                MenuBuscaHash(Tabela);
                break;
            case 6:
                InserePatriciaMenu(cadaFrase, N, &arvore);
                break;
            case 7:
                ImprimePatriciaMenu(&arvore);
                break;
            case 8:
                MenuBusca(arvore);
                break;
        }
        
    }
    fclose(arquivos);

    return 0;
}