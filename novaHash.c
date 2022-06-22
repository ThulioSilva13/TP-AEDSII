#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "novaHash.h"
#include "indiceInvertido.h"
TipoItemEnc itemEnc;
TipoListaEnc listaEnc;

void InicializaListaVazia(TipoLista *Lista)
{
    Lista->Primeiro = (TipoCelula *)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Proximo = NULL;
}

short Vazia(TipoLista Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem item, TipoLista *Lista, int num_arquivo)
{
    printf("Palavra a ser inserida: %s ", item.Chave);

    Lista->Ultimo->Proximo = (TipoCelula *)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Proximo;
    strcpy(Lista->Ultimo->ItemH.Chave, item.Chave);
    Lista->Ultimo->ItemH.qntd_repete = 1;

    //==== insere indice invertido =====
    strcpy(itemEnc.Chave,item.Chave);
    itemEnc.qntd_repete = 1;
    itemEnc.numArquivoIndice = num_arquivo;
    InsereEnc(itemEnc, &listaEnc, num_arquivo);
    printf("=> Palavra inserida!\n");
    Lista->Ultimo->Proximo = NULL;

}
/*
void GeraPesos(TipoPesos p)
{ int i;
  struct timeval semente;
  gettimeofday(&semente, NULL);
  srand((int)(semente.tv_sec + 1000000*semente.tv_usec));
  for (i = 0; i < n; i++)
     p[i] =  1+(int) (10000.0*rand()/(RAND_MAX+1.0));
}

TipoIndice h(TipoChave Chave, TipoPesos p)
{ int i;
  unsigned int Soma = 0;
  int comp = strlen(Chave);
  for (i = 0; i < comp; i++) Soma += (unsigned int)Chave[i] * p[i];
  return (Soma % M);
}
*/

void GeraPesos(TipoPesos peso)
{ /* Gera valores randomicos entre 1 e 10.000 */
    int i, j;
    struct timeval semente;
    /* Utilizar o tempo como semente para a funcao srand() */
    // gettimeofday(&semente, NULL);
    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
    for (i = 0; i < X; i++)
        for (j = 0; j < TAMALFABETO; j++)
            peso[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
}

TipoIndice h(TipoPalavra Chave, TipoPesos peso)
{
    int i;
    unsigned int Soma = 0;
    int comp = strlen(Chave);
    for (i = 0; i < comp; i++)
        Soma += peso[i][(unsigned int)Chave[i]];
    return (Soma % Y);
}

void InicializaDicionario(TipoDicionario dicionario)
{
    int i;
    for (i = 0; i < Y; i++)
        InicializaListaVazia(&dicionario[i]);
}

TipoApontador Pesquisa(TipoPalavra Chave, TipoPesos peso, TipoDicionario dicionario)
{ /* Obs.: TipoApontador de retorno aponta para o item anterior da lista */
    TipoIndice i;
    TipoApontador Apontador;
    i = h(Chave, peso);
    if (Vazia(dicionario[i]))
        return NULL; /* Pesquisa sem sucesso */
    else
    
    {
        Apontador = dicionario[i].Primeiro;
        while (Apontador->Proximo->Proximo != NULL && strncmp(Chave, Apontador->Proximo->ItemH.Chave, sizeof(TipoPalavra)))
            Apontador = Apontador->Proximo;
        if (!strncmp(Chave, Apontador->Proximo->ItemH.Chave, sizeof(TipoPalavra)))
            {
                Apontador->Proximo->ItemH.qntd_repete += 1;
                return Apontador;
            }
        else{
            return NULL; /* Pesquisa sem sucesso */
        }
            
    }
}

void VerificaInsere(TipoItem item, TipoPesos peso, TipoDicionario dicionario, int num_arquivo)
{
    // printf("(palavra: %s) peso: (%u)\n", item.Chave, peso);
    if (Pesquisa(item.Chave, peso, dicionario) == NULL){
        printf("Inserindo: %s\n", item.Chave);
        Insere(item, &dicionario[h(item.Chave, peso)], num_arquivo);
    }
    else{
        TipoApontadorEnc Aux;
        printf("\nvalor busca: %s", item.Chave);
        Aux = listaEnc.Primeiro->Prox;
        while (Aux != NULL)
        {
            if (strcmp(item.Chave, Aux->Item.Chave) == 0)
            {
                Aux->Item.qntd_repete += 1;
                return;
            }
            else
            {
                Aux = Aux->Prox;
            }
        }
        printf(" Registro ja  esta  presente: %s\n", item.Chave);
    }
        
}

// void Retira(TipoItem item, TipoPesos peso, TipoDicionario dicionario)
// {
//     TipoApontador Apontador;
//     Apontador = Pesquisa(item.Chave, peso, dicionario);
//     if (Apontador == NULL)
//         printf(" Registro nao esta  presente\n");
//     else
//         Ret(Apontador, &dicionario[h(item.Chave, peso)], &item);
// }

char* BuscaLista(TipoLista Lista)
{
    TipoApontador ApontadorAux;
    ApontadorAux = Lista.Primeiro->Proximo;
    while (ApontadorAux != NULL)
    {
        // printf("|%.*s|", X, ApontadorAux->Item.Chave);
        ApontadorAux->ItemH.Chave;
        ApontadorAux = ApontadorAux->Proximo;    
    }
}
// char* BuscaTabela(TipoDicionario Tabela)
// {
//     int i;
//     for (i = 0; i < Y; i++)
//     {
//         // printf("%d: ", i);
//         if (!Vazia(Tabela[i]))
//         { 
//             printf("teste")
//             BuscaLista(Tabela[i]);
//         }
//         // putchar('\n');
//     }
// }

void ImprimirLista(TipoLista Lista)
{
    TipoApontador ApontadorAux;
    ApontadorAux = Lista.Primeiro->Proximo;

    while (ApontadorAux != NULL)
    {
        // printf("repete: %d ", ApontadorAux->ItemH.qntd_repete);
        printf("|%.*s|", X, ApontadorAux->ItemH.Chave);
        ApontadorAux = ApontadorAux->Proximo;
    }
}

void ImprimeTabela(TipoDicionario Tabela)
{
    int i;
    for (i = 0; i < Y; i++)
    {
        printf("%d : ", i);
        if (!Vazia(Tabela[i]))
            {
                ImprimirLista(Tabela[i]);
            }
            
        putchar('\n');
    }
}

// void LerPalavra(char *p, int Tam)
// {
//     char c;
//     int i, j;
//     fflush(stdin);
//     j = 0;
//     while (((c = getchar()) != '\n') && j < Tam - 1)
//         p[j++] = c;
//     p[j] = '\0';
//     while (c != '\n')
//         c = getchar();
//     /* Desconsiderar espacos ao final
//       da cadeia como ocorre em Pascal.*/
//     for (i = j - 1; (i >= 0 && p[i] == ' '); i--)
//         p[i] = '\0';
// }