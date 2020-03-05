alfabeto			[a-zA-Z]
numero				[0-9]
simbolo            		[$_]
exponencial			[Ee]
mais_ou_menos			[+-]
proibidos			[^(f|n|r|t|"\\"|"\*")]
%X COMMENT
%X COMMENT2
%X STR
%X ERRO
%{
#include<stdio.h>
int line_count=1;
int col_count=0;
int ini_line=1; //guarda linha em que começa comentario ou string
int ini_col=1; //guarda coluna em que começa comentario ou string
%}

%%

"//"													{BEGIN COMMENT2;col_count=col_count+yyleng;}
<COMMENT2>\n|\r|(\r\n)  								{BEGIN 0;line_count++;} //regressar ao normal
<COMMENT2>.	  											{col_count=col_count+yyleng;} //ignorar

"/*" 													{BEGIN COMMENT;ini_line=line_count;ini_col = col_count+1;col_count=col_count+yyleng;}
<COMMENT>"*/" 											{BEGIN 0;col_count=col_count+yyleng;} //regressar ao normal
<COMMENT><<EOF>>										{printf("Line %d, col %d: unterminated comment\n",ini_line,ini_col);BEGIN 0;} //regressar ao normal
<COMMENT>\n|\r|(\r\n)  									{line_count++;} //ignorar
<COMMENT>.	  											{col_count=col_count+yyleng;} //ignorar

\"														{BEGIN STR;ini_line=line_count;ini_col = col_count+1;col_count=col_count+yyleng;}
<STR><<EOF>>											{printf("Line %d, col %d: unterminated string literal\n",ini_line,ini_col);BEGIN 0;}
<STR>({alfabeto}*|{numero}*|" "*|(\\t)*|(\\f)*|(\\n)*|(\\r)*|(\\\*)*|(\t)*|(\\\\)*|(\\\")*)+\"					  {printf("STRLIT(\"%s)\n",yytext);col_count=col_count+yyleng;BEGIN 0;}
<STR>\\{proibidos}										{col_count++;printf("Line %d, col %d: invalid escape sequence (%s)\n",line_count,col_count,yytext);BEGIN ERRO;}
<STR>.													{col_count=col_count+yyleng;}
<STR>\n|\r|(\r\n)										{line_count++;col_count=0;}

<ERRO>({alfabeto}*|{numero}*|" "*)+\"					{printf("Line %d, col %d: unterminated string literal\n",ini_line,ini_col);BEGIN 0;}					

						
\.|\?|\$|\#									{col_count++;printf("Line %d, col %d: illegal character (%s)\n",line_count,col_count,yytext);}
"++"|"--"|"null"|"Integer"|"System"|"abstract"|"continue"|"switch"|"assert"|"default"|"package"|"synchronized"|"do"|"goto"|"private"|"break"|"byte"|"case"|"catch"|"char"|"const"|"enum"|"extends"|"final"|"finally"|"float"|"for"|"implements"|"import"|"instanceof"|"interface"|"long"|"native"|"new"|"protected"|"short"|"strictfp"|"super"|"this"|"throw"|"throws"|"transient"|"try"|"volatile"	{printf("RESERVED(%s)\n",yytext);col_count=col_count+yyleng;}
(({numero}+(""{numero}+)*)*"."(({numero}+(""+{numero}+)+)|{numero}+|{exponencial}{mais_ou_menos}?{numero}+(""+{numero}+)*)*)|({numero}+(""+{numero}+)*{exponencial}{mais_ou_menos}?{numero}+("_"+{numero}+)*)                      {printf("REALLIT(%s)\n",yytext);}
{numero}+(({numero}|"_")*{numero}+)*					{printf("INTLIT(%s)\n",yytext);col_count=col_count+yyleng;}
"true"|"false"								{printf("BOOLLIT(%s)\n",yytext);col_count=col_count+yyleng;}
"&&"									{printf("AND\n");col_count=col_count+yyleng;}
"="									{printf("ASSIGN\n");col_count=col_count+yyleng;}
"*"									{printf("STAR\n");col_count=col_count+yyleng;}
","									{printf("COMMA\n");col_count=col_count+yyleng;}
"/"									{printf("DIV\n");col_count=col_count+yyleng;}
"=="									{printf("EQ\n");col_count=col_count+yyleng;}	
">="									{printf("GE\n");col_count=col_count+yyleng;}
">"									{printf("GT\n");col_count=col_count+yyleng;}
"{"									{printf("LBRACE\n");col_count=col_count+yyleng;}
"<="									{printf("LE\n");col_count=col_count+yyleng;}
"("									{printf("LPAR\n");col_count=col_count+yyleng;}
"["									{printf("LSQ\n");col_count=col_count+yyleng;}
"<"									{printf("LT\n");col_count=col_count+yyleng;}
"-"									{printf("MINUS\n");col_count=col_count+yyleng;}
"%"									{printf("MOD\n");col_count=col_count+yyleng;}
"!="									{printf("NE\n");col_count=col_count+yyleng;}
"!"									{printf("NOT\n");col_count=col_count+yyleng;}
"||"									{printf("OR\n");col_count=col_count+yyleng;}
"+"									{printf("PLUS\n");col_count=col_count+yyleng;}
"}"									{printf("RBRACE\n");col_count=col_count+yyleng;}
")"									{printf("RPAR\n");col_count=col_count+yyleng;}
"]"									{printf("RSQ\n");col_count=col_count+yyleng;}
";"									{printf("SEMICOLON\n");col_count=col_count+yyleng;}
"->"									{printf("ARROW\n");col_count=col_count+yyleng;}
"<<"									{printf("LSHIFT\n");col_count=col_count+yyleng;}
">>"									{printf("RSHIFT\n");col_count=col_count+yyleng;}
"^"									{printf("XOR\n");col_count=col_count+yyleng;}
"boolean"								{printf("BOOL\n");col_count=col_count+yyleng;}
"class"									{printf("CLASS\n");col_count=col_count+yyleng;}
".length"								{printf("DOTLENGTH\n");col_count=col_count+yyleng;}
"double"								{printf("DOUBLE\n");col_count=col_count+yyleng;}
"else"									{printf("ELSE\n");col_count=col_count+yyleng;}
"if"									{printf("IF\n");col_count=col_count+yyleng;}
"int"									{printf("INT\n");col_count=col_count+yyleng;}
"System.out.print"							{printf("PRINT\n");col_count=col_count+yyleng;}
"Integer.parseInt"							{printf("PARSEINT\n");col_count=col_count+yyleng;}
"public"								{printf("PUBLIC\n");col_count=col_count+yyleng;}
"return"								{printf("RETURN\n");col_count=col_count+yyleng;}
"static"								{printf("STATIC\n");col_count=col_count+yyleng;}
"String"								{printf("STRING\n");col_count=col_count+yyleng;}
"void"									{printf("VOID\n");col_count=col_count+yyleng;}
"while"									{printf("WHILE\n");col_count=col_count+yyleng;}
({alfabeto}|{simbolo})+({numero}|{alfabeto}|{simbolo})*    		{printf("ID(%s)\n",yytext);col_count=col_count+yyleng;}
.									{col_count=col_count+yyleng;}
\n									{line_count++;col_count=0;}


%%

int main()
{
	yylex();
	return 0;
}

int yywrap()
{
	return 1;
}