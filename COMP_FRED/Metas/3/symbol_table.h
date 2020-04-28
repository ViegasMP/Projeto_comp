#ifndef SYMBOL_TABLE_H_INCLUDED
#define SYMBOL_TABLE_H_INCLUDED


#define MAX_S 5000
#define MAX_T 10


typedef struct table {
	int func;							/* Se é Global (0) ou se é Function (1) */
	char name[MAX_S];					/* Nome da função */
	char type[MAX_T];					/* Tipo de retorno da função */

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
table *init_func_table();

/* Funções 'utils' para tabelas */
void add_name_to_table(table *t, char *name);
void add_type_to_table(table *t, char *type);
void add_param_to_table(table *t, char *param, char *type);
void add_var_to_table(table *t, char *var, char *type);
void increaseParams(table *t);
void increaseVars(table *t);

/* Misc */
void print_tables();



#endif // SYMBOL_TABLE_H_INCLUDED