#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "qntdEnc.h"
#define MAX 10
#define X 12

void FLVaziaQntd(TipoListaQntd *Lista)
{
    Lista->Primeiro = (TipoApontadorQntd)malloc(sizeof(TipoCelulaQntd));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

int VaziaQntd(TipoListaQntd Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

void InsereQntd(TipoItemQntd item, TipoListaQntd *Lista)
{
    printf("teste: %d, %d\n", item.qntd_repete, item.idDoc);
    Lista->Ultimo->Prox = (TipoApontadorQntd)malloc(sizeof(TipoCelulaQntd));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item.qntd_repete = item.qntd_repete;
    Lista->Ultimo->Item.idDoc = item.idDoc;

    printf("ListaUltimo: %d, %d\n", Lista->Ultimo->Item.qntd_repete, Lista->Ultimo->Item.idDoc);
    Lista->Ultimo->Prox = NULL;
}

void ImprimeQntd(TipoListaQntd Lista)
{
    TipoApontadorQntd Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL)
    {
        printf("<%d,", Aux->Item.qntd_repete);
        printf("%d>\n", Aux->Item.idDoc);
        Aux = Aux->Prox;
    }
}
// int Busca(TipoLista Lista, int valor_busca)
// {
//     TipoApontador Aux;
//     Aux = Lista.Primeiro->Prox;
//     while (Aux != NULL)
//     {
//         if (valor_busca == Aux->Item.Chave)
//         {
//             return 1;
//         }
//         else
//         {
//             Aux = Aux->Prox;
//         }
//     }
// }

// int busca(TipoCelula *l, int busca_valor)
// {
//     TipoCelula *p;
//     for (p = l; p != NULL; p = p->Prox)
//         if (p->Item.Chave == busca_valor)
//             return 1;
//     return 0; /* não achou o elemento */
// }
// /* função busca: busca um elemento na lista */
// TipoLista *busca(TipoLista *l, int v)
// {
//     TipoLista *p;
//     for (p = l; p != NULL; p = p.Primeiro->Prox)
//         if (&(p->Primeiro->Item) == v)
//             return p;
//     return NULL; /* não achou o elemento */
// }

/* ========================================================================== */
