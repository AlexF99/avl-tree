typedef struct t_avl
{
    int chave;
    int *direita, *esquerda, *pai;
} t_avl;

t_avl *init_avl(t_avl *avl, int valor);

void insere_avl(t_avl *avl, int valor);

void remove_avl(t_avl *avl, int valor);
