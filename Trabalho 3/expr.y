%{
#include <stdio.h>
#include <stdlib.h>
#include "tabela.h"
#define YYSTYPE struct ListaVetor

%}

%token TADD TMUL TSUB TDIV TAPAR TFPAR TAND TOR TNOT TEQUAL TNEQUAL TBIG TSMALL TBIGEQUAL TSMALLEQUAL TIF TELSE TWHILE TRETURN TLITERAL TSTRING TINT TVOID TREAD TPRINT TDOTCOMA TCOMA TACHA TFCHA TATR TID TNUM TDO


%%
 
Inicio: ListFuncoes BlocoPrincipal
	| BlocoPrincipal
	;
ListFuncoes: ListFuncoes Funcao 
	| Funcao
	;
Funcao: TipoRetorno TID TAPAR DeclParametros TFPAR BlocoPrincipal
	| TipoRetorno TID TAPAR TFPAR BlocoPrincipal
	;
TipoRetorno: Tipo
	| TVOID
	;
DeclParametros: DeclParametros TCOMA Parametro
	| Parametro
	;
Parametro: Tipo TID
	;
BlocoPrincipal: TACHA Declaracoes ListCmd TFCHA
	| TACHA ListCmd TFCHA
	;
Declaracoes: Declaracoes Declaracao
	| Declaracao
	;
Declaracao: Tipo ListId TDOTCOMA {insertTabela($2.lista,$1.tipo);destroiList($$.lista);} 
	;
Tipo: TINT {$$.tipo = INT;}
	| TSTRING {$$.tipo = STRING;}
	;
ListId: ListId TCOMA TID {insertList($1.lista, $3.id);}
	| TID {criaList($$.lista); insertList($$.lista,$1.id);}
	;
Bloco: TACHA ListCmd TFCHA
	;
ListCmd: ListCmd Comando
	| Comando
	;
Comando: CmdSe
	| CmdEnquanto
	| CmdAtrib
	| CmdEscrita
	| CmdIncrementa
	| CmdDecrementa
	| CmdLeitura
	| ChamadaFuncao
	| Retorno
	;
Retorno: TRETURN ExpressaoAritmetica TDOTCOMA 
	;
CmdSe: TIF TAPAR ExpressaoLogica TFPAR Bloco
	| TIF TAPAR ExpressaoLogica TFPAR Bloco TELSE Bloco 
	;
CmdEnquanto: TWHILE TAPAR ExpressaoLogica TFPAR Bloco
	|TDO Bloco TWHILE TAPAR ExpressaoLogica TFPAR TDOTCOMA 
	;
CmdAtrib: TID TATR ExpressaoAritmetica TDOTCOMA
	| TID TADD TATR 
	| TID TATR TLITERAL TDOTCOMA
	| TID TATR ChamadaFuncao
	;
CmdEscrita: TPRINT TAPAR Tipagem TFPAR TDOTCOMA
	;
CmdIncrementa: TID TADD TADD TDOTCOMA
	;
CmdDecrementa: TID TSUB TSUB TDOTCOMA
	;
CmdLeitura: TREAD TAPAR TID TFPAR TDOTCOMA
	;
ChamadaFuncao: TID TAPAR ListParametros TFPAR TDOTCOMA
	| TID TAPAR TFPAR TDOTCOMA
	;
ListParametros: ListParametros TCOMA ExpressaoAritmetica
	| ExpressaoAritmetica
	;
ExpressaoAritmetica: ExpressaoAritmetica TADD Termo
	| ExpressaoAritmetica TSUB Termo
	| Termo
	;
Termo: Termo TMUL Fator
	| Termo TDIV Fator
	| Fator
	;
Fator: TID 
	| TAPAR ExpressaoAritmetica TFPAR
	| TSUB Fator
	| TNUM
	;
ExpressaoRelacional:  ExpressaoAritmetica TBIG ExpressaoAritmetica 
	| ExpressaoAritmetica TSMALL ExpressaoAritmetica
	| ExpressaoAritmetica TBIGEQUAL ExpressaoAritmetica
	| ExpressaoAritmetica TSMALLEQUAL ExpressaoAritmetica
	| ExpressaoAritmetica TEQUAL ExpressaoAritmetica
	| ExpressaoAritmetica TNEQUAL ExpressaoAritmetica
	;			
ExpressaoLogica: ExpressaoLogica TAND TermoLogico 
	| ExpressaoLogica TOR TermoLogico
	| TermoLogico
	;
TermoLogico: TNOT TermoLogico
	| TAPAR ExpressaoLogica TFPAR
	| ExpressaoRelacional 
	;
Tipagem: ExpressaoAritmetica
	| TLITERAL
	;


%%
#include "lex.yy.c"
int flag=0;

int yyerror (char *str)
{
	if(flag==0)
		printf("Erro: %s - antes %s\n", str, yytext);
	
} 		 

int yywrap()
{
	flag=1;
	/*printf("Aceito\n");*/
	return 1;
}
