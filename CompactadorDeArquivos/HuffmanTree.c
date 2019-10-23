#include "HuffmanTree.h"
#include <stdlib.h>

void inicie (HuffmanTree *arvore)
{
    arvore->raiz = NULL;
}

//naum ta certu
void percorreArvore(HuffNode *atual, char codigo[], int cont)
{
    if(atual != NULL)
    {
        codigo[cont] = '0';
        percorreArvore(atual->esquerda, codigo, cont + 1);
        codigo[cont] = '1';
        percorreArvore(atual->direita, codigo, cont + 1);
    }
}
