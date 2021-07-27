#include "tree_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

No* cria_no(char* nome, char* valor){
	No* n = (No *) malloc(sizeof(No));
	n->nome = strdup(nome);
	n->valor = valor;
	n->filho = NULL;
	n->irmao = NULL;
	//printf("Criado no %s\n", n->nome);
	return n;
}

void add_irmao(No* n1, No* n2){
	if (n1 == NULL || n2 == NULL) return;
	No* aux = n1;
	while (aux->irmao != NULL){
        //printf("aux = %s\n", aux->irmao);
		aux = aux->irmao;
	}
	aux->irmao = n2;
	//printf("Add %s em %s\n", n2->nome, aux->nome);
}

int check_irmao(No* n){
	if(n->irmao != NULL)
		return 1;
	return 0;
}


void tratamentoIDRep(No* pai, No* tipo) {	
	No* aux = pai;
	No* actual = pai->filho->irmao;
	No* novo_no = NULL;
	No* novo_var = NULL;

	while(actual->irmao != NULL){
		novo_var = cria_no(aux->nome, NULL);
		No *novo_tipo = cria_no(tipo->nome, NULL);
		novo_no = actual->irmao;
		add_irmao(aux, novo_var);
		add_filho(novo_var, novo_tipo);
		add_irmao(novo_tipo, actual->irmao);
		actual->irmao = NULL;
		actual = novo_no;

	} 				
}

void add_filho(No* n, No* filho){
	n->filho = filho;
}


void print_tree(No* n, int nivel) {
    int i;
	if(n==NULL) return;
	for(i=0; i<nivel;i++) printf("..");
	if(n->valor == NULL) printf("%s\n", n->nome);
	else printf("%s(%s)\n", n->nome, n->valor);

	//imprime filhos primeiro
	print_tree(n->filho, nivel+1);
	//imprime irmaos
	print_tree(n->irmao, nivel);
}  
/*
void print_notation_tree (No* n, int nivel, int anotation) {
    int i;
	if(n==NULL) return;
	for(i=0; i<nivel;i++) printf("..");
	if(n->valor == NULL) printf("%s", n->nome);
	else printf("%s(%s)", n->nome, n->valor);   

	if (anotation){
		if (n->isMethod==1){
			printf(" - (");
			if (n->paramtypes != NULL){
				paramtypes_t* pt = n->paramtypes;
				printf("%s", pt->tipo);
				pt = pt->next;
				while (pt != NULL){
					printf(",%s", pt->tipo);
					pt = pt->next;
				}
			}
			printf(")");
		}
		else if (n->tipo!=NULL){ 
			printf(" - %s", n->tipo);
		}
	}
	printf("\n");
	//imprime filhos primeiro
	print_notation_tree(n->filho, nivel+1, anotation);
	//imprime irmaos
	print_notation_tree(n->irmao, nivel, anotation);

}
*/
void free_tree(No* n){
	if (n == NULL) return;
	//apagar filhos
	if (n->filho != NULL){
		free_tree(n->filho);
	}
	//apagar irmaos
	if (n->irmao != NULL){
		free_tree(n->irmao);
	}
	free(n->nome);
	free(n);
}
