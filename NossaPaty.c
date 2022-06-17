#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <sys/time.h>
#include "NossaPaty.h"

void InicializaArvorePatricia(TipoArvoreApontador *arvore){
    *arvore = NULL;
    // InicializaNoInterno(&arvore);
    // InicializaNoExterno(&arvore);
}
int VerificaSeNoExterno(TipoArvoreApontador arvore)
{
    return (arvore->Interno_Externo == Externo);
}
char Bit(int IndiceQueDifere, char *palavraInserir){
    return palavraInserir[IndiceQueDifere - 1];
}
TipoArvoreApontador InicializaNoInterno(TipoArvoreApontador *esq, TipoArvoreApontador *dir, char letra, int indice){
    TipoArvoreApontador arvoreAux;
    arvoreAux = (TipoArvoreApontador)malloc(sizeof(TipoPatNo));

    arvoreAux->Interno_Externo = Interno;
    arvoreAux->NO.NInterno.Esq = *esq;
    arvoreAux->NO.NInterno.Dir = *dir;

    arvoreAux->NO.NInterno.Index = indice;
    arvoreAux->NO.NInterno.LetraComparada = letra;

    return arvoreAux;
}

TipoArvoreApontador InicializaNoExterno(char *palavra){
    TipoArvoreApontador arvoreAux;
    arvoreAux = (TipoArvoreApontador)malloc(sizeof(TipoPatNo));

    arvoreAux->Interno_Externo = Externo;
    strcpy(arvoreAux->NO.Chave, palavra);
    return arvoreAux;
    // arvoreAux->NO.Chave = (char*) malloc (strlen(palavra) * sizeof(char));

}
TipoArvoreApontador InserePatricia(TipoArvoreApontador *arvore, char *palavraInserir, int *compara){
    TipoArvoreApontador arvoreAux;
    char letra;
    char letraQueDifere;
    int tamanhoPalavraInserir;
    tamanhoPalavraInserir = strlen(palavraInserir);

    if (*arvore == NULL){ //se for nulo, cria o no externo
        return InicializaNoExterno(palavraInserir);
    }
    else{
        arvoreAux = *arvore;
        while (!VerificaSeNoExterno(arvoreAux))
        {
            if (arvoreAux->NO.NInterno.Index > tamanhoPalavraInserir)
            {
                letra = palavraInserir[tamanhoPalavraInserir];
            }
            else{
                letra = Bit(arvoreAux->NO.NInterno.Index, palavraInserir);
            }
            if (letra < arvoreAux->NO.NInterno.LetraComparada){
                arvoreAux = arvoreAux->NO.NInterno.Esq;
            }
            else{ //se a letra for maior ou igual que a letra comparada
                arvoreAux = arvoreAux->NO.NInterno.Dir;
            }
        }
        if(strcmp(palavraInserir, arvoreAux->NO.Chave) == 0){
            //as palavras sao iguais, logo decidir onde inserir(direita ou esquerda)
            *compara += 1;
            printf("As chaves são iguais\n");
        }
        int indice = 1;
        
        while(Bit(indice,palavraInserir) == Bit(indice, arvoreAux->NO.Chave)){
            indice = indice + 1;
        }
        if(Bit(indice, palavraInserir) > Bit(indice, arvoreAux->NO.Chave)){
            letraQueDifere = palavraInserir[indice - 1];
        } else{
            letraQueDifere = arvoreAux->NO.Chave[indice - 1];
        }
        return InsereEntrePatricia(palavraInserir, arvore, indice, letraQueDifere);
    }
}
int ContarPalavras(TipoArvoreApontador *arvore, char *palavra){
    int contador = 0;
    if (*arvore != NULL){
        
        if ((*arvore)->Interno_Externo == Externo)
        {
            if(strcmp((*arvore)->NO.Chave, palavra))
            {
                (contador)++;
            }
        }
        else
        {
            ContarPalavras(&(*arvore)->NO.NInterno.Esq, palavra);
            ContarPalavras(&(*arvore)->NO.NInterno.Dir, palavra);
        }
    }
}