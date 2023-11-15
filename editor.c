#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

#define TAMANHO_CHAR 256

int main(int argc,char *argv[])
{
    if (argc != 3) {
        printf("Formato inválido, utilize: ./programa <entrada> <saida>");
        return 1;
    }

    char *entrada = argv[1];
    char *saida = argv[2];

    Node *head = NULL;

    FILE *ptr;
    FILE *binPtr;

    char *ch;

    ptr = fopen(entrada, "rb");
    binPtr = fopen(saida, "wb");

    if (ptr == NULL)
    {
        perror("Erro ao abrir o arquivo de entrada");
        return -1;
    }

    if (binPtr == NULL)
    {

        perror("Erro ao abrir o arquivo de saída");
        return -1;
    }

    int contador = 0;

    while ((ch = readLine(ptr)) != NULL)
    {
        if (strlen(ch) <= 1)
        {
            continue;
        }

        printf("Linha lida: %s\n", ch);

        Node *new_node = newNode(binaryToString(ch));
        insertNode(&head, new_node);

        contador++;
    }

    printf("\nContador: %d\n\n", contador);

    int option;

    do
    {
        printf("\n\nCOMBOLIST PARSER\n\n");
        printf("[1] Adicionar.\n");
        printf("[2] Remover.\n");
        printf("[3] Buscar Email.\n");
        printf("[4] Salvar.\n");
        printf("[0] Finalizar.\n");
        printf("ESCOLHA SUA OPCAO (1, 2 ou 3): \n");

        scanf("%d", &option);

        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        
        char novo[TAMANHO_CHAR];
        char emailRemover[TAMANHO_CHAR];
        char emailBuscar[TAMANHO_CHAR];

        switch (option)
        {
        case 1:
            

            printf("Escreva o texto que gostaria de adicionar (ex: meu.email@gmail.com:segredo123): ");

            scanf("%s", novo);

            Node *new_node = newNode(novo);
            insertNode(&head, new_node);
            break;
        case 2:

            printf("Qual email gostaria de remover? (ex: meu.email@gmail.com): ");

            scanf("%s", emailRemover);

            findNode(&head, NULL, emailRemover, 1);

            break;
        case 3:
            

            printf("Qual email gostaria de buscar? (ex: meu.email@gmail.com): ");

            scanf("%s", emailBuscar);

            findNode(&head, NULL, emailBuscar, 2);
            break;
        case 4:
            writeList(head, 2, binPtr);
            break;
        }

    } while (option != 0);

    // Salvamento obrigatório ao final da execução
    writeList(head, 2, binPtr);

    fclose(ptr);
    fclose(binPtr);

    return 0;
}
