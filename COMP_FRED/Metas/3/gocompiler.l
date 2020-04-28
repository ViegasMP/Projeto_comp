
/* 
	2012138904, Frederico Cardoso
	2015237457, Renato Santos 

	Meta 3
*/



%{
	#include "y.tab.h"
	#include "ast.h"			/* Header das funções para construir a árvore de sintaxe */
	#include "symbol_table.h"
	#include "semantics.h"

	int line = 1, col = 1;		/* Linhas e colunas começam a 1, para a contagem dos erros */
	int commLine, commCol;		/* Variáveis para guardar onde começam os comentários */

	int lexical;				/* Para a análise lexical, usar flag -l */
	int syntax;					/* Para a análise sintática, usar flag -t */
	int semantic;
	int symbols;

	int syntax_error;			/* Para construir a árvore caso haja ou não erros de sintaxe */

	int needsemi = 0;			/* Para detectar se é necessário inserir SEMICOLON */
	int debugPrint = 0;			/* Para debug - if(debugPrintPrint) */

	char str[2000];				/* Para guardar o primeiro caracter de um STRLIT, neste caso um " (ao imprimir, vai imprimir "xxx") e ir adicionando */
	int linecp, colcp; 			/* lineCheckPoint e columnCheckPoint, para indicar onde começou o string literal, para impressão de alguns erros */
	int print_strlit = 1; 		/* Para só imprimir a strlit SÓ SE não tiver erros, EX: "oi\o" imprimiria invalid escape (\o) e strlit("oi\o") */

	int str_error = 0;			/* Caso especial para impressão da string inteira em erro de sintaxe */

	extern node *root;			/* Raiz da árvore. Dá jeito para nunca se perder o início da árvore, serve como cabeçalho */
%}



%X COMMENTBLOCK
%X COMMENTLINE
%X STRLITERAL



%option nounput
%option noinput



newline					"\n"|"\r"|"\r\n"
space					" "
tab 					"\t"
escape 					\\(f|n|r|t|\\|\")


cblockopen				"/*"
cblockclose				"*/"
clineopen				"//"
apostrophe 				"\""


letter 					[A-Z]|[a-z]|"_"
decimal_digit 			[0-9]
octal_digit 			[0-7]
hex_digit 				[0-9]|[a-f]|[A-F]

	
decimals 				{decimal_digit}+
exponent 				("e"|"E")("+"|"-")?{decimals}


decimal_lit				[0-9]{decimal_digit}*
octal_lit 				"0"{octal_digit}*
hex_lit 				"0"("x"|"X"){hex_digit}+


ID 						{letter}({letter}|{decimals})*
INTLIT 					({decimal_lit}|{octal_lit}|{hex_lit})
REALLIT 				({decimals}("."{decimals}?{exponent}?|{exponent})|"."{decimals}{exponent}?)


SEMICOLON				";"
BLANKID					"_"
PACKAGE					"package"
RETURN 					"return"
AND						"&&"
ASSIGN 					"="
STAR 					"*"
COMMA					","
DIV						"/"
EQ						"=="
GE						">="
GT						">"
LBRACE					"{"
LE 						"<="
LPAR					"("
LSQ 					"["
LT						"<"
MINUS	 				"-"
MOD 					"%"
NE						"!="
NOT 					"!"
OR						"||"
PLUS					"+"
RBRACE 					"}"
RPAR					")"
RSQ 					"]"
ELSE 					"else"
FOR 					"for"
IF 						"if"
VAR 					"var"
INT 					"int"
FLOAT32 				"float32"
BOOL 					"bool"
STRING 					"string"
PRINT 					"fmt.Println"
PARSEINT 				"strconv.Atoi"
FUNC 					"func"
CMDARGS 				"os.Args"
RESERVED 				"++"|"--"|"break"|"case"|"chan"|"const"|"continue"|"default"|"defer"|"fallthrough"|"go"|"goto"|"import"|"interface"|"map"|"range"|"select"|"struct"|"switch"|"type"|"var"





%%





{cblockopen} 								{BEGIN COMMENTBLOCK; commLine = line; commCol = col; col += yyleng;}
<COMMENTBLOCK>{cblockclose}					{BEGIN 0; col += yyleng;}
<COMMENTBLOCK><<EOF>>						{if(lexical && needsemi) printf("SEMICOLON\n"); 	if(syntax && needsemi) return SEMICOLON;;	needsemi = 0; printf("Line %d, column %d: unterminated comment\n", commLine, commCol); col += yyleng; yyterminate();}
<COMMENTBLOCK>{newline}						{if(lexical && needsemi) printf("SEMICOLON\n"); 	if(syntax && needsemi) return SEMICOLON;;	needsemi = 0; line++; col = 1;}
<COMMENTBLOCK>.								{col += yyleng;}


{clineopen}									{BEGIN COMMENTLINE; col += yyleng;}
<COMMENTLINE><<EOF>>						{if(lexical && needsemi) printf("SEMICOLON\n"); 	if(syntax && needsemi) return SEMICOLON;;	needsemi = 0; col += yyleng; yyterminate();}
<COMMENTLINE>{newline}						{BEGIN 0; if(lexical && needsemi) printf("SEMICOLON\n"); 	if(syntax && needsemi) return SEMICOLON;;	needsemi = 0; line++; col = 1;}
<COMMENTLINE>. 								{col += yyleng;}


{apostrophe}								{BEGIN STRLITERAL; strcpy(str, yytext); linecp = line; colcp = col; col += yyleng; print_strlit = 1; needsemi = 1;}
<STRLITERAL><<EOF>>							{printf("Line %d, column %d: unterminated string literal\n", linecp, colcp); print_strlit = 0; str_error = 1; yyterminate();}
<STRLITERAL>{newline}						{BEGIN 0; printf("Line %d, column %d: unterminated string literal\n", linecp, colcp); str_error = 1; needsemi = 0; line++; col = 1;}
<STRLITERAL>({escape}|\\\")					{strcat(str, yytext); col += yyleng;}
<STRLITERAL>\\.?							{printf("Line %d, column %d: invalid escape sequence (%s)\n", line, col, yytext); needsemi = 0; print_strlit = 0; col += yyleng;}
<STRLITERAL>{apostrophe}					{BEGIN 0; strcat(str, yytext); col += yyleng; 	if(lexical && print_strlit) printf("STRLIT(%s)\n", str);	if(syntax) { yylval.val = (char*) strdup(str); 	return STRLIT; } }
<STRLITERAL>.								{strcat(str, yytext); col += yyleng;}


{newline}						{line++; col = 1; if(lexical && needsemi) { needsemi = 0; printf("SEMICOLON\n"); } 	if(syntax && needsemi) { /*printf("SEMI %d %d\n", line, col);*/ needsemi = 0; return SEMICOLON;} }
{space}							{col += yyleng;}
{tab}							{col += yyleng;}


{SEMICOLON}				{if(lexical) printf("SEMICOLON\n"); 				col += yyleng; needsemi = 0; 	if(syntax) return SEMICOLON;	}
{BLANKID}				{if(lexical) printf("BLANKID\n");					col += yyleng; needsemi = 0; 	if(syntax) return BLANKID;		}
{PACKAGE}				{if(lexical) printf("PACKAGE\n");					col += yyleng; needsemi = 0; 	if(syntax) return PACKAGE;		}
{RETURN}				{if(lexical) printf("RETURN\n");					col += yyleng; needsemi = 1;	if(syntax) return RETURN;		}
{AND}					{if(lexical) printf("AND\n");						col += yyleng; needsemi = 0;	if(syntax) return AND;			}
{ASSIGN}				{if(lexical) printf("ASSIGN\n");					col += yyleng; needsemi = 0;	if(syntax) return ASSIGN;		}
{STAR}					{if(lexical) printf("STAR\n");						col += yyleng; needsemi = 0;	if(syntax) return STAR;			}
{COMMA}					{if(lexical) printf("COMMA\n");						col += yyleng; needsemi = 0;	if(syntax) return COMMA;		}
{DIV}					{if(lexical) printf("DIV\n");						col += yyleng; needsemi = 0;	if(syntax) return DIV;			}
{EQ}					{if(lexical) printf("EQ\n");						col += yyleng; needsemi = 0;	if(syntax) return EQ;			}
{GE}					{if(lexical) printf("GE\n");						col += yyleng; needsemi = 0;	if(syntax) return GE;			}
{GT}					{if(lexical) printf("GT\n");						col += yyleng; needsemi = 0;	if(syntax) return GT;			}
{LBRACE}				{if(lexical) printf("LBRACE\n");					col += yyleng; needsemi = 0;	if(syntax) return LBRACE;		}
{LE}					{if(lexical) printf("LE\n");						col += yyleng; needsemi = 0;	if(syntax) return LE;			}
{LPAR}					{if(lexical) printf("LPAR\n");						col += yyleng; needsemi = 0;	if(syntax) return LPAR;			}
{LSQ}					{if(lexical) printf("LSQ\n");						col += yyleng; needsemi = 0;	if(syntax) return LSQ;			}
{LT}					{if(lexical) printf("LT\n");						col += yyleng; needsemi = 0;	if(syntax) return LT;			}
{MINUS}					{if(lexical) printf("MINUS\n");						col += yyleng; needsemi = 0;	if(syntax) return MINUS;		}
{MOD}					{if(lexical) printf("MOD\n");						col += yyleng; needsemi = 0;	if(syntax) return MOD;			}
{NE}					{if(lexical) printf("NE\n");						col += yyleng; needsemi = 0;	if(syntax) return NE;			}
{NOT}					{if(lexical) printf("NOT\n");						col += yyleng; needsemi = 0;	if(syntax) return NOT;			}
{OR}					{if(lexical) printf("OR\n");						col += yyleng; needsemi = 0;	if(syntax) return OR;			}
{PLUS}					{if(lexical) printf("PLUS\n");						col += yyleng; needsemi = 0;	if(syntax) return PLUS;			}
{RBRACE}				{if(lexical) printf("RBRACE\n");					col += yyleng; needsemi = 1;	if(syntax) return RBRACE;		}
{RPAR}					{if(lexical) printf("RPAR\n");						col += yyleng; needsemi = 1;	if(syntax) return RPAR;			}
{RSQ}					{if(lexical) printf("RSQ\n");						col += yyleng; needsemi = 1;	if(syntax) return RSQ;			}
{ELSE}					{if(lexical) printf("ELSE\n");						col += yyleng; needsemi = 0; 	if(syntax) return ELSE;			}
{FOR}					{if(lexical) printf("FOR\n");						col += yyleng; needsemi = 0; 	if(syntax) return FOR;			}
{IF}					{if(lexical) printf("IF\n");						col += yyleng; needsemi = 0; 	if(syntax) return IF;			}
{VAR}					{if(lexical) printf("VAR\n");						col += yyleng; needsemi = 0; 	if(syntax) return VAR;			}
{INT}					{if(lexical) printf("INT\n");						col += yyleng; needsemi = 0; 	if(syntax) return INT;			}
{FLOAT32}				{if(lexical) printf("FLOAT32\n");					col += yyleng; needsemi = 0; 	if(syntax) return FLOAT32;		}
{BOOL}					{if(lexical) printf("BOOL\n");						col += yyleng; needsemi = 0; 	if(syntax) return BOOL;			}
{STRING}				{if(lexical) printf("STRING\n");					col += yyleng; needsemi = 0; 	if(syntax) return STRING;		}
{PRINT}					{if(lexical) printf("PRINT\n");						col += yyleng; needsemi = 0; 	if(syntax) return PRINT;		}
{PARSEINT}				{if(lexical) printf("PARSEINT\n");					col += yyleng; needsemi = 0; 	if(syntax) return PARSEINT;		}
{FUNC}					{if(lexical) printf("FUNC\n");						col += yyleng; needsemi = 0; 	if(syntax) return FUNC;			}
{CMDARGS}				{if(lexical) printf("CMDARGS\n");					col += yyleng; needsemi = 0; 	if(syntax) return CMDARGS;		}

{RESERVED}				{if(lexical) printf("RESERVED(%s)\n", yytext);		col += yyleng; needsemi = 0;	if(syntax) { yylval.val = (char*) strdup(yytext); 	return RESERVED; }	}
{ID}					{if(lexical) printf("ID(%s)\n", yytext);			col += yyleng; needsemi = 1;	if(syntax) { yylval.val = (char*) strdup(yytext); 	return ID; }		}
{INTLIT}				{if(lexical) printf("INTLIT(%s)\n", yytext);		col += yyleng; needsemi = 1;	if(syntax) { yylval.val = (char*) strdup(yytext); 	return INTLIT; }	}
{REALLIT}				{if(lexical) printf("REALLIT(%s)\n", yytext);		col += yyleng; needsemi = 1;	if(syntax) { yylval.val = (char*) strdup(yytext); 	return REALLIT; }	}


<<EOF>>					{if(lexical && needsemi) printf("SEMICOLON\n");;	if(syntax && needsemi) {/*printf("1\n");*/ needsemi = 0; return SEMICOLON;  }	yyterminate();}


.						{printf("Line %d, column %d: illegal character (%s)\n", line, col, yytext); col += yyleng;}





%%





int main(int argc, char **argv) {
	lexical = 0;					/* Flag -l */					
	syntax = 0;						/* Flag -t */
	semantic = 0;					/* Flag null */
	symbols = 0;					/* Flag -s */

	syntax_error = 0; 				/* Erro de sintaxe a apanhar pelo yyparse(). Ver caso específico em baixo */

	if(argc == 1) {					/* Se não tiver flag, faz a análise sintática e semântica */
		lexical = 0;
		syntax = 1;
		semantic = 1;
		symbols = 0;
	}

	else if(argc == 2) {
		if(strcmp(argv[1], "-l") == 0) {			/* Flag -l para análise lexical */
			lexical = 1;
			syntax = 0;
			semantic = 0;
			symbols = 0;
		} 			
		else if(strcmp(argv[1], "-t") == 0) {		/* Flag -t para análise sintática */
			lexical = 0;
			syntax = 1;
			semantic = 0;
			symbols = 0;
		} 
		else if(strcmp(argv[1], "-s") == 0) {		/* Flag -s para análise semântica */
			lexical = 0;
			syntax = 1;								/* Aqui a sintaxe entra a 1, para o yyparse funcionar (em vez de mudar tudo lá em cima), ou seja ...*/
			semantic = 0;							/* ... em vez de "if(syntax || symbols) return SEMICOLON;", mantemos o "if(syntax) return SEMICOLON;" */
			symbols = 1;
		} 
	}

	if(lexical) {												/* ----------|| FLAG -L: FAZ A ANÁLISE LEXICAL ||----------- */
																if(debugPrint) printf("FLAG -l: faz a análise lexical.\n");
		yylex();
	}

	else {																	/* Fez a análise sintatica */
																			if(debugPrint) printf("Fez a análise sintática.\n");
		yyparse();															/* Constrói a árvore */

		if(symbols == 1)													/* Feito o yyparse(), muda-se de novo, para entrar no if correcto */
			syntax = 0;

		if(!syntax_error) {													/* Se não houver erros de sintaxe */
																			if(debugPrint) printf("Não houve erros de sintaxe.\n");

			if(semantic) {										/* ----------|| FLAG null: FAZ A ANÁLISE SEMANTICA ||----------- */
																if(debugPrint) printf("FLAG null: faz a análise semantica.\n");
			}
			else {
				if(syntax) {									/* ----------|| FLAG -T: IMPRIME A ÁRVORE DE SINTAXE ||----------- */
																if(debugPrint) printf("FLAG -t: imprime a árvore de sintaxe.\n");
					print_ast(root, 0);
				}
				else {
					if(symbols) {								/* ----------|| FLAG -S: IMPRIME A ÁRVORE DE SINTAXE ||----------- */
																if(debugPrint) printf("FLAG -s: imprime as tabelas e árvore anotada.\n");
						
						/* TODO: META 3 */

						init_global_table();
						global_dfs(root->child);

						last_table = root_table;
						local_dfs(root->child, last_table);

						print_tables(root_table);

						print_ast(root, 0);
					}
				}

				
			}
		}
		else {																/* Se houve erros de sintaxe, então, não fez árvores, tabelas ou análise semântica. Só imprime os erros */
																			if(debugPrint) printf("Houve erros de sintaxe, imprimiu-os, não avançou para árvore, tabelas ou análise semântica.\n");
		}

	}

	return 0;
}



void yyerror(char *s) {
	syntax_error = 1;

	if(strcmp(yytext, "\"") == 0) {
		str_error = 1;
	}

	if(str_error) {						/* Caso especifico quando um STRLIT gera erros de sintaxe, imprime a string toda */
		if(colcp == 0)					/* Este colcp == 0 serve para quando o erro é gerado na coluna 0, ser gerado na coluna 1. Não alterou pontuação. */
			colcp = 1;

		printf("Line %d, column %d: %s: %s\n", linecp, colcp, s, str);
		str_error = 0;
	}
	else {
		colcp = col-(int)yyleng;
		if(colcp == 0)
			colcp = 1;

		printf("Line %d, column %d: %s: %s\n", line, colcp, s, yytext);
	}

	
}


int yywrap() {
	return 1;
}