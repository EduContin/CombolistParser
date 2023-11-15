#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"


// Cria um novo Nó
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
    free(node);
}

// 
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
    free(result);
}

/*
    Percorre a lista
    MODOS: (1) Print | (2) Salva pro BIN como binário
*/
void writeList(Node *head, int mode, FILE *file)
{
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
            stringToBinary(file, data);
        }
        temp = temp->next;
    }
    fclose(file);
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
int findNode(Node **head_ref, Node *prev, char *email, int mode)
{
    if (*head_ref == NULL)
    {
        return 0;
    }

    Node *temp = *head_ref;

    // Handling o node head
    if (strcmp(temp->data.email, email) == 0)
    {
        if (mode == 1) // delete mode
        {
            if (prev != NULL)
            {
                prev->next = temp->next;
            }
            else
            {
                *head_ref = temp->next;
            }
            free(temp);
        }
        else if (mode == 2) // print mode
        {
            printf("\n#######################################################\n");
            printf("EMAIL: %s | SENHA: %s", temp->data.email, temp->data.senha);
            printf("\n#######################################################\n");
        }
        return 1;
    }
    else
    {
        // Recurse with the next node
        return findNode(&(temp->next), temp, email, mode);
    }
}
