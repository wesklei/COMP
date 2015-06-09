caracter [a-zA-Z]
char    [ -~]
delim	[ \t\n]
ws	{delim}+
digito	[0-9]
num	{digito}+
texto \"(char)*\"
id      ({caracter}|\_)({caracter}|{digito}|\_)*

%%
{ws}	{}
"+"	{return TADD;}
"-"	{return TSUB;}
"*"	{return TMUL;}
"/"	{return TDIV;}
"("	{return TAPAR;}
")"	{return TFPAR;}
"<"	{return TMENOR;}
">"	{return TMAIOR;}
">="	{return TMAIORIGUAL;}
"<="	{return TMENORIGUAL;}
"=="	{return TIGUALIGUAL;}
"!="	{return TDIFF;}
"!"	{return TNEG;}
"&&"	{return TEE;}
"||"	{return TOU;}

"else"	{return TELSE;}
"while"	{return TWHILE;}
"return" {return TRETURN;}
"string" {return TSTRING;}
"int"	{return TINT;}
"void"	{return TVOID;}
"printf" {return TPRINTF;}
";"	{return TPTVIRGULA;}
","	{return TVIRGULA;}
"{"	{return TACHAVES;}
"}"	{return TFCHAVES;}
"="	{return TATRIBUIC;}

\n	{return TFIM;}
{texto} {return TTEXTO;}
{id}	{return TID;}
{num}	{return TNUM;} 
