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
        // Atualiza o próximo do novo nó para o antigo início
        novoNo->next = *inicio;
        // Atualiza o início para o novo nó
        *inicio = novoNo;
    }
}

void remove_lista(No **p, int x)
{
    No *anterior = NULL;
    No *atual = *p;

    // Verifica se o elemento a ser removido está no início da lista
    if (atual != NULL && atual->valor == x)
    {
        *p = atual->next;
        free(atual);
        return;
    }

    // Percorre a lista procurando o elemento a ser removido
    while (atual != NULL && atual->valor != x)
    {
        anterior = atual;
        atual = atual->next;
    }

    // Se o elemento não foi encontrado na lista
    if (atual == NULL)
        return;

    // Remove o nó da lista
    anterior->next = atual->next;
    free(atual);
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

int main()
{
    No *inicio = NULL;
    No *resultado = NULL;

    inserirnoinicio(&inicio, 3);
    inserirnoinicio(&inicio, 2);
    inserirnoinicio(&inicio, 1);

    printf("Lista encadeada: ");
    printarlista(inicio);

    int elementoBuscado = 2;
    resultado = buscarElemento(inicio, elementoBuscado);

    if (resultado != NULL)
        printf("O elemento %d foi encontrado na lista.\n", elementoBuscado);
    else
        printf("O elemento %d não está na lista.\n", elementoBuscado);

    // Remove o elemento da lista
    remove_lista(&inicio, elementoBuscado);

    printf("Lista apos a remocao: ");
    printarlista(inicio);

    return 0;
}
