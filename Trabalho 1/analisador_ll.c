/*****************************************************************
 * Analisador Sintatico LL(1)                                     *
 * Exemplo p/ Disciplina de Compiladores                          *
 * Cristiano Damiani Vasconcellos                                 *
 ******************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

/* Nao terminais o bit mais significativo ligado indica que se trata de um nao
   terminal */
#define EXPR_A   0x8001
#define EXPR_AL  0x8002
#define EXPR_B  0x8003
#define EXPR_BL 0x8004
#define EXPR_C  0x8005
#define EXPR_CL  0x8006
#define EXPR_D  0x8007

/* Terminais */
#define ERRO 0x0000
#define BIIMP     0x0100
#define IMPLI    0x0200
#define LOG_E 0X0300
#define LOG_OU    0x0400
#define LOG_NEG	0x0500
#define APAR   0x0600
#define FPAR   0x0700
#define CONST  0x0800
#define FIM    0x0900

//Mascaras
#define NTER   0x8000
#define NNTER  0x7FFF

#define TAMPILHA 100


struct Pilha {
	int topo;
	int dado[TAMPILHA];
};

/* Producoes a primeira posicao do vetor indica quantos simbolos
   gramaticais a producao possui em seu lado direito */

const int PROD1[] = {2, EXPR_B, EXPR_AL};        // A  -> BA'
const int PROD2[] = {3, BIIMP, EXPR_B, EXPR_AL};    // A' -> <->BA'
const int PROD3[] = {0};   // A' -> vazio
const int PROD4[] = {2, EXPR_C,EXPR_BL};   // B -> CB'
const int PROD5[] = {3, IMPLI, EXPR_C, EXPR_BL}; // B' -> ->CB'
const int PROD6[] = {0};       // B'  -> vazio'
const int PROD7[] = {2, EXPR_D, EXPR_CL };  // C -> DC'
const int PROD8[] = {3, LOG_E, EXPR_D, EXPR_CL};  // C' -> ^DC'
const int PROD9[] = {3, LOG_OU, EXPR_D, EXPR_CL}; // C' -> vDC'
const int PROD10[] = {0};               // C'  -> vazio
const int PROD11[]= {2, LOG_NEG, EXPR_D};    // D  -> ~D
const int PROD12[]= {3, APAR, EXPR_A, FPAR};    // D  -> (A)
const int PROD13[]= {1, CONST};    // D  -> c

// vetor utilizado para mapear um numero e uma producao.
const int *PROD[] = {NULL, PROD1, PROD2, PROD3, PROD4, PROD5, PROD6, PROD7, PROD8, PROD9, PROD10, PROD11, PROD12, PROD13};

// Tabela sintatica LL(1). Os numeros correspondem as producoes acima.
const int STAB[7][10] = {	
	{ 0, 0, 0, 0, 1, 1, 0, 1, 0},
	{ 2, 0, 0, 0, 0, 0, 3, 0, 3},
	{ 0, 0, 0, 0, 4, 4, 0, 4, 0},
	{ 6, 5, 0, 0, 0, 0, 6, 0, 6},
	{ 0, 0, 0, 0, 7,7, 0, 7, 0},
	{ 10, 10, 8, 9, 0,0, 10, 0, 10},
	{ 0, 0, 0, 0, 11,12, 0, 13, 0}};

/*****************************************************************
 * int lex (char *str, int *pos)                                  *
 * procura o proximo token dentro de str a partir de *pos,incre-  *
 * menta o valor de *pos a medida que faz alguma tranzicao de     *
 * estados.                                                       *
 * Retorna o inteiro que identifica o token encontrado.           *
 ******************************************************************/

int lex (char *str, int *pos)
{
	int estado = 0;
	char c;

	while (1)
	{
		c =  str[*pos];

		switch(estado)
		{
			case 0:
				if (isdigit(c))
				{
					(*pos)++;
					estado = 1;
				}
				else
					switch (c)
					{
						case ' ':
							(*pos)++;
							break;
						case '.':
							(*pos)++;
							estado = 2;
							break;
						case '<': //equivalente ao <->
							(*pos)++;
							return BIIMP;
						case '>': //equivalente ao ->
							(*pos)++;
							return IMPLI;
						case '^':
							(*pos)++;
							return LOG_E;
						case 'v':
							(*pos)++;
							return LOG_OU;
						case '~': 
							(*pos)++;
							return LOG_NEG;
						case '(':
							(*pos)++;
							return APAR;
						case ')':
							(*pos)++;
							return FPAR;
						case 'c':
							(*pos)++;
							return CONST;
						case '\0':
							return FIM;
						default:
							(*pos)++;
							return ERRO;
					}
				break;
			case 1:
				if(isdigit(c))
					(*pos)++;
				else
					if (c == '.')
					{
						estado = 3;
						(*pos)++;
					}
					else
					{
						//Adicionar constante na tabela de simbolos.
						return CONST;
					}
				break;
			case 2:
				if (isdigit(c))
				{
					(*pos)++;
					estado = 3;
				}
				else
				{
					(*pos)++;
					return ERRO;
				}
				break;
			case 3:
				if (isdigit(c))
					(*pos)++;
				else
				{
					//Adicionar a constante na tabela de simbolos.
					return CONST;
				}
				break;
			default:
				printf("Lex:Estado indefinido");
				exit(1);
		}
	}
}

/*****************************************************************
 * void erro (char *erro, char *expr, int pos)                    *
 * imprime a mensagem apontado por erro, a expressao apontada por *
 * expr, e uma indicacao de que o erro ocorreu na posicao pos de  *
 * expr. Encerra a execucao do programa.                          *
 ******************************************************************/

void erro (char *erro, char *expr, int pos)
{
	int i;
	printf("%s", erro);
	printf("\n%s\n", expr);
	for (i = 0; i < pos-1; i++)
		putchar(' ');
	putchar('^');
	printf("\n");
	exit(1);
}

/*****************************************************************
 * void inicializa(struct Pilha *p)                               *
 * inicializa o topo da pilha em -1, valor que indica que a pilha *
 * esta vazia.                                                    *
 ******************************************************************/

void inicializa(struct Pilha *p)
{
	p->topo = -1;
}

/*****************************************************************
 * void insere (struct Pilha *p, int elemento                     *
 * Insere o valor de elemento no topo da pilha apontada por p.    *
 ******************************************************************/

void insere (struct Pilha *p, int elemento)
{
	if (p->topo < TAMPILHA)
	{
		/* printf("ele %x\n",elemento); */
		p->topo++;
		p->dado[p->topo] = elemento;
	}
	else
	{
		printf("estouro de pilha %d\n", p->topo);
		exit (1);
	}
}

/*****************************************************************
 * int remover (struct Pilha *p)                                  *
 * Remove e retorna o valor armazenado no topo da pilha apontada  *
 * por p                                                          *
 ******************************************************************/

int remover (struct Pilha *p)
{
	int aux;

	if (p->topo >= 0)
	{
		aux = p->dado[p->topo];
		p->topo--;
		return aux;
	}
	else
	{
		printf("Pilha vazia");
		exit(1);
	}
	return 0;
}

/*****************************************************************
 * int consulta (struct Pilha *p)                                 *
 * Retorna o valor armazenado no topo da pilha apontada por p     *
 ******************************************************************/


int consulta (struct Pilha *p)
{
	if (p->topo >= 0)
		return p->dado[p->topo];
	printf("Pilha vazia");
	exit(1);
}

/*****************************************************************
 * void parser (char *expr)                                       *
 * Verifica se a string apontada por expr esta sintaticamente     *
 * correta.                                                       *
 * Variaveis Globais Consultadas: STAB e PROD                     *
 ******************************************************************/


void parser(char *expr)
{
	struct Pilha pilha;
	int x, a, nProd, i, *producao;
	int pos = 0;

	inicializa(&pilha);
	insere(&pilha, FIM);
	insere(&pilha, EXPR_A);
	if ((a = lex(expr, &pos)) == ERRO)
		erro("Erro lexico", expr, pos);
	do
	{
		x = consulta(&pilha);
		if (!(x&NTER))
		{
			if (x == a)
			{
				remover (&pilha);
				if ((a = lex(expr, &pos)) == ERRO)
					erro("Erro lexico", expr, pos);
			}
			else
				erro("Erro sintatico",expr, pos);
		}
		if (x&NTER)
		{
			nProd = STAB[(x&NNTER)-1][(a>>8) - 1];
			if (nProd)
			{
				remover (&pilha);
				producao = PROD[nProd];
				for (i = producao[0]; i > 0; i--)
					insere (&pilha, producao[i]);
			}
			else
				erro ("Erro sintatico", expr, pos);
		}
	} while (x != FIM);
}

void main()
{
	char expr[100];

	printf("\nDigite uma expressao: ");
	gets(expr);
	parser(expr);
	printf("Expressao sintaticamente correta");
	printf("\n");
}
