#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "indiceInvertido.h"

void FLVazia(TipoListaEnc *Lista)
{
    Lista->Primeiro = (TipoApontadorEnc)malloc(sizeof(TipoCelulaEnc));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

int VaziaEnc(TipoListaEnc Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}
// int Busca(TipoListaEnc Lista, char *valor_busca)
// {
//     TipoApontadorEnc Aux;
//     printf("\nvalor busca: %s", valor_busca);
//     Aux = Lista.Primeiro->Prox;
//     while (Aux != NULL)
//     {
//         if (strcmp(valor_busca, Aux->Item.Chave) == 0)
//         {
//             Aux->Item.qntd_repete += 1;
//             return 1;
//         }
//         else
//         {
//             Aux = Aux->Prox;
//         }
//     }
// }

void InsereEnc(TipoItemEnc item, TipoListaEnc *Lista, int numArquivoIndice)
{
    // if (Busca(*Lista, item.Chave) == 1 ){
    //     printf("chave repete!");
    // }
    // else{
        Lista->Ultimo->Prox = (TipoApontadorEnc)malloc(sizeof(TipoCelulaEnc));
        Lista->Ultimo = Lista->Ultimo->Prox;

        strcpy(Lista->Ultimo->Item.Chave, item.Chave);
        Lista->Ultimo->Item.qntd_repete = item.qntd_repete;
        Lista->Ultimo->Item.numArquivoIndice = item.numArquivoIndice;
        // Lista->Ultimo->Item.numArquivoIndice = item.numArquivoIndice;

        Lista->Ultimo->Prox = NULL;
    // }
    

    // printf("\ninseriu: %s", item.Chave);
    // Aux->Item.qntd_repete = 1;
    // printf("\nNao Repete: %d", Lista->Ultimo->Item.qntd_repete);
    // printf("\n");
}

void ImprimeEnc(TipoListaEnc Lista)
{
    TipoApontadorEnc Aux;
    Aux = Lista.Primeiro->Prox;
    while (Aux != NULL)
    {
        printf("%s ", Aux->Item.Chave);
        printf("<%d, %d>\n", Aux->Item.qntd_repete, Aux->Item.numArquivoIndice);
        Aux = Aux->Prox;
    }
}
