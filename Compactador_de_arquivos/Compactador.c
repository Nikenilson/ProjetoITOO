#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void compactar()
{
    clearScreen();

    char nomeArquivo[256];
    FILE *arqEntrada;

    printf("%s", "Digite o nome do arquivo que sera compactado:\n" );
    fflush(stdout);

    gets(&nomeArquivo);
    fflush(stdin);

    if(arqEntrada = fopen(nomeArquivo,"rb") == NULL)
        puts("Esse arquivo nao existe!");
    else
    {
        int vetorFrequencia [256];

        for(int i = 0; i < 256; i++)
            vetorFrequencia[i] = 0;

        /* Segura que deu ruim aqui, n mexe ainda
        char aux = getc(arqEntrada);
        while(aux != EOF)
        {
            vetorFrequencia[aux]++;
            aux = getc(arqEntrada);
        }*/

        rewind(arqEntrada);

        for(int i = 0; i < 256; i++){
            printf("%d", vetorFrequencia[i]);
            printf("%c", vetorFrequencia[i]);
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
    strcpy(nomeArquivo, nomeArquivo);


    if(arqEntrada = fopen(nomeArquivo,"rb") == NULL)
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
