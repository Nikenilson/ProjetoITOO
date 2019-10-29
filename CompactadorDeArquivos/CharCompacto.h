#ifndef CHARCOMPACTO_H_INCLUDED
#define CHARCOMPACTO_H_INCLUDED

typedef struct
{
    char character;
    char codigo[9];
} CharCompacto;

extern CharCompacto* novoCharCompacto (char c, char cod[]);
char getCaracter(CharCompacto *c);
char getCodigo(CharCompacto *c);


#endif // CHARCOMPACTO_H_INCLUDED
