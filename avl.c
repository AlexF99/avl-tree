#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

t_nodo *novo_nodo(int chave)
{
    t_nodo *nodo = (t_nodo *)malloc(sizeof(t_nodo));
    nodo->chave = chave;
    nodo->esquerda = NULL;
    nodo->direita = NULL;
    nodo->pai = NULL;
    nodo->balanceamento = 0;
    return nodo;
}

t_nodo *ajusta_avl(t_nodo*nodo) {
    return nodo;
}

t_nodo *insere_nodo(t_nodo *nodo, int chave)
{

    if (!nodo)
        return novo_nodo(chave);

    if (chave <= nodo->chave)
    {
        nodo->esquerda = insere_nodo(nodo->esquerda, chave);
        nodo->esquerda->pai = nodo;
    }
    else
    {
        nodo->direita = insere_nodo(nodo->direita, chave);
        nodo->direita->pai = nodo;
    }

    return nodo;
}

void remove_nodo(t_nodo *nodo, int chave)
{
    return;
}

void emordem(t_nodo *nodo)
{
    if (nodo != NULL)
    {
        emordem(nodo->esquerda);
        printf("%d\n", nodo->chave);
        emordem(nodo->direita);
    }
}

t_nodo * rot_esquerda(t_nodo * nodo)
{
	// Filho da direita do nodo a ser rotacionado
	t_nodo * filho_direita = nodo->direita;

	// Filho da esqueda do nodo filho passa a ser filho da direita do nodo a ser rot
	nodo->direita = filho_direita->esquerda;

	// Ajusta os ponteiros de pai e filho
	filho_direita->pai = nodo->pai;
	nodo->pai = filho_direita;

	if (filho_direita->esquerda != NULL)
		filho_direita->esquerda->pai = nodo;

	// Nodo rotacionado passa a ser filho da esq do nodo filho
	filho_direita->esquerda = nodo;

	return filho_direita;

}

t_nodo * rot_direita(t_nodo * nodo)
{
	if (nodo->esquerda)
	{
		// Filho da esquerda do nodo a ser rotacionado
		t_nodo * filho_esquerda = nodo->esquerda;

		// Filho da direita do nodo filho passa a ser filho da esquerda do nodo a ser rot
		nodo->esquerda = filho_esquerda->direita;

		// Ajusta os ponteiros de pai e filho
		filho_esquerda->pai = nodo->pai;
		nodo->pai = filho_esquerda;

		if (filho_esquerda->direita != NULL)
			filho_esquerda->direita->pai = nodo;

		// Nodo rotacionado passa a ser filho da direita do nodo filho
		filho_esquerda->direita = nodo;

		return filho_esquerda;
	}
}
