#include "tree_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
typedef struct no{
	char *nome;
	struct no* filho;
	struct no* next;
} No;
*/

No* cria_no(char* nome){
	//printf("Criando no %s\n", nome);
	No* n = (No *) malloc(sizeof(No));
	n->nome = nome;
	n->filho = NULL;
	n->next = NULL;
	printf("Criado no %s\n", n->nome);
	return n;
}

void add_next(No* n1, No* n2){
	if (n1 == NULL || n2 == NULL) return;
	No* aux = n1;
	while (aux->next != NULL){
		aux = aux->next;
	}
	aux->next = n2;
	printf("Add %s em %s\n", n2->nome, n1->nome);
}

void add_filho(No* n, No* filho){
	if (n == NULL || filho == NULL) return;
	No* aux = n;
	if(aux->filho != NULL){
        aux = aux->filho;
        while(aux->filho != NULL) {
            aux = aux->filho;
        }
        aux->next = filho;
    } else {
        aux->filho = filho;
    }
	printf("Add %s em %s\n", filho->nome, n->nome);
}

No* new_id(const char* nome){
	char* arr = (char *) malloc(strlen(nome) + 5);
	sprintf(arr, "Id(%s)", nome);
	return cria_no(arr);
}

void print_tree(No* n, int nivel) {
    if (n == NULL) return;
	for (int i = 0; i < nivel; i++) printf("..");
	printf("%s\n", n->nome);
	//mostrar filhos
	print_tree(n->filho, nivel+1);
	//mostrar irmaos
	print_tree(n->next, nivel);
}

void free_tree(No* n){
	if (n == NULL) return;
	//apagar filhos
	if (n->filho != NULL){
		free_tree(n->filho);
	}
	//apagar irmaos
	if (n->next != NULL){
		free_tree(n->next);
	}
	free(n->nome);
	free(n);
}

/*
int main() {
   	struct no* tree, *node, *node2, *node3;
	tree = cria_no("Program");
	node = cria_no("Class");
	node2 = cria_no("ID");
	node3 = cria_no("outra class");
	add_filho(tree, node);
	add_filho(node, node2);
	add_next(node, node3);
	print_tree(tree, 0);
}
*/