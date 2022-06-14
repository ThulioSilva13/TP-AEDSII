//
// Created by thuli on 09/06/2022.
//

#ifndef TP01AEDSII_HASH_H
#define TP01AEDSII_HASH_H
#define M 7
#define N 7
#define TAMALFABETO 256
typedef char TipoChave[N];
typedef unsigned TipoPesos[N][TAMALFABETO];
typedef struct TipoItem
{
    /* outros componentes */
    TipoChave Chave;
} TipoItem;
typedef unsigned int TipoIndice;
typedef struct TipoCelula* TipoApontador;
typedef struct TipoCelula
{
    TipoItem Item;
    TipoApontador Prox;
} TipoCelula;

typedef struct TipoLista
{
    TipoCelula *Primeiro, *Ultimo;
} TipoLista;

typedef TipoLista TipoTabela[M];
TipoTabela Tabela;
TipoItem Elemento;
TipoPesos peso;
TipoApontador indice;

void FLVazia(TipoLista *Lista);
short Vazia(TipoLista Lista);
void Ret(TipoApontador p, TipoLista *Lista, TipoItem *Item);
void GeraPesos(TipoPesos peso);
TipoIndice h(TipoChave Chave, TipoPesos p);
void Inicializa(TipoTabela Tabela);
TipoApontador Pesquisa(TipoChave Ch, TipoPesos p, TipoTabela Tabela);
void Insere(TipoItem x, TipoPesos p, TipoTabela Tabela);
void Retira(TipoItem x, TipoPesos p, TipoTabela Tabela);
void Imp(TipoLista Lista);
void Imprime(TipoTabela Tabela);
void LerPalavra(char *p, int Tam);


#endif //TP01AEDSII_HASH_H