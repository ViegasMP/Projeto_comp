#include "semantic.h"
#include <ctype.h>

void global_dfs(No* current) {
	if(current == NULL)	// nó está vazio!
		return;
	if(strcmp(current->nome, "FieldDecl") == 0)
		insert_global_var_decl(current);
	if(strcmp(current->nome, "MethodDecl") == 0)
		insert_global_method_decl(current);
	global_dfs(current->irmao);
}

void local_dfs(No*current, table *last_table) {
	if(current == NULL)
		return;
	if(strcmp(current->nome, "MethodDecl") == 0) {
		last_table = last_table->next;
		
		if(current->filho->irmao->filho != NULL) { // primeiro filho de MethodBody
			function_dfs(current->filho->irmao->filho, last_table);
		}			
		fflush(stdin);															
	}
	local_dfs(current->irmao, last_table);

}

char* toLower(char* s) {
  for(char *p=s; *p; p++) *p=tolower(*p);
  return s;
}

void function_dfs(No*current, table *c_table) { // primeiro filho do MethoBody
	//verifica irmãos para VarDecls
	if(current == NULL)
		return;

	if(strcmp(current->nome, "VarDecl") == 0)
		insert_function_var_decl(current->filho, c_table);

	function_dfs(current->irmao, c_table);
}

void insert_function_var_decl(No*current, table *c_table) {
	data_type = toLower(strdup(current->nome));
	var_nome = strdup(current->irmao->valor);

	add_var_to_table(c_table, var_nome, data_type);
}

void insert_global_var_decl(No*current) {
	var_nome = strdup(current->filho->irmao->valor);
	data_type = toLower(strdup(current->filho->nome));
	add_var_to_table(root_table, var_nome, data_type);
}

void insert_global_method_decl(No* current) {
	char *tipo;
	current = current->filho; //MethodHeader
	current = current->filho; //Id return
	// guardar return Id
    if(strcmp(current->nome, "StringArray")==0)
        strcpy(return_type, "String[]");
	else if (strcmp(current->nome, "Bool")==0)
        strcpy(return_type, "boolean");
    else
        return_type = toLower(strdup(current->nome));

    current = current->irmao; //nome e argumentos da funcao
	func_nome = strdup(current->valor); // guardar nome da funcao
    current = current->irmao;                          
	
	table *new_table = init_method_table();
	new_table->nome = strdup(func_nome);
    new_table->type = strdup(return_type);
	if(current->filho != NULL) {
		current = current->filho; //primeiro ParamDecl 
		while(current != NULL) {
            if(strcmp(current->filho->nome, "StringArray")==0)
				strcpy(tipo, "String[]");
			else if (strcmp(current->filho->nome, "bool")==0)
				strcpy(tipo, "boolean");
            else
                tipo = toLower(strdup(current->filho->nome));
			param_nome = strdup(current->filho->irmao->valor);
			
			add_param_to_table(new_table, param_nome, tipo);
			current = current->irmao;
		}
	}

}