#include <stdio.h>           
#include <stdlib.h>
#include <string.h>
#include "lista.h"

/*
    Lê dados de um arquivo texto
    Armazena internamente esses dados em memória heap
    Grava esses dados em um arquivo binário
*/

int main(int argc, char *argv[])
{   
    if (argc != 3) {
        printf("Formato inválido, utilize: ./programa <entrada> <saida>");
        return 1;
    }

    Node* head = NULL;

    // Arquivos de entrada(string) e saída(binário)
    FILE* ptr;
    FILE* binPtr;

    char *arquivo_txt_entrada = argv[1];
    char *arquivo_bin_saida = argv[2];

    char ch[256];

    ptr = fopen(arquivo_txt_entrada, "r"); // lendo arquivo de entrada
    binPtr = fopen(arquivo_bin_saida, "wb"); // wb para gravação binária

    if (ptr == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return -1;
    }

    if (binPtr == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        return -1;
    }

    int contador;

    // Printing what is written in file
    // character by character using loop.
    while (fgets(ch, sizeof(ch), ptr)) {

        // Remove linhas nulas
        if (strlen(ch) <= 1) {
            continue;
        }


        ch[strcspn(ch, "\n")] = 0;  // Remove the newline character
        printf("Linha lida: %s\n", ch);

        Node *new_node = newNode(ch);
        insertNode(&head, new_node);

        contador++;
 
        // Checking if character is not EOF.
        // If it is EOF stop reading.
    };

    printf("\nContador: %d\n\n", contador);

    printf("Lista Encadeada Ordenada: ");
    writeList(head, 1, NULL);
    writeList(head, 2, binPtr);

    // Closing the file
    fclose(ptr);
    fclose(binPtr);

    return 0;
}
