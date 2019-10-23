#include "Lista.h"
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
