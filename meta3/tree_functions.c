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
 void print_params_annotationFun(params_type* params) {
    if(params==NULL) {
        printf(" - (undef)");
        return;
    }    
    params_type* tmp = params;

    printf(" - (");
    while(tmp->next!=NULL) {
        printf("%s,",basic_type_to_string(tmp->param_type));
        tmp=tmp->next;
    }
    switch (tmp->param_type){
        case blank:
            printf(")");
            break;
        default:
            printf("%s)",basic_type_to_string(tmp->param_type));
    }


}   

void print_params_annotation(params_type* params) {
    if(params == NULL) {
        printf(" - undef");
        return;
    }    
    params_type* tmp = params;

    while(tmp->next!=NULL) {
        printf(" - ");
        printf("%s,",basic_type_to_string(tmp->param_type));
        tmp=tmp->next;
    }
    switch (tmp->param_type){
        case blank:
            break;
        default:
            if(tmp == params)
                printf(" - ");
            printf("%s",basic_type_to_string(tmp->param_type));
    }

}

void print_annotation(No* n) {
    No*aux = n; 
    if ((strcmp(aux->nome, "IntLit") == 0) ||
    (strcmp(aux->nome, "RealLit") == 0) ||
    (strcmp(aux->nome, "StrLit") == 0) ||
    (strcmp(aux->nome, "String") == 0) ||
    (strcmp(aux->nome, "Bool") == 0) ||
    (strcmp(aux->nome, "Eq") == 0) ||
    (strcmp(aux->nome,"Add") == 0) ||
    (strcmp(aux->nome,"Sub") == 0) ||
    (strcmp(aux->nome,"Mul") == 0) ||
    (strcmp(aux->nome,"Div") == 0) ||
    (strcmp(aux->nome,"Mod") == 0) ||
    (strcmp(aux->nome,"Plus") == 0) ||
    (strcmp(aux->nome,"Minus") == 0) ||
    (strcmp(aux->nome,"Not") == 0) ||
    (strcmp(aux->nome,"And") == 0) ||
    (strcmp(aux->nome,"Or") == 0) ||
    (strcmp(aux->nome,"Ge") == 0) ||
    (strcmp(aux->nome,"Le") == 0) ||
    (strcmp(aux->nome,"Lt") == 0) ||
    (strcmp(aux->nome,"Gt") == 0) ||
    (strcmp(aux->nome,"Ne") == 0) ||
    (strcmp(aux->nome,"ParseArgs") == 0) ||
    (strcmp(aux->nome,"Call") == 0) ||
    (strcmp(aux->nome,"Assign") == 0)){
        print_params_annotation(aux->nome);  

    } else if (strcmp(aux->nome, "Id") == 0 ){
        if(aux->is_fun){
            print_params_annotationFun(aux->nome);
        } else {
            print_params_annotation(aux->nome);

        }
    } 
}

void print_notation_tree (No* n, int nivel, int anotation) {
    int i;
	int body=0;
	if(n==NULL) return;
    for(i=0; i<nivel;i++) printf("..");
	if(n->valor == NULL) printf("%s\n", n->nome);
	else printf("%s(%s)\n", n->nome, n->valor);    

	if(strcmp(n->nome, "MethodBody")==0) {
		body=1;
	} else if(strcmp(n->nome, "MethodHeader")==0) {
		body=0;
	}  
	
	if(strcmp(n->nome, "VarDecl")==0) {
		print_notation_tree(n->filho, nivel+1, 0);
		print_notation_tree(n->irmao, nivel, 1);
		
	}
	else {
		if(anotation && body)
			print_annotation(n);
		print_notation_tree(n->filho, nivel+1, anotation);
		print_notation_tree(n->irmao, nivel, anotation);
	}

}*/

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
