#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "qntdEnc.h"
#define MAX 10

/* ========================================================================= */
#define X 12
// typedef struct TipoQntdEnc *
typedef char TipoChaveEnc[X];
typedef int TipoRepete;
typedef struct TipoItemEnc
{
    TipoChaveEnc Chave;
    TipoItemQntd qntd;
    int qntdTotalRepete;
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
void FLVaziaIndice(TipoListaEnc *Lista);
int VaziaEnc(TipoListaEnc Lista);
int Busca(TipoListaEnc Lista, char *valor_busca);
void InsereEnc(TipoItemEnc item, TipoListaEnc *Lista);
void ImprimeEnc(TipoListaEnc Lista);