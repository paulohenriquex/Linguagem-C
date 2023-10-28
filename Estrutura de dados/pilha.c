// Código de uma pilha

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *next;
} No;

No *head = NULL;

void show()
{
    No *temp = head;

    while (temp != NULL)
    {
        printf("Valor: %d\n", temp->valor);
        temp = temp->next;
    }
}

void add(int valor)
{
    No *novoNo = NULL;

    novoNo = (No *)malloc(sizeof(No));

    novoNo->valor = valor;
    novoNo->next = head;
    head = novoNo;
}

int main()
{
    int valor;

    do
    {
        scanf("%d", &valor);
        add(valor);

    } while (valor != 0);

    show();
}
