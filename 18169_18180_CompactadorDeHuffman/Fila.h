#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include "Lista.h"

typedef struct
{
    Lista lis;
} Fila;

extern void  enfileirar(Lista *lis, void *dado);
extern void* desenfileirar(Lista *lis);
extern void  inicieFila(Fila *fila);

#endif // FILA_H_INCLUDED
