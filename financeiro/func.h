#ifndef func_h
#define func_h

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

#define TAM 100

typedef struct
{
    char nome[50];
    int id, mes;
    float vl;
} despesas;

typedef struct
{
    char nome[50];
    int id, mes;
    float vl;
} receitas;

void mostrarLista();
void cad_despesas();
void cad_receitas();
void listar(int a);
void balanco();

receitas *rec;
despesas *des;
FILE *despesa;
FILE *receita;
FILE *temp;

#endif
