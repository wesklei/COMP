%{
#include <stdio.h>
#include <stdlib.h>
#define YYSTYPE double
%}

%token TADD TMUL TSUB TDIV TAPAR TFPAR TNUM TFIM TMENOR TMAIOR TMAIORIGUAL TMENORIGUAL TIGUALIGUAL TDIFF TNEG TEE TOU

%%
Linha :ExpL TFIM {printf("Aceito\n");exit(0);}
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
Fator: TNUM 
	| TAPAR ExpA TFPAR 
	;
%%
#include "lex.yy.c"

int yyerror (char *str)
{
	printf("Erro: %s - antes %s\n", str, yytext);
	
} 		 

int yywrap()
{
	return 1;
}
