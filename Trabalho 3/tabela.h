#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define iadd 100
#define imull 101
#define isub 102
#define idiv 103
#define istore 104
#define iload 105
#define bipush 106
#define iconst_0 107
#define iconst_1 108
#define iconst_2 109
#define iconst_3 110
#define iconst_4 111
#define iconst_5 112
#define if_icmpeq 113 
#define if_icmpne 114 //diferente 
#define if_icmplt 115 
#define if_icmpge 116 
#define if_icmpgt 117 //maior
#define if_icmple 118 
#define getstatic 119
#define invokevirtual 120
#define ireturn 121
#define areturn 122
#define ldc 123
#define READ 124
#define aload 125
#define astore 126
#define invokestatic 127
#define Goto 130
#define lx 99999



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
	int local;
	int funcao;
	char nome[20];
	int listav[10];
	int listaf[10];
	int par;
	Lista lista; 
	char imprimir[500];

}ListaVetor;

typedef struct instrucao
{
	int label;	
	int marca;
	int inst;
	int par1,par2;
	int funcao;
	int tipo;
	char impr[200];
}instrucao;


typedef struct tabSimbolos 
{
	char nomeId[20];
	int pos;
	int tipo;
}simbolos;

