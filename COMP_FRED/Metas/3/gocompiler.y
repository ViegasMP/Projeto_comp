/* 
	2012138904, Frederico Cardoso
	2015237457, Renato Santos 

	Meta 2
*/



%{
    #include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "ast.h"

	void yyerror(char *s);
	int yylex(void);

	node *aux_node = NULL;			/* Nó auxiliar usado para recursões e outros casos */

	node *root = NULL;	
	node *vardecl = NULL;
	node *type = NULL;
	node *id = NULL;
	node *fdecl = NULL;
	node *fheader = NULL;
	node *fbody = NULL;
	node *fparams = NULL;
	node *paramdecl = NULL;
	node *statement = NULL;

									/* Nós para blocos */
	node *block;
	node *ifnode = NULL;
	node *fornode = NULL;
	node *retnode = NULL;
	node *ifblock = NULL;
	node *elseblock = NULL;
	node *forblock = NULL;

									/* Outros nós */
	node *statelist = NULL;
	node *parseargs = NULL;
	node *print = NULL;
	node *strlit = NULL;

									/* Nós para expressões */
	node *expr = NULL;
	node *or = NULL;
	node *and = NULL;
	node *eq = NULL;
	node *ne = NULL;
	node *lt = NULL;
	node *gt = NULL;
	node *le = NULL;
	node *ge = NULL;
	node *add = NULL;
	node *sub = NULL;
	node *mult = NULL;
	node *divi = NULL;
	node *mod = NULL;
	node *not = NULL;
	node *minus = NULL;
	node *plus = NULL;
	node *assign = NULL;
	node *call = NULL;

	int debug = 0; 			/* Variável de ouro, ajudou imenso no debug :) */
%}



%token SEMICOLON
%token BLANKID
%token PACKAGE
%token RETURN
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
%token ELSE
%token FOR
%token IF
%token VAR
%token INT
%token FLOAT32
%token BOOL
%token STRING
%token PRINT
%token PARSEINT
%token FUNC
%token CMDARGS


%union{
	char *val;
	struct node *node;
}


%token <val> ID
%token <val> INTLIT
%token <val> REALLIT
%token <val> STRLIT
%token <val> RESERVED


%type <node> Program
%type <node> Declarations
%type <node> DeclarationList
%type <node> VarDeclaration
%type <node> VarSpec
%type <node> IDList
%type <node> Type
%type <node> FuncDeclaration
%type <node> Parameters
%type <node> IDTypeList
%type <node> FuncBody
%type <node> VarsAndStatements
%type <node> Statement
%type <node> StatementSemiList
%type <node> ParseArgs
%type <node> FuncInvocation
%type <node> ExprList
%type <node> Expr


%left COMMA
%right ASSIGN

%left OR 
%left AND
%left LT LE GT GE EQ NE
%left PLUS MINUS
%left STAR DIV MOD

%right NOT
%left LPAR RPAR LSQ RSQ

%nonassoc IF ELSE FOR





%%





Program:
		PACKAGE ID SEMICOLON 						{root = create_node("Program", NULL); 							$$ = root;}
	|	PACKAGE ID SEMICOLON Declarations			{root = create_node("Program", NULL); add_child(root, $4);  	$$ = root;}
	;


Declarations:
		DeclarationList			{$$ = $1;}
	;


DeclarationList:
		DeclarationList VarDeclaration SEMICOLON		{aux_node = $1; add_brother(aux_node, $2); 		$$ = aux_node;}
	|	DeclarationList FuncDeclaration	SEMICOLON 		{aux_node = $1; add_brother(aux_node, $2); 		$$ = aux_node;}
	|	VarDeclaration SEMICOLON 						{$$ = $1;}
	|	FuncDeclaration SEMICOLON 						{$$ = $1;}
	;


VarDeclaration:
		VAR VarSpec 							{$$ = $2;}
	| 	VAR LPAR VarSpec SEMICOLON RPAR 		{$$ = $3;}
	;

VarSpec:
		IDList Type 		{aux_node = $1; 	add_first_child_varDecl(aux_node, $2); 		$$ = aux_node;}
	;

IDList:
		IDList COMMA ID 		{vardecl = create_node("VarDecl", NULL); id = create_node("Id", $3); add_child(vardecl, id); 	aux_node = $1; add_brother(aux_node, vardecl); 		$$ = aux_node;}
	|	ID 						{vardecl = create_node("VarDecl", NULL); id = create_node("Id", $1); add_child(vardecl, id); 														$$ = vardecl;}
	;

Type:
		INT 			{$$ = create_node("Int", NULL);}
	|	FLOAT32 		{$$ = create_node("Float32", NULL);}
	| 	BOOL 			{$$ = create_node("Bool", NULL);}
	| 	STRING 			{$$ = create_node("String", NULL);}
	;


FuncDeclaration:
		FUNC ID LPAR RPAR FuncBody 		 				{fdecl = create_node("FuncDecl", NULL); fheader = create_node("FuncHeader", NULL); add_child(fdecl, fheader); id = create_node("Id", $2); add_child(fheader, id); 			fparams = create_node("FuncParams", NULL); add_brother(id, fparams); 														fbody = create_node("FuncBody", NULL); add_brother(fheader, fbody); add_child(fbody, $5); $$ = fdecl;}
	| 	FUNC ID LPAR Parameters RPAR FuncBody			{fdecl = create_node("FuncDecl", NULL); fheader = create_node("FuncHeader", NULL); add_child(fdecl, fheader); id = create_node("Id", $2); add_child(fheader, id); 			fparams = $4; add_brother(id, fparams); 																										fbody = create_node("FuncBody", NULL); add_brother(fheader, fbody); add_child(fbody, $6); $$ = fdecl;}
	|	FUNC ID LPAR RPAR Type FuncBody 				{fdecl = create_node("FuncDecl", NULL); fheader = create_node("FuncHeader", NULL); add_child(fdecl, fheader); id = create_node("Id", $2); add_child(fheader, id); 			type = $5; add_brother(id, type); fparams = create_node("FuncParams", NULL); add_brother(type, fparams); 					fbody = create_node("FuncBody", NULL); add_brother(fheader, fbody); add_child(fbody, $6); $$ = fdecl;}
	|	FUNC ID LPAR Parameters RPAR Type FuncBody 		{fdecl = create_node("FuncDecl", NULL); fheader = create_node("FuncHeader", NULL); add_child(fdecl, fheader); id = create_node("Id", $2); add_child(fheader, id); 			type = $6; add_brother(id, type); fparams = $4; add_brother(type, fparams); 												fbody = create_node("FuncBody", NULL); add_brother(fheader, fbody); add_child(fbody, $7); $$ = fdecl;}
	;


Parameters:
		IDTypeList 				{fparams = create_node("FuncParams", NULL); add_child(fparams, $1); $$ = fparams;}
	;


IDTypeList:
		IDTypeList COMMA ID Type 		{paramdecl = create_node("ParamDecl", NULL); id = create_node("Id", $3); 	type = $4; add_brother(type, id); add_child(paramdecl, type); 	aux_node = $1; add_brother(aux_node, paramdecl); 	$$ = aux_node;}
	| 	ID Type 						{paramdecl = create_node("ParamDecl", NULL); id = create_node("Id", $1); 	type = $2; add_brother(type, id); add_child(paramdecl, type); 													 	$$ = paramdecl;}
	;


FuncBody:
		LBRACE VarsAndStatements RBRACE			{$$ = $2;}
	;


VarsAndStatements:
		VarsAndStatements SEMICOLON						{aux_node = $1; if(aux_node != NULL) {$$ = aux_node;}}
	|	VarsAndStatements VarDeclaration SEMICOLON		{aux_node = $1; vardecl = $2; if(aux_node != NULL) {add_brother(aux_node, vardecl); $$ = aux_node;} else {$$ = vardecl;} }
	| 	VarsAndStatements Statement SEMICOLON 			{aux_node = $1; statement = $2; if(aux_node != NULL) {if(statement != NULL) add_brother(aux_node, statement); $$ = aux_node;} else {$$ = statement;};} 

	|	%empty											{$$ = NULL;}
	;

Statement:
		ID ASSIGN Expr																	{assign = create_node("Assign", NULL); id = create_node("Id", $1); expr = $3; add_child(assign, id); add_brother(id, expr); $$ = assign;}

	|	LBRACE RBRACE																	{$$ = NULL;}
	|	LBRACE StatementSemiList RBRACE													{statelist = $2; if(statelist != NULL) {if(has_brother(statelist)) {block = create_node("Block", NULL); add_child(block, statelist); $$ = block;} else {$$ = statelist;}}  else {$$ = statelist;} }
	
	|	IF Expr LBRACE RBRACE															{ifnode = create_node("If", NULL); expr = $2; add_child(ifnode, expr); 		ifblock = create_node("Block", NULL); add_brother(expr, ifblock);		elseblock = create_node("Block", NULL); add_brother(ifblock, elseblock);																																					$$ = ifnode;}
	|	IF Expr LBRACE StatementSemiList RBRACE 										{ifnode = create_node("If", NULL); expr = $2; add_child(ifnode, expr); 		ifblock = create_node("Block", NULL); add_brother(expr, ifblock);		elseblock = create_node("Block", NULL); add_brother(ifblock, elseblock);																							statelist = $4; add_child(ifblock, statelist); 			$$ = ifnode;}
	|	IF Expr LBRACE RBRACE ELSE LBRACE RBRACE 										{ifnode = create_node("If", NULL); expr = $2; add_child(ifnode, expr); 		ifblock = create_node("Block", NULL); add_brother(expr, ifblock);		elseblock = create_node("Block", NULL); add_brother(ifblock, elseblock); 																																					$$ = ifnode;}
	|	IF Expr LBRACE RBRACE ELSE LBRACE StatementSemiList RBRACE 						{ifnode = create_node("If", NULL); expr = $2; add_child(ifnode, expr); 		ifblock = create_node("Block", NULL); add_brother(expr, ifblock);		elseblock = create_node("Block", NULL); add_brother(ifblock, elseblock);																							statelist = $7; add_child(elseblock, statelist); 		$$ = ifnode;}
	|	IF Expr LBRACE StatementSemiList RBRACE ELSE LBRACE RBRACE						{ifnode = create_node("If", NULL); expr = $2; add_child(ifnode, expr); 		ifblock = create_node("Block", NULL); add_brother(expr, ifblock);		statelist = $4; add_child(ifblock, statelist); 								elseblock = create_node("Block", NULL); add_brother(ifblock, elseblock);																		$$ = ifnode;}
	|	IF Expr LBRACE StatementSemiList RBRACE ELSE LBRACE StatementSemiList RBRACE 	{ifnode = create_node("If", NULL); expr = $2; add_child(ifnode, expr); 		ifblock = create_node("Block", NULL); add_brother(expr, ifblock);		statelist = $4; add_child(ifblock, statelist); 								elseblock = create_node("Block", NULL); add_brother(ifblock, elseblock);				statelist = $8; add_child(elseblock, statelist); 		$$ = ifnode;}
	
	|	FOR LBRACE RBRACE																{fornode = create_node("For", NULL); 											forblock = create_node("Block", NULL); add_child(fornode, forblock);																	$$ = fornode;}
	|	FOR Expr LBRACE RBRACE															{fornode = create_node("For", NULL); expr = $2; add_child(fornode, expr); 		forblock = create_node("Block", NULL); add_brother(expr, forblock);																		$$ = fornode;}
	|	FOR LBRACE StatementSemiList RBRACE												{fornode = create_node("For", NULL); 											forblock = create_node("Block", NULL); add_child(fornode, forblock);		statelist = $3; add_child(forblock, statelist); 			$$ = fornode;}
	| 	FOR Expr LBRACE StatementSemiList RBRACE										{fornode = create_node("For", NULL); expr = $2; add_child(fornode, expr);		forblock = create_node("Block", NULL); add_brother(expr, forblock);			statelist = $4; add_child(forblock, statelist); 			$$ = fornode;}

	| 	RETURN 																			{retnode = create_node("Return", NULL); $$ = retnode;}
	| 	RETURN Expr																		{retnode = create_node("Return", NULL); expr = $2; add_child(retnode, expr); $$ = retnode;}

	|	FuncInvocation																	{$$ = $1;}
	| 	ParseArgs 																		{$$ = $1;}

	|	PRINT LPAR Expr RPAR 															{print = create_node("Print", NULL); expr = $3; add_child(print, expr); $$ = print;}
	| 	PRINT LPAR STRLIT RPAR 															{print = create_node("Print", NULL); strlit = create_node("StrLit", $3); add_child(print, strlit); $$ = print;}

	| 	error																			{$$ = NULL;}
	;


StatementSemiList:
		StatementSemiList Statement SEMICOLON 				{/* BLOCK */statelist = $1; statement = $2; add_brother(statelist, statement); $$ = statelist;}
	|	Statement SEMICOLON									{$$ = $1;}
	;


ParseArgs:
		ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR 		{parseargs = create_node("ParseArgs", NULL); id = create_node("Id", $1); add_child(parseargs, id); expr = $9; add_brother(id, expr); $$ = parseargs;}
	|	ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR						{$$ = NULL;}
	;	


FuncInvocation:
		ID LPAR RPAR 				{call = create_node("Call", NULL); id = create_node("Id", $1); add_child(call, id); $$ = call;}
	| 	ID LPAR ExprList RPAR 		{call = create_node("Call", NULL); id = create_node("Id", $1); add_child(call, id); expr = $3; add_brother(id, expr); $$ = call;}
	| 	ID LPAR error RPAR 			{$$ = NULL;}
	;


ExprList:
		ExprList COMMA Expr 		{aux_node = $1; expr = $3; add_brother(aux_node, expr); $$ = aux_node;}
	|	Expr 						{$$ = $1;}
	;


Expr:
		Expr OR Expr 			{or = create_node("Or", NULL); expr = $1; add_child(or, expr); add_brother(expr, $3); 			$$ = or;}
	|	Expr AND Expr			{and = create_node("And", NULL); expr = $1; add_child(and, expr); add_brother(expr, $3); 		$$ = and;}

	|	Expr LT Expr			{lt = create_node("Lt", NULL); expr = $1; add_child(lt, expr); add_brother(expr, $3); 			$$ = lt;}
	|	Expr GT Expr			{gt = create_node("Gt", NULL); expr = $1; add_child(gt, expr); add_brother(expr, $3); 			$$ = gt;}
	|	Expr EQ Expr			{eq = create_node("Eq", NULL); expr = $1; add_child(eq, expr); add_brother(expr, $3); 			$$ = eq;}
	|	Expr NE Expr			{ne = create_node("Ne", NULL); expr = $1; add_child(ne, expr); add_brother(expr, $3); 			$$ = ne;}
	|	Expr LE Expr			{le = create_node("Le", NULL); expr = $1; add_child(le, expr); add_brother(expr, $3); 			$$ = le;}
	|	Expr GE Expr			{ge = create_node("Ge", NULL); expr = $1; add_child(ge, expr); add_brother(expr, $3); 			$$ = ge;}

	|	Expr PLUS Expr			{add = create_node("Add", NULL); expr = $1; add_child(add, expr); add_brother(expr, $3); 		$$ = add;}
	|	Expr MINUS Expr 		{sub = create_node("Sub", NULL); expr = $1; add_child(sub, expr); add_brother(expr, $3); 		$$ = sub;}
	|	Expr STAR Expr			{mult = create_node("Mul", NULL); expr = $1; add_child(mult, expr); add_brother(expr, $3); 		$$ = mult;}
	|	Expr DIV Expr			{divi = create_node("Div", NULL); expr = $1; add_child(divi, expr); add_brother(expr, $3); 		$$ = divi;}
	|	Expr MOD Expr			{mod = create_node("Mod", NULL); expr = $1; add_child(mod, expr); add_brother(expr, $3);		$$ = mod;}

	|	NOT Expr  				{not = create_node("Not", NULL); add_child(not, $2); 			$$ = not;}
	|	MINUS Expr %prec NOT	{minus = create_node("Minus", NULL); add_child(minus, $2); 		$$ = minus;}
	|	PLUS Expr %prec NOT		{plus = create_node("Plus", NULL); add_child(plus, $2); 		$$ = plus;}

	|	INTLIT					{$$ = create_node("IntLit", $1);}
	|	REALLIT					{$$ = create_node("RealLit", $1);}
	|	ID						{$$ = create_node("Id", $1);}
	|	FuncInvocation			{$$ = $1;}
	|	LPAR Expr RPAR			{$$ = $2;}

	|	LPAR error RPAR			{$$ = NULL;}
	;





%%

