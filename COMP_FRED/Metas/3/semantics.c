#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast.h"
#include "symbol_table.h"
#include "semantics.h"


void global_dfs(node *current) {

	if(current == NULL)										/* Caso de retorno quando o nó está vazio! */
		return;

	if(strcmp(current->token_type, "VarDecl") == 0)
		insert_global_var_decl(current);init_global_table
	if(strcmp(current->token_type, "FuncDecl") == 0)
		insert_global_func_decl(current);

	global_dfs(current->brother);
}

void local_dfs(node *current, table *last_table) {
	if(current == NULL)
		return;

	if(strcmp(current->token_type, "FuncDecl") == 0) {
		last_table = last_table->next;
		
		if(current->child->brother->child != NULL) {						/* Entrar directo para o primeiro filho de FuncBody se esta tiver um filho */
			function_dfs(current->child->brother->child, last_table);
		}			
																			
	}

	local_dfs(current->brother, last_table);

}

void function_dfs(node *current, table *c_table) {							/* Estamos no primeiro filho do FuncBody, ou seja, ver os irmãos se há VarDecls */
	if(current == NULL)
		return;

	if(strcmp(current->token_type, "VarDecl") == 0)
		insert_function_var_decl(current->child, c_table);


	function_dfs(current->brother, c_table);
}

void insert_function_var_decl(node *current, table *c_table) {
	data_type = strdup(current->token_type);
	var_name = strdup(current->brother->token_value);

	for(down = 0; down < strlen(data_type); down++)
		data_type[down] = tolower(data_type[down]);

	add_var_to_table(c_table, var_name, data_type);
}

/*
..FuncDecl
....FuncHeader
......Id(fcb)
......Int
......FuncParams
....FuncBody
......VarDecl
........Int
........Id(fafcb)
......Assign - int
........Id(fafcb) - int
........IntLit(132) - int
......Return
........Id(fafcb) - int

*/

void insert_global_var_decl(node *current) {
	data_type = strdup(current->child->token_type);
	var_name = strdup(current->child->brother->token_value);

	for(down = 0; down < strlen(data_type); down++)
		data_type[down] = tolower(data_type[down]);

	add_var_to_table(root_table, var_name, data_type);
}

void insert_global_func_decl(node *current) {
	current = current->child;							/* Ir para FuncHeader */
	current = current->child;							/* Ir para Id*/
	func_name = strdup(current->token_value);

	current = current->brother;
	if(strcmp(current->token_type, "FuncParams") == 0)
		data_type = strdup("none");
	else {
		data_type = strdup(current->token_type);
		for(down = 0; down < strlen(data_type); down++)
			data_type[down] = tolower(data_type[down]);

		current = current->brother;
	}

	table *new_table = init_func_table();
	add_name_to_table(new_table, func_name);
	add_type_to_table(new_table, data_type);

	if(current->child != NULL) {
		current = current->child;						/* Ir para primeiro ParamDecl */
		while(current != NULL) {
			data_type = strdup(current->child->token_type);
			param_name = strdup(current->child->brother->token_value);

			for(down = 0; down < strlen(data_type); down++)
			data_type[down] = tolower(data_type[down]);

			add_param_to_table(new_table, param_name, data_type);

			current = current->brother;
		}
	}


}
