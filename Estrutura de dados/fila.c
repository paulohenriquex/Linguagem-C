#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *proximo;
} No;

typedef struct Fila
{
    No *inicio;
    No *fim;
} Fila;

void inicializarFila(Fila *fila)
{
    fila->inicio = NULL;
    fila->fim = NULL;
}

int estaVazia(Fila *fila)
{
    return (fila->inicio == NULL);
}

void enfileirar(Fila *fila, int valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->proximo = NULL;

    if (estaVazia(fila))
    {
        fila->inicio = novoNo;
        fila->fim = novoNo;
    }
    else
    {
        fila->fim->proximo = novoNo;
        fila->fim = novoNo;
    }
}

int desenfileirar(Fila *fila)
{
    if (estaVazia(fila))
    {
        printf("A fila está vazia.\n");
        return -1; // Valor inválido para indicar erro
    }

    No *temp = fila->inicio;
    int valor = temp->valor;

    fila->inicio = fila->inicio->proximo;
    free(temp);

    if (fila->inicio == NULL)
    {
        fila->fim = NULL;
    }

    return valor;
}

void exibirFila(Fila *fila)
{
    if (estaVazia(fila))
    {
        printf("A fila está vazia.\n");
        return;
    }

    No *temp = fila->inicio;
    printf("Elementos da fila: ");
    while (temp != NULL)
    {
        printf("%d ", temp->valor);
        temp = temp->proximo;
    }
    printf("\n");
}

int main()
{
    Fila fila;
    
    inicializarFila(&fila);

    enfileirar(&fila, 10);
    enfileirar(&fila, 20);
    enfileirar(&fila, 30);

    exibirFila(&fila);

    int valor = desenfileirar(&fila);
    printf("Valor removido: %d\n", valor);

    exibirFila(&fila);

    return 0;
}
