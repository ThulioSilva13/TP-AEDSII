#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "novaHash.h"
#include "indiceInvertido.h"
// #include "qntdEnc.h"

TipoItemEnc itemEnc;
TipoListaEnc listaEnc;

TipoListaQntd listaQntd;

void InicializaListaVazia(TipoLista *Lista)
{
    Lista->Primeiro = (TipoCelula *)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Proximo = NULL;
}

short VaziaHash(TipoLista Lista)
{
    return (Lista.Primeiro == Lista.Ultimo);
}

void InsereHash(TipoItem item, TipoLista *Lista, int num_arquivo)
{
    // printf("Palavra a ser inserida: %s\n", item.Chave);
    // printf("NumArqvs: %d", num_arquivo);

    Lista->Ultimo->Proximo = (TipoCelula *)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Proximo;
    strcpy(Lista->Ultimo->ItemH.Chave, item.Chave);

    //==== insere indice invertido =====
    strcpy(itemEnc.Chave,item.Chave);
    itemEnc.qntd.qntd_repete = 1;
    itemEnc.qntd.idDoc = num_arquivo;
    itemEnc.qntdTotalRepete = 1;
    InsereEnc(itemEnc, &listaEnc);
    printf("=> Palavra inserida!\n");
    Lista->Ultimo->Proximo = NULL;

}
/*
void GeraPesos(TipoPesos p)
{ int i;
  struct timeval semente;
  gettimeofday(&semente, NULL);
  srand((int)(semente.tv_sec + 1000000*semente.tv_usec));
  for (i = 0; i < n; i++)
     p[i] =  1+(int) (10000.0*rand()/(RAND_MAX+1.0));
}

TipoIndice h(TipoChave Chave, TipoPesos p)
{ int i;
  unsigned int Soma = 0;
  int comp = strlen(Chave);
  for (i = 0; i < comp; i++) Soma += (unsigned int)Chave[i] * p[i];
  return (Soma % M);
}
*/

void GeraPesos(TipoPesos peso)
{ /* Gera valores randomicos entre 1 e 10.000 */
    int i, j;
    struct timeval semente;
    /* Utilizar o tempo como semente para a funcao srand() */
    // gettimeofday(&semente, NULL);
    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
    for (i = 0; i < X; i++)
        for (j = 0; j < TAMALFABETO; j++)
            peso[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
}

TipoIndice h(TipoPalavra Chave, TipoPesos peso)
{
    int i;
    unsigned int Soma = 0;
    int comp = strlen(Chave);
    for (i = 0; i < comp; i++)
        Soma += peso[i][(unsigned int)Chave[i]];
    return (Soma % Y);
}

void InicializaDicionario(TipoDicionario dicionario)
{
    int i;
    for (i = 0; i < Y; i++)
        InicializaListaVazia(&dicionario[i]);
}

// =================== OLHAR AQUI !!!!!!!!!!!!!!!!
TipoApontador Pesquisa(TipoPalavra Chave, TipoPesos peso, TipoDicionario dicionario)
{ /* Obs.: TipoApontador de retorno aponta para o item anterior da lista */
    TipoIndice i;
    TipoApontador Apontador;
    TipoApontadorEnc ApontEnc;
    i = h(Chave, peso);
    if (VaziaHash(dicionario[i]))
        return NULL; /* Pesquisa sem sucesso */
    else
    {
        Apontador = dicionario[i].Primeiro;
        // ApontEnc = 
        while (Apontador->Proximo->Proximo != NULL && strncmp(Chave, Apontador->Proximo->ItemH.Chave, sizeof(TipoPalavra)))
            Apontador = Apontador->Proximo;
        if (!strncmp(Chave, Apontador->Proximo->ItemH.Chave, sizeof(TipoPalavra)))
            {
                // Apontador->Proximo->ItemH.qntd_repete += 1;
                // ApontEnc->Prox->Item.qntd.qntd_repete += 1;
                return Apontador;
            }
        else{
            return NULL; /* Pesquisa sem sucesso */
        }
            
    }
}
// repetindo o ninguem por causa de inicio de arquivo
// nao ta printando todos os valores do qntdEnc 
// provavelmente porque ta printando o tamanho da lista encadeada
// entao tem q trocar o print pra printar o tamanho da qntdEncs


// --------> olhar se insere de novo no indice invertido (e se isso acontece, tirar)
// se vier outra palavra repetida, percorre a lista de ocorrencias p fzr os trem la
// TipoApontadorEnc VerificaIgual(char *chave, int num_arquivo){
//     TipoApontadorEnc Aux;
//     TipoApontadorQntd AuxQntd;
//     AuxQntd = listaQntd.Primeiro->Prox;
//     Aux = listaEnc.Primeiro->Prox;

//     while (Aux != NULL)
//     {
//         if (strcmp(chave, Aux->Item.Chave) == 0){
//             // printf("\n======Verifica Igual =========\n");
//             // printf("%s = %s ", chave, Aux->Item.Chave);
//             // casa <1,1>
//             // casa <2,1>
//             if (Aux->Item.qntd.idDoc == num_arquivo){
//                 AuxQntd->Item.qntd_repete += 1;
//             }
//             else{
//                 itemQntd.idDoc = num_arquivo;
//                 itemQntd.qntd_repete = 1;
//                 InsereQntd(itemQntd, &listaQntd);
//             }
        
                

//                 // while (Aux != NULL)
//                 // {
//                 //     // if (strcmp(item.Chave, AuxAp->Item.Chave) == 0)
//                 //     // {
//                 //     if (Aux->Item.qntd.idDoc == num_arquivo)
//                 //     {
//                 //         // AuxAp->Item.qntd.qntd_repete += 1;
//                 //         // AuxQntd->Item.qntd_repete += 1;
//                 //     }
//                 //     // }
//                 //     AuxQntd = AuxQntd->Prox;
//                 // }

//                 // return Aux;
//         }
//         Aux = Aux->Prox;
//         AuxQntd = AuxQntd->Prox;
//     }
//     return NULL;
// }

void VerificaInsere(TipoItem item, TipoPesos peso, TipoDicionario dicionario, int num_arquivo)
{
    // printf("(palavra: %s) peso: (%u)\n", item.Chave, peso);
    if (Pesquisa(item.Chave, peso, dicionario) == NULL){
        // printf("Inserindo: %s\n", item.Chave);
        InsereHash(item, &dicionario[h(item.Chave, peso)], num_arquivo);
    }
    else{ //entra no else se a palavra ja existir na hash
        TipoApontadorEnc Aux;
        TipoApontadorQntd AuxQntd;
        TipoItemQntd itemQntd;
        // TipoListaEnc listaEnc;
        // TipoApontadorEnc

        // printf("\nvalor busca: %s", item.Chave);
        // faz uma funcao IdentificarDocumento e retorna como apontador do indice (se for diferente de nulo, incrementa)
        //pra encontrar o id doc faz la a funcao do print (indice lista apontador aux, se o aux do documento == ao documento q chega)
        // printf("chave chegando")
        // Aux = listaEnc.Primeiro->Prox;
        // AuxQntd = listaQntd.Primeiro->Prox;

        AuxQntd = listaQntd.Primeiro->Prox;
        Aux = listaEnc.Primeiro->Prox;
        printf("-----Chave A: %s ", item.Chave);
        while (Aux != NULL)
        {
            printf("Chave B: %s\n", Aux->Item.Chave);
            if (strcmp(item.Chave, Aux->Item.Chave) == 0)
            {
                if (Aux->Item.qntd.idDoc == num_arquivo)
                {
                    AuxQntd->Item.qntd_repete += 1;
                }
                else
                {
                
                    printf("-----Entrou Else-----\n");
                    printf("-----Aux->Item.qntd.idDoc: %d\n", Aux->Item.qntd.idDoc);
                    printf("-----num_arquivo-: %d\n", num_arquivo);
                    // while (AuxQntd != NULL)
                    // {
                    //     // AuxQntd->Item.
                    // }
                    
                    // printf("entrou else if ------------------\n");
                    // AuxQntd->Item.qntd_repete += 1;
                    itemQntd.idDoc = num_arquivo;
                    itemQntd.qntd_repete = 1;
                    InsereQntd(itemQntd, &listaQntd);
                }
                
                // {
                //     itemQntd.idDoc = num_arquivo;
                //     itemQntd.qntd_repete = 1;
                //     InsereQntd(itemQntd, &listaQntd);
                // }

                // while (Aux != NULL)
                // {
                //     // if (strcmp(item.Chave, AuxAp->Item.Chave) == 0)
                //     // {
                //     if (Aux->Item.qntd.idDoc == num_arquivo)
                //     {
                //         // AuxAp->Item.qntd.qntd_repete += 1;
                //         // AuxQntd->Item.qntd_repete += 1;
                //     }
                //     // }
                //     AuxQntd = AuxQntd->Prox;
                // }

                // return Aux;
            }
            Aux = Aux->Prox;
            AuxQntd = AuxQntd->Prox;
            // int count = 0;
            // if (AuxAp != NULL)
            // {
            // //    printf("%s ", AuxAp->Item.Chave);

            //     // count++;
            //     // printf("%d ", count);

            //     // printf("\n======AUXAP=======\n");
            //     // printf("%s ", AuxAp->Item.Chave);
            //     // printf("%d %d\n", AuxAp->Item.qntd.qntd_repete, AuxAp->Item.qntd.idDoc);
            //     while (AuxQntd != NULL)
            //     {
            //         // if (strcmp(item.Chave, AuxAp->Item.Chave) == 0)
            //         // {
            //             if (AuxQntd->Item.idDoc == num_arquivo)
            //             {
            //                 // AuxAp->Item.qntd.qntd_repete += 1;
            //                 AuxQntd->Item.qntd_repete += 1;
            //             }
            //         // }
            //         AuxQntd = AuxQntd->Prox;
            //     }

            //     // AuxAp = AuxAp->Prox;
            // }
        
            /* code */
        
        
        // while (Aux != NULL)
        // {
            // if (strcmp(item.Chave, Aux->Item.Chave) == 0){
                

            // }
            // printf("\n=========== comeca =========\n");
            // printf("\npalavra Chegando: %s\n", item.Chave);
            // printf("idDoc Chegando: %d\n", num_arquivo);
            // printf("AuxQntd->Item.idDoc: %d\n", AuxQntd->Item.idDoc);

            // printf("chave: %s\n", item.Chave);
            // printf("aux chave: %s", Aux->Item.Chave);
            
            // if (strcmp(item.Chave, Aux->Item.Chave) == 0){
            //     if (Aux->Item.qntd.idDoc == num_arquivo)
            //     {
            //         printf("entra iffffffffffffffffffffffffffffff");
            //         AuxQntd->Item.qntd_repete += 1;
            //         // Aux->Item.qntd.qntd_repete += 1;
            //         // return;
            //         //
            //     }
                //  AuxQntd->Item.qntd_repete += 1;
            // }
            
            // else{
            //     if (strcmp(item.Chave, Aux->Item.Chave) == 0){
            //         itemQntd.idDoc = num_arquivo;
            //         itemQntd.qntd_repete = 1;
            //         InsereQntd(itemQntd, &listaQntd);
            //     }
            // }
            // AuxQntd = AuxQntd->Prox;
            // else
            // {
            //     itemQntd.idDoc = num_arquivo;
            //     itemQntd.qntd_repete = 1;
            //     InsereQntd(itemQntd, &listaQntd);
        }
    }

            // {
            //     //   printf("entra!!!!!!!!!!!!");
            //     // Aux->Item.qntdTotalRepete+=1;
            //     // qntdRepeteTOTAL = Aux->Item.qntdTotalRepete;
            //     // printf("qntdRepeteTotal: %d\n", qntdRepeteTOTAL);
                
            //         // AuxQntd->Item.qntd_repete += 1;
                   
            //     // else{
            //     //     strcpy(itemEnc.Chave, Aux->Item.Chave);
            //     //     itemEnc.qntd.qntd_repete = 1;
            //     //     itemEnc.qntd.idDoc = num_arquivo;

            //     //     InsereEnc(itemEnc, &listaEnc); //[ ]
            //     //     // }
            //     //         // return;
            //     // }
            //     return;
            // }
            
            // AuxQntd = AuxQntd->Prox;
            //   

            //     // if(AuxQntd->Item.qntd_repete > 1 ){
            //     //     Aux = Aux->Prox;
            //     //     AuxQntd = AuxQntd->Prox;
            //     // }

            //     // Aux->Item.qntdTotalRepete += 1;
            //     // qntdRepeteTOTAL = itemEnc.qntdTotalRepete;
            //     // printf("qntdTotal %d ", qntdRepeteTOTAL);
            //     if (AuxQntd->Item.idDoc == num_arquivo)
            //     {
            //         // AuxQntd->Item.qntd_repete += 1;
            //         if (AuxQntd != NULL)
            //         {
            //             AuxQntd->Item.qntd_repete += 1;
            //         }
            //     }
            //     else
            //     {
            //         // while (qntdRepeteTOTAL != 1)
            //         // {
            //         //     // while (Aux->Prox != NULL)
            //         //     // {
            //         //         if (strcmp(item.Chave, Aux->Prox->Item.Chave) == 0){
            //         //             strcpy(chave, Aux->Prox->Item.Chave);
            //         //             qntdRepeteTOTAL--;
            //         //         }
            //         //     // }
                        
            //         // }
            //         printf("chave: %s", chave);
            //         strcpy(itemEnc.Chave, Aux->Item.Chave);
            //         itemEnc.qntd.qntd_repete = 1;
            //         itemEnc.qntd.idDoc = num_arquivo;

            //         InsereEnc(itemEnc, &listaEnc); //[ ]
            //     }
            //     return;
            // }
            // else{
                
            // }
            
               
            
            
            // else
            // {
            //             //se forem de arquivos DIFERENTES
            //             //
            //             strcpy(itemEnc.Chave, Aux->Item.Chave);
            //             itemEnc.qntd.qntd_repete =  1;
            //             itemEnc.qntd.idDoc = num_arquivo;

            //             InsereEnc(itemEnc, &listaEnc); //[ ]
            // }

                

                // if (strcmp(item.Chave, Aux->Item.Chave) == 0) // verifica se a palavra esta sendo repetida no INDICE invertido
                // {
                //     // printf("Chave: %s\n", Aux->Item.Chave);
                //     // printf("AuxQntdItem = %d\n", AuxQntd->Item.idDoc);
                //     // printf("itemEncQntd = %d\n ", itemEnc.qntd.idDoc);

                //     // printf("AuxQntdItem - Repete = %d\n", AuxQntd->Item.qntd_repete);
                //     // printf("itemEncQntd - Repete = %d\n ", itemEnc.qntd.qntd_repete);

                //     // printf("numero_arquivoInsere = %d\n ", num_arquivo);

                //     // se as mesmas palavras são do MESMO arquivo, entra no if:
                //     if (AuxQntd->Item.idDoc == num_arquivo)
                //     {
                //         // incrementa dizendo que repete NESSE ARQUIVO ESPECIFICO
                //         AuxQntd->Item.qntd_repete += 1;
                //         // printf("\nchave: %s, repete: %d", Aux->Item.Chave, AuxQntd->Item.qntd_repete);
                //     }
                //     else{
                //         //se forem de arquivos DIFERENTES
                //         //
                //         strcpy(itemEnc.Chave, Aux->Item.Chave);
                //         itemEnc.qntd.qntd_repete =  1;
                //         itemEnc.qntd.idDoc = num_arquivo;

                //         InsereEnc(itemEnc, &listaEnc); //[ ]
                //     }

                //     return;
                // }
                // else
                // {
                //     Aux = Aux->Prox;
                //     AuxQntd = AuxQntd->Prox;
                // }
            
        // printf(" Registro ja  esta  presente: %s\n", item.Chave);
}
        


// void Retira(TipoItem item, TipoPesos peso, TipoDicionario dicionario)
// {
//     TipoApontador Apontador;
//     Apontador = Pesquisa(item.Chave, peso, dicionario);
//     if (Apontador == NULL)
//         printf(" Registro nao esta  presente\n");
//     else
//         Ret(Apontador, &dicionario[h(item.Chave, peso)], &item);
// }
// char* BuscaIndice(TipoLista Lista)
// {
//     TipoApontador ApontadorAux;
//     ApontadorAux = Lista.Primeiro->Proximo;
//     while (ApontadorAux != NULL)
//     {
//         // printf("|%.*s|", X, ApontadorAux->Item.Chave);
//         ApontadorAux->ItemH.Chave;
//         ApontadorAux = ApontadorAux->Proximo;    
//     }
//     TipoApontadorEnc Aux;
//     TipoApontadorQntd AuxQntd;
//     TipoItemQntd itemQntd;

//     Aux = listaEnc.Primeiro->Prox;
//     AuxQntd = listaQntd.Primeiro->Prox;

//     while (Aux != NULL)
//     {
//         int count = 0;
//         if (strcmp(item.Chave, Aux->Item.Chave) == 0)
//         {
//             if (AuxQntd->Item.idDoc == num_arquivo)
//             {
//                 if (AuxQntd != NULL)
//                 {
//                     AuxQntd->Item.qntd_repete += 1;
//                 }
//             }
//             else
//             {
//                 strcpy(itemEnc.Chave, Aux->Item.Chave);
//                 itemEnc.qntd.qntd_repete = 1;
//                 itemEnc.qntd.idDoc = num_arquivo;

//                 InsereEnc(itemEnc, &listaEnc); //[ ]
//             }
//             return;
//         }
//         else
//         {
//             Aux = Aux->Prox;
//             AuxQntd = AuxQntd->Prox;
//         }
//     }
// }
char* BuscaLista(TipoLista Lista)
{
    TipoApontador ApontadorAux;
    ApontadorAux = Lista.Primeiro->Proximo;
    while (ApontadorAux != NULL)
    {
        // printf("|%.*s|", X, ApontadorAux->Item.Chave);
        ApontadorAux->ItemH.Chave;
        ApontadorAux = ApontadorAux->Proximo;    
    }
}
// char* BuscaTabela(TipoDicionario Tabela)
// {
//     int i;
//     for (i = 0; i < Y; i++)
//     {
//         // printf("%d: ", i);
//         if (!Vazia(Tabela[i]))
//         { 
//             printf("teste")
//             BuscaLista(Tabela[i]);
//         }
//         // putchar('\n');
//     }
// }

void ImprimirLista(TipoLista Lista)
{
    TipoApontador ApontadorAux;
    ApontadorAux = Lista.Primeiro->Proximo;

    while (ApontadorAux != NULL)
    {
        printf("|%.*s|", X, ApontadorAux->ItemH.Chave);
        ApontadorAux = ApontadorAux->Proximo;
    }
    
}

void ImprimeTabela(TipoDicionario Tabela)
{
    int i;
    for (i = 0; i < Y; i++)
    {
        printf("%d : ", i);
        if (!VaziaHash(Tabela[i]))
            {
                ImprimirLista(Tabela[i]);
            }
            
        putchar('\n');
    }
}

// void LerPalavra(char *p, int Tam)
// {
//     char c;
//     int i, j;
//     fflush(stdin);
//     j = 0;
//     while (((c = getchar()) != '\n') && j < Tam - 1)
//         p[j++] = c;
//     p[j] = '\0';
//     while (c != '\n')
//         c = getchar();
//     /* Desconsiderar espacos ao final
//       da cadeia como ocorre em Pascal.*/
//     for (i = j - 1; (i >= 0 && p[i] == ' '); i--)
//         p[i] = '\0';
// }