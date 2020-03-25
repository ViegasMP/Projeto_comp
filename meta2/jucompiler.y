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

%%

%{
/*
		TIRAR os '{' '}'- significa 0 ou mais repetições
*/
%}

program: 	CLASS ID LBRACE { MethodDecl | FieldDecl | SEMICOLON } RBRACE
		;
MethodDecl: 	PUBLIC STATIC MethodHeader MethodBody
    		;
FieldDecl: 		PUBLIC STATIC Type ID { COMMA ID } SEMICOLON
		;
Type: 			BOOL | INT | DOUBLE
		;
MethodHeader: 		( Type | VOID ) ID LPAR [ FormalParams ] RPAR
		;
FormalParams: 		Type ID { COMMA Type ID }
			|	STRING LSQ RSQ ID
		;
MethodBody:		LBRACE { Statement | VarDecl } RBRACE
		;
VarDecl:		Type ID { COMMA ID } SEMICOLON
		;
Statement:		LBRACE { Statement } RBRACE
		|	IF LPAR Expr RPAR Statement [ ELSE Statement ]
		|	WHILE LPAR Expr RPAR Statement
		|	RETURN [ Expr ] SEMICOLON
		|	[ ( MethodInvocation | Assignment | ParseArgs ) ] SEMICOLON
		|	PRINT LPAR ( Expr | STRLIT ) RPAR SEMICOLON
		;
MethodInvocation: 	ID LPAR [ Expr { COMMA Expr } ] RPAR
		;
Assignment:		ID ASSIGN Expr
		;
ParseArgs:		PARSEINT LPAR ID LSQ Expr RSQ LPAR
		;
Expr:			Expr ( PLUS | MINUS | STAR | DIV | MOD ) Expr
		|	Expr ( AND | OR | XOR | LSHIFT | RSHIFT ) Expr
		|	Expr ( EQ | GE | GT | LE | LT | NE ) Expr
		|	( MINUS | NOT | PLUS ) Expr
		|	LPAR Expr RPAR
		|	MethodInvocation | Assignment | ParseArgs
		|	ID [ DOTLENGTH ]
		|	INTLIT | REALLIT | BOOLLIT
		;


%%

int main() {
    yyparse();
    return 0;
}

