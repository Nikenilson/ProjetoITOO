#include <stdio.h>
#include <stdlib.h>

int main()
{
    char nomeArquivo[50];
    char escolha;
    FILE *arqEntrada;

    printf("%s","Digite o nome do arquivo que sera compactado ou descompactado:\n" );
    //fflush();

    scanf("%s", &nomeArquivo);
    strcpy(nomeArquivo,nomeArquivo);

    printf("%s","Digite 1 para descompactar o arquivo, ou qualquer outra coisa para compactar " );
    //fflush();
    scanf("%c", &escolha);

    if(escolha != 1) //compactar
    {
        if(arqEntrada = fopen(nomeArquivo,"%rb") == NULL)
            printf("%s", "Esse arquivo nao existe");
        else
        {

            /*1.
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

            //for()//preendhe a fila de frequencia


            fclose(arqEntrada);
        }

    }
    else //descompactar
    {

    }




    return 0;
}
