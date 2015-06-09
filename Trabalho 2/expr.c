#include <stdio.h>

extern FILE *yyin;

int main(int argc, char **argv)
{
	/* yyin = stdin; */
	/* printf("Digite uma expressão:"); */
	/* yyparse(); */
	/* return 0; */
	
	if((yyin=fopen(argv[1],"r")) == NULL)
	{
		printf("Erro! Informe um arquivo!\n");
		return 0;
	}
	else{
		yyparse();
		fclose(yyin);
		return 0;
	}
}

