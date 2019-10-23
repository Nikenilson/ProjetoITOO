#include "Lista.h"
#include "HuffNode.h"
#include <stdlib.h>

No* novoNo (void *inf, No *prx)
{
   No *novo   = (No*)malloc(sizeof(No));
   novo->info = inf;
   novo->prox = prx;
   return novo;
}

void inicieLista (Lista *lis)
{
    lis->inicio=NULL;
    (*lis).fim =NULL;
}

void insiraNoInicio (Lista *lis, void *inf)
{
    lis->inicio=novoNo(inf,lis->inicio);
    if (lis->fim==NULL)
        lis->fim=lis->inicio;
}

void insiraEmOrdem (Lista *lis, void *inf, int (*compar)(void *, void*))
{
    No* atual;
    No* no = novoNo(inf, NULL);
    // Special case for the head end
    if (lis->inicio == NULL || compar(lis->inicio->info, no->info) >= 0)
    {
        no->prox = lis->inicio;
        lis->inicio = no;
    }
    else
    {
        // Locate the node before the point of insertion
        atual = lis->inicio;
        while (atual->prox != NULL && compar(atual->prox->info, no->info) < 0)
        {
            atual = atual->prox;
        }
        no->prox = atual->prox;
        atual->prox = no;
    }
}
