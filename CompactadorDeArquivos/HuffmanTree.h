#ifndef HUFFMANTREE_H_INCLUDED
#define HUFFMANTREE_H_INCLUDED
#include "HuffNode.h"
#include "Lista.h"

typedef struct
{
    HuffNode *raiz;
} HuffmanTree;

extern void inicieArvore     (HuffmanTree *arvore);
extern void inserirNaRaizNula(HuffmanTree *arvore, HuffNode *x);
extern No*  percorreArvore   (HuffNode    *atual , char codigo[], int cont, Lista *lista, int (*compar)(void *, void*));

#endif // HUFFMANTREE_H_INCLUDED
