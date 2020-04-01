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
struct no* dcl;
struct no* body;
struct no* par;
struct no* assign;
struct no* no_void;
struct no* no_id;
struct no* header;
%}

%union{
	char * str;
	struct no* no;
}

%type <no> Program MethodHeader MethodDecl ProgramRepetition FieldDecl MethodBody Type FormalParamsRepetition FormalParams CommaIDRepetition MethodBodyRepetition Statement VarDecl StatementRepetition Expr MethodInvocation Assignment ParseArgs CommaExprRepetition Expr1
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

Program: 				CLASS ID LBRACE ProgramRepetition RBRACE				{	
																					tree = cria_no("Program", NULL);
																					no_id = cria_no("Id",$2);
																					add_filho(tree, no_id);
																					add_irmao(no_id, $4);
																				}											
						;
ProgramRepetition:																{$$ = NULL;}							
						|	ProgramRepetition MethodDecl 						{$$ = $2;}
						|	ProgramRepetition FieldDecl 						{$$ = $2;}
						|	ProgramRepetition SEMICOLON							{$$ = $1;}		
						;
MethodDecl: 			PUBLIC STATIC MethodHeader MethodBody					{	
																					$$ = cria_no("MethodDecl", NULL);
																					add_filho($$, $3);
																					add_irmao($3, $4);
																				}		
    					;
FieldDecl: 				PUBLIC STATIC Type ID CommaIDRepetition SEMICOLON		{	
																					$$ = cria_no("FieldDecl", NULL);
																					add_filho($$, $3);
																					no_id = cria_no("Id",$4);
																					add_irmao($3, no_id);
																					add_irmao(no_id, $5);
																				}
						|	error SEMICOLON										{$$ = NULL;}
						;
CommaIDRepetition:																{$$ = NULL;}						
						|	CommaIDRepetition COMMA ID 							{
																					$$ = $1;
																					add_irmao($$, cria_no("ID",$3));
																				}			
						;	
Type:						BOOL 												{$$ = cria_no("Bool", NULL);}
						| 	INT 												{$$ = cria_no("Int", NULL);}
						| 	DOUBLE												{$$ = cria_no("Double", NULL);}
						;
MethodHeader: 			Type ID LPAR FormalParams RPAR							{
																					header = cria_no("MethodHeader", NULL);
																					par = cria_no("MethodParams", NULL);
																					type = $1;
																					no_id = cria_no("ID", $2);
																					add_filho(header, type);
																					add_irmao(type, no_id);
																					add_irmao(no_id, par);
																					add_irmao(par, $4);
																					$$ = header;
																				}
						|	Type ID LPAR RPAR									{
																					header = cria_no("MethodHeader", NULL);
																					par = cria_no("MethodParams", NULL);
																					type = $1;
																					no_id = cria_no("ID", $2);
																					add_filho(header, type);
																					add_irmao(type, no_id);
																					add_irmao(no_id, par);
																					$$ = header;
																				}
																				
						|	VOID ID LPAR FormalParams RPAR						{
																					header = cria_no("MethodHeader", NULL);
																					no_void = cria_no("Void", NULL);
																					par = cria_no("MethodParams", NULL);
																					no_id = cria_no("ID",$2);
																					add_filho(header, no_void);
																					add_irmao(no_void, no_id);
																					add_irmao(no_id, par);
																					add_irmao(par, $4);
																					$$ = header;
																				}				
						|	VOID ID LPAR RPAR									{
																					header = cria_no("MethodHeader", NULL);
																					par = cria_no("MethodParams", NULL);
																					no_void =  cria_no("Void", NULL);
																					no_id = cria_no("ID",$2);
																					add_filho(header, no_void);
																					add_irmao(no_void, no_id);
																					add_irmao(no_id, par);
																					$$ = header;
																				}					
						;
FormalParams: 			Type ID FormalParamsRepetition							{
																					par = cria_no("ParamDecl", NULL);
																					add_filho($$, par);
																					add_filho(par, $1);
																					aux = cria_no("ID", $2);
																					add_irmao($1, aux);
																					add_irmao(aux, $3);
																					$$ = par;
																				}									
						|	STRING LSQ RSQ ID									{
																					par = cria_no("ParamDecl", NULL);
																					aux = cria_no("StringArray", NULL);
																					add_filho($$, par);
																					add_filho(par, aux);
																					add_irmao(aux, cria_no("ID",$4));
																					$$ = par;
																				}					
						;
FormalParamsRepetition:															{$$ = NULL;}
						| 	FormalParamsRepetition COMMA Type ID				{	
																					$$ = $1;
																					add_irmao($1, $3);
																					add_irmao($3, cria_no("ID", $4));
																				}
						;
MethodBody:				LBRACE MethodBodyRepetition RBRACE						{	
																					$$ = cria_no("MethodBody", NULL);
																					add_filho($$, $2);
																				}
						;
MethodBodyRepetition:															{$$ = NULL;}
						|	MethodBodyRepetition Statement						{$$ = $2;}
						|	MethodBodyRepetition VarDecl						{$$ = $2;}
						;
VarDecl:				Type ID CommaIDRepetition SEMICOLON						{
																					$$ = cria_no("VarDecl", NULL);
																					add_filho($$, $1);
																					aux = cria_no("ID",$2);
																					add_irmao($1,aux);
																					add_irmao(aux, $3);
																				}				
						;
Statement:				LBRACE StatementRepetition RBRACE						{$$ = $2;}
						|	IF LPAR Expr RPAR Statement %prec IF				{
																					$$ = cria_no("If", NULL);
                                                            						add_filho($$, $3);
                                                            						add_irmao($3, $5);
                                                            						add_irmao($5, cria_no("Block", NULL));
																				}
						|	IF LPAR Expr RPAR Statement ELSE Statement			{
																					$$ = cria_no("If", NULL);
                                                            						add_filho($$, $3);
                                                            						aux = cria_no("Else", NULL);
                                                            						add_irmao($3, $5);
                                                            						add_irmao($5, cria_no("Block", NULL));
																					add_irmao($$, aux);
																					add_filho(aux, $7);
																				}
						|	WHILE LPAR Expr RPAR Statement						{
																					$$ = cria_no("While", NULL);
                                                            						add_filho($$, $3);
                                                            						add_irmao($3, $5);
																				}
						|	RETURN Expr SEMICOLON								{
																					$$ = cria_no("Return", NULL);
                                                            						add_filho($$, $2);
																				}
						|	RETURN SEMICOLON									{$$ = cria_no("Return", NULL);}
						|  	SEMICOLON											{$$ = NULL;}
						|	MethodInvocation SEMICOLON							{$$ = $1;}	
						|	Assignment SEMICOLON								{$$ = $1;}
						|   ParseArgs SEMICOLON									{$$ = $1;}
						|	PRINT LPAR Expr RPAR SEMICOLON						{
																					$$ = cria_no("Print", NULL);
                                                            						add_filho($$, $3);
																				}
						|	PRINT LPAR STRLIT RPAR SEMICOLON					{
																					$$ = cria_no("Print", NULL);
																					aux = cria_no("StrLit", $3);
                                                            						add_filho($$, aux);
																				}
						|	error SEMICOLON										{$$ = NULL;}
						;
StatementRepetition:															{$$ = NULL;}
						|	StatementRepetition Statement						{$$ = $2;}
						;
MethodInvocation: 		ID LPAR Expr CommaExprRepetition RPAR					{
																					$$ = cria_no("Call", NULL);
																					aux = cria_no("ID", NULL);
																					add_filho($$, aux);
																					add_irmao(aux, $3);
																					add_irmao($3, $4);
																				}
						|	ID LPAR RPAR										{
                                                                        			$$ = cria_no("Call", NULL);
																					aux = cria_no("ID", $1);
                                                                        			add_filho($$, aux);
                                                                    			}
						|	ID LPAR error RPAR									{$$ = NULL;}
						;
CommaExprRepetition:															{$$ = NULL;}
						|	CommaExprRepetition COMMA Expr						{$$ = $3;}
						;
Assignment:				ID ASSIGN Expr											{
																					$$ = cria_no("Assign", NULL);
																					aux = cria_no("ID", $1);
																					add_filho(assign, aux);
																					add_irmao(aux, $3);
																				}
						;
ParseArgs:				PARSEINT LPAR ID LSQ Expr RSQ RPAR						{
																					$$ = cria_no("ParseArgs", NULL);
																					aux = cria_no("ID", $3);
																					add_filho($$, aux) ;
																					add_irmao(aux, $5);
																				}
						|	PARSEINT LPAR error RPAR							{$$ = NULL;}
						;
Expr:					Expr1													{$$ = $1;}
						| 	Assignment											{$$ = $1;}
						;
Expr1:					Expr1 PLUS Expr1										{
																					$$ = cria_no("Plus", NULL);
																					add_filho($$, $1);
																					add_irmao($1, $3);
																				}
						|	Expr1 MINUS Expr1									{
																					$$ = cria_no("Minus", NULL);
																					add_filho($$, $1);
																					add_irmao($1, $3);
																				}
						|	Expr1 STAR Expr1									{
																					$$ = cria_no("Mul", NULL);
																					add_filho($$, $1);
																					add_irmao($1, $3);
																				}
						|	Expr1 DIV Expr1										{
																					$$ = cria_no("Div", NULL);
																					add_filho($$, $1);
																					add_irmao($1, $3);
																				}
						|	Expr1 MOD Expr1										{
																					$$ = cria_no("Mod", NULL);
																					add_filho($$, $1);
																					add_irmao($1, $3);
																				}
						|	Expr1 AND Expr1										{
																					$$ = cria_no("And", NULL);
																					add_filho($$, $1);
																					add_irmao($1, $3);
																				}
						|	Expr1 OR  Expr1										{
																					$$ = cria_no("Or", NULL);
																					add_filho($$, $1);
																					add_irmao($1, $3);
																				}
						|	Expr1 XOR Expr1										{
																					$$ = cria_no("Xor", NULL);
																					add_filho($$, $1);
																					add_irmao($1, $3);
																				}
						|	Expr1 LSHIFT Expr1									{
																					$$ = cria_no("Lshift", NULL);
																					add_filho($$, $1);
																					add_irmao($1, $3);
																				}
						|	Expr1 RSHIFT Expr1									{
																					$$ = cria_no("Rshift", NULL);
																					add_filho($$, $1);
																					add_irmao($1, $3);
																				}
						|	Expr1 EQ Expr1										{
																					$$ = cria_no("Eq", NULL);
																					add_filho($$, $1);
																					add_irmao($1, $3);
																				}
						|	Expr1 GE Expr1										{
																					$$ = cria_no("Ge", NULL);
																					add_filho($$, $1);
																					add_irmao($1, $3);
																				}
						|	Expr1 GT Expr1										{
																					$$ = cria_no("Gt", NULL);
																					add_filho($$, $1);
																					add_irmao($1, $3);
																				}
						|	Expr1 LE Expr1										{
																					$$ = cria_no("Le", NULL);
																					add_filho($$, $1);
																					add_irmao($1, $3);
																				}
						|	Expr1 LT Expr1										{
																					$$ = cria_no("Lt", NULL);
																					add_filho($$, $1);
																					add_irmao($1, $3);
																				}
						|	Expr1 NE Expr1										{
																					$$ = cria_no("Ne", NULL);
																					add_filho($$, $1);
																					add_irmao($1, $3);
																				}
						|	MINUS Expr1	%prec NOT								{
																					$$ = cria_no("Minus", NULL);
                            														add_filho($$, $2);
																				}
						|	NOT Expr1											{
																					$$ = cria_no("Not", NULL);
                            														add_filho($$, $2);
																				}
						|	PLUS Expr1 %prec NOT								{
																					$$ = cria_no("Plus", NULL);
                            														add_filho($$, $2);
																				}
						|	LPAR Expr RPAR										{$$=$2;}
						|	MethodInvocation 									{$$ = $1;}
						|	ParseArgs											{$$ = $1;}
						|	ID DOTLENGTH										{$$ = cria_no("ID",$1);}
						|	ID 													{$$ = cria_no("ID",$1);}			
						|	INTLIT												{$$ = cria_no("Declit",$1);}
						|  	REALLIT 											{$$ = cria_no("RealLit",$1);}
						|  	BOOLLIT												{$$ = cria_no("BoolLit",$1);}
						| 	LPAR error RPAR										{$$ = NULL;}
						;


%%

void yyerror ( char *s) {
	if(e2){
		if(yychar==STRLIT){
			printf("Line %d, col %d: %s: \"%s\n",ini_line,ini_col,s,yylval.str);

		}
		else{
			printf("Line %d, col %d: %s: %s\n",line_count,col_syntax,s,yytext);
		}
	}
}

