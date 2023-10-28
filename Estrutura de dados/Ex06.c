#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No
{
    char nome[20];
    struct No *next;
} tNo;

int conta_lista(tNo *lista)
{
    int count = 0;
    while (lista->next)
    {
        count++;
        lista = lista->next;
    }
    return count;
}

void insere_comeco(tNo **lista, char *palavra)
{
    tNo *novoNo = (tNo *)malloc(sizeof(tNo));
    strcpy(novoNo->nome, palavra);
    novoNo->next = *lista;
    *lista = novoNo;
}

tNo *busca_lista(tNo *lista, char *palavra)
{
    while (lista)
    {
        if (strcmp(lista->nome, palavra) == 0)
        {
            return lista;
        }
        lista = lista->next;
    }
    return NULL;
}

void remove_lista(tNo **lista, char *palavra)
{
    tNo *anterior = NULL;
    tNo *atual = *lista;

    while (atual)
    {
        if (strcmp(atual->nome, palavra) == 0)
        {
            if (anterior == NULL)
            {
                *lista = atual->next;
            }
            else
            {
                anterior->next = atual->next;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->next;
    }
}

int main(int argc, char **argv)
{
    tNo *lista = (tNo *)malloc(sizeof(tNo));
    lista->next = NULL;

    add(lista, "João");
    add(lista, "Maria");
    add(lista, "José");

    printf("Lista:\n");
    show(lista);

    int count = conta_lista(lista);
    printf("Número de elementos na lista: %d\n", count);

    insere_comeco(&lista, "Ana");
    printf("\nLista após a inserção no começo:\n");
    show(lista);

    tNo *resultado = busca_lista(lista, "Maria");
    if (resultado != NULL)
    {
        printf("\nO elemento 'Maria' foi encontrado na lista.\n");
    }
    else
    {
        printf("\nO elemento 'Maria' não está na lista.\n");
    }

    remove_lista(&lista, "João");
    printf("\nLista após a remoção do elemento 'João':\n");
    show(lista);

    return 0;
}
