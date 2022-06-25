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
} TipoPatNo;

void InicializaArvorePatricia(TipoArvoreApontador *arvore);
TipoArvoreApontador InicializaNoInterno(TipoArvoreApontador *esq, TipoArvoreApontador *dir, char letra, int indice);
TipoArvoreApontador InicializaNoExterno(char *palavra);
TipoArvoreApontador InserePatricia(TipoArvoreApontador *arvore, char *palavraInserir);
TipoArvoreApontador InsereEntrePatricia(char *palavra, TipoArvoreApontador *arvore, int indice, char letraQueDifere);
void ImprimePatricia(TipoArvoreApontador *arvore);