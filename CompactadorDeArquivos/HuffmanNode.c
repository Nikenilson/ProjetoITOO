#include "HuffmanNode.h"

HuffNode* novoHuffNode (char c, int f)
{
    HuffNode* ret = (HuffNode*) malloc(sizeof(HuffNode));
    ret->caracter = c;
    ret->frequencia = f;
    ret->esquerda = NULL;
    ret->direita = NULL;
}
