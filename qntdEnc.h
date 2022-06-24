#include <stdio.h>
#include <stdlib.h>

typedef struct TipoItemQntd
{
    int qntd_repete;
    int idDoc;
} TipoItemQntd;

typedef struct TipoCelulaQntd *TipoApontadorQntd;

typedef struct TipoCelulaQntd
{
    TipoItemQntd Item;
    TipoApontadorQntd Prox;
} TipoCelulaQntd;

typedef struct TipoListaQntd
{
    TipoApontadorQntd Primeiro, Ultimo;
} TipoListaQntd;

void FLVaziaQntd(TipoListaQntd *Lista);
int VaziaQntd(TipoListaQntd Lista);
void InsereQntd(TipoItemQntd item, TipoListaQntd *Lista);
void ImprimeQntd(TipoListaQntd Lista);