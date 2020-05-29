#ifndef TREE_FUNCTIONS_H
#define TREE_FUNCTIONS_H

typedef struct no{
	char *nome;
	char *valor;
	struct no* filho;
	struct no* irmao;
} No;

No* cria_no(char* nome, char* valor);
void add_irmao(No* n1, No* n2);
void add_filho(No* n, No* filho);
int check_irmao(No* n);
void tratamentoIDRep(No* pai, No* filho);
void print_tree(No* n, int nivel);
//void print_notation_tree (No* n, int nivel, int anotation);
void free_tree(No* n);

#endif
