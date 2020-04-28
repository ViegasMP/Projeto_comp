#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symbol_table.h"
#include "semantics.h"


void print_ast(node *current_node, int npoints) {
	int i;

	if(current_node == NULL)
		return;

	for(i = 0; i < npoints; i++)
		printf(".");

	if(current_node->token_value == NULL)				/* Caso seja um token sem valor (LBRACE, RETURN) */
		printf("%s\n", current_node->token_type);
	else												/* Caso o token tenha valor (ID, STRLIT) */
		printf("%s(%s)\n", current_node->token_type, current_node->token_value);

	print_ast(current_node->child, npoints + 2);		/* Os filhos recebem mais dois pontos para impressão porque estão num nível abaixo. */
	print_ast(current_node->brother, npoints);			/* Os irmãos recebem os mesmos pontos para impressão porque estão no mesmo nível. */
}



node *create_node(char *type, char *value) {
	node *new_node = (node*) malloc(sizeof(node));

	new_node->token_type = strdup(type);				/* strdup(type) copia o valor armazenado no ponteiro type para um outro ponteiro, neste caso new_node->token_type */
	new_node->token_value = value;

	new_node->child = NULL;
	new_node->brother = NULL;

	return new_node;
}



void add_child(node *parent, node *child) {
	parent->child = child;
}


void add_first_child_varDecl(node *parent, node *new_child) {		/* Isto percorre todos os VarDecls, que vão ser tratados sempre como pais. */
	node *actual = parent;
	node *new_node = NULL;

	int primeira_vez = 1;							/* Variável usada para da primeira vez, ser adicionado o new_child como filho do nó pai, sem verificar se este tem irmãos. Basicamente, para não incrementar "actual = actual->brother" da primeira vez */

	do {
		if(primeira_vez)
			primeira_vez = 0;
		else
			actual = actual->brother;				/* Passar para o próximo irmão do pai. */

		new_node = create_node(new_child->token_type, NULL);

		new_node->brother = actual->child;			/* Este novo nó vai ter como irmão o anterior filho do nó actual. */
		actual->child = new_node;					/* O nó pai, por sua vez, vai ter como filho o novo nó*/

	} while(actual->brother != NULL);				/* Se o nó pai não tiver irmãos, quebra o ciclo. */

	
}

void add_brother(node *first, node *last) {
	if(first != NULL) {								
		while(first->brother != NULL)				/* Se o primeiro nó tiver irmãos: */
			first = first->brother;					/* Avança para o próximo irmão. */
		first->brother = last;						/* O last va ficar irmão, então, do último nó encontrado (fica, portanto, no final). */
	}
}


int has_brother(node *child) {
	if(child->brother != NULL)
		return 1;

	return 0;
}


