typedef struct t_nodo
{
    int chave;
    struct t_nodo *direita, *esquerda, *pai;
    int balanceamento;
} t_nodo;

t_nodo *novo_nodo(int chave);

t_nodo *insere_nodo(t_nodo *nodo, int chave);

void remove_nodo(t_nodo *nodo, int chave);

void emordem(t_nodo *nodo);

t_nodo * rot_esquerda(t_nodo * nodo);
