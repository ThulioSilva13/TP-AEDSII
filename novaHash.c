#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "novaHash.h"

TipoListaQntd listaQntd;
//metodo que cria uma lista e inicializa como nulo
void InicializaListaVazia(TipoLista *Lista)
{
    Lista->Primeiro = (TipoCelula *)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Proximo = NULL;
    FLVaziaQntd(&listaQntd);
}
//retorna 1 caso lista estiver vazia e 0 se nao
short VaziaHash(TipoLista Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

void InsereHash(int idDoc,char *chave, TipoLista *Lista)
{
    TipoApontador ApHash;
    //insere na ultima posicao da lista
    Lista->Ultimo->Proximo = (TipoCelula *)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Proximo;
    strcpy(Lista->Ultimo->ItemH.Chave, chave);

    //=====insere no indice========

    Lista->Ultimo->lista_ocorrencias = (TipoListaQntd *)malloc(sizeof(TipoListaQntd));
    FLVaziaQntd(Lista->Ultimo->lista_ocorrencias);
    InsereQntd(idDoc, 1, Lista->Ultimo->lista_ocorrencias);
    Lista->Ultimo->Proximo = NULL;

}

void GeraPesos(TipoPesos peso)  
{ /* Gera valores randomicos entre 1 e 10.000 */
    int i, j;
    struct timeval semente;
    /* Utilizar o tempo como semente para a funcao srand() */
    gettimeofday(&semente, NULL);
    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
    for (i = 0; i < M; i++)
        for (j = 0; j < TAMALFABETO; j++)
            peso[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
}
//Função que faz o espalhamento(hash)
TipoIndice h(TipoPalavra Chave, TipoPesos peso)
{
    int i;
    unsigned int Soma = 0;
    int comp = strlen(Chave);
    for (i = 0; i < comp; i++)
        Soma += peso[i][(unsigned int)Chave[i]];
    return (Soma % M);
}
//inicializa uma lista vazia para cada posicao de M
void InicializaDicionario(TipoDicionario dicionario)
{
    int i;
    for (i = 0; i < M; i++)
        InicializaListaVazia(&dicionario[i]);
}
//função que busca palavra na lista
TipoApontador buscarNaLista(char *palavra, TipoDicionario table){
    TipoApontador aux;

    aux = table->Primeiro;
    while (aux != NULL)
    {
        if(strcmp(aux->ItemH.Chave, palavra) == 0){
            return aux;
        }
        else{
            aux = aux->Proximo;
        }
    }
    return NULL;
}

void VerificaInsere(int num_arquivo, char *chave ,TipoPesos peso, TipoDicionario dicionario)
{
    TipoApontador AuxAp;
    int i;
    for (i = 0; i < M; i++)
    {
        //para cada M da tabela, verifica se a lista 
        if (!VaziaHash(dicionario[i]))
        {
            AuxAp = buscarNaLista(chave, &dicionario[i]);
            if (AuxAp != NULL)
            {//se o idDoc da palavra for diferente do id passado por parametro, 
            //insere na lista de frequencia 
                if (confereIdDocHash(*AuxAp->lista_ocorrencias, num_arquivo) == 0)
                {
                    InsereQntd(num_arquivo, 1, AuxAp->lista_ocorrencias);
                }
                
                return;
            }
        }
    }
    InsereHash(num_arquivo, chave, &dicionario[h(chave, peso)]);
}
void BuscaPesquisa(TipoDicionario dicionario, char *buscaPalavra)
{
    TipoApontador AuxAp;
    int i;
    for (i = 0; i < M; i++)
    {//verifica se a lista daquele 'M' está vazia, senao tiver, busca a palavra na lista 
        if (!VaziaHash(dicionario[i]))
        {
            AuxAp = buscarNaLista(buscaPalavra, &dicionario[i]);
            if (AuxAp != NULL)
            {//se achar a palavra, printa e imprime o indice
                printf("Encontramos a chave '%s': ", AuxAp->ItemH.Chave);
                ImprimeIndiceHash(*AuxAp->lista_ocorrencias);
                return;
            }
        }
    }
}

void ImprimirLista(TipoLista Lista)
{
    TipoApontador ApontadorAux;
    ApontadorAux = Lista.Primeiro->Proximo;
    //percorre a lista encadeada, imprime a chave e chama a funcao imprimeIndiceHash
    while (ApontadorAux != NULL)
    {
        printf("%.*s ", M, ApontadorAux->ItemH.Chave);
        ImprimeIndiceHash(*ApontadorAux->lista_ocorrencias);
        ApontadorAux = ApontadorAux->Proximo;
    }
}

void ImprimeTabela(TipoDicionario Tabela)
{
    int i;
    for (i = 0; i < M; i++)
    {
        //para cada M, verifica se a tabela ta vazia, se estiver, imprime a lista encadeada daquela posicao
        if (!VaziaHash(Tabela[i]))
            {
                ImprimirLista(Tabela[i]);
            }
    }
}
