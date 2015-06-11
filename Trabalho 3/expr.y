%{
#include <stdio.h>
#include <stdlib.h>
#include "tabela.h"
#define YYSTYPE struct atributo

%}

%token TADD TMUL TSUB TDIV TAPAR TFPAR TNUM TFIM TMENOR TMAIOR TMAIORIGUAL TMENORIGUAL TIGUALIGUAL TDIFF TNEG TEE TOU TIF TELSE TWHILE TRETURN TPRINTF TPTVIRGULA TVIRGULA TACHAVES TREAD TFCHAVES TINT TSTRING TATRIBUIC TVOID TTEXTO TID

%%
Inicio: ExpFuncao ExpBlocoPrincipal
	| ExpBlocoPrincipal
	;
ExpFuncao: ExpFuncao ExpTFuncao
	| ExpTFuncao
	;
ExpTFuncao: ExpTRetorno TID TAPAR ExpParams TFPAR ExpBlocoPrincipal 
	| ExpTRetorno TID TAPAR TFPAR ExpBlocoPrincipal
	;
ExpBloco: TACHAVES ExpListaCmd TFCHAVES
	;
ExpTRetorno: ExpTipo 
	| TVOID
	;
ExpParams: ExpParams TVIRGULA ExpTParams
	| ExpTParams
	;
ExpTParams: ExpTipo TID  
	;
ExpBlocoPrincipal: TACHAVES ExpVariaveis ExpListaCmd TFCHAVES
	| TACHAVES ExpListaCmd TFCHAVES
	;
ExpVariaveis: ExpVariaveis ExpTVariavel
	| ExpTVariavel
	;
ExpTVariavel: ExpTipo ExpListaID TPTVIRGULA {insereTabSimbolos($2.lista,$1.tipo);destroiLista($$.lista);}  
	;
ExpTipo: TINT {$$.tipo = TINT;}
	| TSTRING {$$.tipo = TSTRING;}
	;
ExpListaID: ExpListaID TVIRGULA TID {insereLista($1.lista, $3.nome);}
	| TID  {criaLista($$.lista); insereLista($$.lista,$1.nome);}
	;
ExpListaCmd: ExpListaCmd ExpComando
	| ExpComando
	;
ExpComando: CmdSe
	| ExpWhile
	| ExpAtribuic
	| ExpPrintf
	| ExpRead
	| ExpChamaFunc
	| ExpReturn
	;
ExpReturn: TRETURN ExpA TPTVIRGULA
	;
CmdSe: TIF TAPAR ExpL TFPAR ExpBloco
	| TIF TAPAR ExpL TFPAR ExpBloco TELSE ExpBloco
	;
ExpWhile: TWHILE TAPAR ExpL TFPAR ExpBloco
	;
ExpAtribuic: TID TATRIBUIC ExpA TPTVIRGULA 
	| TID TATRIBUIC TTEXTO TPTVIRGULA  
	;
ExpPrintf: TPRINTF TAPAR ExpA TFPAR TPTVIRGULA
	| TPRINTF TAPAR TTEXTO TFPAR TPTVIRGULA
	;
ExpRead: TREAD TAPAR TID TFPAR TPTVIRGULA 
	;
ExpChamaFunc: TID TAPAR ExpFuncParams TFPAR TPTVIRGULA
	| TID TAPAR TFPAR TPTVIRGULA 
	;
ExpFuncParams: ExpFuncParams TVIRGULA ExpA
	| ExpA
	;

ExpL: ExpL TEE ExpN 
	| ExpL TOU ExpN 
	| ExpN
	;
ExpN: TNEG ExpN 
	| ExpR
	;
ExpR: ExpA TMENOR ExpA 
   	| ExpA TMAIOR ExpA 
	| ExpA TMAIORIGUAL ExpA 
	| ExpA TMENORIGUAL ExpA 
	| ExpA TIGUALIGUAL ExpA 
	| ExpA TDIFF ExpA 
	| TAPAR ExpR TFPAR
	;
ExpA: ExpA TADD Termo 
	| ExpA TSUB Termo
	| Termo
	;
Termo: Termo TMUL Fator 
	| Termo TDIV Fator 
	| Fator
	;
Fator: TID  
     	| TNUM 
	| TAPAR ExpA TFPAR 
	| TSUB Fator 
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
