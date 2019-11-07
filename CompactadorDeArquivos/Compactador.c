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
        char aux = 0;

        Fila fila;
        HuffmanTree *arvore;
        HuffNode *auxHuff;
        Lista *lista;
        No* atual;

        inicieFila(&fila);

        /*Inicia vetor de frequencia*/
        for(int i = 0; i < 256; i++)
            vetorFrequencia[i] = 0;

        /*Conta a frequencia de cada caracter no arquivo e a quantidade de caracteres no arquivo*/
        aux = getc(arqEntrada);
        while(aux != EOF)
        {
            vetorFrequencia[aux]++;
            qtdChars++;
            aux = getc(arqEntrada);
        }

        /*Retorna ao inicio do arquivo para futuras leituras*/
        rewind(arqEntrada);

        /*Insere os caracteres na fila de prioridades */
        for(int i = 0; i < 256; i++)
        {
            if(vetorFrequencia[i] != 0)
                insiraEmOrdem(&fila.lis, novoHuffNode(i, vetorFrequencia[i]), comparaHuffNode);
        }

        /*Enquanto tem 2 ou mais nos na fila*/
        while(fila.lis.qtd >= 2)
        {
            /*Cria um novo no*/
            HuffNode* novo = novoHuffNode(-1,0);

            /*Desenfileira dois nos, para a esquerda e para a direita do novo no*/
            novo->esquerda = desenfileirar(&fila.lis);
            novo->direita  = desenfileirar(&fila.lis);

            /*Atrinui a frequencia desse novo no como a soma da  frequencia dos nos anteriores*/
            novo->frequencia = novo->esquerda->frequencia + novo->direita->frequencia;

            /*Insere o no na lista em ordem*/
            insiraEmOrdem(&fila.lis, novo, comparaHuffNode);
        }

        limparVetorChar(codigo, 9);
        inicieArvore(&arvore);
        inicieLista(&lista);

        /*AuxHuff agora eh a raiz da arvore*/
        auxHuff = (HuffNode*) desenfileirar(&fila.lis);

        /*Percorre a arvore guardando o codigo dos caracteres em uma lista, cuja raiz eh o no inicial*/
        No* inicial = percorreArvore(auxHuff, codigo, cont, &lista, comparaHuffNode);
        atual = inicial;

        /*Printa os codigos*/
        /*
        while(atual != NULL)
        {
            CharCompacto *aux = (CharCompacto*)atual->info;
            printf("%c : %s\n",aux->character, aux->codigo);
            atual = atual->prox;
        }*/


        /*Pega o nome do arquivo e troca a extensao para .alula*/
        strcpy(nomeArquivoAlula, &nomeArquivo);
        for(int j = 50; nomeArquivoAlula[j] != '.'; j--)
            nomeArquivoAlula[j] = '\0';
        strcat(nomeArquivoAlula, "alula");

        /*Cria o arquivo de saida*/
        FILE *arqSaida;
        if((arqSaida = fopen(nomeArquivoAlula, "wb")) == NULL)
            puts("Esse arquivo nao pode ser criado!");
        else
        {
            CharCompacto *au;
            char tamanhoCodigo = 0;
            char lixo = 0;
            int charLido = 0;

            limparVetorChar(codigo, 9);

            /*Reserva lugar para printar a quantidade de lixo de memoria no final dos codigos
            Tamanho do char -> 1 byte*/
            fputc('\0', arqSaida);

            /*Printa a quantidade de caracteres que o arquivo tem*/
            fprintf(arqSaida, "%d", qtdChars);;

            /*em teoria aqui tinha que ter isso*/
            /*fprintf(extensao, "%s", qtdChars);*/
            /*Mas n sei como fazer*/

            /*Printa a lista com os codigos no arquivo para ser lida na descompactacao*/
            No* auxiliar = inicial;
            while(auxiliar != NULL)
            {
                au = (CharCompacto*) auxiliar->info;
                fputc(au->character, arqSaida);
                fputc(au->codigo, arqSaida);
                auxiliar = auxiliar->prox
            }

            /*Le o arquivo novamente e printa os codigos correspondentes aos caracteres*/
            charLido = getc(arqEntrada);
            while(charLido != EOF)
            {
                No* auxiliar = inicial;
                if(charLido >= 0)
                {
                    /*Percorre a lista para pegar o codigo do charLido*/
                    while(auxiliar != NULL)
                    {
                        au = (CharCompacto*) auxiliar->info;
                        if(au->character == charLido)
                        {
                            /*Vai adicionando os bits do codigo um por um ate que tenha suficiente(8) para printar*/
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
                    /*Se ainda ha algo no codigo, printa com lixo de memoria e avisa quantos bits de lixo tem*/
                    if(codigo)
                        printarArquivo(codigo, arqSaida);
                    lixo = 8 - tamanhoCodigo;
                }
                charLido = getc(arqEntrada);
            }

            /*Volta para o inico do aquivo para printar a quantidade de lixo de memoria*/
            rewind(arqSaida);

            fprintf(arqSaida, "%c", lixo);


            /*fecha os arquivos*/
            puts(nomeArquivoAlula);
            fclose(arqSaida);
            fclose(arqEntrada);

            /*da free na memoria*/
            auxiliar = inicial;
            while(auxiliar != NULL)
            {
                auxiliar = auxiliar->prox;
                free(auxiliar);
            }
            free(inicial);
        }
    }

    system("PAUSE");
}

void descompactar()
{
    clearScreen();

    char nomeArquivoAlula[50];
    char nomeArquivo[50];
    FILE *arqEntrada;
    FILE *arqSaida;

    printf("%s", "Digite o nome do arquivo que sera descompactado:\n" );
    fflush(stdout);

    scanf("%s", &nomeArquivoAlula);
    fflush(stdin);

    if((arqEntrada = fopen(nomeArquivoAlula,"rb")) == NULL)
        puts("Esse arquivo nao existe!");
    else
    {
        int qtdChars = 0;
        char[10] extensao;
        char lixoMemoria;
        int auxChar = 0;
        Lista lista;

        inicieLista(&lista);

        /*Le qual sera a quantidade de lixo de memoria no final dos codigos*/
        lixoMemoria = getc(arqEntrada);

        /*Le qual sera a quantidade de chars na lista*/
        fscanf(arqEntrada, "%d", qtdChars);

        /*em teoria aqui tinha que ter isso*/
        /*fscanf(extensao, "%s", qtdChars);*/
        /*Mas n sei como fazer*/


        /*Reconstroe a Lista com os codigos dos chars*/
        for(int i = 0; i < qtdChars; i++)
        {
            CharCompacto auxCompacto = novoCharCompacto(getc(arqEntrada),getc(arqEntrada))
            insiraEmOrdem(lista, auxCompacto, comparaHuffNode());
        }

        strcpy(nomeArquivo, &nomeArquivoAlula);
        for(int j = 50; nomeArquivo[j] != '.'; j--)
            nomeArquivo[j] = '\0';
        strcat(nomeArquivo, extensao);

        fopen(nomeArquivo);




        fclose(arqEntrada);
        fclose(nomeArquivo);
    }

    system("PAUSE");
}

void clearScreen()
{
    system("@cls||clear");
}

