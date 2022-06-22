#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 10

/* ========================================================================= */
#define X 12
// typedef struct TipoQntdEnc *
typedef char TipoChaveEnc[X];
typedef int TipoRepete;
typedef struct
{
    TipoChaveEnc Chave;
    TipoRepete qntd_repete;
    int numArquivoIndice;
    // int numArquivoIndice;
    /* outros componentes */
} TipoItemEnc;

typedef struct TipoCelulaEnc *TipoApontadorEnc;

typedef struct TipoCelulaEnc
{
    TipoItemEnc Item;
    TipoApontadorEnc Prox;
} TipoCelulaEnc;

typedef struct TipoListaEnc
{
    TipoApontadorEnc Primeiro, Ultimo;
} TipoListaEnc;

/* ========================================================================= */
void FLVazia(TipoListaEnc *Lista);
int VaziaEnc(TipoListaEnc Lista);
int Busca(TipoListaEnc Lista, char *valor_busca);
void InsereEnc(TipoItemEnc item, TipoListaEnc *Lista, int numArquivoIndice);
void ImprimeEnc(TipoListaEnc Lista);