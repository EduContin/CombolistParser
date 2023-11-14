#include <stdio.h>
#include "lista.h"

// Função para criar um novo nó
struct Node* newNode(char* data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data  = strdup(data); // strdup cria uma nova cópia da string
    node->next = NULL;
    return node;
}

// Função para inserir novo nó de maneira ordenada
void insertNode(struct Node** head_ref, struct Node* new_node) {
    struct Node* current;
    
    // Caso especial para o cabeçalho da lista
    if (*head_ref == NULL || strcmp((*head_ref)->data, new_node->data) >= 0) {
        new_node->next = *head_ref;
        *head_ref = new_node;
    } else {
        // Localize o nó antes do ponto de inserção
        current = *head_ref;
        while (current->next!=NULL && strcmp(current->next->data, new_node->data) < 0) {
            current = current->next;
        }
        
        new_node->next = current->next;
        current->next = new_node;
    }
}


// String para binário
void writeAsBinary(FILE *f, char *data) {
    for (size_t i = 0; i < strlen(data); ++i) {
        char c = data[i];
        for (int j = 7; j >= 0; --j) {
            if (c & (1 << j))
                fputc('1', f);
            else
                fputc('0', f);
        }
    }
    fputc('\n', f);
}


// Função para percorrer a lista organizada e escrever para o arquivo de saída
void writeList(struct Node *head) {
    FILE* binPtr;
    binPtr = fopen("saida.bin", "wb");
    
    struct Node *temp = head;
    while(temp != NULL) {
        printf("%s ", temp->data);
        writeAsBinary(binPtr, temp->data);
        temp = temp->next;
    }
    fclose(binPtr);
}
