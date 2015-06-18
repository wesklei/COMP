delim	[ \t\n]
ws	{delim}+
digito	[0-9]
letra	[a-zA-Z]
char    [ -~]
num	{digito}+
id      ({letra}|\_)({letra}|{digito}|\_)*
literal \"({char})*\"

%%
{ws}	{}
"+"	{return TADD;}
"-"	{return TSUB;}
"*"	{return TMUL;}
"/"	{return TDIV;}
"("	{return TAPAR;}
")"	{return TFPAR;}
"&&"    {return TAND;}

"||"    {return TOR;}

"=="    {return TEQUAL;}

"!="    {return TNEQUAL;}

"!"     {return TNOT;}

">="	{return TBIGEQUAL;}

"<="    {return TSMALLEQUAL;}

">"     {return TBIG;}

"<"	{return TSMALL;}

"if"    {return TIF;}

"else"	{return TELSE;}

"while"	{return TWHILE;}

"do" {return TDO;}

"return" {return TRETURN;}

"String" {return TSTRING;}

"int"	{return TINT;}

"void"	{return TVOID;}

"read"	{return TREAD;}

"print"	{return TPRINT;}

";"	{return TDOTCOMA;}

","	{return TCOMA;}

"{"	{return TACHA;}

"}"	{return TFCHA;}

"="	{return TATR;}


{id}	{strcpy(yylval.nome,yytext);return TID;}
{num}	{yylval.valor = atoi(yytext); yylval.tipo = INT; return TNUM;}
{literal} {strcpy(yylval.imprimir,yytext);return TLITERAL;}

