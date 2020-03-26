%{
/*
		Carolina de Castilho Godinho	-	2017247087
		Maria Paula de Alencar Viegas	-	2017125592
*/
%}
%{
    #include <stdio.h>
    int yylex(void);
    void yyerror (const char *s);
%}

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

%left OR AND
%left EQ NE LT LE GT GE
%left PLUS MINUS
%left STAR DIV MOD
%left COMMA
%right ASSIGN
%right NOT

%%

%{
/*
		TIRAR os '{' '}'- significa 0 ou mais repetições
*/
%}
programRepetition:													{$$ = NULL;}
		|		programRepetition MethodDecl 
		|		programRepetition FieldDecl 
		|		programRepetition  SEMICOLON
		;
program: 	CLASS ID LBRACE programRepetition RBRACE
		;
MethodDecl: 	PUBLIC STATIC MethodHeader MethodBody
    	;
CommaIDRepetition:													{$$ = NULL;}
			|		 CommaIDRepetition COMMA ID 
			;	
FieldDecl: 		PUBLIC STATIC Type ID CommaIDRepetition SEMICOLON
		|		error SEMICOLON
		;
Type:		BOOL 
		| 	INT 
		| 	DOUBLE
		;
MethodHeader: 		Type ID LPAR FormalParams RPAR
		|			Type ID LPAR RPAR
		|			VOID ID LPAR FormalParams RPAR
		|			VOID ID LPAR RPAR
		;
FormalParamsRepetition:												{$$ = NULL;}
				| 		FormalParamsRepetition COMMA Type ID
				;

FormalParams: 		Type ID FormalParamsRepetition
			|		STRING LSQ RSQ ID
		;
MethodBodyRepetition:												{$$ = NULL;}
			|		 MethodBodyRepetition Statement
			|		MethodBodyRepetition VarDecl
			;
MethodBody:		LBRACE MethodBodyRepetition RBRACE
		;	
VarDecl:		Type ID CommaIDRepetition SEMICOLON
		;
StatementRepetition:												{$$ = NULL;}
				|		StatementRepetition Statement				
				;
Statement:	LBRACE StatementRepetition RBRACE
		|	IF LPAR Expr RPAR Statement
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
CommaExprRepetition:												{$$ = NULL;}
				|	CommaExprRepetition COMMA Expr
				;
MethodInvocation: 	ID LPAR Expr CommaExprRepetition RPAR
			|		ID LPAR  RPAR
			|		ID LPAR error RPAR
			;
Assignment:		ID ASSIGN Expr
		;
ParseArgs:		PARSEINT LPAR ID LSQ Expr RSQ LPAR
		|		PARSEINT LPAR error RPAR
		;
Expr:		Expr PLUS Expr
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
		|   REALLIT 
		|   BOOLLIT
		| 	LPAR error RPAR
		;


%%

int main() {
    yyparse();
    return 0;
}

