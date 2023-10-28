// lista encadeada

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *next;
} No;

No *inicio = NULL;

void add(No **atual, int valor)
{
    No *novoNo = (No *)malloc(sizeof(No));

    novoNo->valor = valor;
    novoNo->next = NULL;

    if (inicio == NULL)
        inicio = novoNo;
    else
        (*atual)->next = novoNo;
    *atual = novoNo;
}

void show()
{
    No *temp = inicio;

    while (temp != NULL)
    {
        printf("Valor: %d\n", temp->valor);
        temp = temp->next;
    }
}

int main()
{
    No *atual = NULL;

    int valor;

    do
    {
        scanf("%d", &valor);
        add(&atual, valor);
    } while (valor != 0);

    show();
}