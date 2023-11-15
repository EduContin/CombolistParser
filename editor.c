#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char email[50];
    char senha[50];
} Dado;

typedef struct Node
{
    Dado data;
    struct Node *next;
} Node;

Node *newNode(char *data)
{
    char *email = strtok(data, ":");
    char *senha = strtok(NULL, ":");

    if (email == NULL || senha == NULL)
    {
        return NULL;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    strncpy(node->data.email, email, sizeof(node->data.email) - 1);
    strncpy(node->data.senha, senha, sizeof(node->data.senha) - 1);
    node->next = NULL;
    return node;
}

void insertNode(Node **head_ref, Node *new_node)
{
    Node *current;

    if (*head_ref == NULL || strcmp((*head_ref)->data.email, new_node->data.email) >= 0)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        current = *head_ref;
        while (current->next != NULL && strcmp(current->next->data.email, new_node->data.email) < 0)
        {
            current = current->next;
        }

        new_node->next = current->next;
        current->next = new_node;
    }
}

void stringToBinary(FILE *f, char *data)
{
    for (size_t i = 0; i < strlen(data); ++i)
    {
        char c = data[i];
        for (int j = 7; j >= 0; --j)
        {
            if (c & (1 << j))
                fputc('1', f);
            else
                fputc('0', f);
        }
    }
    fputc('\n', f);
}

char *binaryToString(char *binary)
{
    size_t len = strlen(binary);
    if (len % 8 != 0)
        return NULL;

    size_t resultLen = len / 8;
    char *result = (char *)malloc(resultLen + 1);

    for (size_t i = 0; i < len; i += 8)
    {
        char c = 0;
        for (int j = 0; j < 8; ++j)
        {
            if (binary[i + j] == '1')
                c |= (1 << (7 - j));
        }
        result[i / 8] = c;
    }
    result[resultLen] = '\0';

    return result;
}

/*
    Percorre a lista
    MODOS: (1) Print | (2) Salva pro BIN como binário
*/
void writeList(Node *head, int mode)
{
    FILE *binPtr;
    binPtr = fopen("editado.bin", "wb");

    if (binPtr == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    Node *temp = head;

    if (temp == NULL)
    {
        printf("Head node is NULL.\n");
        return;
    }
    // Percorre a lista de Nós até achar o final
    while (temp != NULL)
    {
        if (mode == 1)
        {
            printf("%s:%s ", temp->data.email, temp->data.senha);
        }
        else
        {
            char data[101];
            snprintf(data, sizeof(data), "%s:%s", temp->data.email, temp->data.senha);
            stringToBinary(binPtr, data);

        }
        temp = temp->next;
        fclose(binPtr);
    }
}

char *readLine(FILE *file)
{
    size_t size = 256;
    char *line = malloc(size);
    if (!line)
        return NULL;

    char *pos = line;
    while (1)
    {
        char ch = fgetc(file);
        if (ch == EOF)
        {
            if (pos == line)
            {
                free(line);
                return NULL;
            }
            *pos = '\0';
            return line;
        }
        else if (ch == '\n')
        {
            *pos = '\0';
            return line;
        }
        else
        {
            *pos = ch;
            pos++;
        }

        if (pos - line == size)
        {
            size *= 2;
            char *newline = realloc(line, size);
            if (!newline)
            {
                free(line);
                return NULL;
            }
            line = newline;
            pos = line + size / 2;
        }
    }
}

/*
    FINDS THE NOME BY EMAIL
    MODES: (1) Remove | (2) Prints FULL DATA
*/
int findNode(Node **head_ref, char *email, int mode)
{
    Node *temp = *head_ref, *prev;

    // Caso o primeiro seja o node buscado:
    if (temp != NULL && strcmp(temp->data.email, email) == 0)
    {
        if (mode == 1)
        {
            *head_ref = temp->next; // Novo head_ref = próximo
            free(temp);             // Deleta node buscado
            return 1;
        }
        else if (mode == 2)
        {
            printf("EMAIL: %s | SENHA: %s", temp->data.email, temp->data.senha);
            return 1;
        }
    }

    // Procura pelo email entre os nodes
    // Mantém armazenado o node anterior para junção pós remoção (se o modo for de remover)
    while (temp != NULL && strcmp(temp->data.email, email) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    // If email was not present in linked list
    if (temp == NULL)
        return 0;

    if (mode == 1)
    {
        // Unlink the node from linked list
        prev->next = temp->next;

        free(temp); // Free memory
        return 1;
    }
    else if (mode == 2)
    {
        printf("EMAIL: %s | SENHA: %s", temp->data.email, temp->data.senha);
        printf("\n\nNODE | BUSCAR | SUCESSO\n\n");
    }
    
}

int main()
{
    Node *head = NULL;

    FILE *ptr;
    FILE *binPtr;

    char *ch;

    ptr = fopen("saida.bin", "rb");
    binPtr = fopen("editado.bin", "wb");

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
        writeList(head, 1);

        printf("\n\nCOMBOLIST PARSER\n\n");
        printf("[1] Adicionar.\n");
        printf("[2] Remover.\n");
        printf("[3] Buscar Email.\n");
        printf("[0] Finalizar Programa.\n\n");
        printf("ESCOLHA SUA OPÇÃO (1, 2 ou 3): \n");


        scanf("%d", &option);

        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        switch (option)
        {
        case 1:
            char novo[256];

            printf("Escreva o texto que gostaria de adicionar (ex: meu.email@gmail.com:segredo123): ");

            scanf("%s", novo);

            Node *new_node = newNode(novo);
            insertNode(&head, new_node);
            break;
        case 2:
            char emailRemover[256];

            printf("Qual email gostaria de remover? (ex: meu.email@gmail.com): ");

            scanf("%s", emailRemover);

            findNode(&head, emailRemover, 1);

            break;
        case 3:
            char emailBuscar[256];

            printf("Qual email gostaria de buscar? (ex: meu.email@gmail.com): ");

            scanf("%s", emailBuscar);

            findNode(&head, emailBuscar, 2);
            break;
        }

    } while (option != 0);

    fclose(ptr);
    fclose(binPtr);

    return 0;
}