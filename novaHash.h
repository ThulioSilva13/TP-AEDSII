#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "indiceHash.h"

#define M 33
#define Y 13
#define TAMALFABETO 256

/* typedef unsigned int  TipoPesos[n]; */
typedef char TipoPalavra[Y];
typedef unsigned TipoPesos[M][TAMALFABETO];

typedef struct TipoItem
{
    TipoPalavra Chave;
    // TipoListaQntd *qntd;
} TipoItem;

typedef unsigned int TipoIndice;
typedef struct TipoCelula *TipoApontador;
typedef struct TipoCelula
{
    TipoItem ItemH;
    TipoListaQntd *lista_ocorrencias;
    TipoApontador Proximo;
} TipoCelula;
typedef struct TipoLista
{
    TipoCelula *Primeiro, *Ultimo;
} TipoLista;

typedef TipoLista TipoDicionario[M]; 

void InicializaListaVazia(TipoLista *Lista);
short VaziaHash(TipoLista Lista);
void InsereHash(int idDoc, char *chave, TipoLista *Lista);
void GeraPesos(TipoPesos peso);
TipoIndice h(TipoPalavra Chave, TipoPesos peso);
void InicializaDicionario(TipoDicionario dicionario);
void VerificaInsere(int num_arquivo, char *chave, TipoPesos peso, TipoDicionario dicionario);

void ImprimirLista(TipoLista Lista);
void ImprimeTabela(TipoDicionario Tabela);
void BuscaLista(TipoLista Lista);
void BuscaPesquisa(TipoDicionario dicionario, char *buscaPalavra);