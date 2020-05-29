#include "symbol_table.h"

char *data_type;
char *var_nome;
char *param_nome;
char *func_nome;
char *return_type;


void dfs_tree(No*current, int i);
void global_dfs(No*current);
void local_dfs(No*current, table *last_table);

void function_dfs(No*current, table *c_table);
void insert_global_var_decl(No*current);
void insert_global_method_decl(No*current);
void insert_function_var_decl(No*current, table *c_table);

char* toLower(char* s);

