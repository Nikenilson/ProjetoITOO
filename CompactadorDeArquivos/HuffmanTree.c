#include "HuffmanTree.h"
#include "CharCompacto.h"
#include "Lista.h"

#include <stdlib.h>

void inicieArvore(HuffmanTree *arvore)
{
    arvore->raiz = NULL;
}

void percorreArvore(HuffNode *atual, char codigo[], int cont, Lista *lista)
{
    if(atual != NULL)
    {
        printf("%s","lula");
        if(atual->esquerda != NULL && atual->esquerda != NULL)
        {
            codigo[cont] = '0';
            percorreArvore(atual->esquerda, codigo, cont + 1, lista);
            codigo[cont] = '1';
            percorreArvore(atual->direita, codigo, cont + 1, lista);
            codigo[cont] = NULL;
            cont--;
        }
        else
            insiraNoInicio(lista, novoCharCompacto(atual->caracter, codigo));

    }
}

void inserirNaRaizNula(HuffmanTree *arvore, HuffNode *x)
{
    if(arvore->raiz == NULL)
        arvore->raiz = x;
}
