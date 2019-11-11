#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct No
{
    void      *info;
    struct No *prox;
}No;

typedef struct
{
    No *inicio, *fim;
    int qtd;
}
Lista;

extern No* novoNo (void *inf, No *prx);
extern void inicieLista    (Lista *lis);
extern void insiraNoInicio (Lista *lis, void *inf);
extern void insiraEmOrdem  (Lista *lis, void *inf, int (*compar)(void *, void*));

#endif
