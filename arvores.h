#ifndef ARVORES_H
#define ARVORES_H

typedef struct nodop Nodo;

struct nodop{
    char nome[100];
    float tempo;
    Nodo* dir;
    Nodo* esq;
};

Nodo* CriaABP();

Nodo* CriaNodoABP(char* n, float t);

void InsereABP(char* n, float t, Nodo** nodo);

void ImprimeABP(Nodo* nodo);

char* StringMinusculo(char *str);

Nodo* consulta(Nodo* nodo, char* n);

float TempoNodoABP(Nodo* nodo, char* n, int* comp);

int AlturaABP(Nodo* nodo);

#endif