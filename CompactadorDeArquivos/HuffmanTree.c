#include "HuffmanTree.h"
#include <stdlib.h>

void inicieArvore(HuffmanTree *arvore)
{
    arvore->raiz = NULL;
}

//naum ta certu
void percorreArvore(HuffNode *atual, char codigo[], int cont, char **codigos, int contS)
{
    if(atual != NULL)
    {
        puts("lula");
        if(atual->esquerda != NULL|| atual->esquerda != NULL)
        {
            codigo[cont] = '0';
            percorreArvore(atual->esquerda, codigo, cont + 1, codigos, contS);
            codigo[cont] = '1';
            percorreArvore(atual->direita, codigo, cont + 1, codigos, contS );
            codigo[cont] = NULL;
            cont--;
        }
        else
            for(int i = 0; i < 8; i++)
                codigos[contS++][i] = codigo[i];


    }
}
