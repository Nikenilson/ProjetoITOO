#include <stdlib.h>
#include <string.h>

#include "CharCompacto.h"

CharCompacto* novoCharCompacto (char c, char cod[], int f)
{
    CharCompacto* ret = (CharCompacto*) malloc(sizeof(CharCompacto));
    ret->frequencia = f;
    ret->character = c;
    strcpy(ret->codigo, cod);
    return ret;
}

