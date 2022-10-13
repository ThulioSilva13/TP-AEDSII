#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "NossaPaty.h"
//#include "indicePaty.h"
// Método para inicializar arvore PATRICIA como null
void InicializaArvorePatricia(TipoArvoreApontador *arvore)
{
    *arvore = NULL;
}
// retorna 1 caso o nó for externo e 0 se o nó for falso
int VerificaSeNoExterno(TipoArvoreApontador arvore)
{
    return (arvore->Interno_Externo == Externo);
}
// retorna a letra que difere as duas palavras
char Bit(int IndiceLetraDiferente, char *palavraInserir)
{
    return palavraInserir[IndiceLetraDiferente - 1];
}
// Inicializa nó interno da arvore
TipoArvoreApontador InicializaNoInterno(TipoArvoreApontador *esq, TipoArvoreApontador *dir, char letra, int indice)
{
    TipoArvoreApontador arvoreAux;
    arvoreAux = (TipoArvoreApontador)malloc(sizeof(TipoPatNo));

    arvoreAux->Interno_Externo = Interno;
    arvoreAux->NO.NInterno.Esq = *esq;
    arvoreAux->NO.NInterno.Dir = *dir;

    arvoreAux->NO.NInterno.Index = indice;
    arvoreAux->NO.NInterno.LetraComparada = letra;

    return arvoreAux;
}
// Inicializa nó exteno da arvore
TipoArvoreApontador InicializaNoExterno(char *palavra, int idDoc)
{
    TipoArvoreApontador arvoreAux;
    arvoreAux = (TipoArvoreApontador)malloc(sizeof(TipoPatNo));
    arvoreAux->Interno_Externo = Externo;
    arvoreAux->NO.Chave = (char *)malloc(strlen(palavra) * sizeof(char));
    strcpy(arvoreAux->NO.Chave, palavra);

    // ====== insere no indice invertido =======
    int qntd_repete_inicial = 1;
    arvoreAux->lista_de_ocorrencias = (ListaIndicePat *)malloc(sizeof(ListaIndicePat));
    FazListaIndiceVazia_Pat(arvoreAux->lista_de_ocorrencias);
    InsereIndice_Pat(idDoc, qntd_repete_inicial, arvoreAux->lista_de_ocorrencias);

    return arvoreAux;
}

TipoArvoreApontador InserePatricia(TipoArvoreApontador *arvore, char *palavraInserir, int idDoc)
{
    TipoArvoreApontador arvoreAux;
    char letra;
    char letraQueDifere;
    int tamanhoPalavraInserir = strlen(palavraInserir);
    // se a arvore for nula, cria um nó externo e insere a palavra la
    if (*arvore == NULL)
    {
        return InicializaNoExterno(palavraInserir, idDoc);
    }
    else
    {
        arvoreAux = *arvore;
        while (!VerificaSeNoExterno(arvoreAux)) // executa enquanto for nó interno
        {
            // se o índice do nó for maior que o tamanho da palavra, adiciona
            if (arvoreAux->NO.NInterno.Index > tamanhoPalavraInserir)
            {
                letra = palavraInserir[tamanhoPalavraInserir];
            }
            else
            { // letra recebe a letra que difere as duas palavras
                letra = Bit(arvoreAux->NO.NInterno.Index, palavraInserir);
            }
            if (letra < arvoreAux->NO.NInterno.LetraComparada)
            { // se a letra for menor, olha para a arvore da esquerda
                arvoreAux = arvoreAux->NO.NInterno.Esq;
            }
            else
            { // se for maior ou igual, olha pra arvore da direita
                arvoreAux = arvoreAux->NO.NInterno.Dir;
            }
        }
        if (strcmp(palavraInserir, arvoreAux->NO.Chave) == 0) //se a palavra já estiver inserida na arvore, entra no if
        {
            if (confereIdDoc(*arvoreAux->lista_de_ocorrencias, idDoc) == 0) //nao encontrou o arquivo
            {
                //cria uma nova celula para adicionar uma nova lista de ocorrencias daquela palavra repetida!
                InsereIndice_Pat(idDoc, 1, arvoreAux->lista_de_ocorrencias);
            }
            return (*arvore);
        }else{
            // printf("Palavra inserida!\n");
            int indice = 1;
            // indice variavel de controle, verifica se as letras são iguais, se for, aumenta o indice
            while (Bit(indice, palavraInserir) == Bit(indice, arvoreAux->NO.Chave))
            {
                indice = indice + 1;
            }
            // quando acha o indice em que as letras são diferentes, compara pra ver qual é maior
            if (Bit(indice, palavraInserir) > Bit(indice, arvoreAux->NO.Chave))
            {
                // se a letra da palavra que queremos inserir for maior que a letra que ja tá la
                // a letra que difere vai receber a letra da palavra que queremos inserir
                letraQueDifere = palavraInserir[indice - 1];
            }
            else
            {
                // se a letra da palavra que querermos inserir for menor ou igual que a letra que ja ta no nó
                // a letra que difere vai receber a letra da palavra que está no nó
                letraQueDifere = arvoreAux->NO.Chave[indice - 1];
            }
            // pega a letra que difere, a palavra, a arvore e o indice em que ela difere e passa pra função insere entre
            return InsereEntrePatricia(palavraInserir, arvore, indice, letraQueDifere, idDoc);
        }
    }
}

TipoArvoreApontador InsereEntrePatricia(char *palavra, TipoArvoreApontador *arvore, int indice, char letraQueDifere, int idDoc)
{
    TipoArvoreApontador arvoreAux;
    if (VerificaSeNoExterno(*arvore))
    {

        arvoreAux = InicializaNoExterno(palavra,idDoc);
        // se a letra da palavra que veio for maior que a letra da palavra que tá no nó
        if (Bit(indice, palavra) >= Bit(indice, (*arvore)->NO.Chave))
        { // cria um nó interno com a arvore a esquerda e uma arvore auxiliar a direita

            return (InicializaNoInterno(arvore, &arvoreAux, letraQueDifere, indice));
        }
        else
        { // cria um nó interno com uma arvore auxiliar a esquerda e a arvore auxiliar a direita

            return (InicializaNoInterno(&arvoreAux, arvore, letraQueDifere, indice));
        }
    }
    else if (indice < (*arvore)->NO.NInterno.Index)
    {
        // se o índice da letra que difere for menor que o indice do nó interno, cria um externo
        arvoreAux = InicializaNoExterno(palavra, idDoc);
        // se a letra for maior ou igual cria o nó interno com a arvore a esquerda e arvore auxiliar a direita
        if (Bit(indice, palavra) >= letraQueDifere)
        {

            return (InicializaNoInterno(arvore, &arvoreAux, letraQueDifere, indice));
        }
        else
        { // se for menor, cria um nó interno com uma arvore auxiliar a esquerda e a arvore a direita

            return (InicializaNoInterno(&arvoreAux, arvore, letraQueDifere, indice));
        }
    }
    else
    { // se o indice for maior ou igual que o indice do nó interno

        if (Bit((*arvore)->NO.NInterno.Index, palavra) >= (*arvore)->NO.NInterno.LetraComparada)
        {
            // se a letra da palavra for maior ou igual do que a letra comparada, chamar recursivo o insereEntrePatricia para nó direito
            (*arvore)->NO.NInterno.Dir = InsereEntrePatricia(palavra, &(*arvore)->NO.NInterno.Dir, indice, letraQueDifere,idDoc);
        }
        else
        {
            // se a letra da palavra for menor do que a letra comparada, chamar recursivo o insereEntrePatricia para o nó esquerdo
            (*arvore)->NO.NInterno.Esq = InsereEntrePatricia(palavra, &(*arvore)->NO.NInterno.Esq, indice, letraQueDifere, idDoc);
        }
    }

    return (*arvore);
}

int BuscaPatiEIndice(TipoArvoreApontador arvore, char *palavraBusca)
{
    // verifica se arvore nao está vazia
    if (arvore != NULL)
    {
        // se no for extrerno printa a chave
        if (arvore->Interno_Externo == Externo)
        {
            if (strcmp(palavraBusca,arvore->NO.Chave) == 0)
            {
                printf("A palavra '%s':\n",arvore->NO.Chave);
                BuscaIndice(*arvore->lista_de_ocorrencias, palavraBusca);
                return 1;
            }
        }
        else
        { // se for nó interno, percorre recursivo tanto para esquerda como para direita
            BuscaPatiEIndice(arvore->NO.NInterno.Esq, palavraBusca);
            BuscaPatiEIndice(arvore->NO.NInterno.Dir, palavraBusca);
        }
    }

    
}

void ImprimePatricia(TipoArvoreApontador arvore)
{
    // verifica se arvore nao está vazia
    if (arvore != NULL)
    {
        // se no for extrerno printa a chave
        if (arvore->Interno_Externo == Externo)
        {
            printf("%s ", arvore->NO.Chave);
            ImprimeIndicePatricia(*arvore->lista_de_ocorrencias);
        }
        else
        { // se for nó interno, percorre recursivo tanto para esquerda como para direita
            ImprimePatricia(arvore->NO.NInterno.Esq);
            ImprimePatricia(arvore->NO.NInterno.Dir);
        }
    }
    
}
