#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fila.h"
#include "Lista.h"
#include "HuffNode.h"
#include "HuffmanTree.h"
#include "CharCompacto.h"

int main()
{
    int escolha;

    do
    {
        clearScreen();
        puts("[Descompactador de Arquivos]\n");
        puts("1. Compactar arquivo");
        puts("2. Descompactar arquivo");
        puts("3. Sair\n");
        printf("%s", "Digite a opcao desejada: ");
        fflush(stdout);

        scanf("%d", &escolha);
        fflush(stdin);

        switch(escolha)
        {
            case 1:
                compactar();
                break;
            case 2:
                descompactar();
                break;
            case 3:
                exit(0);
                break;
        }
    }
    while (escolha != 3);

    return 0;
}

int comparaHuffNode (void * a, void * b)
{
   return ( ((HuffNode*)a)->frequencia - ((HuffNode*)b)->frequencia );
}

void setBit(unsigned char qual_bit, unsigned char* valor)
{
    unsigned int bit_desejado = 1;
    bit_desejado <<= qual_bit;
    *valor = *valor | bit_desejado;
}

void printarArquivo(char* c, FILE *f)
{
    unsigned char b = 0;
    for(int i = 0; i < 9; i++)
    {
        if(c[i] == '1')
            setBit(i, b);
    }
    fputc(b, f);
    fflush(f);
}

void limparVetorChar(char *v, int t)
{
    for(int i = 0; i < t; i++)
    {
        v[i] = '\0';
    }

}


void compactar()
{
    clearScreen();

    char nomeArquivo[50];
    char nomeArquivoAlula[50];
    FILE *arqEntrada;

    printf("%s", "Digite o nome do arquivo que sera compactado:\n" );
    fflush(stdout);

    scanf("%s", &nomeArquivo);
    fflush(stdin);

    if((arqEntrada = fopen(nomeArquivo, "rb")) == NULL)
        puts("Esse arquivo nao existe!");
    else
    {
        int vetorFrequencia [256];
        int qtdChars = 0;
        int cont = 0;
        char codigo[9];

        Fila fila;
        HuffmanTree *arvore;
        HuffNode *auxHuff;
        Lista *lista;
        No* atual;

        inicieFila(&fila);

        for(int i = 0; i < 256; i++)
            vetorFrequencia[i] = 0;

        char aux = getc(arqEntrada);
        while(aux != EOF)
        {
            vetorFrequencia[aux]++;
            qtdChars++;
            aux = getc(arqEntrada);
        }
        rewind(arqEntrada);

        for(int i = 0; i < 256; i++)
        {
            if(vetorFrequencia[i] != 0)
                insiraEmOrdem(&fila.lis, novoHuffNode(i, vetorFrequencia[i]), comparaHuffNode);
        }

        while(fila.lis.qtd >= 2)
        {
            HuffNode* novo = novoHuffNode(-1,0);

            novo->esquerda = desenfileirar(&fila.lis);
            novo->direita  = desenfileirar(&fila.lis);
            novo->frequencia = novo->esquerda->frequencia + novo->direita->frequencia;

            insiraEmOrdem(&fila.lis, novo, comparaHuffNode);
        }

        limparVetorChar(codigo, 9);

        inicieArvore(&arvore);
        auxHuff = (HuffNode*) desenfileirar(&fila.lis);

        inicieLista(&lista);
        No* inicial = percorreArvore(auxHuff, codigo, cont, &lista, comparaHuffNode);
        atual = inicial;

        while(atual != NULL)
        {
            CharCompacto *aux = (CharCompacto*)atual->info;
            printf("%c : %s\n",aux->character, aux->codigo);
            atual = atual->prox;
        }
        puts("alula 3");

        strcpy(nomeArquivoAlula, &nomeArquivo);
        for(int j = 50; nomeArquivoAlula[j] != '.'; j--)
            nomeArquivoAlula[j] = '\0';
        strcat(nomeArquivoAlula, "alula");

        FILE *arqSaida;
        if((arqSaida = fopen(nomeArquivoAlula, "wb")) == NULL)
            puts("Esse arquivo nao pode ser criado!");
        else
        {
            CharCompacto *au;
            char tamanhoCodigo = 0;
            char lixo = 0;
            int auxChar = 0;

            limparVetorChar(codigo, 9);

            /*Tamanho do int -> 4 bytes*/
            fputc('\0', arqSaida);
            fputc('\0', arqSaida);
            fputc('\0', arqSaida);
            fputc('\0', arqSaida);

            /*Tamanho do char -> 1 byte*/
            fputc('\0', arqSaida);

            auxChar = getc(arqEntrada);
            while(auxChar != EOF)
            {
                No* auxiliar = inicial;
                if(auxChar >= 0)
                {
                    while(auxiliar != NULL)
                    {
                        au = (CharCompacto*) auxiliar->info;
                        if(au->character == auxChar)
                        {
                            for (int c = 0; c < strlen(au->codigo); c++)
                            {
                                codigo[tamanhoCodigo++] = au->codigo[c];
                                if (tamanhoCodigo == 8)
                                {
                                    printarArquivo(codigo, arqSaida);
                                    limparVetorChar(codigo, 9);
                                    tamanhoCodigo = 0;
                                }
                            }
                        }
                        auxiliar = auxiliar->prox;
                    }
                    if(codigo)
                        printarArquivo(codigo, arqSaida);
                    lixo = 8 - tamanhoCodigo;
                }
                auxChar = getc(arqEntrada);
            }

            rewind(arqSaida);

            fprintf(arqSaida, "%d", qtdChars);
            fprintf(arqSaida, "%c", lixo);

            puts(nomeArquivoAlula);
            fclose(arqSaida);
            fclose(arqEntrada);
        }
    }

    system("PAUSE");
}

void descompactar()
{
    clearScreen();

    char nomeArquivo[50];
    FILE *arqEntrada;

    printf("%s", "Digite o nome do arquivo que sera descompactado:\n" );
    fflush(stdout);

    scanf("%s", &nomeArquivo);
    fflush(stdin);

    if((arqEntrada = fopen(nomeArquivo,"wb")) == NULL)
        puts("Esse arquivo não pode ser criado!");
    else
    {
        fclose(arqEntrada);
    }

    system("PAUSE");
}

void clearScreen()
{
    system("@cls||clear");
}

