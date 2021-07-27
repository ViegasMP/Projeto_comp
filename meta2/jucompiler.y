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
int syntax_error = 0;
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
struct no* no_if;
struct no* elseblock;
struct no* no_call;
struct no* no_parse;
struct no* no_block;
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

Program: 				CLASS ID LBRACE RBRACE									{	
																					tree = cria_no("Program", NULL);
																					no_id = cria_no("Id",$2);
																					add_filho(tree, no_id);
																				}
						|	CLASS ID LBRACE ProgramRepetition RBRACE			{	
																					tree = cria_no("Program", NULL);
																					no_id = cria_no("Id",$2);
																					add_filho(tree, no_id);
																					add_irmao(no_id, $4);
																				}											
						;
ProgramRepetition:		ProgramRepetition MethodDecl 							{
																					aux = $1;
																					if(aux!=NULL){
																						add_irmao(aux,$2);
																						$$ = aux;
																					}else
																						$$ = $2;
																				}
						|	ProgramRepetition FieldDecl 						{
																					aux = $1;
																					if(aux!=NULL){
																						add_irmao(aux,$2);
																						$$ = aux;
																					}else
																						$$ = $2;
																				}
						|	ProgramRepetition SEMICOLON					 		{$$ = $1;}
						|	FieldDecl											{$$ = $1;}	
						|	MethodDecl											{$$ = $1;}
						|	SEMICOLON											{$$ = NULL;}
						;
MethodDecl: 			PUBLIC STATIC MethodHeader MethodBody					{	
																					aux = cria_no("MethodDecl", NULL);
																					add_filho(aux, $3);
																					add_irmao($3, $4);
																					$$=aux;
																				}		
    					;
FieldDecl: 				PUBLIC STATIC Type CommaIDRepetition SEMICOLON			{	
																					aux = cria_no("FieldDecl", NULL);
																					add_filho(aux, $3);
																					add_irmao($3, $4);
																					tratamentoIDRep(aux, $3);
																					$$ = aux;
																				}
						|	error SEMICOLON										{$$ = NULL;}
						;
CommaIDRepetition:		CommaIDRepetition COMMA ID 								{
																					aux = $1;
																					add_irmao(aux, cria_no("Id",$3));
																					$$=aux;
																				}
						|	ID													{$$ = cria_no("Id",$1);}
						;	
Type:						BOOL 												{$$ = cria_no("Bool", NULL);}
						| 	INT 												{$$ = cria_no("Int", NULL);}
						| 	DOUBLE												{$$ = cria_no("Double", NULL);}
						;
MethodHeader: 			Type ID LPAR FormalParams RPAR							{
																					header = cria_no("MethodHeader", NULL);
																					par = cria_no("MethodParams", NULL);
																					type = $1;
																					no_id = cria_no("Id", $2);
																					add_filho(header, type);
																					add_irmao(type, no_id);
																					add_irmao(no_id, par);
																					add_filho(par, $4);
																					$$ = header;
																				}
						|	Type ID LPAR RPAR									{
																					header = cria_no("MethodHeader", NULL);
																					par = cria_no("MethodParams", NULL);
																					type = $1;
																					no_id = cria_no("Id", $2);
																					add_filho(header, type);
																					add_irmao(type, no_id);
																					add_irmao(no_id, par);
																					$$ = header;
																				}
																				
						|	VOID ID LPAR FormalParams RPAR						{
																					header = cria_no("MethodHeader", NULL);
																					no_void = cria_no("Void", NULL);
																					par = cria_no("MethodParams", NULL);
																					no_id = cria_no("Id",$2);
																					add_filho(header, no_void);
																					add_irmao(no_void, no_id);
																					add_irmao(no_id, par);
																					add_filho(par, $4);
																					$$ = header;
																				}				
						|	VOID ID LPAR RPAR									{
																					header = cria_no("MethodHeader", NULL);
																					par = cria_no("MethodParams", NULL);
																					no_void =  cria_no("Void", NULL);
																					no_id = cria_no("Id",$2);
																					add_filho(header, no_void);
																					add_irmao(no_void, no_id);
																					add_irmao(no_id, par);
																					$$ = header;
																				}					
						;
FormalParams: 			Type ID FormalParamsRepetition							{
																					par = cria_no("ParamDecl", NULL);
																					add_filho(par, $1);
																					aux = cria_no("Id", $2);
																					add_irmao($1, aux);
																					add_irmao(par, $3);
																					$$ = par;
																				}	
						|	Type ID												{
																					par = cria_no("ParamDecl", NULL);
																					add_filho(par, $1);
																					aux = cria_no("Id", $2);
																					add_irmao($1, aux);
																					$$ = par;
																				}									
						|	STRING LSQ RSQ ID									{
																					par = cria_no("ParamDecl", NULL);
																					aux = cria_no("StringArray", NULL);
																					add_filho(par, aux);
																					add_irmao(aux, cria_no("Id",$4));
																					$$ = par;
																				}					
						;
FormalParamsRepetition:	COMMA Type ID FormalParamsRepetition					{	
																					par = cria_no("ParamDecl", NULL);
																					add_filho(par, $2);
																					add_irmao($2, cria_no("Id", $3));
																					add_irmao(par, $4);
																					$$ = par;
																				}
						|	COMMA Type ID										{	
																					par = cria_no("ParamDecl", NULL);
																					add_filho(par, $2);
																					add_irmao($2, cria_no("Id", $3));
																					$$ = par;
																				}
						;
MethodBody:				LBRACE MethodBodyRepetition RBRACE						{	
																					body = cria_no("MethodBody", NULL);
																					add_filho(body, $2);
																					$$ = body;
																				}
						|	LBRACE RBRACE										{$$ = cria_no("MethodBody", NULL);}														
						;
MethodBodyRepetition:	MethodBodyRepetition Statement							{
																					aux = $1;
																					if(aux!=NULL){
																						add_irmao(aux,$2);
																						$$ = aux;
																					}else
																						$$ = $2;
																				}
						|	MethodBodyRepetition VarDecl						{
																					aux = $1;
																					if(aux!=NULL){
																						add_irmao(aux,$2);
																						$$ = aux;
																					}else
																						$$ = $2;
																				}
						|	 Statement											{
																					$$ = $1;
																				}
						|	 VarDecl											{
																					$$ = $1;
																				}
						;
VarDecl:				Type CommaIDRepetition SEMICOLON						{
																					dcl = cria_no("VarDecl", NULL);
																					add_filho(dcl, $1);
																					add_irmao($1, $2);
																					tratamentoIDRep(dcl, $1);
																					$$=dcl;
																				}				
						;
Statement:				LBRACE RBRACE											{
																					$$ = NULL;
																				}
						|	LBRACE StatementRepetition RBRACE					{
																					aux = $2;
																					if(aux!=NULL){
																						if(check_irmao(aux)){
																							no_block = cria_no("Block", NULL);
																							add_filho(no_block, aux);
																							$$ = no_block;
																						} else{
																							$$ = aux;
																						}
																					} else {
																						$$=NULL;
																					}
																				}
						|	IF LPAR Expr RPAR Statement %prec IF				{
																					no_if = cria_no("If", NULL);
																					aux = $3;
                                                            						add_filho(no_if, aux);
																					no_block = cria_no("Block", NULL);
																					elseblock = cria_no("Block", NULL); 
																					if($5==NULL){
																						add_irmao(aux, no_block);
																						add_irmao(no_block, elseblock);
																					}else{
                                                            							add_irmao(aux, $5);
																						add_irmao($5, no_block);
																					}
																					$$ = no_if;
																				}
						|	IF LPAR Expr RPAR Statement ELSE Statement			{
																					no_if = cria_no("If", NULL);
																					aux = $3;
                                                            						add_filho(no_if, aux);
																					no_block = cria_no("Block", NULL);
																					elseblock = cria_no("Block", NULL); 
																					if($5==NULL && $7==NULL){
																						add_irmao(aux,no_block);
																						add_irmao(no_block,elseblock);
																					}else if($5!=NULL && $7==NULL){
																						add_irmao(aux,$5);
																						add_irmao($5,no_block);
																					}else if($5==NULL && $7!=NULL){
																						add_irmao(aux,elseblock);
																						add_irmao(elseblock,$7);
																					}else if($5!=NULL && $7!=NULL){
																						add_irmao(aux,$5);
																						add_irmao($5,$7);
																					}


																					$$=no_if;
																				}
						|	WHILE LPAR Expr RPAR Statement						{
																					aux = cria_no("While", NULL);
                                                            						add_filho(aux, $3);
																					no_block = cria_no("Block", NULL);
																					if($5==NULL){
																						add_irmao($3, no_block);
																					}else{
																						add_irmao($3, $5);
																					}
																					$$ = aux;
																				}
						|	RETURN Expr SEMICOLON								{
																					aux = cria_no("Return", NULL);
                                                            						add_filho(aux, $2);
																					$$ = aux;
																				}
						|	RETURN SEMICOLON									{$$ = cria_no("Return", NULL);}
						|  	SEMICOLON											{$$ = NULL;}
						|	MethodInvocation SEMICOLON							{$$ = $1;}	
						|	Assignment SEMICOLON								{$$ = $1;}
						|   ParseArgs SEMICOLON									{$$ = $1;}
						|	PRINT LPAR Expr RPAR SEMICOLON						{
																					aux = cria_no("Print", NULL);
                                                            						add_filho(aux, $3);
																					$$ = aux;
																				}
						|	PRINT LPAR STRLIT RPAR SEMICOLON					{
																					aux = cria_no("Print", NULL);
                                                            						add_filho(aux, cria_no("StrLit", $3));
																					$$ = aux;
																				}
						|	error SEMICOLON										{$$ = NULL;}
						;
StatementRepetition:	StatementRepetition Statement							{
																					aux = $1;
																					add_irmao(aux,$2);
																					$$ = aux;
																				}
						|	Statement											{
																					$$ = $1;
																				}
						;
MethodInvocation: 		ID LPAR Expr CommaExprRepetition RPAR					{
																					no_call = cria_no("Call", NULL);
																					aux = cria_no("Id", $1);
																					add_filho(no_call, aux);
																					add_irmao(aux, $3);
																					add_irmao($3, $4);
																					$$ = no_call;
																				}
						|	ID LPAR Expr RPAR									{
																					no_call = cria_no("Call", NULL);
																					aux = cria_no("Id", $1);
																					add_filho(no_call, aux);
																					add_irmao(aux, $3);
																					$$ = no_call;
																				}
						|	ID LPAR RPAR										{
                                                                        			no_call = cria_no("Call", NULL);
																					aux = cria_no("Id", $1);
                                                                        			add_filho(no_call, aux);
																					$$ = no_call;
                                                                    			}
						|	ID LPAR error RPAR									{$$ = NULL;}
						;
CommaExprRepetition:	COMMA Expr CommaExprRepetition 						{
																				aux = $2;
																				add_irmao(aux, $3);
																				$$ = aux;
																			}
						|	COMMA Expr										{$$ = $2;}
						;
Assignment:				ID ASSIGN Expr											{
																					assign = cria_no("Assign", NULL);
																					aux = cria_no("Id", $1);
																					add_filho(assign, aux);
																					add_irmao(aux, $3);
																					$$ = assign;
																				}
						;
ParseArgs:				PARSEINT LPAR ID LSQ Expr RSQ RPAR						{
																					no_parse = cria_no("ParseArgs", NULL);
																					aux = cria_no("Id", $3);
																					add_filho(no_parse, aux);
																					add_irmao(aux, $5);
																					$$ = no_parse;
																				}
						|	PARSEINT LPAR error RPAR							{$$ = NULL;}
						;
Expr:					Expr1													{$$ = $1;}
						| 	Assignment											{$$ = $1;}
						;
Expr1:					Expr1 PLUS Expr1										{
																					aux = cria_no("Add", NULL);
																					add_filho(aux, $1);
																					add_irmao($1, $3);
																					$$ = aux;
																				}
						|	Expr1 MINUS Expr1									{
																					aux = cria_no("Sub", NULL);
																					add_filho(aux, $1);
																					add_irmao($1, $3);
																					$$ = aux;
																				}
						|	Expr1 STAR Expr1									{
																					aux = cria_no("Mul", NULL);
																					add_filho(aux, $1);
																					add_irmao($1, $3);
																					$$ = aux;
																				}
						|	Expr1 DIV Expr1										{
																					aux = cria_no("Div", NULL);
																					add_filho(aux, $1);
																					add_irmao($1, $3);
																					$$ = aux;
																				}
						|	Expr1 MOD Expr1										{
																					aux = cria_no("Mod", NULL);
																					add_filho(aux, $1);
																					add_irmao($1, $3);
																					$$ = aux;
																				}
						|	Expr1 AND Expr1										{
																					aux = cria_no("And", NULL);
																					add_filho(aux, $1);
																					add_irmao($1, $3);
																					$$ = aux;
																				}
						|	Expr1 OR  Expr1										{
																					aux = cria_no("Or", NULL);
																					add_filho(aux, $1);
																					add_irmao($1, $3);
																					$$ = aux;
																				}
						|	Expr1 XOR Expr1										{
																					aux = cria_no("Xor", NULL);
																					add_filho(aux, $1);
																					add_irmao($1, $3);
																					$$ = aux;
																				}
						|	Expr1 LSHIFT Expr1									{
																					aux = cria_no("Lshift", NULL);
																					add_filho(aux, $1);
																					add_irmao($1, $3);
																					$$ = aux;
																				}
						|	Expr1 RSHIFT Expr1									{
																					aux = cria_no("Rshift", NULL);
																					add_filho(aux, $1);
																					add_irmao($1, $3);
																					$$ = aux;
																				}
						|	Expr1 EQ Expr1										{
																					aux = cria_no("Eq", NULL);
																					add_filho(aux, $1);
																					add_irmao($1, $3);
																					$$ = aux;
																				}
						|	Expr1 GE Expr1										{
																					aux = cria_no("Ge", NULL);
																					add_filho(aux, $1);
																					add_irmao($1, $3);
																					$$ = aux;
																				}
						|	Expr1 GT Expr1										{
																					aux = cria_no("Gt", NULL);
																					add_filho(aux, $1);
																					add_irmao($1, $3);
																					$$ = aux;
																				}
						|	Expr1 LE Expr1										{
																					aux = cria_no("Le", NULL);
																					add_filho(aux, $1);
																					add_irmao($1, $3);
																					$$ = aux;
																				}
						|	Expr1 LT Expr1										{
																					aux = cria_no("Lt", NULL);
																					add_filho(aux, $1);
																					add_irmao($1, $3);
																					$$ = aux;
																				}
						|	Expr1 NE Expr1										{
																					aux = cria_no("Ne", NULL);
																					add_filho(aux, $1);
																					add_irmao($1, $3);
																					$$ = aux;
																				}
						|	MINUS Expr1	%prec NOT								{
																					aux = cria_no("Minus", NULL);
                            														add_filho(aux, $2);
																					$$ = aux;
																				}
						|	NOT Expr1											{
																					aux = cria_no("Not", NULL);
                            														add_filho(aux, $2);
																					$$ = aux;
																				}
						|	PLUS Expr1 %prec NOT								{
																					aux = cria_no("Plus", NULL);
                            														add_filho(aux, $2);
																					$$ = aux;
																				}
						|	LPAR Expr RPAR										{$$=$2;}
						|	MethodInvocation 									{$$ = $1;}
						|	ParseArgs											{$$ = $1;}
						|	ID DOTLENGTH										{
																					aux = cria_no("Length", NULL);
																					add_filho(aux,cria_no("Id",$1));
																					$$=aux;
																				}
						|	ID 													{$$ = cria_no("Id",$1);}			
						|	INTLIT												{$$ = cria_no("DecLit",$1);}
						|  	REALLIT 											{$$ = cria_no("RealLit",$1);}
						|  	BOOLLIT												{$$ = cria_no("BoolLit",$1);}
						| 	LPAR error RPAR										{$$ = NULL;}
						;


%%

void yyerror ( char *s) {
	syntax_error = 1;
	if(e2){
		if(yychar==STRLIT){
			printf("Line %d, col %d: %s: \"%s\n",ini_line,ini_col,s,yylval.str);

		}
		else{
			printf("Line %d, col %d: %s: %s\n",line_count,col_syntax,s,yytext);
		}
	}
}
