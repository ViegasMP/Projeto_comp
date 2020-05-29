#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree_functions.h"

#define MAX_S 5000

typedef struct table {
	int isMethod; //se eh Global (0) ou se eh Method (1)
	char *nome; // nome do mettodo
	char *type;	// tipo de retorno 

	int n_params; // nmero de parâmetros 
	char **params; //array de parâmetros [n_param][nome_param] -linha a seguir- [n_param] 
	char params_str[MAX_S * 10]; //Parametros para string (x,y,z)

	int n_vars;
	char **vars;

	struct table *next;
} table;


table *root_table; //ponteiro para a primeira tabela de símbolos - tabela Global
table *last_table; //ponteiro para a última tabela de símbolos



void init_global_table();
table *init_method_table();

void add_param_to_table(table *t, char *param, char *type);
void add_var_to_table(table *t, char *var, char *type);
void increaseParams(table *t);
void increaseVars(table *t);

void print_tables();
#endif
