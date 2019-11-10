#include <stdlib.h>
#include "HuffNode.h"

HuffNode* novoHuffNode (int c, int f)
{
    HuffNode* ret = (HuffNode*) malloc(sizeof(HuffNode));
    ret->caracter = c;
    ret->frequencia = f;
    ret->esquerda = NULL;
    ret->direita = NULL;
}
