typedef struct No
{
    void      *info;
    struct No *prox;
}
No;

typedef struct
{
    No *inicio, *fim;
}
Lista;

extern No* novoNo (void *inf, No *prx);
extern void inicieLista    (Lista *lis);
extern void insiraNoInicio (Lista *lis, void *inf);
