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
        puts("alula 1");

        for(int i = 0; i < 10; i++)
        {
            codigo[i] = NULL;
        }

        inicieArvore(&arvore);
        auxHuff = (HuffNode*) desenfileirar(&fila.lis);

        puts("alula 2");

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
            unsigned char numeroMagico = 0;
            char stringGrande[256];
            char codigo[9];
            char i = 0;
            char qtdSG = 0;
            char tamanhoCodigo = 0;
            char tamanhoSG = 0;
            char temSobra = 0;
            char lixo = 0;
            int auxChar = 0;

            /*Tamanho do int -> 4 bytes*/
            fputc('\0', arqSaida);
            fputc('\0', arqSaida);
            fputc('\0', arqSaida);
            fputc('\0', arqSaida);

            /*Tamanho do char -> 1 byte*/
            fputc('\0', arqSaida);

            while(!feof(arqEntrada))
            {
                No* auxiliar = inicial;

                for(i = 0 ; i < 8; i++)
                {
                    if((auxChar = getc(arqEntrada)) >= 0)
                    {
                        CharCompacto *au;
                        while(auxiliar != NULL)
                        {
                            au = (CharCompacto*)auxiliar->info;
                            if(au->character == auxChar)
                            {
                                for (int c = 0; c < strlen(au->codigo); c++)
                                {
                                    codigo[tamanhoCodigo] = au->codigo[c];
                                    tamanhoCodigo++;
                                    if (tamanhoCodigo == 8)
                                    {
                                        temSobra = 1;
                                    }
                                }
                            }
                            auxiliar = auxiliar->prox;
                        }


                        if(temSobra)
                        {
                            for(char j = 0; j < tamanhoSG; j++)
                            {
                                stringGrande[j] = stringGrande[qtdSG];
                                stringGrande[qtdSG++] = '\0';
                            }
                            qtdSG = tamanhoSG;
                        }

                        for(int a = 0; a < strlen(codigo); a++)
                        {
                            stringGrande[qtdSG++] = codigo[a];
                            codigo[a] = '\0';
                            tamanhoCodigo--;
                        }
                    }
                    else
                    {
                        tamanhoSG = strlen(stringGrande);
                        lixo = tamanhoSG - qtdChars;
                        numeroMagico = 0;
                        for(char k = 0 ; k < lixo; k++)
                        {
                            if(stringGrande[qtdSG++] == 1)
                            {
                                unsigned int bit_desejado = 1;
                                bit_desejado <<= qtdSG;
                                numeroMagico = numeroMagico | bit_desejado;

                            }

                        }
                        lixo = 8 - lixo;

                        fputc(numeroMagico, arqSaida);

                    }

                }

                i = 0;
                qtdSG = 0;
                tamanhoSG = strlen(stringGrande);

                while(strlen(stringGrande) >= 8)
                {
                    codigo[i++] = stringGrande[qtdSG];
                    stringGrande[qtdSG++] = '\0';
                    tamanhoSG--;

                    if(i == 8)
                    {
                        numeroMagico = 0;
                        for(i = 0 ; i < 8; i++)
                        {
                            if(codigo[i] == 1)
                            {

                            }
                        }

                        i = 0;
                        fputc(numeroMagico, arqSaida);
                    }
                }
                if(tamanhoSG)
                    temSobra = 1;
            }
            rewind(arqSaida);

            fprintf(arqSaida, "%d", qtdChars);
            fprintf(arqSaida, "%d", lixo);

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

void setBit(unsigned char qual_bit, unsigned int* valor)
{
    unsigned int bit_desejado = 1;
    bit_desejado <<= qual_bit;
    *valor = *valor | bit_desejado;
}

void printarArquivo(char* c, FILE *f)
{

}
