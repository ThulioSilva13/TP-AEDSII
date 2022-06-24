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
TipoArvoreApontador InserePatricia(TipoArvoreApontador *arvore, char *palavraInserir)
{
    TipoArvoreApontador arvoreAux;
    char letra;
    char letraQueDifere;
    int tamanhoPalavraInserir = strlen(palavraInserir);

    if (*arvore == NULL)
    { // se for nulo, cria o no externo
        return InicializaNoExterno(palavraInserir);
    }
    else
    {
        arvoreAux = *arvore;
        while (!VerificaSeNoExterno(arvoreAux))
        {
            if (arvoreAux->NO.NInterno.Index > tamanhoPalavraInserir)
            {
                letra = palavraInserir[tamanhoPalavraInserir];
            }
            else
            {
                letra = Bit(arvoreAux->NO.NInterno.Index, palavraInserir);
            }
            if (letra < arvoreAux->NO.NInterno.LetraComparada)
            {
                arvoreAux = arvoreAux->NO.NInterno.Esq;
            }
            else
            { // se a letra for maior ou igual que a letra comparada
                arvoreAux = arvoreAux->NO.NInterno.Dir;
            }
        }
        // if (strcmp(palavraInserir, arvoreAux->NO.Chave) == 0)
        // {
        //     // as palavras sao iguais, logo decidir onde inserir(direita ou esquerda)
        //     *compara += 1;
        //     // printf("As chaves sÃ£o iguais\n");
        //     // adicionar no indice invertido
        // }
        int indice = 1;

        while (Bit(indice, palavraInserir) == Bit(indice, arvoreAux->NO.Chave))
        {
            indice = indice + 1;
        }
        if (Bit(indice, palavraInserir) > Bit(indice, arvoreAux->NO.Chave))
        {
            letraQueDifere = palavraInserir[indice - 1];
        }
        else
        {
            letraQueDifere = arvoreAux->NO.Chave[indice - 1];
        }
        return InsereEntrePatricia(palavraInserir, arvore, indice, letraQueDifere);
    }
}
TipoArvoreApontador CriaNoExterno(char *palavra)
{
    TipoArvoreApontador aux;
    int tamanhoPalavra = strlen(palavra);

    aux = (TipoArvoreApontador)malloc(sizeof(TipoPatNo));

    aux->NO.Chave = (char*)malloc(sizeof(char) * tamanhoPalavra);
    // = ;

    aux->Interno_Externo = Externo;
    strcpy(aux->NO.Chave, palavra);

    return aux;
}
TipoArvoreApontador CriaNoInterno(int i, TipoArvoreApontador *Esq, TipoArvoreApontador *Dir, char letra)
{
    /// Variavel i -> indice onde as palavras se diferem
    /// Variavel letra -> letra escolhida para ser armazenada no NO interno
    TipoArvoreApontador aux;
    aux = (TipoArvoreApontador)malloc(sizeof(TipoPatNo));

    aux->Interno_Externo = Interno;
    aux->NO.NInterno.Esq = *Esq;
    aux->NO.NInterno.Dir = *Dir;

    aux->NO.NInterno.Index = i;
    aux->NO.NInterno.LetraComparada = letra;

    return aux;
}
TipoArvoreApontador InsereEntrePatricia(char *palavra, TipoArvoreApontador *arvore, int indice, char letraQueDifere)
{
    TipoArvoreApontador arvoreAux;

    /// Verifica se o NO da chamada atual eh um NO externo
    if (VerificaSeNoExterno(*arvore))
    {

        arvoreAux = CriaNoExterno(palavra);
        /// Verifica qual das letras eh maior na posicao i, vai para a direita se for maior ou igual
        if (Bit(indice, palavra) >= Bit(indice, (*arvore)->NO.Chave))
        {

            return (CriaNoInterno(indice, arvore, &arvoreAux, letraQueDifere));
        }
        else
        {

            return (CriaNoInterno(indice, &arvoreAux, arvore, letraQueDifere));
        }
        /// Verifica se o i eh menor que o indice guardado no No interno
    }
    else if (indice < (*arvore)->NO.NInterno.Index)
    {

        arvoreAux = CriaNoExterno(palavra);
        /// Compara a letra na posicao que diferiu com a letra escolhida para o No interno
        if (Bit(indice, palavra) >= letraQueDifere)
        {

            return (CriaNoInterno(indice, arvore, &arvoreAux, letraQueDifere));
        }
        else
        {

            return (CriaNoInterno(indice, &arvoreAux, arvore, letraQueDifere));
        }
    }
    else
    {

        /// Nos internos, compara a letra guardada dentro do No com a letra na posicao i (onde difere), se for maior -> direita
        if (Bit((*arvore)->NO.NInterno.Index, palavra) >= (*arvore)->NO.NInterno.LetraComparada)
        {

            (*arvore)->NO.NInterno.Dir = InsereEntrePatricia(palavra, &(*arvore)->NO.NInterno.Dir, indice, letraQueDifere);
        }
        else
        {

            (*arvore)->NO.NInterno.Esq = InsereEntrePatricia(palavra, &(*arvore)->NO.NInterno.Esq, indice, letraQueDifere);
        }
    }
    return (*arvore);
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