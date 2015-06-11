#include <stdio.h>
#include <stdlib.h>
#include "tabela.h"

extern FILE *yyin;

simbolos tabSimb[500];
atributo listaVet[500];
int cont=0,contLista=0,contCod=0;
int contLabel=0,contFuncao=0;
int contParametros=0;
int contar=0;
int funcaoPar=0,contPar=0;
int posicao,contTeste=0,contCont=0;

void teste(){
	int i;
	printf("\n\n\n\n\nTestando:\n\n\n");
	
	for(i=0;i<contTeste;i++)
	{
		printf("\nnomeId: %s",tabSimb[i].nomeId);
		printf("       tipo: %s",tabSimb[i].tipo == 285 ? "int" : "string");
		printf("        pos: %d",tabSimb[i].pos);
	}
	printf("\n");
}
int main(int argc, char **argv)
{	

	if(argc!=2)	
	{
	    printf("Falta parametros!\n");	
	    return 0;
	}
	else
	{	
	    	if((yyin = fopen (argv[1],"r"))==NULL)
		{
		 	printf("Erro ao abrir o arquivo!\n");
			return 0;
		}
		else{    		
			yyparse();
			teste();
	    		fclose(yyin);
	    		return 0;
		}
	}
}

void criaLista(Lista lista)//funcao q so inicializa quant com '0'
{  	
	lista.quant = 0;
}

int insereLista(Lista lista,char *yytext)//insere em um vetor de atributos o nome da variavel declarada no programa, incrementa uma variavel global, para saber o numero de variaveis existem no programa
{		
	strcpy(listaVet[contLista].nome, yytext);  	
	printf("inser => %s\n" , yytext);
	contLista++;
	return SUCESSO;
}

int listaQuant(Lista lista) //passa o valor de variaveis para a variavel quant e retorna esse valor
{   	
	lista.quant = contLista;		
	return lista.quant;
}

int buscaLista(Lista lista, void *elemento, int posicao)//procura no vetor na posição passada e copia para elemento
{
    //Verifica se lista não esta vazia e se a posicao existe
    if(listaQuant(lista) == 0 || listaQuant(lista)>posicao)
        return FRACASSO; //Sai fora
    else{
	strcpy(elemento,listaVet[posicao].nome);
    	return SUCESSO; 
    }
}


int insereTabSimbolos(Lista lista, int tipo)//insere o nome das variaveis, o tipo delas e um valor de posição
{
	
	int i;
	
	if(contPar!=0)
	{
		contTeste = (listaQuant(lista)+contPar);
		for(i=contPar; i <contTeste; i++)
		{
			buscaLista(lista, &listaVet[cont].nome, cont);		
			printf("coipou => %s\n" , listaVet[cont].nome);
			strcpy(tabSimb[i].nomeId, listaVet[cont].nome);	
			tabSimb[i].tipo = tipo;
			tabSimb[i].pos = i;
			cont++;
		}
	}
	else
	{	contTeste =  listaQuant(lista);
		for(i=cont; i < listaQuant(lista); i++)
		{     
			buscaLista(lista, &listaVet[cont].nome, cont);
			strcpy(tabSimb[i].nomeId, listaVet[cont].nome);	
			printf("coipou2 =>  %s => pos %d\n" , listaVet[cont].nome, i);
			tabSimb[i].tipo = tipo;
			tabSimb[i].pos = i;
			cont++;
		}
	}

	return SUCESSO;
}
void destroiLista(Lista lista)//so atribui '0' pra quant, se for preciso eh so sobreescrever o vetor
{		
	lista.quant=0;
}


void erro()//função que imprime erro se os tipos das variaveis forem diferentes, na hora de fazer operações entre elas
{
	printf("\n Operacao com tipos invalidos \n");
	exit(1);
}


		
