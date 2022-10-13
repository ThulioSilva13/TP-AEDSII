#include "indicePaty.h"

typedef unsigned char *TipoChave; /* a definir, dependendo da aplicacao */
typedef unsigned char TipoIndexAmp;
typedef unsigned char TipoDib;
typedef enum
{
    Interno,
    Externo
} TipoNo;
typedef struct TipoPatNo *TipoArvoreApontador;
typedef struct TipoPatNo
{
    TipoNo Interno_Externo;
    union
    {
        struct
        {
            TipoIndexAmp Index;
            TipoArvoreApontador Esq, Dir;
            char LetraComparada;
        } NInterno;
        TipoChave Chave;
    } NO;
    ListaIndicePat *lista_de_ocorrencias;
} TipoPatNo;

void InicializaArvorePatricia(TipoArvoreApontador *arvore);
TipoArvoreApontador InicializaNoInterno(TipoArvoreApontador *esq, TipoArvoreApontador *dir, char letra, int indice);
TipoArvoreApontador InicializaNoExterno(char *palavra, int idDoc);
TipoArvoreApontador InserePatricia(TipoArvoreApontador *arvore, char *palavraInserir, int idDoc);
TipoArvoreApontador InsereEntrePatricia(char *palavra, TipoArvoreApontador *arvore, int indice, char letraQueDifere, int idDoc);
void ImprimePatricia(TipoArvoreApontador arvore);
int confereIdDoc(ListaIndicePat Lista, int recebe_idDoc);
int BuscaPatiEIndice(TipoArvoreApontador arvore, char *palavraBusca);
// void PesquisaPatricia(TipoArvoreApontador *arvore, char *palavra);