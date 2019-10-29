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
        if(atual->esquerda != NULL)
        {
          codigo[cont] = '0';
          percorreArvore(atual->esquerda, codigo, cont + 1, lista);
        }

        if(atual->esquerda == NULL && atual->direita == NULL)
        {
            insiraNoInicio(lista, novoCharCompacto(atual->caracter, codigo));
        }
        if(atual->direita != NULL)
        {
          codigo[cont] = '1';
            percorreArvore(atual->direita, codigo, cont + 1, lista);
        }

        /*if(atual->esquerda != NULL && atual->direita != NULL)
        {
            codigo[cont] = '0';
            percorreArvore(atual->esquerda, codigo, cont + 1, lista);
            codigo[cont] = '1';
            percorreArvore(atual->direita, codigo, cont + 1, lista);
            codigo[cont] = '2'; //Teste clan calma
            cont--;
        }
        else
            insiraNoInicio(lista, novoCharCompacto(atual->caracter, codigo));*/
    }
}

void inserirNaRaizNula(HuffmanTree *arvore, HuffNode *x)
{
    if(arvore->raiz == NULL)
        arvore->raiz = x;
}
