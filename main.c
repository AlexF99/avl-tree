#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

//Comentario

#define LENGTH 1024

void processa_entradas(t_nodo *nodo)
{
    char op[1];
    int chave;

    printf("'q+enter' para finalizar a entrada\nescreva as entradas da arvore:\n");
    scanf("%s", op);
    if (op[0] == 'q')
        exit(0);
    scanf("%d", &chave);
    nodo = novo_nodo(chave);
    while (1)
    {
        scanf("%s", op);
        switch (op[0])
        {
        case 'q':
            emordem(nodo);
            exit(0);
        case 'i':
            scanf("%d", &chave);
            insere_nodo(nodo, chave);
        case 'r':
            scanf("%d", &chave);
            remove_nodo(nodo, chave);
        }
    }
}

int main()
{

    t_nodo *nodo;

    processa_entradas(nodo);

    return 0;
}
