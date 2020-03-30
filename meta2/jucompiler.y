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

%type <no> Program Type MethodHeader MethodDecl ProgramRepetition FieldDecl
%type <str> ID INTLIT REALLIT STRLIT


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

Program: 			CLASS ID LBRACE ProgramRepetition RBRACE		{	
																		tree = cria_no("Program");
																		aux = new_id($2);
																		add_filho(tree, aux);
																		add_next(aux, $4);
																	}													
				;
ProgramRepetition:													{$$ = NULL;}							
				|	ProgramRepetition MethodDecl 					{add_next($1, $2); $$ = $1;}
				|	ProgramRepetition FieldDecl 					{add_next($1, $2); $$ = $1;}
				|	ProgramRepetition SEMICOLON						{$$ = $1;}
				;
MethodDecl: 		PUBLIC STATIC MethodHeader MethodBody			{	
																		aux = cria_no("MethodDecl");
																		add_next(tree, aux);
																		header = cria_no("MethodHeader");
																		add_filho(aux, header);
																		add_filho(header, $3);
                                                                        $$ = aux;
																	}
    				;
FieldDecl: 			PUBLIC STATIC Type ID CommaIDRepetition SEMICOLON {$$ = NULL;}
				|	error SEMICOLON									{$$ = NULL;}	
				;
CommaIDRepetition:			
				|	CommaIDRepetition COMMA ID 
				;	
Type:				BOOL 											{$$ = NULL;}
				| 	INT 											{$$ = NULL;}
				| 	DOUBLE											{$$ = NULL;}
				;
MethodHeader: 		Type ID LPAR FormalParams RPAR					{$$ =NULL;}
				|	Type ID LPAR RPAR
				|	VOID ID LPAR FormalParams RPAR					{$$ =NULL;}
				|	VOID ID LPAR RPAR								{$$ =NULL;}
				;
FormalParams: 		Type ID FormalParamsRepetition					
				|	STRING LSQ RSQ ID
				;
FormalParamsRepetition:			
				| 	FormalParamsRepetition COMMA Type ID
				;
MethodBody:				LBRACE MethodBodyRepetition RBRACE
				;	
MethodBodyRepetition:			
				|	MethodBodyRepetition Statement
				|	MethodBodyRepetition VarDecl
				;
VarDecl:				Type ID CommaIDRepetition SEMICOLON
				;
Statement:				LBRACE StatementRepetition RBRACE
				|	IF LPAR Expr RPAR Statement %prec IF
				|	IF LPAR Expr RPAR Statement ELSE Statement
				|	WHILE LPAR Expr RPAR Statement
				|	RETURN Expr SEMICOLON
				|	RETURN SEMICOLON		
				|  	SEMICOLON
				|	MethodInvocation SEMICOLON
				|	Assignment SEMICOLON
				|   	ParseArgs SEMICOLON
				|	PRINT LPAR Expr RPAR SEMICOLON
				|	PRINT LPAR STRLIT RPAR SEMICOLON
				|	error SEMICOLON
				;
StatementRepetition:			
				|	StatementRepetition Statement				
				;
MethodInvocation: 			ID LPAR Expr CommaExprRepetition RPAR
				|	ID LPAR  RPAR
				|	ID LPAR error RPAR
				;
CommaExprRepetition:			
				|	CommaExprRepetition COMMA Expr
				;
Assignment:				ID ASSIGN Expr
				;
ParseArgs:				PARSEINT LPAR ID LSQ Expr RSQ RPAR
				|	PARSEINT LPAR error RPAR
				;
Expr:				Expr PLUS Expr
				|	Expr MINUS Expr
				|	Expr STAR Expr
				|	Expr DIV Expr
				|	Expr MOD Expr
				|	Expr AND Expr
				|	Expr OR  Expr
				|	Expr XOR Expr
				|	Expr LSHIFT Expr
				|	Expr RSHIFT Expr
				|	Expr EQ Expr
				|	Expr GE Expr
				|	Expr GT Expr
				|	Expr LE Expr
				|	Expr LT Expr
				|	Expr NE Expr
				|	MINUS Expr
				|	NOT Expr
				|	PLUS Expr
				|	LPAR Expr RPAR
				|	MethodInvocation 
				|	Assignment 
				|	ParseArgs
				|	ID DOTLENGTH
				|	ID 									
				|	INTLIT
				|  	REALLIT 
				|  	BOOLLIT
				| 	LPAR error RPAR
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

