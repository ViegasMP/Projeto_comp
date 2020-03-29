#include "tree_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

No* cria_no(char* nome){
	printf("Criando no %s\n", nome);
	no* n = malloc(sizeof(no));
	n->nome = strdup(nome);
	printf("Criou no %s\n", nome);
	return n;
}

void add_next(No* n1, no* n2){
	No* aux = n1;
	while (aux->next != NULL){
		aux = aux->next;
	}
	aux->next = n2;
}

void add_filho(No* n, No* fiho){
	if (n->filho == NULL){
		n->filho = filho;
	} else {
		add_next(n->filho, filho);
	}
}

No* new_id(char* nome){
	char* str = (char *) malloc(strlen(nome) + 5);
	sprintf(str, "Id(%s)", name);
	return create_node(str);
}

void print_arvore (No n){
    No aux = n;
    while (aux) {
		for (int i = 0; i < aux->nivel; i++) printf("..");
        printf("%s\n", aux->name);
        aux = aux->next;
    }
}

void destruir_arvore (No n) {
    No aux;
    while (l != NULL) {
		aux = l;
		n = aux->next;
		free (aux);
	}
	free (n);
}
