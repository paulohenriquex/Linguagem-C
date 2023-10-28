#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct No
{
    int valor;
    struct No *next;
} No;

No *inicio = NULL, *atual = NULL, *novoNo = NULL;

void pop()
{
    No *temp = inicio;
    while (temp != NULL)
    {
        No *prox = temp->next;
        free(temp);
        temp = prox;
    }

    inicio = NULL;
}

void show()
{
    int cont = 0;
    No *temp = inicio;
    while (temp != NULL)
    {
        printf("%d", temp->valor);
        temp = temp->next;
        cont++;
    }
    printf("\n");
    printf("O numero de numeros cadastrados e : %d\n", cont);
}

void add(int valor)
{
    novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL)
    {
        printf("Erro ao alocar memoria\n");
        return;
    }

    novoNo->valor = valor;
    novoNo->next = NULL;

    if (inicio == NULL)
    {
        inicio = novoNo;
        atual = novoNo;
    }
    else
    {
        atual->next = novoNo;
        atual = novoNo;
    }
}

int main()
{
    int valor;

    do
    {
        printf("Digite um valor ou (1) para sair: ");
        scanf("%d", &valor);

        if (valor == 1)
            break;

        add(valor);

    } while (valor != 1);
    show();
    pop();
    return 0;
}
