#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
	char *nome;
    int nivel;
	struct no* filho;
	struct no* next;
} No;

no* cria_no(char* nome);

void add_next(no* n1, no* n2);

void add_filho(no* n, no* fiho);

no* new_id(char* nome);

void print_arvore (no n);

void destruir_arvore (no n);