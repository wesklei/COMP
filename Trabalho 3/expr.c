#include <stdio.h>
#include <stdlib.h>
#include "tabela.h"

extern FILE *yyin;

simbolos tabSimb[500];
instrucao cod[500];
ListaVetor listaVet[500];
int cont=0,contList=0,contCod=0,contLabel=0,contFuncao=0,contParametros=0,contar=0,contPar=0, posicao,contTeste=0,contCont=0;

void teste(){
	int i;
	printf("\n Saida \n");
	char buffer[500];
	for(i=0;i<contCod;i++)
	{

		if (cod[i].par1==1){sprintf(buffer,"%d",cod[i].par2);}
		else{strcpy(buffer,cod[i].impr);}
		switch(cod[i].inst){
			case 100 :{printf("   iadd\n");}break;	
			case 101 :{printf("   imul\n");}break;
			case 102 :{printf("   isub\n");}break;
			case 103 :{printf("   idiv\n");}break;	
			case 104 :{printf("   istore ");printf("%s",buffer);printf("\n");}break;	
			case 105 :{printf("   iload ");printf("%s",buffer);printf("\n");}break;
			case 106 :{printf("   bipush ");printf("%s",buffer);printf("\n");}break;
			case 107 :{printf("   iconst_0\n");}break;
			case 108 :{printf("   iconst_1\n");}break;
			case 109 :{printf("   iconst_2\n");}break;
			case 110 :{printf("   iconst_3\n");}break;
			case 111 :{printf("   iconst_4\n");}break;
			case 112 :{printf("   iconst_5\n");}break;	
			case 113 :{printf("   if_icmpeq l");printf("%s",buffer);printf("\n");}break;		
			case 114 :{printf("   if_icmpne l");printf("%s",buffer);printf("\n");}break;
			case 115 :{printf("   if_icmplt l");printf("%s",buffer);printf("\n");}break;			
			case 116 :{printf("   if_icmpge l");printf("%s",buffer);printf("\n");}break;
			case 117 :{printf("   if_icmpgt l");printf("%s",buffer);printf("\n");}break;
			case 118 :{printf("   if_icmple l");printf("%s",buffer);printf("\n");}break;
				  
			case 119 :{printf("   getstatic java/lang/System/out Ljava/io/PrintStream;\n");}break;
			case 120 :{printf("   invokevirtual ");printf("%s",buffer);printf("\n");}break;
			case 123 :{printf("   ldc ");printf("%s",buffer);printf("\n");}break;
			case 130 :{printf("   goto l");printf("%s",buffer);printf("\n");}break;
			case 99999 :{printf(" l");printf("%s",buffer);printf(":\n");}break;
				  
		}
		
	}


	for(i=0;i<contTeste;i++)
	{
		printf("\nId: %s",tabSimb[i].nomeId);
		printf("       tipo: %d",tabSimb[i].tipo);
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

void criaList(Lista lista)//funcao q so inicializa quant com '0'
{  	
	lista.quant = 0;
}

int insertList(Lista lista,char *yytext)//insere em um vetor de ListaVetors o nome da variavel declarada no programa, incrementa uma variavel global, para saber o numero de variaveis existem no programa
{		
	strcpy(listaVet[contList].nome, yytext);  	
	contList++;
	return SUCESSO;
}

int listaQuant(Lista lista) //passa o valor de variaveis para a variavel quant e retorna esse valor
{   	
	lista.quant = contList;		
	return lista.quant;
}

int buscaList(Lista lista, void *elemento, int posicao)//procura no vetor na posição passada e copia para elemento
{
    //Verifica se lista não esta vazia e se a posicao existe
    if(listaQuant(lista) == 0 || listaQuant(lista)>posicao)
        return FRACASSO; //Sai fora
    else{
	strcpy(elemento,listaVet[posicao].nome);
    	return SUCESSO; 
    }
}

void destroiList(Lista lista)//so atribui '0' pra quant, se for preciso eh so sobreescrever o vetor
{		
	lista.quant=0;
}

int insertTabela(Lista lista, int tipo)//insere o nome das variaveis, o tipo delas e um valor de posição
{
	
	int i;
	
	if(contPar!=0)
	{
		contTeste = (listaQuant(lista)+contPar);
		for(i=contPar; i <contTeste; i++)
		{
			buscaList(lista, &listaVet[cont].nome, cont);		
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
			buscaList(lista, &listaVet[cont].nome, cont);
			strcpy(tabSimb[i].nomeId, listaVet[cont].nome);	
			tabSimb[i].tipo = tipo;
			tabSimb[i].pos = i;
			cont++;
		}
	}

	return SUCESSO;
}

void gerar(int funcao,int posicao)//passa os define's e o label, posicao recebe ou -1 ou um valor gerado pela função novoLabel()
{
	cod[contCod].par1 = 1;//para comparação futura, para a impressao
	cod[contCod].inst = funcao;//recebe o valor do define para impressao posterior
	cod[contCod].par2 = posicao;//recebe o valor do label	
	cod[contCod].funcao = contFuncao;//numero da funcao
	contCod++;
}
//verificar
void gerarString(int funcao,char imprimir[200])//recebe o valor do define de invokevirtual e o q sera impresso
{
	cod[contCod].par1 = 2;
	cod[contCod].inst = funcao;
	cod[contCod].par2 = -1;
	cod[contCod].funcao = contFuncao;
	strcpy(cod[contCod].impr,imprimir);
	contCod++;
}


void erro()//função que imprime erro se os tipos das variaveis forem diferentes, na hora de fazer operações entre elas
{
	printf("\n Operacao com tipos invalidos \n");
	exit(1);
}

int buscaNome(char *nome)//procura na tabela o nome das variaveis e retorna a posicao delas na tabela de Simbolos
{
	int q,i;
	if(contTeste!=0)
	{
		for(q=0;q<contTeste;q++)
		{
			if((strcmp(tabSimb[q].nomeId,nome))==0)
			{   
				return tabSimb[q].pos;
			}	
		}
	}
	else
	{
		for(q=0;q<contPar;q++)
		{	
			if((strcmp(tabSimb[q].nomeId,nome))==0)
			{   
				return tabSimb[q].pos;
			}	
		}	
	}
}

int buscaTipo(char *nome)//procura na tabela o nome das variaveis e retorna a posicao delas na tabela de Simbolos
{
	int q,i;
	if(contTeste!=0)
	{       
		for(q=0;q<contTeste;q++)
		{
			if((strcmp(tabSimb[q].nomeId,nome))==0)
			{   
				return tabSimb[q].tipo;
			}	
		}
	}
	else
	{
		for(q=0;q<contPar;q++)
		{	
			if((strcmp(tabSimb[q].nomeId,nome))==0)
			{   
				return tabSimb[q].tipo;
			}	
		}	
	}	
}	

void corrigir(int *list, int label)
{
	int q=0;
	char bufferAux[200];
	sprintf(bufferAux,"%d",label);
	do{	
		strcpy(cod[list[q]].impr, bufferAux);
		list[q]=-1;
		q++;
	}while(list[q]!=-1);
} 

void atribui(int destino[],int origem[])//funcao de atribuicao
{
	int q;
	for (q=0;q<10;q++){
		destino[q]=origem[q];//listav recebe listaf ou listaf recebe listav
	}
}

int novoLabel()
{
	contLabel++;
	cod[contLabel].label = contLabel;
	gerar(lx, cod[contLabel].label);//passa a funcao do label e o valor do label
	return cod[contLabel].label;//retorna o valor do label
}

void inserirListavf(int listav[],int listaf[])
{
	int q;
	if (listav[9]!=-1 && listaf[9]!=-1){ 
		for (q=0;q<10;q++){
			listav[q]=-1;
			listaf[q]=-1;
		}
	}
	q=0;
	while(listav[q]!=-1){
		q++;	
	}
	listav[q]=contCod;
	q=0;
	while(listaf[q]!=-1){
		q++;	
	}
	listaf[q]=contCod+1;
}
void merge(int origem1[],int origem2[], int destino[])
{
	int q=0,w;
	while(origem1[q]!=-1){
		destino[q]=origem1[q];
		q++;
	}
	w=q;
	while(origem2[w-q]!=-1){
		destino[w]=origem2[w-q];
		w++;
	}
}

