#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

#define LENGTH 1024

void processa_entradas(t_nodo *nodo)
{
    char op[1];
    char line[LENGTH];
    int chave;
    int calcula_fb = 0;
    t_nodo *nodo_excluir = NULL;

    scanf("%s", op);
    if (op[0] == 'q')
        exit(0);

    scanf("%d", &chave);
    nodo = novo_nodo(chave);

    while (fgets(line, 1024, stdin) != NULL)
    {
        scanf("%s", op);
        switch (op[0])
        {
        case 'q':
            emordem(nodo);
            exit(0);
        case 'i':
            scanf("%d", &chave);
            nodo = insere_nodo(nodo, chave, &calcula_fb);
            break;
        case 'r':
            scanf("%d", &chave);
            nodo_excluir = busca(nodo, chave);
            if (nodo_excluir != NULL)
            {
                nodo = remove_nodo(nodo_excluir, nodo);
            }
            break;
        default:
            emordem(nodo);
            break;
        }
    }
    emordem(nodo);
}

int main()
{
    t_nodo *nodo;
    processa_entradas(nodo);

    return 0;
}
