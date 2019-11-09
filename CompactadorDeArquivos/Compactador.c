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

void printarArvore(HuffNode* r, FILE* f)
{
    if(r != NULL)
    {
        if(r->esquerda == NULL && r->direita == NULL)
        {
            /*Printa caracter*/
            fputc(r->caracter, f);

            /*Printa frequencia*/
            fwrite(&r->frequencia, sizeof(int), 1, f);

            fflush(f);
        }

        printarArvore(r->esquerda, f);
        printarArvore(r->direita, f);
    }
}


int comparaHuffNode (void * a, void * b)
{
   return ( ((HuffNode*)a)->frequencia - ((HuffNode*)b)->frequencia );
}

void setBit(unsigned char* valor, unsigned char qual_bit)
{
    unsigned int bit_desejado = 1;
    bit_desejado <<= 7 - qual_bit;
    *valor = *valor | bit_desejado;
}

void printarArquivo(char* c, FILE *f)
{
    unsigned char b = 0;
    char i;
    for(i = 0; i < 9; i++)
    {
        if(c[i] == '1')
            setBit(&b, i);
    }
    fputc(b, f);
    fflush(f);
}

void limparVetorChar(char *v, int t)
{
    for(int i = 0; i < t; i++)
        v[i] = '\0';
}

void freeArvore(HuffNode* r)
{
    if(r != NULL)
    {
        freeArvore(r->esquerda);
        freeArvore(r->direita);
        free(r);
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
        int aux = 0;

        Fila fila;
        HuffmanTree *arvore;
        HuffNode *auxHuff;
        Lista *lista;
        No* inicial;
        No* anteriorAuxiliar;

        inicieFila(&fila);

        /*Inicia vetor de frequencia*/
        int i;
        for(i = 0; i < 256; i++)
            vetorFrequencia[i] = 0;

        /*Conta a frequencia de cada caracter no arquivo e a quantidade de caracteres no arquivo*/
        aux = getc(arqEntrada);
        while(aux != EOF)
        {
            vetorFrequencia[aux]++;
            aux = getc(arqEntrada);
        }

        /*Retorna ao inicio do arquivo para futuras leituras*/
        rewind(arqEntrada);

        /*Insere os caracteres na fila de prioridades */
        for(i = 0; i < 256; i++)
            if(vetorFrequencia[i] != 0)
                insiraEmOrdem(&fila.lis, novoHuffNode(i, vetorFrequencia[i]), comparaHuffNode);

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

        /*AuxHuff agora eh a raiz da arvore*/
        auxHuff = (HuffNode*) desenfileirar(&fila.lis);

        inicieLista(&lista);

        /*Percorre a arvore guardando o codigo dos caracteres em uma lista, cuja raiz eh o no inicial*/
        inicial = percorreArvore(auxHuff, codigo, cont, &lista, comparaHuffNode);

        /*Pega o nome do arquivo e troca a extensao para .alula*/
        strcat(nomeArquivo, "alula");

        /*Cria o arquivo de saida*/
        FILE *arqSaida;
        if((arqSaida = fopen(nomeArquivo, "wb")) == NULL)
            puts("Esse arquivo nao pode ser criado!");
        else
        {
            CharCompacto *au;
            int tamanhoCodigo = 0;
            int lixo = 0;
            int charLido = 0;

            limparVetorChar(codigo, 9);

            /*Reserva lugar para printar a quantidade de lixo de memoria no final dos codigos
            Tamanho do char -> 1 byte*/
            fputc('\0', arqSaida);

            /*Printa a quantidade de caracteres que o arquivo tem*/
            qtdChars = qtdFolhas(auxHuff);
            fwrite(&qtdChars, sizeof(short int), 1, arqSaida);;

            /*Printa a lista com os codigos no arquivo para ser lida na descompactacao*/
            printarArvore(auxHuff, arqSaida);

            No* auxiliar;
            /*Le o arquivo novamente e printa os codigos correspondentes aos caracteres*/
            charLido = getc(arqEntrada);
            while(charLido != EOF)
            {
                auxiliar = inicial;
                if(charLido >= 0)
                {
                    /*Percorre a lista para pegar o codigo do charLido*/
                    while(auxiliar != NULL)
                    {
                        au = (CharCompacto*) auxiliar->info;
                        if(au->character == charLido)
                        {
                            int tamanho = strlen(au->codigo);
                            int c;
                            /*Vai adicionando os bits do codigo um por um ate que tenha suficiente(8) para printar*/
                            for (c = 0; c < tamanho; c++)
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
                }
                charLido = getc(arqEntrada);
            }
            /*Se ainda ha algo no codigo, printa com lixo de memoria e avisa quantos bits de lixo tem*/
            if(codigo)
            {
                lixo = 8 - tamanhoCodigo;
                for(int i = tamanhoCodigo; i < 8; i++)
                    codigo[i] = '0';
                codigo[9] = '\0';
                printarArquivo(codigo, arqSaida);
            }

            /*Volta para o inicio do aquivo para printar a quantidade de lixo de memoria*/
            rewind(arqSaida);

            fprintf(arqSaida, "%c", lixo);

            fflush(arqSaida);

            printf("%s\n", nomeArquivo);
            fflush(stdout);

            /*fecha os arquivos*/

            fclose(arqSaida);
            fclose(arqEntrada);

            /*da free na memoria(Lista e CharCompacto)*/
            auxiliar = inicial;
            while(auxiliar != NULL)
            {
                anteriorAuxiliar = auxiliar;
                free(auxiliar->info);
                auxiliar = auxiliar->prox;
                free(anteriorAuxiliar);

            }
            free(inicial);

            /*da free na memoria(Arvore)*/
            freeArvore(auxHuff);
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
    puts(nomeArquivoAlula);
    fflush(stdin);

    if((arqEntrada = fopen(nomeArquivoAlula,"rb")) == NULL)
        puts("Esse arquivo nao existe!");
    else
    {
        char lixoMemoria    = 0;
        int  caracterLido   = 0;
        int  qtdChars       = 0;
        int  auxChar        = 0;
        int  frequenciaLida = 0;

        HuffNode* auxHuff;
        Lista lista;
        Fila fila;

        inicieFila(&fila);
        inicieLista(&lista);

        /*Le qual sera a quantidade de lixo de memoria no final dos codigos*/
        lixoMemoria = getc(arqEntrada);

        /*Le qual sera a quantidade de chars na lista*/
        fread(&qtdChars, sizeof(short int), 1, arqEntrada);

        int cont = 0;

        while (cont < qtdChars)
        {
            /*L� um byte da frequencia*/
            caracterLido = getc(arqEntrada);
            fread(&frequenciaLida, sizeof(int), 1, arqEntrada);
            insiraEmOrdem(&fila.lis, novoHuffNode(caracterLido, frequenciaLida), comparaHuffNode);
            cont++;
        }

        /*Reconstroe a arvore com os codigos dos chars*/
        while(fila.lis.qtd >= 2)
        {
            /*Cria um novo no*/
            HuffNode* novo = novoHuffNode(-1,0);

            /*Desenfileira dois nos, para a esquerda e para a direita do novo no*/
            novo->esquerda = desenfileirar(&fila.lis);
            novo->direita  = desenfileirar(&fila.lis);

            /*Atribui a frequencia desse novo no como a soma da  frequencia dos nos anteriores*/
            novo->frequencia = novo->esquerda->frequencia + novo->direita->frequencia;

            /*Insere o no na lista em ordem*/
            insiraEmOrdem(&fila.lis, novo, comparaHuffNode);
        }

        puts("aqui");
        auxHuff = (HuffNode*) desenfileirar(&fila.lis);

        inicieLista(&lista);

        limparVetorChar(nomeArquivo, 50);
        strncpy(nomeArquivo, nomeArquivoAlula, (strlen(nomeArquivoAlula) - 5));
        puts(nomeArquivo);
        if((arqSaida = fopen(nomeArquivo, "wb")) == NULL)
            puts("Esse arquivo nao pode ser criado!");
        else
        {
            char aux = 0;
            unsigned char codLido = 0;
            char chegouNoLixo = 0;
            char auxLixo = 0;
            HuffNode* atual;

            int ultimoBit = 8 - lixoMemoria;
            atual = auxHuff;
            while(fread(&codLido, 1, sizeof(char), arqEntrada))
            {
                for (int c = 0; c < 8; c++)
                {
                    if (chegouNoLixo)
                        if(c > ultimoBit)
                            break;

                    aux = codLido >> 7;
                    codLido = codLido << 1;

                    if(atual->esquerda == NULL && atual->direita == NULL)
                    {
                        fputc(atual->caracter, arqSaida);
                        fflush(arqSaida);
                        atual = auxHuff;
                    }

                    if(aux == 1)
                        atual = atual->direita;
                    if(aux == 0)
                        atual = atual->esquerda;

                }

                if(chegouNoLixo)
                    break;

                if(fread(&auxLixo, 1, sizeof(char), arqEntrada))
                   chegouNoLixo = 1;
                ungetc(auxLixo, arqEntrada);
            }
        }

    }

    fclose(arqEntrada);
    fclose(arqSaida);

    system("PAUSE");
}

void p(HuffNode* avere)
{
    if(avere != NULL)
    {
        p(avere->esquerda);
        if(avere->caracter != -1)
            printf("%c : %d\n", avere->caracter, avere->frequencia);
        p(avere->direita);
    }
}

void clearScreen()
{
    system("@cls||clear");
}

