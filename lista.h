#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

// Definindo a estrutura do nó
struct Node {
    char* data;
    struct Node* next;
};

// Função para criar um novo nó
struct Node* newNode(char* data);

// Função para inserir novo nó de maneira ordenada
void insertNode(struct Node** head_ref, struct Node* new_node);


// Função para percorrer a lista organizada e escrever para o arquivo de saída
void writeList(struct Node *head);

// String para binário
void writeAsBinary(FILE *f,char *data);


#endif // PILHA_H_INCLUDED