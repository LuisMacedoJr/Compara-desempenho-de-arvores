#ifndef ARVORES_H
#define ARVORES_H

typedef struct nodop Nodo;

struct nodop{
    char nome[100];
    float tempo;
    int FB; //não é usado na abp
    Nodo* dir;
    Nodo* esq;
};

Nodo* CriaArvore();
Nodo* CriaNodo(char* n, float t);
void InsereABP(char* n, float t, Nodo** nodo);
void ImprimeABP(Nodo* nodo);
char* StringMinusculo(char *str);
Nodo* consulta(Nodo* nodo, char* n);
float TempoNodoArvore(Nodo* nodo, char* n, int* comp);
int AlturaABP(Nodo* nodo);
Nodo* InsereAVL(char* n, float t, Nodo* nodo, int* ok, int* rot);
Nodo* Caso1 (Nodo* a , int* ok);
Nodo* Caso2 (Nodo* a , int* ok);
Nodo* rotacao_direita(Nodo* a);
Nodo* rotacao_esquerda(Nodo* a);
Nodo* rotacao_dupla_direita (Nodo* a);
Nodo* rotacao_dupla_esquerda (Nodo* a);
int AlturaAVL(Nodo* a);

#endif