#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int value;
    struct No *next;
} No;

void inserirnoinicio(No **inicio, int x)
{
    // Cria um novo nó
    No *novoNo = (No *)malloc(sizeof(No));

    novoNo->value = x;
    novoNo->next = NULL;

    // Verifica se a lista está vazia
    if (*inicio == NULL)
        *inicio = novoNo;
    else
    {
        novoNo->next = *inicio;
        *inicio = novoNo;
    }
}

void printList(No *inicio)
{
    No *atual = inicio;

    while (atual != NULL)
    {
        printf("%d ", atual->value);
        atual = atual->next;
    }

    printf("\n");
}

int main()
{
    No *inicio = NULL;

    inserirnoinicio(&inicio, 3);
    inserirnoinicio(&inicio, 2);
    inserirnoinicio(&inicio, 1);

    printf("Lista encadeada: ");
    printList(inicio);

    return 0;
}
