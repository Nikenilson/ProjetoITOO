#include "Fila.h"
#include <stdlib.h>

void enfileirar(void *dado)
{
    Lista->fim->prox = novoNo(*dado, NULL);
}

void* desenfileirar()
{
    No* aux = Lista->inicio;
    Lista->inicio = Lista->inicio->prox;

    return aux->info;
}
