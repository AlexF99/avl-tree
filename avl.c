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

int altura(t_nodo *p)
{
    int he, hd;
    if (p == NULL)
        return -1;
    he = altura(p->esquerda);
    hd = altura(p->direita);
    if (he > hd)
        return he + 1;
    else
        return hd + 1;
}

int nivel_atual(t_nodo * nodo)
{
	if (!nodo)
		return -1;
	return 1 + nivel_atual(nodo->pai);
}

void emordem(t_nodo *nodo)
{
    if (nodo != NULL)
    {
        emordem(nodo->esquerda);
        printf("%d,%d\n", nodo->chave, nivel_atual(nodo));
        emordem(nodo->direita);
    }
}

t_nodo *min(t_nodo *no)
{
    if (no->esquerda == NULL)
        return no;
    else
        return min(no->esquerda);
}

t_nodo *sucessor(t_nodo *no)
{
    t_nodo *s = NULL;
    if (no->direita != NULL)
        return min(no->direita);
    else
    {
        s = no->pai;
        while (s != NULL && no == s->direita)
        {
            no = s;
            s = s->pai;
        }
    }
    return s;
}

t_nodo *busca(t_nodo *no, int chave)
{
    if (no == NULL)
        return NULL;
    if (no->chave == chave)
        return no;
    if (chave < no->chave)
        return busca(no->esquerda, chave);
    else
        return busca(no->direita, chave);
}

t_nodo *ajustaFBalanceamentoPai(t_nodo *p)
{
    t_nodo *no = p;
    while (no->pai != NULL && no->balanceamento != -2 && no->balanceamento != 2)
    {
        if (no->pai->esquerda == no)
            no->pai->balanceamento++;
        else
            no->pai->balanceamento--;
        no = no->pai;
    }
    return no;
}

t_nodo *rot_esquerda(t_nodo *nodo)
{
    // Filho da direita do nodo a ser rotacionado
    t_nodo *filho_direita = nodo->direita;

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

t_nodo *rot_direita(t_nodo *nodo)
{
    if (nodo->esquerda)
    {
        // Filho da esquerda do nodo a ser rotacionado
        t_nodo *filho_esquerda = nodo->esquerda;

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

t_nodo *ajusta_avl(t_nodo *no, int *calcula_fb)
{
    t_nodo *noAjuste;
    if (no->balanceamento == -2)
    {
        if (no->esquerda != NULL && no->esquerda->balanceamento > 0)
            no->esquerda = rot_esquerda(no->esquerda);
        noAjuste = rot_direita(no);
    }
    else
    {
        if (no->direita->balanceamento < 0)
            no->direita = rot_direita(no->direita);
        noAjuste = rot_esquerda(no);
    }
    if (noAjuste->pai != NULL)
    {
        if (noAjuste->pai->esquerda == no)
            noAjuste->pai->esquerda = noAjuste;
        else
            noAjuste->pai->direita = noAjuste;
    }
    noAjuste->balanceamento = 0;
    noAjuste->esquerda->balanceamento = (altura(noAjuste->esquerda->direita) - altura(noAjuste->esquerda->esquerda));
    noAjuste->direita->balanceamento = (altura(noAjuste->direita->direita) - altura(noAjuste->direita->esquerda));
    *calcula_fb = 0;
    return noAjuste;
}

t_nodo *insere_nodo(t_nodo *nodo, int chave, int * calcula_fb)
{

    if (!nodo)
	{
		*calcula_fb = 1;
		return novo_nodo(chave);
	}

    if (chave <= nodo->chave)
    {
        nodo->esquerda = insere_nodo(nodo->esquerda, chave, calcula_fb);
        nodo->esquerda->pai = nodo;
		if (*calcula_fb)
			nodo->balanceamento -= 1;
    }

    else
    {
        nodo->direita = insere_nodo(nodo->direita, chave, calcula_fb);
        nodo->direita->pai = nodo;

		if (*calcula_fb)
			nodo->balanceamento+= 1;
    }

	if (*calcula_fb)
	{
		if (nodo->balanceamento == 0)
			(*calcula_fb = 0);

		if (nodo->balanceamento == 2 || nodo->balanceamento == -2)
			nodo = ajusta_avl(nodo, calcula_fb);

	}

    return nodo;
}

void ajustaNoPai(t_nodo *nodo, t_nodo *novo)
{
    if (nodo->pai != NULL)
    {
        if (nodo->pai->esquerda == nodo)
            nodo->pai->esquerda = novo;
        else
            nodo->pai->direita = novo;
        if (novo != NULL)
            novo->pai = nodo->pai;
    }
}

t_nodo *remove_nodo(t_nodo *no, t_nodo *raiz)
{
    int calcula_fb;
    t_nodo *direitaSuc, *s, *novaRaiz = raiz;
    if (no == NULL)
        return NULL;
    t_nodo *noAjuste = no->pai;
    if (no->esquerda == NULL && no->direita == NULL)
    {
        if (no == raiz)
        {
            free(no);
            return NULL;
        }
        if (no->pai->esquerda == no)
            no->pai->balanceamento++;
        else
            no->pai->balanceamento--;
        noAjuste = ajustaFBalanceamentoPai(no->pai);
        ajustaNoPai(no, NULL);
        free(no);
    }
    else
    {
        if (no->esquerda == NULL)
        {
            noAjuste = ajustaFBalanceamentoPai(no);
            ajustaNoPai(no, no->direita);
            if (no->pai == NULL)
                novaRaiz = no->direita;
            free(no);
        }
        else
        {
            if (no->direita == NULL)
            {
                noAjuste = ajustaFBalanceamentoPai(no);
                ajustaNoPai(no, no->esquerda);
                if (no->pai == NULL)
                    novaRaiz = no->esquerda;
                free(no);
            }
            else
            {
                int ultimoSucessor;
                s = sucessor(no);
                direitaSuc = s->direita;
                ultimoSucessor = s->esquerda == NULL && s->direita == NULL;
                ajustaNoPai(s, s->direita);
                s->esquerda = no->esquerda;
                s->direita = no->direita;
                s->balanceamento = no->balanceamento;
                ajustaNoPai(no, s);
                s->esquerda->pai = s;
                if (ultimoSucessor)
                {
                    s->balanceamento--;
                    noAjuste = s;
                }
                else
                    s->direita->pai = s;
                if (no == raiz)
                {
                    novaRaiz = s;
                    s->pai = NULL;
                }
                free(no);
                if (s->balanceamento != -2 && direitaSuc != NULL)
                    noAjuste = ajustaFBalanceamentoPai(direitaSuc);
            }
        }
    }
    while (noAjuste != NULL && (noAjuste->balanceamento == 2 || noAjuste->balanceamento == -2))
    {
        calcula_fb = 1;
        no = ajusta_avl(noAjuste, &calcula_fb);
        if (no->pai == NULL)
        {
            novaRaiz = no;
            noAjuste = NULL;
        }
        else
            noAjuste = ajustaFBalanceamentoPai(noAjuste->pai);
    }
    return novaRaiz;
}
