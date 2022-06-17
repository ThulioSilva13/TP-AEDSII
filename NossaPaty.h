typedef unsigned char TipoChave[30]; /* a definir, dependendo da aplicacao */
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
} TipoPatNo;

void InicializaArvorePatricia(TipoArvoreApontador *arvore);
TipoArvoreApontador InicializaNoInterno(TipoArvoreApontador *esq, TipoArvoreApontador *dir, char letra, int indice);
TipoArvoreApontador InicializaNoExterno(char *palavra);
TipoArvoreApontador InserePatricia(TipoArvoreApontador *arvore, char *palavraInserir, int* compara);
TipoArvoreApontador InsereEntrePatricia(palavraInserir, arvore, indice, letraQueDifere);