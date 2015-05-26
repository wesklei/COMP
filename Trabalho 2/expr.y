%{
#include <stdio.h>
#include <stdlib.h>
#define YYSTYPE double
%}

%token TADD TMUL TSUB TDIV TAPAR TFPAR TNUM TFIM TMENOR TMAIOR TMAIORIGUAL TMENORIGUAL TIGUALIGUAL TDIFF TNEG TEE TOU

%%
Linha :ExpL TFIM {printf("Resultado:%lf\n", $1);exit(0);}
	;
ExpL: ExpL TEE ExpL
	| ExpL TOU ExpL
	| ExpN
	;
ExpN: TNEG ExpN
	| TAPAR ExpN TFPAR
	| ExpR
	;
ExpR: ExpA TMENOR ExpA
   	| ExpA TMAIOR ExpA
	| ExpA TMAIORIGUAL ExpA
	| ExpA TMENORIGUAL ExpA
	| ExpA TIGUALIGUAL ExpA
	| ExpA TDIFF ExpA
	;
ExpA: ExpA TADD Termo {$$ = $1 + $3;}
	| ExpA TSUB Termo {$$ = $1 - $3;}
	| Termo
	;
Termo: Termo TMUL Fator {$$ = $1 * $3;}
	| Termo TDIV Fator {$$ = $1 / $3;}
	| Fator
	;
Fator: TNUM 
	| TAPAR ExpA TFPAR {$$ = $2;}
	;
%%
#include "lex.yy.c"

int yyerror (char *str)
{
	printf("%s - antes %s\n", str, yytext);
	
} 		 

int yywrap()
{
	return 1;
}
