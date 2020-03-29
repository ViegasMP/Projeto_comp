%{
/*
		Carolina de Castilho Godinho	-	2017247087
		Maria Paula de Alencar Viegas	-	2017125592
		Correr com:
		lex jucompiler.l
		yacc -d jucompiler.y
		cc -o jucompiler y.tab.c lex.yy.c
		diff field_decl.out out.out 

*/
%}
%{
    #include <stdio.h>
	#include <stdbool.h> 
	#include "y.tab.h"
	#include "tree_functions.h"
	int yylex(void);
	void yyerror (char *s);
	extern char* yytext;
	extern int line_count;
	extern int col_count;
	extern int ini_line; //guarda linha em que começa comentario ou string
	extern int ini_col; //guarda coluna em que começa comentario ou string
	extern bool p;
	struct no* tree;
	struct no* aux = NULL;
%}

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

%union {
	char* s;
	struct no* no;
};

%type <no> program programRepetition MethodDecl FieldDecl

%%

program: 			CLASS ID LBRACE programRepetition RBRACE					{tree = cria_no("Program"); add_filho(tree, $);$$ = tree;}
				;
programRepetition:			
				|	programRepetition MethodDecl 								{if ($1 != NULL){$$ = $1; add_next($1, $2);} else {$$ = $2;}}
				|	programRepetition FieldDecl 								{if ($1 != NULL){$$ = $1; add_next($1, $2);} else {$$ = $2;}}
				|	programRepetition  SEMICOLON								{if ($1 != NULL){$$ = $1; add_next($1, $2);} else {$$ = $2;}}
				;
MethodDecl: 		PUBLIC STATIC MethodHeader MethodBody
    			;
FieldDecl: 			PUBLIC STATIC Type ID CommaIDRepetition SEMICOLON
				|	error SEMICOLON
				;
CommaIDRepetition:			
				|	CommaIDRepetition COMMA ID 
				;	
Type:				BOOL 
				| 	INT 
				| 	DOUBLE
				;
MethodHeader: 		Type ID LPAR FormalParams RPAR
				|	Type ID LPAR RPAR
				|	VOID ID LPAR FormalParams RPAR
				|	VOID ID LPAR RPAR
				;
FormalParams: 		Type ID FormalParamsRepetition
				|	STRING LSQ RSQ ID
				;
FormalParamsRepetition:			
				| 	FormalParamsRepetition COMMA Type ID
				;
MethodBody:			LBRACE MethodBodyRepetition RBRACE
				;	
MethodBodyRepetition:			
				|	MethodBodyRepetition Statement
				|	MethodBodyRepetition VarDecl
				;
VarDecl:			Type ID CommaIDRepetition SEMICOLON
				;
Statement:			LBRACE StatementRepetition RBRACE
				|	IF LPAR Expr RPAR Statement %prec IF
				|	IF LPAR Expr RPAR Statement ELSE Statement
				|	WHILE LPAR Expr RPAR Statement
				|	RETURN Expr SEMICOLON
				|	RETURN SEMICOLON		
				|   SEMICOLON
				|	MethodInvocation SEMICOLON
				|	Assignment SEMICOLON
				|   ParseArgs SEMICOLON
				|	PRINT LPAR Expr RPAR SEMICOLON
				|	PRINT LPAR STRLIT RPAR SEMICOLON
				|	error SEMICOLON
				;
StatementRepetition:			
				|	StatementRepetition Statement				
				;
MethodInvocation: 	ID LPAR Expr CommaExprRepetition RPAR
				|	ID LPAR  RPAR
				|	ID LPAR error RPAR
				;
CommaExprRepetition:			
				|	CommaExprRepetition COMMA Expr
				;
Assignment:			ID ASSIGN Expr
				;
ParseArgs:			PARSEINT LPAR ID LSQ Expr RSQ RPAR
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

void yyerror (char *s) {
	if (p){
		printf("Line %d, col %d: %s: %s\n",line_count,col_count,s,yytext);
	}
}
