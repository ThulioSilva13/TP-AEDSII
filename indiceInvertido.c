#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "indiceInvertido.h"
TipoListaQntd listaQntd;
TipoItemQntd itemQntd;

void FLVaziaIndice(TipoListaEnc *Lista)
{
    Lista->Primeiro = (TipoApontadorEnc)malloc(sizeof(TipoCelulaEnc));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
    FLVaziaQntd(&listaQntd);
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

void InsereEnc(TipoItemEnc item, TipoListaEnc *Lista)
{
    // if (Busca(*Lista, item.Chave) == 1 ){
    //     printf("chave repete!");
    // }
    // else{
        Lista->Ultimo->Prox = (TipoApontadorEnc)malloc(sizeof(TipoCelulaEnc));
        Lista->Ultimo = Lista->Ultimo->Prox;

        strcpy(Lista->Ultimo->Item.Chave, item.Chave);
        Lista->Ultimo->Item.qntd.idDoc = item.qntd.idDoc;
        Lista->Ultimo->Item.qntdTotalRepete = item.qntdTotalRepete;

        // Lista->Ultimo->Item.numArquivoIndice = item.numArquivoIndice;

        // Lista->Ultimo->Item.qntd.num_arquivo = item.qntd.num_arquivo;
        // Lista->Ultimo->Item.qntd.qntd_repete = item.qntd.qntd_repete;
        // printf("Ta chegando arquivo: %d ", item.qntd.idDoc);
        // printf("Ta chegando repete: %d ", item.qntd.qntd_repete);
        itemQntd.idDoc = item.qntd.idDoc;
        itemQntd.qntd_repete = item.qntd.qntd_repete;
        InsereQntd(itemQntd, &listaQntd);
        Lista->Ultimo->Prox = NULL;
        // }

        // printf("\ninseriu: %s", item.Chave);
        // Aux->Item.qntd_repete = 1;
        // printf("\nNao Repete: %d", Lista->Ultimo->Item.qntd_repete);
        // printf("\n");
}

// void ImprimeEnc(TipoListaEnc Lista)
// {
//     TipoApontadorEnc AuxEnc;
//     TipoApontadorQntd AuxQntd;
//     AuxEnc = Lista.Primeiro->Prox;
//     AuxQntd = listaQntd.Primeiro->Prox;

//     while (AuxEnc != NULL)
//     {
//         printf("%s ", AuxEnc->Item.Chave);
//         printf("<%d,%d>\n", AuxQntd->Item.qntd_repete, AuxQntd->Item.idDoc);
//         // printf("Qntd total repete: %d\n", AuxEnc->Item.qntdTotalRepete);

//         AuxQntd = AuxQntd->Prox;
//         AuxEnc = AuxEnc->Prox;
//     }

//     // ImprimeQntd(listaQntd);
// }

void ImprimeEnc(TipoListaEnc Lista)
{
    TipoApontadorEnc AuxEnc;
    TipoApontadorQntd AuxQntd;
    AuxEnc = Lista.Primeiro->Prox;
    AuxQntd = listaQntd.Primeiro->Prox;

    while (AuxEnc != NULL)
    {
        
        // while ()
        // {
            printf("%s ", AuxEnc->Item.Chave);
            printf("<%d,%d>\n", AuxQntd->Item.qntd_repete, AuxQntd->Item.idDoc);
            AuxQntd = AuxQntd->Prox;
        
        
        
        // ImprimeQntd(listaQntd);

        // printf("Qntd total repete: %d\n", AuxEnc->Item.qntdTotalRepete);

        // AuxQntd = AuxQntd->Prox;
        AuxEnc = AuxEnc->Prox;
    }
    

    ImprimeQntd(listaQntd);
}
