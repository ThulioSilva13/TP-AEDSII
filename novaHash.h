#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#define X 12
#define Y 12
#define TAMALFABETO 256

/* typedef unsigned int  TipoPesos[n]; */
typedef char TipoPalavra[X];
typedef unsigned TipoPesos[X][TAMALFABETO];
typedef struct TipoItem
{
    TipoPalavra Chave;
} TipoItem;
typedef unsigned int TipoIndice;
typedef struct TipoCelula *TipoApontador;
typedef struct TipoCelula
{
    TipoItem ItemH;
    TipoApontador Proximo;
} TipoCelula;
typedef struct TipoLista
{
    TipoCelula *Primeiro, *Ultimo;
} TipoLista;
typedef TipoLista TipoDicionario[Y];

void InicializaListaVazia(TipoLista *Lista);
short VaziaHash(TipoLista Lista);
void InsereHash(TipoItem item, TipoLista *Lista, int num_arquivo);
void GeraPesos(TipoPesos peso);
TipoIndice h(TipoPalavra Chave, TipoPesos peso);
void InicializaDicionario(TipoDicionario dicionario);
TipoApontador Pesquisa(TipoPalavra Chave, TipoPesos peso, TipoDicionario dicionario);
void VerificaInsere(TipoItem item, TipoPesos peso, TipoDicionario dicionario, int num_arquivo);
void ImprimirLista(TipoLista Lista);
void ImprimeTabela(TipoDicionario Tabela);
char *BuscaLista(TipoLista Lista);
char *BuscaTabela(TipoDicionario Tabela);

// TipoApontadorEnc VerificaIgual(char *chave);
