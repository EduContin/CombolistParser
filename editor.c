#include <stdio.h>           
#include <stdlib.h>
#include <string.h>

/*
    Lê dados do arquivo binário
    Armazena internamente esses dados em memória heap
    Realiza operações sobre esses dados
    Gera um novo arquivo binário contendo os dados atualizados
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
void stringToBinary(FILE *f, char *data) {
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

// Binário para string
char* binaryToString(char *binary) {
    size_t len = strlen(binary);
    if (len % 8 != 0) return NULL; // Deve ser divisível por 8 (1 byte)

    size_t resultLen = len / 8;
    char *result = (char*)malloc(resultLen + 1); // +1 para o caractere nulo de terminação
    
    for (size_t i = 0; i < len; i += 8) {
        char c = 0;
        for (int j = 0; j < 8; ++j) {
            if (binary[i + j] == '1') c |= (1 << (7 - j));
        }
        result[i / 8] = c;
    }
    result[resultLen] = '\0'; // Adiciona o caractere nulo de terminação
    
    return result;
}

/*
Função para percorrer a lista organizada e:
MODOS:
1 - PRINT
2 - ESCREVE NO ARQUIVO DE SAIDA
*/
void writeList(struct Node *head, int mode) {
    FILE* binPtr;
    binPtr = fopen("editado.bin", "wb");

    if (binPtr == NULL) {
    printf("Error opening file.\n");
    return;
    }

    struct Node *temp = head;

    if (temp == NULL) {
    printf("Head node is NULL.\n");
    return;
    }
    
    printf("%s", temp->data);
    while(temp != NULL) {
        printf("ddd");
        if (mode == 1) {
        printf("%s ", temp->data);
        } else {
        stringToBinary(binPtr, temp->data);
        }
        temp = temp->next;
    }
    fclose(binPtr);
}

char* readLine(FILE *file) {
    size_t size = 256;
    char *line = malloc(size);
    if (!line) return NULL;

    char *pos = line;  // CPosição atual de leitura
    while (1) {
        char ch = fgetc(file);
        if (ch == EOF) {
            if (pos == line) {  // Se não achar nenhum character
                free(line);
                return NULL;
            }
            *pos = '\0';  // Finaliza a string
            return line;
        } else if (ch == '\n') {
            *pos = '\0';  // Finaliza a string
            return line;
        } else {
            *pos = ch;
            pos++;
        }
        // Se encontrar o fim do buffer, dobra o tamanho
        if (pos - line == size) {
            size *= 2;
            char *newline = realloc(line, size);
            if (!newline) {
                free(line);
                return NULL;
            }
            line = newline;
            pos = line + size / 2;  // Atualiza a posição atual (se coloca no fim do buffer antigo [metade do atual])
        }
    }
}

int main()
{   
    struct Node* head = NULL;

    // Arquivos de entrada(binário) e saída editado(binário)
    FILE* ptr;
    FILE* binPtr;

    char* ch;

    ptr = fopen("saida.bin", "rb"); // lendo arquivo de entrada
    binPtr = fopen("editado.bin", "wb"); // wb para gravação binária

    if (ptr == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return -1;
    }

    if (binPtr == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        return -1;
    }

    int contador;

    while ((ch = readLine(ptr)) != NULL)
    {
        // Remove linhas nulas
        if (strlen(ch) <= 1) {
            continue;
        }

        printf("Linha lida: %s\n", ch);

        struct Node* new_node = newNode(binaryToString(ch));
        insertNode(&head, new_node);

        contador++;
    };

    printf("\nContador: %d\n\n", contador);
 

    printf("Lista Encadeada Ordenada: ");
    writeList(head, 1); // Print
    printf("\n\n\n\nAA");
    writeList(head, 1); // Print

    char option;

    do
    {
        printf("\n\nCOMBOLIST PARSER\n\n");
        printf("[1] Ler lista.\n");
        printf("[2] Remover.\n");
        printf("[3] Adicionar.\n\n");
        printf("[0] Finalizar Programa.\n\n");
        printf("ESCOLHA SUA OPÇÃO (1, 2 ou 3): \n");

        writeList(head, 1);

        scanf("%d", &option);

        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        switch (option)
        {
        case 1:

            break;
        case 2:
            break;
        case 3:
            char novo[256];

            printf("Escreva o texto que gostaria de adicionar (ex: meu.email@gmail.com:segredo123): ");

            scanf("%s", novo);
            
            struct Node* new_node = newNode(novo);
            insertNode(&head, new_node);

            break;
        }
        
    }
    while (option != 0);

    // Closing the file
    fclose(ptr);
    fclose(binPtr);
    

    return 0;
}