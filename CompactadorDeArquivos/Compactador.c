#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fila.h"
#include "Lista.h"
#include "HuffNode.h"

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
        Fila fila;

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
                insiraEmOrdem(fila.lis, novoHuffNode(i, vetorFrequencia[i]), comparaHuffNode);
        }

        while(fila.lis->inicio != NULL)
        {
            HuffNode *aux = (HuffNode*) fila.lis->inicio->info;
            printf("[Funcionou] %c : %d\n", aux->caracter, aux->frequencia);
            fila.lis->inicio = fila.lis->inicio->prox;
        }

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

    if((arqEntrada = fopen(nomeArquivo,"rb")) == NULL)
        puts("Esse arquivo nao existe!");
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
