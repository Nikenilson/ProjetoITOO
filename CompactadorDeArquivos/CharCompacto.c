#include <stdlib.h>
#include <string.h>

#include "CharCompacto.h"

CharCompacto* novoCharCompacto (char c, char cod[])
{
    CharCompacto* ret = (CharCompacto*) malloc(sizeof(CharCompacto));
    ret->character = c;
    strcpy(ret->codigo, cod);
    return ret;
}

char getCaracter(CharCompacto *c)
{
    return c->character;
}

char getCodigo(CharCompacto *c)
{
    return c->codigo;
}

