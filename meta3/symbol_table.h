#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_functions.h"

#define MAX_S 5000

typedef struct table {
	int func;							/* Se é Global (0) ou se é Function (1) */
	char *nome;					/* Nome da função */
	char *type;					/* Tipo de retorno da função */

	int n_params;						/* Número de parâmetros */
	char **params;						/* Array de parâmetros [n_param][nome_param] -linha a seguir- [n_param] */
	char params_str[MAX_S * 10];		/* Parametros para string (x,y,z) */

	int n_vars;
	char **vars;

	struct table *next;
} table;


table *root_table;					/* Um ponteiro para a primeira tabela de símbolos - tabela Global */
table *last_table;					/* Um ponteiro para a última tabela de símbolos, para não andarmos sempre a percorrer à procura desta */



/* Funções gerais para tabelas*/
void init_global_table();
table *init_method_table();

/* Funções 'utils' para tabelas */
void add_param_to_table(table *t, char *param, char *type);
void add_var_to_table(table *t, char *var, char *type);
void increaseParams(table *t);
void increaseVars(table *t);

/* Misc */
void print_tables();




#endif
