%{
/*
		Carolina de Castilho Godinho	-	2017247087
		Maria Paula de Alencar Viegas	-	2017125592
		Correr com:
		lex jucompiler.l
		yacc -d jucompiler.y
		cc -o jucompiler y.tab.c lex.yy.c tree_functions.c
*/
%}
%{
#include <stdio.h>
#include <stdbool.h> 
#include "tree_functions.h"
int yylex(void);
void yyerror (char *s);
extern char* yytext;
extern int line_count;
extern int col_count;
extern int ini_line; //guarda linha em que começa comentario ou string
extern int ini_col; //guarda coluna em que começa comentario ou string
extern bool e2;
extern int col_syntax;
struct no* tree;
struct no* aux;
struct no* type;
struct no* header;
struct no* body;
struct no* par;
%}

%union{
	char * str;
	struct no* no;
}

%type <no> Program MethodHeader MethodDecl ProgramRepetition FieldDecl MethodBody Type FormalParamsRepetition FormalParams CommaIDRepetition MethodBodyRepetition Statement VarDecl StatementRepetition Expr MethodInvocation Assignment ParseArgs CommaExprRepetition
%type <str> ID INTLIT REALLIT STRLIT BOOLLIT


%token STRLIT
%token RESERVED
%token REALLIT
%token INTLIT
%token BOOLLIT
%token AND
%token ASSIGN
%token STAR
%token COMMA
%token DIV
%token EQ
%token GE
%token GT
%token LBRACE
%token LE
%token LPAR
%token LSQ
%token LT
%token MINUS
%token MOD
%token NE
%token NOT
%token OR
%token PLUS
%token RBRACE
%token RPAR
%token RSQ
%token SEMICOLON
%token ARROW
%token LSHIFT
%token RSHIFT
%token XOR
%token BOOL
%token CLASS
%token DOTLENGTH
%token DOUBLE
%token ELSE
%token IF
%token INT
%token PRINT
%token PARSEINT
%token PUBLIC
%token RETURN
%token STATIC
%token STRING
%token VOID
%token WHILE
%token ID

%right ASSIGN
%left OR 
%left AND
%left XOR
%left EQ NE
%left LT LE GT GE
%left LSHIFT RSHIFT
%left PLUS MINUS
%left STAR DIV MOD
%right NOT

%nonassoc IF
%nonassoc ELSE

%%

Program: 					CLASS ID LBRACE ProgramRepetition RBRACE			{	
																					tree = cria_no("Program");
																					aux = new_id($2);
																					add_filho(tree, aux);
																					add_next(aux, $4);
																				}													
						;
ProgramRepetition:																{$$ = NULL;}							
						|	ProgramRepetition MethodDecl 						{$$ = $2;}
						|	ProgramRepetition FieldDecl 						{$$ = $2;}
						|	ProgramRepetition SEMICOLON							{$$ = $1;}
						;
MethodDecl: 				PUBLIC STATIC MethodHeader MethodBody				{	
																					$$ = cria_no("MethodDecl");
																					add_filho($$, $3);
																					add_next($3, $4);
																				}
    					;
FieldDecl: 					PUBLIC STATIC Type ID CommaIDRepetition SEMICOLON	{$$ = NULL;}
						|	error SEMICOLON										{$$ = NULL;}	
						;
CommaIDRepetition:																{$$ = NULL;}						
						|	CommaIDRepetition COMMA ID 							{
																					$$ = $1;
																					add_next($1, new_id($3));
																				}
						;	
Type:						BOOL 												{$$ = cria_no("Bool");}
						| 	INT 												{$$ = cria_no("Int");}
						| 	DOUBLE												{$$ = cria_no("Double");}
						;
MethodHeader: 				Type ID LPAR FormalParams RPAR						{
																					$$ = cria_no("MethodHeader");
																					add_filho($$, $1);
																					aux = new_id($2);
																					add_next($1, aux);
																					add_next(aux, $4);
																				}
						|	Type ID LPAR RPAR									{
																					$$ = cria_no("MethodHeader");
																					add_filho($$, $1);
																					add_next($1, new_id($2));
																				}
						|	VOID ID LPAR FormalParams RPAR						{
																					$$ = cria_no("MethodHeader");
																					aux = cria_no("Void");
																					add_filho($$, aux);
																					add_next(aux, $4);
																				}
						|	VOID ID LPAR RPAR									{
																					$$ = cria_no("MethodHeader");
																					add_filho($$, cria_no("Void"));
																					add_filho($$, new_id($2));
																				}
						;
FormalParams: 				Type ID FormalParamsRepetition						{
																					$$ = cria_no("MethodParams");
																					par = cria_no("ParamDecl");
																					add_filho($$, par);
																					add_next(par, $1);
																					aux = new_id($2);
																					add_next($1, aux);
																					add_next(aux, $3);
																				}				
						|	STRING LSQ RSQ ID									{
																					$$ = cria_no("MethodParams");
																					par = cria_no("ParamDecl");
																					add_filho($$, par);
																					add_filho(par, cria_no("StringArray"));
																					add_filho($$, new_id($4));
																				}
						;
FormalParamsRepetition:															{$$ = NULL;}
						| 	FormalParamsRepetition COMMA Type ID				{	
																					$$ = $1;
																					add_next($1, $3);
																					add_next($3, new_id($4));
																				}
						;
MethodBody:					LBRACE MethodBodyRepetition RBRACE					{	
																					$$ = cria_no("MethodBody");
																					add_filho($$, $2);
																				}
						;	
MethodBodyRepetition:															{$$ = NULL;}
						|	MethodBodyRepetition Statement						{$$ = $2;}
						|	MethodBodyRepetition VarDecl						{$$ = $2;}
						;
VarDecl:					Type ID CommaIDRepetition SEMICOLON					{
																					$$ = cria_no("VarDecl");
																					add_filho($$,$1);
																					aux = new_id($2);
																					add_next($1,aux);
																					add_next(aux, $3);
																				}
						;
Statement:					LBRACE StatementRepetition RBRACE					{$$ = $2;}
						|	IF LPAR Expr RPAR Statement %prec IF				{
																					aux = cria_no("If");
                                                            						add_filho(aux, $3);
                                                            						add_next($3, $5);
                                                            						add_next($5, cria_no("Block"));
                                                            						$$ = aux;
																				}
						|	IF LPAR Expr RPAR Statement ELSE Statement			{
																					aux = cria_no("If");
                                                            						add_filho(aux, $3);
                                                            						struct no* aux2 = cria_no("Else");
                                                            						add_next($3, $5);
                                                            						add_next($5, cria_no("Block"));
																					add_next(aux, aux2);
																					add_filho(aux2, $7);
                                                            						$$ = aux;
																				}
						|	WHILE LPAR Expr RPAR Statement						{
																					aux = cria_no("While");
                                                            						add_filho(aux, $3);
                                                            						add_next($3, $5);
                                                            						$$ = aux;
																				}
						|	RETURN Expr SEMICOLON								{
																					aux = cria_no("Return");
                                                            						add_filho(aux, $2);
                                                            						$$ = aux;
																				}
						|	RETURN SEMICOLON									{$$ = cria_no("Return");}
						|  	SEMICOLON											{$$ = NULL;}
						|	MethodInvocation SEMICOLON							{$$ = $1;}	
						|	Assignment SEMICOLON								{$$ = $1;}
						|   ParseArgs SEMICOLON									{$$ = $1;}
						|	PRINT LPAR Expr RPAR SEMICOLON						{
																					aux = cria_no("Print");
                                                            						add_filho(aux, $3);
                                                            						$$ = aux;
																				}
						|	PRINT LPAR STRLIT RPAR SEMICOLON					{
																					aux = cria_no("Print");
                                                            						add_filho(aux, new_strlit($3));
                                                            						$$ = aux;
																				}
						|	error SEMICOLON										{$$ = NULL;}
						;
StatementRepetition:															{$$ = NULL;}
						|	StatementRepetition Statement						{$$ = $2;}
						;
MethodInvocation: 			ID LPAR Expr CommaExprRepetition RPAR				{
																					$$ = new_id($1);
																					add_next($$, $3);
																					add_next($3, $4);
																				}
						|	ID LPAR RPAR										{$$ = new_id($1);}
						|	ID LPAR error RPAR									{$$ = NULL;}
						;
CommaExprRepetition:															{$$ = NULL;}
						|	CommaExprRepetition COMMA Expr						{$$ = $3;}
						;
Assignment:					ID ASSIGN Expr										{
																					$$ = new_id($1);
																					add_next($$, $3);
																				}
						;
ParseArgs:					PARSEINT LPAR ID LSQ Expr RSQ RPAR					{
																					$$ = cria_no("ParseArgs");
																					add_filho( $$,new_id($3)) ;
																					add_filho($$, $5);
																				}
						|	PARSEINT LPAR error RPAR							{$$ = NULL;}
						;
Expr:						Expr PLUS Expr										{
																					aux = cria_no("Plus");
																					add_filho(aux, $1);
																					add_filho(aux, $3);
																					$$ = aux;
																				}
						|	Expr MINUS Expr										{
																					aux = cria_no("Minus");
																					add_filho(aux, $1);
																					add_filho(aux, $3);
																					$$ = aux;
																				}
						|	Expr STAR Expr										{
																					aux = cria_no("Star");
																					add_filho(aux, $1);
																					add_filho(aux, $3);
																					$$ = aux;
																				}
						|	Expr DIV Expr										{
																					aux = cria_no("Div");
																					add_filho(aux, $1);
																					add_filho(aux, $3);
																					$$ = aux;
																				}
						|	Expr MOD Expr										{
																					aux = cria_no("Mod");
																					add_filho(aux, $1);
																					add_filho(aux, $3);
																					$$ = aux;
																				}
						|	Expr AND Expr										{
																					aux = cria_no("And");
																					add_filho(aux, $1);
																					add_filho(aux, $3);
																					$$ = aux;
																				}
						|	Expr OR  Expr										{
																					aux = cria_no("Or");
																					add_filho(aux, $1);
																					add_filho(aux, $3);
																					$$ = aux;
																				}
						|	Expr XOR Expr										{
																					aux = cria_no("Xor");
																					add_filho(aux, $1);
																					add_filho(aux, $3);
																					$$ = aux;
																				}
						|	Expr LSHIFT Expr									{
																					aux = cria_no("Lshift");
																					add_filho(aux, $1);
																					add_filho(aux, $3);
																					$$ = aux;
																				}
						|	Expr RSHIFT Expr									{
																					aux = cria_no("Rshift");
																					add_filho(aux, $1);
																					add_filho(aux, $3);
																					$$ = aux;
																				}
						|	Expr EQ Expr										{
																					aux = cria_no("Eq");
																					add_filho(aux, $1);
																					add_filho(aux, $3);
																					$$ = aux;
																				}
						|	Expr GE Expr										{
																					aux = cria_no("Ge");
																					add_filho(aux, $1);
																					add_filho(aux, $3);
																					$$ = aux;
																				}
						|	Expr GT Expr										{
																					aux = cria_no("Gt");
																					add_filho(aux, $1);
																					add_filho(aux, $3);
																					$$ = aux;
																				}
						|	Expr LE Expr										{
																					aux = cria_no("Le");
																					add_filho(aux, $1);
																					add_filho(aux, $3);
																					$$ = aux;
																				}
						|	Expr LT Expr										{
																					aux = cria_no("Lt");
																					add_filho(aux, $1);
																					add_filho(aux, $3);
																					$$ = aux;
																				}
						|	Expr NE Expr										{
																					aux = cria_no("Ne");
																					add_filho(aux, $1);
																					add_filho(aux, $3);
																					$$ = aux;
																				}
						|	MINUS Expr											{
																					aux = cria_no("Minus");
                            														add_filho(aux, $2);
                            														$$ = aux;
																				}
						|	NOT Expr											{
																					aux = cria_no("Not");
                            														add_filho(aux, $2);
                            														$$ = aux;
																				}
						|	PLUS Expr											{
																					aux = cria_no("Plus");
                            														add_filho(aux, $2);
                            														$$ = aux;
																				}
						|	LPAR Expr RPAR										{$$=$2;}
						|	MethodInvocation 									{$$ = $1;}
						|	Assignment 											{$$ = $1;}
						|	ParseArgs											{$$ = $1;}
						|	ID DOTLENGTH										{$$ = new_id($1);}
						|	ID 													{$$ = cria_no($1);}			
						|	INTLIT												{$$ = new_intlit($1);}
						|  	REALLIT 											{$$ = new_reallit($1);}
						|  	BOOLLIT												{$$ = new_boollit($1);}
						| 	LPAR error RPAR										{$$ = NULL;}
						;


%%

void yyerror ( char *s) {
	if(e2){
		if(yychar==STRLIT){
			printf("Line %d, col %d: %s: \"%s\"\n",ini_line,ini_col,s,yylval.str);
		}
		else{
			printf("Line %d, col %d: %s: %s\n",line_count,col_syntax,s,yytext);
		}
	}
}

