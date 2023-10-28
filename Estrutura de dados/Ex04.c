#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *next;
} No;

void inserirnoinicio(No **inicio, int x)
{
    // Cria um novo nó
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->valor = x;
    novoNo->next = NULL;

    // Verifica se a lista está vazia
    if (*inicio == NULL)
        *inicio = novoNo;
    else
    {
        // Atualiza o próximo do novo nó para o antigo inicio
        novoNo->next = *inicio;
        // Atualiza o inicio para o novo nó
        *inicio = novoNo;
    }
}

No *buscarElemento(No *inicio, int x)
{
    No *atual = inicio;
    while (atual != NULL)
    {
        if (atual->valor == x)
            return atual;

        atual = atual->next;
    }

    return NULL;
}

void printarlista(No *inicio)
{
    No *atual = inicio;

    while (atual != NULL)
    {
        printf("%d ", atual->valor);
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
    printarlista(inicio);

    int elementoBuscado = 2;
    No *resultado = buscarElemento(inicio, elementoBuscado);

    if (resultado != NULL)
        printf("O elemento %d foi encontrado na lista.\n", elementoBuscado);
    else
        printf("O elemento %d nao esta na lista.\n", elementoBuscado);

    return 0;
}
