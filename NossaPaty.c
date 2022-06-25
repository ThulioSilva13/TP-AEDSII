#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
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
    arvoreAux->NO.Chave = (char*) malloc (strlen(palavra) * sizeof(char));

    strcpy(arvoreAux->NO.Chave, palavra);
    return arvoreAux;
}

TipoArvoreApontador InserePatricia(TipoArvoreApontador *arvore, char *palavraInserir){
    TipoArvoreApontador arvoreAux;
    char letra;
    char letraQueDifere;
    int tamanhoPalavraInserir = strlen(palavraInserir);

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
            //printf("As chaves são iguais\n");
           //adicionar no indice invertido
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



TipoArvoreApontador InsereEntrePatricia(char *palavra, TipoArvoreApontador *arvore, int indice, char letraQueDifere){
    TipoArvoreApontador arvoreAux;
    /// Verifica se o NO da chamada atual eh um NO externo
    if (VerificaSeNoExterno(*arvore)){

        arvoreAux = InicializaNoExterno(palavra);
        /// Verifica qual das letras eh maior na posicao i, vai para a direita se for maior ou igual
        if (Bit(indice, palavra) >= Bit(indice, (*arvore)->NO.Chave)) {

            return (InicializaNoInterno(arvore, &arvoreAux, letraQueDifere, indice));
        } else {

            return (InicializaNoInterno(&arvoreAux, arvore, letraQueDifere, indice));
        }
        /// Verifica se o i eh menor que o indice guardado no No interno
    } else if (indice < (*arvore)->NO.NInterno.Index) {

        arvoreAux = InicializaNoExterno(palavra);
        /// Compara a letra na posicao que diferiu com a letra escolhida para o No interno
        if (Bit(indice, palavra) >= letraQueDifere) {

            return (InicializaNoInterno(arvore, &arvoreAux, letraQueDifere,indice));
        } else {

            return (InicializaNoInterno(&arvoreAux, arvore, letraQueDifere,indice));
        }

    } else {

        /// Nos internos, compara a letra guardada dentro do No com a letra na posicao i (onde difere), se for maior -> direita
        if (Bit((*arvore)->NO.NInterno.Index, palavra) >= (*arvore)->NO.NInterno.LetraComparada){

            (*arvore)->NO.NInterno.Dir = InsereEntrePatricia(palavra, &(*arvore)->NO.NInterno.Dir, indice, letraQueDifere);
        } else {

            (*arvore)->NO.NInterno.Esq = InsereEntrePatricia(palavra, &(*arvore)->NO.NInterno.Esq, indice, letraQueDifere);
        }
    }
    
    return (*arvore);
}

void ImprimirPatricia(TipoArvoreApontador *arvore){
    if (*arvore != NULL){
       
        if ((*arvore)->Interno_Externo == Externo){
            printf("%s\n", (*arvore)->NO.Chave);
        } else {
            ImprimirPatricia(&(*arvore)->NO.NInterno.Esq);
            ImprimirPatricia(&(*arvore)->NO.NInterno.Dir);
        }
    }
}