#ifndef AST_H_INCLUDED
#define AST_H_INCLUDED

typedef struct node {
	char *token_type;			/* Tipo de variável que é (VarDecl, Program, Id(), ...) */
	char *token_value;			/* Valor dessa variável (VarDecl não tem, por exemplo, fica a NULL; Id tem, ou seja, fica Id(3), por exemplo */
								/* IMPORTANTE: cada nó só tem um filho e um irmão. Se quisermos que um nó tenha dois filhos, o primeiro é filho e o segundo liga-se ao primeiro como seu irmão */
	struct node *child;			/* O filho desse nó (que tem os seus próprios irmãos) */
	struct node *brother;		/* O irmão desse nó */
} node;


void print_ast(node *current_node, int npoints);				/* Imprimir a árvore. Função recursiva que imprime o número de pontos necessários a cada iteração. */

node *create_node(char *type, char *value);						/* Criar novo nó, em que os parâmetros são armazenados em token_value e token_type. */

void add_child(node *parent, node *child);						/* Adicionar o filho de um nó. Parâmetros são o nó que se quer adicionar como filho e a quem. */
void add_first_child_varDecl(node *parent, node *new_child);	/* Adicionar um filho no início, para todos os VarDecls. Serve para o caso específico do VarDecl em que o tipo (int, float), tem que vir primeiro que o filho que já lá está (Id(a1), Id(a2), etc.). */
void add_brother(node *first, node *last);						/* Adicionar um irmão a um nó. O nó last é adicionado como irmão do nó first. */
int has_brother(node *child);									/* Verificar se o nó tem irmão. */

#endif // AST_H_INCLUDED