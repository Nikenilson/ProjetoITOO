#ifndef HUFFMANTREE_H_INCLUDED
#define HUFFMANTREE_H_INCLUDED
#include "HuffNode.h"
#include "Lista.h"

typedef struct
{
    HuffNode *raiz;
} HuffmanTree;

extern void inicieArvore(HuffmanTree *arvore);
extern void inserirNaRaizNula(HuffmanTree *arvore, HuffNode *x);
extern void percorreArvore(HuffNode *atual, char codigo[], int cont, Lista *lista);

#endif // HUFFMANTREE_H_INCLUDED
