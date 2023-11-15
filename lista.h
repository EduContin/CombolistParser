#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

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

Node *newNode(char *data);
void insertNode(Node **head_ref, Node *new_node);
void stringToBinary(FILE *f, char *data);
char *binaryToString(char *binary);
void writeList(Node *head, int mode, FILE *file);
char *readLine(FILE *file);
int findNode(Node **head_ref, Node *prev, char *email, int mode);

#endif // PILHA_H_INCLUDED