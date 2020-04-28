#ifndef SEMANTICS_H_INCLUDED
#define SEMANTICS_H_INCLUDED

char *data_type;
char *var_name;
char *param_name;
char *func_name;
int debug;
int down;


void dfs_tree(node *current, int i);
void global_dfs(node *current);
void local_dfs(node *current, table *last_table);

void function_dfs(node *current, table *c_table);
void insert_global_var_decl(node *current);
void insert_global_func_decl(node *current);
void insert_function_var_decl(node *current, table *c_table);


#endif // SEMANTICS_H_INCLUDED