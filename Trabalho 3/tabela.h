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

typedef struct ListaVetor
{
	int tipo;
	int valor;
	char id[20];
	int par;
	Lista lista; 
	char imprimir[500];
}ListaVetor;

typedef struct tabSimbolos 
{
	char nomeId[20];
	int pos;
	int tipo;
}simbolos;

