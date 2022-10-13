#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
// #include "qntdEnc.h"
#include "indicePaty.h"
#define MAX 10
#define X 12
//inicializa lista vazia
void FazListaIndiceVazia_Pat(ListaIndicePat *Lista) //inicializa a lista de ocorrencias
{
    Lista->Primeiro = (ApIndicePat)malloc(sizeof(ApIndicePat));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}
//retorna 1 se lista for vazia e 0 senao
int VaziaIndice_Pat(ListaIndicePat Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

void InsereIndice_Pat(int idDoc, int qntd_repete, ListaIndicePat *Lista)
{   //aloca memória para uma celula na lista e inicializa
    Lista->Ultimo->Prox = (ApIndicePat)malloc(sizeof(CelIndicePat));

    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item.qntd_repete = qntd_repete;
    Lista->Ultimo->Item.idDoc = idDoc;

    Lista->Ultimo->Prox = NULL;
}
void ImprimeIndicePatricia(ListaIndicePat Lista)
{ 
    ApIndicePat ap;
    ap = Lista.Primeiro->Prox;

    while (ap != NULL) // percorre a lista de ocorrencias da lista que esta sendo passada como parametro
    {
        printf("<%d,", ap->Item.qntd_repete);
        printf("%d> ", ap->Item.idDoc);
        ap = ap->Prox;
    }
    printf("\n");
}
int confereIdDoc(ListaIndicePat Lista, int recebe_idDoc)
{
    ApIndicePat ap;
    ap = Lista.Primeiro->Prox;
    while (ap != NULL) // também percorre a lista de ocorrencias com a finalidade de verificar se o arquivo ja é existente
    {
        if (ap->Item.idDoc == recebe_idDoc)
        {
            ap->Item.qntd_repete +=  1;
            return 1;
        }
        ap = ap->Prox;
    }
    return 0;
}

void BuscaIndice(ListaIndicePat Lista, char *valor_busca) //percorre a lista para encontrar quantas vezes a palavra escolhida se repete e em qual arquivo!
{
    ApIndicePat ap;
    ap = Lista.Primeiro->Prox;
    while (ap != NULL)
    {
        printf("repete %d veze(s) no arquivo %d", ap->Item.qntd_repete, ap->Item.idDoc);
        printf("\n");
        ap = ap->Prox;
    }
    return;
}
