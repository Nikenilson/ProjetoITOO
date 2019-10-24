#ifndef HUFFMANTREE_H_INCLUDED
#define HUFFMANTREE_H_INCLUDED
#include "HuffNode.h"

typedef struct
{
    HuffNode *raiz;
} HuffmanTree;

extern void inicieArvore(HuffmanTree *arvore);
extern void percorreArvore(HuffNode *atual, char codigo[], int cont, char **codigos, int contS);

#endif // HUFFMANTREE_H_INCLUDED
