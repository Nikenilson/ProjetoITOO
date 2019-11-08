#ifndef CHARCOMPACTO_H_INCLUDED
#define CHARCOMPACTO_H_INCLUDED

typedef struct
{
    char character;
    char codigo[9];
    int frequencia;
} CharCompacto;

extern CharCompacto* novoCharCompacto (char c, char cod[], int f);

#endif // CHARCOMPACTO_H_INCLUDED
