#ifndef HUFFNODE_H_INCLUDED
#define HUFFNODE_H_INCLUDED

typedef struct HuffNode
{
	unsigned char caracter;
	int frequencia;
	struct HuffNode *esquerda, *direita;
} HuffNode;

extern HuffNode* novoHuffNode (unsigned char c, int f);

#endif // HUFFMANNODE_H_INCLUDED
