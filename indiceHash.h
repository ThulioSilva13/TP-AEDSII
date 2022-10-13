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
void InsereQntd(int idDoc, int qntd_repete, TipoListaQntd *Lista);
void ImprimeQntd(TipoListaQntd Lista);
void ImprimeIndiceHash(TipoListaQntd Lista);
int confereIdDocHash(TipoListaQntd Lista, int idDoc);