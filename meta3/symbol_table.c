#include "symbol_table.h"
#include "tree_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicia_tabela_global() {
	Tabela *tabela_aux = (Tabela*) malloc(sizeof(Tabela));

	tabela_aux->method = 0;
	strcpy(tabela_aux->nome, "");
	strcpy(tabela_aux->tipo_return, "");

	tabela_aux->n_parametros = 0;
	strcpy(tabela_aux->params_str, "");

	tabela_aux->n_variaveis = 0;

	tabela_aux->next = NULL;
	root = tabela_aux;
	symbol_table = tabela_aux;
}

Tabela* inicia_tabela_metodos() {
	Tabela *tabela_aux = (Tabela*) malloc(sizeof(Tabela));

	tabela_aux->method = 1;
	strcpy(tabela_aux->nome, "");
	strcpy(tabela_aux->tipo_return, "");

	tabela_aux->n_parametros = 0;
	strcpy(tabela_aux->params_str, "");

	tabela_aux->n_variaveis = 0;

	tabela_aux->next = NULL;
	symbol_table->next = tabela_aux;
	symbol_table = symbol_table->next;

	return tabela_aux;
}

void add_param(Tabela *t, char *param, char *type) {
	int i = t->n_parametros;
	t->parametros = realloc(t->parametros, sizeof(char*) * (i + 2));
	t->parametros[i] = (char*) malloc(sizeof(char));							
	t->parametros[i + 1] = (char*) malloc(sizeof(char));
	t->n_parametros += 2;
	strcpy(t->parametros[i], param);		
	strcpy(t->parametros[i+1], type);		

	if(i != 0)							
		strcat(t->params_str, ",");
	strcat(t->params_str, type);			
}

void add_var(Tabela *t, char *var, char *type) {
	int i = t->n_variaveis;		
	t->variaveis = realloc(t->variaveis, sizeof(char*) * (i + 2));
	t->variaveis[i] = (char*) malloc(sizeof(char));							
	t->variaveis[i + 1] = (char*) malloc(sizeof(char));
	t->n_variaveis += 2;					
	strcpy(t->variaveis[i], var);			
	strcpy(t->variaveis[i + 1], type);		
}


void print_simbolos_globais() {
	Tabela *aux = root;
	for(int i = 0; i < aux->n_variaveis; i++) {
		if(i%2 == 0)
			printf("%s\t\t", aux->variaveis[i]);
		else
			printf("%s\n", aux->variaveis[i]);
	}

	aux = root->next;
	while(aux != NULL) {
		printf("%s\t(%s)\t%s\n", aux->nome, aux->params_str, aux->tipo_return);
		aux = aux->next;
	}
}

void print_simbolos_metodos(Tabela *t) {
	printf("return\t\t%s\n", t->tipo_return);

	for(int i = 0; i < t->n_parametros; i++) {
		if(i % 2 == 0)
			printf("%s\t\t", t->parametros[i]);
		else
			printf("%s\tparam\n", t->parametros[i]);

	}

	for(int i = 0; i < t->n_variaveis; i++) {
		if(i % 2 == 0)
			printf("%s\t\t", t->variaveis[i]);
		else
			printf("%s\n", t->variaveis[i]);
	}
}

void print_symbol_table() {

	Tabela *aux = root;

	while(aux) {
		if(aux->method == 0) {
			printf("===== Class %s Symbol Table =====\n", aux->nome);
			print_simbolos_globais();
		}
		else {
			printf("===== Method %s(%s) Symbol Table =====\n", aux->nome, aux->params_str);
			print_simbolos_metodos(aux);
		}
		printf("\n");
		aux = aux->next;
	}
}
