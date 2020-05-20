#include "semantic.h"
#include <ctype.h>

void global_dfs(No* current) {
	if(current == NULL)										/* Caso de retorno quando o nó está vazio! */
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
		
		if(current->filho->irmao->filho != NULL) {						// Entrar directo para o primeiro filho de MethodBody se esta tiver um filho
			function_dfs(current->filho->irmao->filho, last_table);
		}			
		fflush(stdin);															
	}
	local_dfs(current->irmao, last_table);

}

void function_dfs(No*current, table *c_table) {							// Estamos no primeiro filho do MethoBody, ou seja, ver os irmãos se há VarDecls
	if(current == NULL)
		return;

	if(strcmp(current->nome, "VarDecl") == 0)
		insert_function_var_decl(current->filho, c_table);

	function_dfs(current->irmao, c_table);
}

void insert_function_var_decl(No*current, table *c_table) {
	data_type = strdup(current->nome);
	var_nome = strdup(current->irmao->valor);

	for(down = 0; down < strlen(data_type); down++)
		data_type[down] = tolower(data_type[down]);

	add_var_to_table(c_table, var_nome, data_type);
}

void insert_global_var_decl(No*current) {
	data_type = strdup(current->filho->nome);
	var_nome = strdup(current->filho->irmao->valor);

	for(down = 0; down < strlen(data_type); down++)
		data_type[down] = tolower(data_type[down]);

	add_var_to_table(root_table, var_nome, data_type);
}

char* toLower(char* s) {
  for(char *p=s; *p; p++) *p=tolower(*p);
  return s;
}

void insert_global_method_decl(No* current) {
	char *tipo;
	current = current->filho;							// Ir para MethodHeader
	current = current->filho;							// Ir para Id return
    if(strcmp(current->nome, "StringArray")==0)
        strcpy(return_type, "String[]");
    else
        return_type = toLower(strdup(current->nome));   // guardar return Id
    current = current->irmao;                           // ir para nome e argumentos da funcao
	func_nome = strdup(current->valor);                 // guardar nome da funcao
    current = current->irmao;                          
	table *new_table = init_method_table();
	new_table->nome = strdup(func_nome);
    new_table->type = strdup(return_type);
	if(current->filho != NULL) {
		current = current->filho;						//Ir para primeiro ParamDecl 
		while(current != NULL) {
            if(strcmp(current->filho->nome, "StringArray")==0)
				strcpy(tipo, "String[]");
            else
                tipo = toLower(strdup(current->filho->nome));
			param_nome = strdup(current->filho->irmao->valor);
			
			add_param_to_table(new_table, param_nome, tipo);

			current = current->irmao;
		}
	}


}
