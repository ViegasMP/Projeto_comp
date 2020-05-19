#include "symbol_table.h"
#include "semantic.h"

void init_global_table(No* no) {
	table *new_table = (table*) malloc(sizeof(table));

	new_table->func = 0;
	new_table->nome = strdup(no->valor);

	new_table->n_params = 0;

	new_table->n_vars = 0;

	new_table->next = NULL;
	root_table = new_table;
	last_table = new_table;

    global_dfs(no->irmao);

}

table *init_method_table() {
	table *new_table = (table*) malloc(sizeof(table));

	new_table->func = 1;
	new_table->n_params = 0;
	new_table->n_vars = 0;
	new_table->next = NULL;
	last_table->next = new_table;
	last_table = last_table->next;

	return new_table;
}

void add_param_to_table(table *t, char *param, char *type) {
	int place = t->n_params;				/* Número total de parâmetros, ou seja, se forem 2 (param,tipo), o place a colocar o novo parâmetro vai ser 2 */
	
	increaseParams(t);						/* Acrescentam-se duas posições */
	strcpy(t->params[place], param);		/* Mete-se o PARAM na posição place */
	strcpy(t->params[place + 1], type);		/* Mete-se o TYPE na posição place+1 */

	if(place != 0)							/* Mete uma virgula se houver mais do que um */
		strcat(t->params_str, ",");
	strcat(t->params_str, type);			/* Acrescenta o type à string total */
}


void add_var_to_table(table *t, char *var, char *type) {
	int place = t->n_vars;					/* Número total de variáveis, ou seja, se forem 2 (var,tipo), o place a colocar a nova variavel vai ser 2 */

	increaseVars(t);						/* Acrescentam-se duas posições */
	strcpy(t->vars[place], var);			/* Mete-se o VAR na posição place */
	strcpy(t->vars[place + 1], type);		/* Mete-se o TYPE na posição place+1 */
}

void increaseParams(table *t) {
	int size = t->n_params;											/* Número de parâmetros que já se tem */

	t->params = realloc(t->params, sizeof(char*) * (size + 2));
	t->params[size] = (char*) malloc(sizeof(char));							
	t->params[size + 1] = (char*) malloc(sizeof(char));
	t->n_params += 2;
}

void increaseVars(table *t) {
	int size = t->n_vars;

	t->vars = realloc(t->vars, sizeof(char*) * (size + 2));
	t->vars[size] = (char*) malloc(sizeof(char));							
	t->vars[size + 1] = (char*) malloc(sizeof(char));
	t->n_vars += 2;
}

void print_global_symbols() {
	table *aux = root_table;


	/* Variáveis globais */
	int size = aux->n_vars;
	int i;
	for(i = 0; i < size; i++) {
		if(i % 2 == 0)
			printf("%s\t\t", aux->vars[i]);
		else
			printf("%s\n", aux->vars[i]);

	}


	/* Funções (tabelas seguintes) */
	aux = root_table->next;
	while(aux != NULL) {
		printf("%s\t(%s)\t%s\n", aux->nome, aux->params_str, aux->type);

		aux = aux->next;
	}
}

void print_method_symbols(table *table) {
	/* Retorno da função */
	printf("return\t\t%s\n", table->type);


	/* Parâmetros de entrada */
	int size = table->n_params;
	int i;
	for(i = 0; i < size; i++) {
		if(i % 2 == 0)
			printf("%s\t\t", table->params[i]);
		else
			printf("%s\tparam\n", table->params[i]);

	}


	/* Variáveis */
	size = table->n_vars;
	for(i = 0; i < size; i++) {
		if(i % 2 == 0)
			printf("%s\t\t", table->vars[i]);
		else
			printf("%s\n", table->vars[i]);

	}
}

void print_tables() {

	table *aux_table = root_table;

	while(aux_table) {
		if(aux_table->func == 0) {
			printf("===== Class %s Symbol Table =====\n", aux_table->nome);
			print_global_symbols();
		}
		else {
			printf("===== Method %s(%s) Symbol Table =====\n", aux_table->nome, aux_table->params_str);
			print_method_symbols(aux_table);
		}


		printf("\n");
		aux_table = aux_table->next;
	}
}
