#include <stdlib.h>
#include <string.h>

#include "CharCompacto.h"

CharCompacto* novoCharCompacto (char c, char cod[])
{
    CharCompacto* ret = (CharCompacto*) malloc(sizeof(CharCompacto));
    ret->character = c;
    printf("%s",cod);
    strcpy(ret->codigo, cod);
    return ret;
}
