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
