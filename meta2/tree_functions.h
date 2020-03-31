#ifndef TREE_FUNCTIONS_H
#define TREE_FUNCTIONS_H

typedef struct no{
	char *nome;
	struct no* filho;
	struct no* next;
} No;

No* cria_no(char* nome);
void add_next(No* n1, No* n2);
void add_filho(No* n, No* filho);
No* new_id(char* nome);
No* new_strlit(char* nome);
No* new_reallit(char* nome);
No* new_intlit(char* nome);
No* new_boollit(const char* nome);
void print_tree(No* n, int nivel);
void free_tree(No* n);

#endif
