#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define VOID -1
#define INT 0
#define STRING 1
#define SUCESSO 1
#define FRACASSO 0

typedef struct Lista
{
	int quant;
}Lista;

typedef struct atributo
{
	int tipo;
	int valor;
	char nome[20];
	Lista lista; 
	char imprimir[500];
}atributo;

typedef struct tabSimbolos 
{
	char nomeId[20];
	int pos;
	int tipo;
}simbolos;

void criaLista(Lista lista);
int insereLista(Lista lista,char *yytext);
int buscaLista(Lista lista,void *elemento,int posicao);
void destroiLista(Lista lista);
int insereTabSimbolos(Lista lista, int tipo);
int novoLabel();
void merge(int origem1[],int origem2[], int destino[]);
void atribui(int destino[],int origem[]);
void corrigir(int *list, int par);
void inserirListavf(int listav[],int listaf[]);
int buscaNome(char *nome);
int consulta(char *yytext);
void insereParametro(int tipo,char *nome);
void insereFuncao(char *nome, int tipoRetorno);
int conta(int contador);
int buscaTipo(char *nome);
void comparaFuncao(char *nome);
void listaParametros(int tipo,char *nome);

