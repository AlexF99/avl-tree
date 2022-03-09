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

int nivel_atual(t_nodo *nodo)
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

t_nodo *ajusta_fb_pai(t_nodo *pai)
{
    t_nodo *nodo = pai;
    while (nodo->pai != NULL && nodo->balanceamento != -2 && nodo->balanceamento != 2)
    {
        if (nodo->pai->esquerda == nodo)
            nodo->pai->balanceamento++;
        else
            nodo->pai->balanceamento--;
        nodo = nodo->pai;
    }
    return nodo;
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
    t_nodo *nodo_ajuste;
    if (no->balanceamento == -2)
    {
        if (no->esquerda != NULL && no->esquerda->balanceamento > 0)
            no->esquerda = rot_esquerda(no->esquerda);
        nodo_ajuste = rot_direita(no);
    }
    else
    {
        if (no->direita->balanceamento < 0)
            no->direita = rot_direita(no->direita);
        nodo_ajuste = rot_esquerda(no);
    }
    if (nodo_ajuste->pai != NULL)
    {
        if (nodo_ajuste->pai->esquerda == no)
            nodo_ajuste->pai->esquerda = nodo_ajuste;
        else
            nodo_ajuste->pai->direita = nodo_ajuste;
    }
    nodo_ajuste->balanceamento = 0;
    nodo_ajuste->esquerda->balanceamento = (altura(nodo_ajuste->esquerda->direita) - altura(nodo_ajuste->esquerda->esquerda));
    nodo_ajuste->direita->balanceamento = (altura(nodo_ajuste->direita->direita) - altura(nodo_ajuste->direita->esquerda));
    *calcula_fb = 0;
    return nodo_ajuste;
}

t_nodo *insere_nodo(t_nodo *nodo, int chave, int *calcula_fb)
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
            nodo->balanceamento += 1;
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

void ajusta_pai(t_nodo *nodo, t_nodo *novo)
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

t_nodo *remove_nodo(t_nodo *nodo, t_nodo *raiz)
{
    int calcula_fb;
    t_nodo *sucessor_direita, *s, *nova_raiz = raiz;
    if (!nodo)
        return NULL;
    t_nodo *nodo_ajuste = nodo->pai;
    if (nodo->esquerda == NULL && nodo->direita == NULL) // se for folha
    {
        if (nodo == raiz)
        {
            free(nodo);
            return NULL;
        }
        if (nodo->pai->esquerda == nodo)
            nodo->pai->balanceamento++;
        else
            nodo->pai->balanceamento--;
        nodo_ajuste = ajusta_fb_pai(nodo->pai);
        ajusta_pai(nodo, NULL);
        free(nodo);
    }
    else
    {
        if (nodo->esquerda == NULL)
        {
            nodo_ajuste = ajusta_fb_pai(nodo);
            ajusta_pai(nodo, nodo->direita);
            if (nodo->pai == NULL)
                nova_raiz = nodo->direita;
            free(nodo);
        }
        else
        {
            if (nodo->direita == NULL)
            {
                nodo_ajuste = ajusta_fb_pai(nodo);
                ajusta_pai(nodo, nodo->esquerda);
                if (nodo->pai == NULL)
                    nova_raiz = nodo->esquerda;
                free(nodo);
            }
            else // nodo sendo excluido tem 2 filhos
            {
                int ultimo_sucessor;
                s = sucessor(nodo);
                sucessor_direita = s->direita;
                ultimo_sucessor = s->esquerda == NULL && s->direita == NULL;
                ajusta_pai(s, s->direita);
                s->esquerda = nodo->esquerda;
                s->direita = nodo->direita;
                s->balanceamento = nodo->balanceamento;
                ajusta_pai(nodo, s);
                s->esquerda->pai = s;
                if (ultimo_sucessor)
                {
                    s->balanceamento--;
                    nodo_ajuste = s;
                }
                else
                    s->direita->pai = s;
                if (nodo == raiz)
                {
                    nova_raiz = s;
                    s->pai = NULL;
                }
                free(nodo);
                if (s->balanceamento != -2 && sucessor_direita != NULL)
                    nodo_ajuste = ajusta_fb_pai(sucessor_direita);
            }
        }
    }

    // verifica balanceamento e ajusta caso necessario
    while (nodo_ajuste != NULL && (nodo_ajuste->balanceamento == 2 || nodo_ajuste->balanceamento == -2))
    {
        calcula_fb = 1;
        nodo = ajusta_avl(nodo_ajuste, &calcula_fb);
        if (nodo->pai == NULL)
        {
            nova_raiz = nodo;
            nodo_ajuste = NULL;
        }
        else
            nodo_ajuste = ajusta_fb_pai(nodo_ajuste->pai);
    }
    return nova_raiz;
}
