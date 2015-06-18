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
ListId: ListId TCOMA TID {insertList($1.lista, $3.nome);}
	| TID {criaList($$.lista); insertList($$.lista,$1.nome);}
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
CmdAtrib: TID TATR ExpressaoAritmetica TDOTCOMA  {if(buscaTipo($1.nome)==buscaTipo($3.nome)){gerar(istore,buscaNome($1.nome));}else{erro();}}
	| TID TADD TATR {gerar(iload,buscaNome($1.nome));} ExpressaoAritmetica TDOTCOMA {gerar(iadd,-1); if(buscaTipo($1.nome)==buscaTipo($3.nome)){gerar(istore,buscaNome($1.nome));}else{erro();}}
	| TID TATR TLITERAL TDOTCOMA {if(buscaTipo($1.nome)==buscaTipo($3.nome)){gerarString(ldc,$3.imprimir);gerar(astore,buscaNome($1.nome));}else{erro();}}
	| TID TATR ChamadaFuncao
	;
CmdEscrita: TPRINT P TAPAR Tipagem TFPAR TDOTCOMA {if(buscaTipo($4.nome)==STRING){gerarString(invokevirtual,"java/io/PrintStream/println(Ljava/lang/String;)V");} else{ gerarString(invokevirtual,"java/io/PrintStream/println(I)V");}} 


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
ExpressaoAritmetica: ExpressaoAritmetica TADD Termo {if ($1.tipo==$3.tipo && $1.tipo==0){gerar(iadd,-1);}else{erro();}}
	| ExpressaoAritmetica TSUB Termo {if ($1.tipo==$3.tipo && $1.tipo==0){gerar(isub,-1);}else{erro();}}

	| Termo
	;
Termo: Termo TMUL Fator {if ($1.tipo==$3.tipo && $1.tipo==0){gerar(imull,-1);}else{erro();}}
	| Termo TDIV Fator {if ($1.tipo==$3.tipo && $1.tipo==0){gerar(idiv,-1);}else{erro();}}

	| Fator
	;
Fator: TID  {if((buscaTipo($1.nome))==INT){gerar(iload,buscaNome($1.nome));}else{gerar(aload,buscaNome($1.nome));}}
	| TAPAR ExpressaoAritmetica TFPAR
	| TSUB Fator
	| TNUM {switch($1.valor){
            	case 0: gerar(iconst_0,-1); break;
           	case 1: gerar(iconst_1,-1); break;
            	case 2: gerar(iconst_2,-1); break;
            	case 3: gerar(iconst_3,-1); break;
            	case 4: gerar(iconst_4,-1); break;
            	case 5: gerar(iconst_5,-1); break;
		default: gerar(bipush,$1.valor);
		}break;}
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

M: {$$.par = novoLabel();}
	;
Tipagem: ExpressaoAritmetica {$$.tipo=INT;}
	| TLITERAL {gerarString(ldc,$1.imprimir);$$.tipo=STRING;}
	;
P: {gerar(getstatic,-1);}

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
