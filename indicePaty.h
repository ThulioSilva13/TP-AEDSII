#include <stdio.h>
#include <stdlib.h>

typedef struct ItemIndicePat
{
    int qntd_repete;
    int idDoc;
} ItemIndicePat;

typedef struct CelIndicePat *ApIndicePat;

typedef struct CelIndicePat
{
    ItemIndicePat Item;
    ApIndicePat Prox;
} CelIndicePat;

typedef struct ListaIndicePat
{
    ApIndicePat Primeiro, Ultimo;
} ListaIndicePat;

void FazListaIndiceVazia_Pat(ListaIndicePat *Lista);
int VaziaIndice_Pat(ListaIndicePat Lista);
void InsereIndice_Pat(int idDoc, int qntd_repete, ListaIndicePat *Lista);
void ImprimeIndicePatricia(ListaIndicePat Lista);
void BuscaIndice(ListaIndicePat Lista, char *valor_busca);
// void InsereQntd(int idDoc, int qntd_repete, TipoListaQntd *Lista);
// void ImprimeQntd(TipoListaQntd Lista);