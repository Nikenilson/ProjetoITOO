#include "Fila.h"
#include "Lista.h"
#include <stdlib.h>

void enfileirar(Lista* lis, void *dado)
{
    lis->fim->prox = novoNo(dado, NULL);
}

void* desenfileirar(Lista *lis)
{
    No* aux = lis->inicio;
    lis->inicio = lis->inicio->prox;
    lis->qtd--;

    return aux->info;
}

void inicieFila(Fila *fila)
{
    inicieLista(&fila->lis);
}
