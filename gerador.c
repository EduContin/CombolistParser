#include <stdio.h>           
#include <stdlib.h>
#include <string.h>

/*
    Lê dados de um arquivo texto
    Armazena internamente esses dados em memória heap
    Grava esses dados em um arquivo binário
*/

// Definindo a estrutura do nó
struct Node {
    char* data;
    struct Node* next;
};

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

int main()
{   
    struct Node* head = NULL;

    struct Node* new_node = newNode("banana");
    insertNode(&head, new_node);
    new_node = newNode("abacate");
    insertNode(&head, new_node);
    new_node = newNode("uva");
    insertNode(&head, new_node);
    new_node = newNode("manga");
    insertNode(&head, new_node);
    new_node = newNode("laranja");
    insertNode(&head, new_node);

    // Arquivos de entrada(string) e saída(binário)
    FILE* ptr;
    FILE* binPtr;

    char ch[256];

    ptr = fopen("entrada.txt", "r"); // lendo arquivo de entrada
    binPtr = fopen("saida.bin", "wb"); // wb para gravação binária

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

        printf("Linha lida: %s", ch);

        if (ch[strlen(ch) - 1] == '\n') {
            ch[strlen(ch) - 1] = '\0';
        }

        struct Node* new_node = newNode(ch);
        insertNode(&head, new_node);

        contador++;
 
        // Checking if character is not EOF.
        // If it is EOF stop reading.
    };

    printf("\nContador: %d\n\n", contador);
 
    // Closing the file
    fclose(ptr);

    printf("Lista Encadeada Ordenada: ");
    writeList(head);

    

    return 0;
}