#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

#define LENGTH 1024

void processa_entradas(t_avl *avl) {
    char op[1];
    int chave;

    printf("'q+enter' para finalizar a entrada\nescreva as entradas da arvore:\n");
    fscanf(stdin, "%s", op);
    if (op[0] == 'q') exit(0);
    fscanf(stdin, "%d", &chave);
    init_avl(avl, chave);
    while (1)
    {
        fscanf(stdin, "%s", op);
        switch(op[0]) {
            case 'q':
                exit(0);
            case 'i':
                fscanf(stdin, "%d", &chave);
                insere_avl(avl, chave);
            case 'r':
                fscanf(stdin, "%d", &chave);
                remove_avl(avl, chave);
        }
    }
}

int main() {

    t_avl *avl;

    processa_entradas(avl);

    return 0;
}