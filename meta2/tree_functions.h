#ifndef TREE_FUNCTIONS_H
#define TREE_FUNCTIONS_H
typedef struct no{
	char *nome;
    int nivel;
	struct no* filho;
	struct no* next;
} No;

No* cria_no(char* nome);

void add_next(No* n1, No* n2);

void add_filho(No* n, No* fiho);

No* new_id(char* nome);

void print_arvore (No n);

void destruir_arvore (No n);

#endif