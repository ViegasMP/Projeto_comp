%{
/*
		Carolina de Castilho Godinho	-	2017247087
		Maria Paula de Alencar Viegas	-	2017125592
*/
%}
%{
#include <stdbool.h> 
#include "y.tab.h"
#include "tree_functions.h"
#include "semantic.h"
#include "symbol_table.h"

int yyparse(void);
bool l;
bool e2;
int line_count=1;
int col_count=1;
int ini_line=1; //guarda linha em que começa comentario ou string
int ini_col=1; //guarda coluna em que começa comentario ou string
int col_escape=0;
int error_flag=0;
int col_syntax = 1;
int prev_col=1;
int prev_line=-2;
int ini_comment_line=1;
extern struct no* tree;
extern int syntax_error;
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

%%
"//"												{
														BEGIN COMMENT2;
														col_syntax=col_count;
														col_count+=yyleng;
													}
<COMMENT2>{next_line}								{
														line_count++;
														col_count=1;
														col_syntax=col_count;
														BEGIN 0;
													}
<COMMENT2>.											{
														col_count+=yyleng;
														col_syntax=col_count;
													}
"/*" 												{
														BEGIN COMMENT;
														ini_line=line_count;
														ini_col=col_count;
														col_count+=yyleng;
														col_syntax=col_count;
													}
<COMMENT>"*/" 										{
														col_syntax=col_count;
														col_count+=yyleng;
														BEGIN 0;
													}
<COMMENT><<EOF>>									{
														printf("Line %d, col %d: unterminated comment\n",ini_line,ini_col);
														col_syntax=col_count;
														return 0;
													}
<COMMENT>{next_line}  											{
														line_count++;
														col_count=1;
														col_syntax=col_count;
													}
<COMMENT>.	  											{
														col_count+=yyleng;
														col_syntax=col_count;
														prev_col=col_count;
													}
\"													{
														ini_line=line_count;
														ini_col=col_count;
														col_syntax=col_count;
														col_count+=yyleng;
														BEGIN STR;
													}
<STR>{chars}*\\										{
														col_count+=yyleng;
														col_syntax=col_count;
														col_escape=col_count-1;
														BEGIN ESCAPE;
													}
<ESCAPE>{next_line}									{
														printf("Line %d, col %d: invalid escape sequence (\\)\n",ini_line,col_escape);
														printf("Line %d, col %d: unterminated string literal\n",ini_line,ini_col);
														line_count++;
														col_count=1;
														BEGIN 0;
													}
<ESCAPE>[^fnrt\\\"]									{
														printf("Line %d, col %d: invalid escape sequence (\\%s)\n",ini_line,col_escape,yytext);
														col_count+=yyleng;
														error_flag=1;
														BEGIN STR;
													}
<STR>{chars}*\"										{
														BEGIN 0;
														col_count+=yyleng;
														if(!error_flag){
															if(l){
																printf("STRLIT(\"%s)\n",yytext);
																error_flag=0;
															}
															else if(!l && e2){
																yylval.str=strdup(yytext);
																error_flag=0;
																return STRLIT;
															}
														}else{
															error_flag=0;
														}
													}
<STR><<EOF>>										{
														printf("Line %d, col %d: unterminated string literal\n",ini_line,ini_col);
														line_count--;
														return 0;
													}
<STR>{next_line}									{
														printf("Line %d, col %d: unterminated string literal\n",ini_line,ini_col);
														line_count++;
														col_syntax=col_count;
														col_count=1;
														error_flag=0;
														BEGIN 0;
													}
<STR>({chars}|" "|"\t")*							{
														col_syntax=col_count;
														col_count+=yyleng;
													}						

{reserved}											{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("RESERVED(%s)\n",yytext);
														else if(!l && e2){
															yylval.str=strdup(yytext);
															return RESERVED;
														}	
													}
({numero}+("_"*{numero}+)*"."({numero}+("_"*{numero}+)*)?({exponencial}[+-]?{numero}+("_"*{numero}+)*)?)|({numero}+("_"*{numero}+)*)({exponencial}[+-]?{numero}+("_"*{numero}+)*)|"."{numero}+("_"*{numero}+)*({exponencial}[+-]?{numero}+("_"*{numero}+)*)?						{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("REALLIT(%s)\n",yytext);
														else if(!l && e2){
															yylval.str=strdup(yytext);
															return REALLIT;
														}
													}
([1-9]+(({numero}|"_")*{numero}+)*)|"0"				{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("INTLIT(%s)\n",yytext);
														else if(!l && e2){
															yylval.str=strdup(yytext);
															return INTLIT;
														}
													}
"true"|"false"										{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("BOOLLIT(%s)\n",yytext);
														else if(!l && e2){
															yylval.str=strdup(yytext);
															return BOOLLIT;
														}

													}
"&&"												{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("AND\n");
														else if(!l && e2)
															return AND;

													}
"="													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("ASSIGN\n");
														else if(!l && e2)
															return ASSIGN;
													}
"*"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("STAR\n");
														else if(!l && e2)
															return STAR;
													}
","													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("COMMA\n");
														else if(!l && e2)
															return COMMA;
													}
"/"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("DIV\n");
														else if(!l && e2)
															return DIV;
													}
"=="													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("EQ\n");
														else if(!l && e2)
															return EQ;

													}	
">="												{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("GE\n");
														else if(!l && e2)
															return GE;

													}
">"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("GT\n");
														else if(!l && e2)
															return GT;
													}
"{"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("LBRACE\n");
														else if(!l && e2)
															return LBRACE;
													}
"<="												{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("LE\n");
														else if(!l && e2)
															return LE;
													}
"("													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("LPAR\n");
														else if(!l && e2)
															return LPAR;
													}
"["													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("LSQ\n");
														else if(!l && e2)
															return LSQ;
													}
"<"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("LT\n");
														else if(!l && e2)
															return LT;
													}
"-"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("MINUS\n");
														else if(!l && e2)
															return MINUS;
													}
"%"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("MOD\n");
														else if(!l && e2)
															return MOD;
													}
"!="													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("NE\n");
														else if(!l && e2)
															return NE;
													}
"!"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("NOT\n");
														else if(!l && e2)
															return NOT;
													}
"||"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("OR\n");
														else if(!l && e2)
															return OR;
													}
"+"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("PLUS\n");
														else if(!l && e2)
															return PLUS;
													}
"}"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("RBRACE\n");
														else if(!l && e2)
															return RBRACE;
													}
")"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("RPAR\n");
														else if(!l && e2)
															return RPAR;
													}
"]"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("RSQ\n");
														else if(!l && e2)
															return RSQ;
													}
";"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("SEMICOLON\n");
														else if(!l && e2)
															return SEMICOLON;
													}
"->"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("ARROW\n");
														else if(!l && e2)
															return ARROW;
													}
"<<"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("LSHIFT\n");
														else if(!l && e2)
															return LSHIFT;
													}
">>"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("RSHIFT\n");
														else if(!l && e2)
															return RSHIFT;
													}
"^"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("XOR\n");
														else if(!l && e2)
															return XOR;
													}
"boolean"												{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("BOOL\n");
														else if(!l && e2)
															return BOOL;
													}
"class"												{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("CLASS\n");
														else if(!l && e2)
															return CLASS;
													}
".length"												{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("DOTLENGTH\n");
														else if(!l && e2)
															return DOTLENGTH;
													}
"double"												{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("DOUBLE\n");
														else if(!l && e2)
															return DOUBLE;
													}
"else"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("ELSE\n");
														else if(!l && e2)
															return ELSE;
													}
"if"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("IF\n");
														else if(!l && e2)
															return IF;
													}
"int"											    {
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("INT\n");
														else if(!l && e2)
															return INT;
													}
"System.out.print"								    {
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("PRINT\n");
														else if(!l && e2)
															return PRINT;
													}
"Integer.parseInt"											{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("PARSEINT\n");
														else if(!l && e2)
															return PARSEINT;
													}
"public"												{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("PUBLIC\n");
														else if(!l && e2)
															return PUBLIC;
													}
"return"												{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("RETURN\n");
														else if(!l && e2)
															return RETURN;

													}
"static"												{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("STATIC\n");
														else if(!l && e2)
															return STATIC;
													}
"String"												{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("STRING\n");
														else if(!l && e2)
															return STRING;
													}
"void"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("VOID\n");
														else if(!l && e2)
															return VOID;
													}
"while"													{
														col_syntax=col_count;
														col_count+=yyleng;
														if(l)
															printf("WHILE\n");
														else if(!l && e2)
															return WHILE; 
													}
({alfabeto}|{simbolo})+({numero}|{alfabeto}|{simbolo})* {
															col_syntax=col_count;
															col_count+=yyleng;
															if(l)
																printf("ID(%s)\n",yytext);
															else if(!l && e2){
																yylval.str=strdup(yytext);
																return ID;
															}
														}
{whitespace}           											{
														col_count+=yyleng;
														col_syntax=col_count;
													}
{next_line}											{
														line_count++;
														col_count=1;
														col_syntax=col_count;
													}
.													{
														printf("Line %d, col %d: illegal character (%s)\n",line_count,col_count,yytext);
														col_count+=yyleng;
														col_syntax=col_count;
													}
<<EOF>>												{
														/*
														if(line_count==prev_line+1){
															if(ini_comment_line!=line_count){
																col_syntax=prev_col;
																line_count--;
															}
														}
														*/
														return 0;
													}


%%
int main(int argc, char **argv)
{
	if(argc == 2){
		if (strcmp(argv[1],"-l") == 0){
			l = true;
			e2 = false;
			yylex();
			free_tree(tree);
		}
		else if (strcmp(argv[1],"-e1") == 0){
			l = false;
			e2 = false;
			yylex();
			free_tree(tree);
		}
		else if(strcmp(argv[1],"-e2") == 0){
			l = false;
			e2 = true;
			yyparse();
			free_tree(tree);
		}
		else if	(strcmp(argv[1], "-t") == 0){
			l=false;
			e2 = true;
			yyparse();
			if(syntax_error==0)
				print_tree(tree,0);
			free_tree(tree);
		}
		else if(strcmp(argv[1], "-s") == 0){
			l=false;
			e2 = true;
			yyparse();
			init_global_table(tree->filho);

			last_table = root_table;
			local_dfs(tree, last_table);

			print_tables(root_table);
			print_tree(tree,0);
			free_tree(tree);
			return 0;
		} else {
			return 0;
		}
	}
	else if (argc == 1){
		l = false;
		e2 = true;
		yyparse();
		free_tree(tree);
	}
	else{
		free_tree(tree);
		return 0;
	}
	return 0;
}
int yywrap()
{
	return 1;
}