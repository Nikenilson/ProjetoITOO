#ifndef HUFFNODE_H_INCLUDED
#define HUFFNODE_H_INCLUDED

typedef struct HuffNode
{
	int caracter;
	int frequencia;
	struct HuffNode *esquerda, *direita;
} HuffNode;

extern HuffNode* novoHuffNode (int c, int f);

#endif // HUFFMANNODE_H_INCLUDED
