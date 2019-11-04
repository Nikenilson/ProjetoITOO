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

        while(!feof(arqEntrada))
        {
            char aux = getc(arqEntrada);
            vetorFrequencia[aux]++;
            qtdChars++;
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

            /*Create new node

            Dequeue node and make it left subtree

            Dequeue next node and make it right
            subtree

            Frequency of new node equals sum of
            frequency of left and right children

            Enqueue new node back into queue*/
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
        atual = percorreArvore(auxHuff, codigo, cont, &lista, comparaHuffNode);
        lista->inicio = atual;

        while(atual != NULL)
        {
            CharCompacto *aux = (CharCompacto*)atual->info;
            printf("%c : %s\n",aux->character, aux->codigo);
            atual = atual->prox;
        }

        puts("alula 3");

        /*
        1.
        Scan text to be compressed and tally
        occurrence of all characters.

        2.
        Sort or prioritize characters based on
        number of occurrences in text.

        3.
        Build Huffman code tree based on
        prioritized list.

        4.
        Perform a traversal of tree to determine
        all code words.

        5.
        Scan text again and create new file
        using the Huffman codes.
        */

        strcpy(nomeArquivoAlula, &nomeArquivo);
        for(int j = 50; nomeArquivoAlula[j] != '.'; j--)
            nomeArquivoAlula[j] = '\0';
        strcat(nomeArquivoAlula, "alula");

        FILE *arqSaida;
        if((arqSaida = fopen(nomeArquivoAlula, "wb")) == NULL)
            puts("Esse arquivo nao pode ser criado!");
        else
        {
            while(!feof(arqEntrada))
            {
                char aux1[9];
                char aux2[9];

                int auxChar = 0;
                if((auxChar = getc(arqEntrada)) >= 0 )
                {
                    No* auxiliar = lista->inicio;
                    while(auxiliar != NULL)
                    {
                        CharCompacto *au = (CharCompacto*)auxiliar->info;
                        if(au->character == auxChar)
                        {
                            char sobra[9];
                            char temSobra = 0;

                            if(strlen(aux1) + strlen(au->codigo) < 10)
                            {
                                if(!temSobra)
                                {
                                    char codigoAU[9];
                                    strcpy(codigoAU,au->codigo);
                                    strcat(aux1,codigoAU);
                                    printf("%s\n",aux1);
                                }
                                else
                                {
                                    if(strlen(aux1) + strlen(au->codigo) + strlen(sobra) < 10)
                                    {
                                        char codigoAU[9];
                                        strcpy(codigoAU,au->codigo);
                                        strcat(sobra,aux1);
                                        strcat(sobra,codigoAU);
                                        printf("%s\n",sobra);
                                    }
                                    else
                                    {
                                        if(strlen(aux1) + strlen(sobra) < 10)
                                        {
                                            strcat(aux1,sobra);
                                            printf("%s\n",aux1);
                                        }
                                        else
                                        {
                                            char codigoAU[9];
                                            char OlhaAGambiBrasil[9];
                                            char jaAcabou = 0;
                                            char emQualAcabou = 0;

                                            strcpy(codigoAU,au->codigo);


                                            for(int i = 0; i < 10; i++)
                                            {
                                                if(!jaAcabou)
                                                {
                                                    OlhaAGambiBrasil[i] = codigoAU[i];
                                                    if(codigoAU[i] == '\0')
                                                    {
                                                        jaAcabou = 1;
                                                        emQualAcabou = i;
                                                    }
                                                }
                                                else
                                                {
                                                    sobra[i - emQualAcabou] = codigoAU[i];

                                                }
                                            }

                                            strcat(aux1,OlhaAGambiBrasil);
                                            temSobra = 1;

                                        }
                                    }
                                }


                            }
                            else
                            {
                                char codigoAU[9];
                                strcpy(codigoAU,au->codigo);

                                char OlhaAGambiBrasil[9];
                                char jaAcabou = 0;
                                char emQualAcabou = 0;

                                for(int i = 0; i < 10; i++)
                                {
                                    if(!jaAcabou)
                                    {
                                        OlhaAGambiBrasil[i] = codigoAU[i];
                                        if(codigoAU[i] == '\0')
                                        {
                                            jaAcabou = 1;
                                            emQualAcabou = i;
                                        }
                                    }
                                    else
                                    {
                                        sobra[i - emQualAcabou] = codigoAU[i];

                                    }
                                }

                                strcat(aux1,OlhaAGambiBrasil);
                                temSobra = 1;
                            }
                        }
                    auxiliar = auxiliar->prox;
                    }
                }
                else
                    puts("let it go"); /*Deu ruim brasil*/

                }

            }

        puts(nomeArquivoAlula);
        fclose(arqSaida);
        fclose(arqEntrada);
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
