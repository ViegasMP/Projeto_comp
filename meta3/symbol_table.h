#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct tabela{
    int method;
	char *nome;
	char *tipo_return;
    int n_parametros;
    char **parametros;
    char params_str[100];
    int n_variaveis;
    char **variaveis;
    struct tabela *next;
} Tabela;

struct tabela *symbol_table;
struct tabela *root;

void inicia_tabela_global();
Tabela* inicia_tabela_metodos();
void add_param(Tabela *t, char *param, char *type);
void add_var(Tabela *t, char *var, char *type);
void print_simbolos_globais();
void print_simbolos_metodos(Tabela *t);
void print_symbol_table();


#endif
