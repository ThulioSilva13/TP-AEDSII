#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "indiceHash.h"
#define MAX 10
#define X 12
//inicializa lista
void FLVaziaQntd(TipoListaQntd *Lista)
{
    Lista->Primeiro = (TipoApontadorQntd)malloc(sizeof(TipoApontadorQntd));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}
//retorna 1 se a lista estiver vazia e 0 senao
int VaziaQntd(TipoListaQntd Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

void InsereQntd(int idDoc, int qntd_repete, TipoListaQntd *Lista)
{
    //insere na lista de frequencia
    Lista->Ultimo->Prox = (TipoApontadorQntd)malloc(sizeof(TipoCelulaQntd));

    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item.qntd_repete = qntd_repete;
    Lista->Ultimo->Item.idDoc = idDoc;

    Lista->Ultimo->Prox = NULL;
}
//retorna 1 se o idDoc da palavra estiver for igual ao idDoc passado 
//por parametroe e retorna 0 se for diferente
int confereIdDocHash(TipoListaQntd Lista, int idDoc)
{
    TipoApontadorQntd ApHash;
    ApHash = Lista.Primeiro->Prox;
    //percorre a lista encadeada
    while (ApHash != NULL)
    {//se o idDoc for igual ao do documento passado, incrementa mais um na frequencia da palavra e retorna 1
        if (ApHash->Item.idDoc == idDoc)
        {
            ApHash->Item.qntd_repete += 1;
            return 1;
        }
        ApHash = ApHash->Prox;
    }
    return 0;
}
//percorre a lista de indices e imprime
void ImprimeIndiceHash(TipoListaQntd Lista){

    TipoApontadorQntd ApHash;
    ApHash = Lista.Primeiro->Prox;

    while (ApHash != NULL)
    {
        printf("<%d,%d>", ApHash->Item.qntd_repete, ApHash->Item.idDoc);
        ApHash = ApHash->Prox;
    }
    printf("\n");
}
