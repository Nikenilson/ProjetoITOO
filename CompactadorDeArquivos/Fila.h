#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include "Lista.h"

extern void enfileirar(void *dado);
extern void* desenfileirar();

typedef struct
{
    Lista lis;
} Fila;

#endif // FILA_H_INCLUDED
