%{
/*
		Carolina de Castilho Godinho	-	2017247087
		Maria Paula de Alencar Viegas	-	2017125592
*/
%}



alfabeto												[a-zA-Z]
numero													[0-9]
simbolo            										$|_
exponencial												E|e
mais_ou_menos											+|-
whitespace  											" "|\t|\f
chars													\\(f|n|r|t|\\|\")|[^"\n""\r""\"""\\"]
reserved												"++"|"--"|"null"|"Integer"|"System"|"abstract"|"continue"|"switch"|"assert"|"default"|"package"|"synchronized"|"do"|"goto"|"private"|"break"|"byte"|"case"|"catch"|"char"|"const"|"enum"|"extends"|"final"|"finally"|"float"|"for"|"implements"|"import"|"instanceof"|"interface"|"long"|"native"|"new"|"protected"|"short"|"strictfp"|"super"|"this"|"throw"|"throws"|"transient"|"try"|"volatile"
next_line												\n|\r|(\r\n)  

%X COMMENT
%X COMMENT2
%X STR
%X ESCAPE

%{
#include<stdio.h>
int line_count=1;
int col_count=1;
int ini_line=1; //guarda linha em que começa comentario ou string
int ini_col=1; //guarda coluna em que começa comentario ou string
int col_escape=0;
int error_flag=0;
int l=1;
%}

%%

"//"													{BEGIN COMMENT2;col_count=col_count+yyleng;}
<COMMENT2>{next_line}									{BEGIN 0;line_count++;col_count=1;} //regressar ao normal
<COMMENT2>.	  											{col_count=col_count+yyleng;} //ignorar

"/*" 													{ini_line=line_count;ini_col = col_count;BEGIN COMMENT;col_count=col_count+yyleng;}
<COMMENT>"*/" 											{BEGIN 0; col_count=col_count+yyleng;} //regressar ao normal
<COMMENT><<EOF>>										{printf("Line %d, col %d: unterminated comment\n",ini_line,ini_col);BEGIN 0;} //regressar ao normal
<COMMENT>{next_line}  									{line_count++;col_count=1;} //ignorar
<COMMENT>.	  											{col_count=col_count+yyleng;} //ignorar

\"														{BEGIN STR;ini_line=line_count;ini_col = col_count;col_count=col_count+yyleng;}
<STR>{chars}*\\											{BEGIN ESCAPE;col_count=col_count+yyleng;col_escape=col_count-1;}
<ESCAPE>{next_line}										{printf("Line %d, col %d: invalid escape sequence (\\)\n",ini_line,col_escape);printf("Line %d, col %d: unterminated string literal\n",ini_line,ini_col);BEGIN 0;line_count++;col_count=1;}
<ESCAPE>[^fnrt\\\"]										{BEGIN STR; printf("Line %d, col %d: invalid escape sequence (\\%s)\n",ini_line,col_escape,yytext);col_count=col_count+yyleng;error_flag=1;}
<STR>{chars}*\"											{if(!error_flag){if(l)printf("STRLIT(\"%s)\n",yytext);}col_count=col_count+yyleng;error_flag=0;BEGIN 0;}
<STR><<EOF>>											{printf("Line %d, col %d: unterminated string literal\n",ini_line,ini_col);BEGIN 0;}
<STR>{next_line}										{printf("Line %d, col %d: unterminated string literal\n",ini_line,ini_col);BEGIN 0;line_count++;col_count=1;error_flag=0;}
<STR>({chars}|" "|"\t")*								{col_count=col_count+yyleng;}						

{reserved}												{if(l)printf("RESERVED(%s)\n",yytext);col_count=col_count+yyleng;}
({numero}+("_"*{numero}+)*"."({numero}+("_"*{numero}+)*)?({exponencial}[+-]?{numero}+("_"*{numero}+)*)?)|({numero}+("_"*{numero}+)*)({exponencial}[+-]?{numero}+("_"*{numero}+)*)|"."{numero}+("_"*{numero}+)*({exponencial}[+-]?{numero}+("_"*{numero}+)*)?									{if(l)printf("REALLIT(%s)\n",yytext);col_count=col_count+yyleng;}
([1-9]+(({numero}|"_")*{numero}+)*)|"0"					{if(l)printf("INTLIT(%s)\n",yytext);col_count=col_count+yyleng;}
"true"|"false"											{if(l)printf("BOOLLIT(%s)\n",yytext);col_count=col_count+yyleng;}
"&&"													{if(l)printf("AND\n");col_count=col_count+yyleng;}
"="														{if(l)printf("ASSIGN\n");col_count=col_count+yyleng;}
"*"														{if(l)printf("STAR\n");col_count=col_count+yyleng;}
","														{if(l)printf("COMMA\n");col_count=col_count+yyleng;}
"/"														{if(l)printf("DIV\n");col_count=col_count+yyleng;}
"=="													{if(l)printf("EQ\n");col_count=col_count+yyleng;}	
">="													{if(l)printf("GE\n");col_count=col_count+yyleng;}
">"														{if(l)printf("GT\n");col_count=col_count+yyleng;}
"{"														{if(l)printf("LBRACE\n");col_count=col_count+yyleng;}
"<="													{if(l)printf("LE\n");col_count=col_count+yyleng;}
"("														{if(l)printf("LPAR\n");col_count=col_count+yyleng;}
"["														{if(l)printf("LSQ\n");col_count=col_count+yyleng;}
"<"														{if(l)printf("LT\n");col_count=col_count+yyleng;}
"-"														{if(l)printf("MINUS\n");col_count=col_count+yyleng;}
"%"														{if(l)printf("MOD\n");col_count=col_count+yyleng;}
"!="													{if(l)printf("NE\n");col_count=col_count+yyleng;}
"!"														{if(l)printf("NOT\n");col_count=col_count+yyleng;}
"||"													{if(l)printf("OR\n");col_count=col_count+yyleng;}
"+"														{if(l)printf("PLUS\n");col_count=col_count+yyleng;}
"}"														{if(l)printf("RBRACE\n");col_count=col_count+yyleng;}
")"														{if(l)printf("RPAR\n");col_count=col_count+yyleng;}
"]"														{if(l)printf("RSQ\n");col_count=col_count+yyleng;}
";"														{if(l)printf("SEMICOLON\n");col_count=col_count+yyleng;}
"->"													{if(l)printf("ARROW\n");col_count=col_count+yyleng;}
"<<"													{if(l)printf("LSHIFT\n");col_count=col_count+yyleng;}
">>"													{if(l)printf("RSHIFT\n");col_count=col_count+yyleng;}
"^"														{if(l)printf("XOR\n");col_count=col_count+yyleng;}
"boolean"												{if(l)printf("BOOL\n");col_count=col_count+yyleng;}
"class"													{if(l)printf("CLASS\n");col_count=col_count+yyleng;}
".length"												{if(l)printf("DOTLENGTH\n");col_count=col_count+yyleng;}
"double"												{if(l)printf("DOUBLE\n");col_count=col_count+yyleng;}
"else"													{if(l)printf("ELSE\n");col_count=col_count+yyleng;}
"if"													{if(l)printf("IF\n");col_count=col_count+yyleng;}
"int"													{if(l)printf("INT\n");col_count=col_count+yyleng;}
"System.out.print"										{if(l)printf("PRINT\n");col_count=col_count+yyleng;}
"Integer.parseInt"										{if(l)printf("PARSEINT\n");col_count=col_count+yyleng;}
"public"												{if(l)printf("PUBLIC\n");col_count=col_count+yyleng;}
"return"												{if(l)printf("RETURN\n");col_count=col_count+yyleng;}
"static"												{if(l)printf("STATIC\n");col_count=col_count+yyleng;}
"String"												{if(l)printf("STRING\n");col_count=col_count+yyleng;}
"void"													{if(l)printf("VOID\n");col_count=col_count+yyleng;}
"while"													{if(l)printf("WHILE\n");col_count=col_count+yyleng;}
({alfabeto}|{simbolo})+({numero}|{alfabeto}|{simbolo})* {if(l)printf("ID(%s)\n",yytext);col_count=col_count+yyleng;}
{whitespace}           									{col_count+=yyleng;};
{next_line}												{line_count++;col_count=1;}
.														{printf("Line %d, col %d: illegal character (%s)\n",line_count,col_count,yytext);col_count=col_count+yyleng;}



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