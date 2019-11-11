#include "HuffmanTree.h"
#include "CharCompacto.h"
#include "Lista.h"

#include <stdlib.h>

void inicieArvore(HuffmanTree *arvore)
{
    arvore->raiz = NULL;
}

No* percorreArvore(HuffNode *atual, char codigo[], int cont, Lista *lista, int (*compar)(void *, void*))
{
    if(atual != NULL)
    {
        if(atual->esquerda != NULL)
        {
            codigo[cont] = '0';
            codigo[cont + 1] = '\0';
            percorreArvore(atual->esquerda, codigo, cont + 1, lista, compar);
        }

        if(atual->esquerda == NULL && atual->direita == NULL)
        {
            insiraEmOrdem(lista, novoCharCompacto(atual->caracter, codigo, atual->frequencia), compar);
            codigo[cont - 1] = '\0';
        }

        if(atual->direita != NULL)
        {
            codigo[cont] = '1';
            codigo[cont + 1] = '\0';
            percorreArvore(atual->direita, codigo, cont + 1, lista, compar);
        }
    }

    return lista->inicio;
}

short int qtdFolhas(HuffNode* atual)
{
    if(atual == NULL)
        return 0;
      if(atual->esquerda == NULL && atual->direita==NULL)
        return 1;
      else
        return qtdFolhas(atual->esquerda) +
               qtdFolhas(atual->direita);
}

void inserirNaRaizNula(HuffmanTree *arvore, HuffNode *x)
{
    if(arvore->raiz == NULL)
        arvore->raiz = x;
}
