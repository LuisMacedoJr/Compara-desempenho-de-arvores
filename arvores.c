#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "arvores.h"

//funções gerais
Nodo* CriaArvore(){
    return NULL;
}

Nodo* CriaNodo(char* n, float t){
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
    strcpy(novo->nome,n);
    novo->tempo = t;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->FB = 0;
    return novo;
}

float TempoNodoArvore(Nodo* nodo, char* n, int* comp) {
    (*comp)++;
    if (nodo == NULL) {
        printf("Nao achou o jogo %s\n", n);
        return 0;
    } else if (strcmp(nodo->nome,n) < 0) {
        TempoNodoArvore(nodo->dir, n, comp);
    } else if (strcmp(nodo->nome,n) > 0) {
        TempoNodoArvore(nodo->esq, n, comp);
    } else if (strcmp(nodo->nome,n) == 0) {
        return nodo->tempo;
    }
}

char* StringMinusculo(char *str){
    unsigned char *p = (unsigned char *)str;

    while (*p) {
        *p = tolower((unsigned char)*p);
        p++;
    }

    return str;
}

//ABP
void InsereABP(char* n, float t, Nodo** nodo){
    if (*nodo == NULL){
        *nodo = CriaNodo(n, t);
    } else if (strcmp((*nodo)->nome,n) < 0) {
        if ((*nodo)->dir == NULL) {
            (*nodo)->dir = CriaNodo(n, t);
        } else {
            InsereABP(n, t, &(*nodo)->dir);
        }
    } else if (strcmp((*nodo)->nome,n) > 0) {
        if ((*nodo)->esq == NULL) {
            (*nodo)->esq = CriaNodo(n, t);
        } else {
            InsereABP(n, t, &(*nodo)->esq);
        }
    }
}

void ImprimeABP(Nodo* nodo) {
    if (nodo != NULL) {
        ImprimeABP(nodo->esq);
        printf("%s %.2f\n", nodo->nome, nodo->tempo);
        ImprimeABP(nodo->dir);
    }
}

int AlturaABP(Nodo* nodo) {
    if (nodo == NULL) {
        return 0;
    } else {
        int alturaDireita = 1 + AlturaABP(nodo->dir);
        int alturaEsquerda = 1 + AlturaABP(nodo->esq);
        if (alturaDireita > alturaEsquerda) {
            return alturaDireita;
        } else {
            return alturaEsquerda;
        }
    }
}

//AVL
Nodo* InsereAVL(char* n, float t, Nodo* a, int* ok, int* rot){
    if (a == NULL) {
        a = CriaNodo(n, t);
        *ok = 1;
    } else if (strcmp(a->nome,n) > 0) {
        a->esq = InsereAVL(n, t, a->esq, ok, rot);
        if (*ok) {
            switch (a->FB) {
                case -1: 
                    a->FB = 0; 
                    *ok = 0; 
                    break;
                case 0: 
                    a->FB = 1; 
                    break;
                case 1: 
                    a = Caso1(a,ok);
                    (*rot)++; //caso rotaçao dupla conte como duas, mudar para as funçoes de rotação
                    break;
            }
        }
    } else {
        a->dir = InsereAVL(n, t, a->dir, ok, rot);
        if (*ok) {
            switch (a->FB) {
                case 1: 
                    a->FB = 0; 
                    *ok = 0; 
                    break;
                case 0: 
                    a->FB = -1; 
                    break;
                case -1: 
                    a = Caso2(a,ok);
                    (*rot)++;
                    break;
                }
        }
    }

    return a;
}

Nodo* Caso1(Nodo* a , int* ok) {
    Nodo* z;
    z = a->esq;

    if (z->FB == 1) a = rotacao_direita(a);
    else a = rotacao_dupla_direita(a);

    a->FB = 0;
    *ok = 0;
    
    return a;
}

Nodo* Caso2(Nodo* a , int* ok) {
    Nodo* z;
    z = a->dir;

    if (z->FB == -1) a = rotacao_esquerda(a);
    else a = rotacao_dupla_esquerda(a);

    a->FB = 0;
    *ok = 0;
    
    return a;
}

Nodo* rotacao_direita(Nodo* a){
    Nodo* u;
    
    u = a->esq;
    a->esq = u->dir;
    u->dir = a;
    a->FB = 0;
    a = u;
    
    return a;
}

Nodo* rotacao_esquerda(Nodo* a){
    Nodo* z;
    
    z = a->dir;
    a->dir = z->esq;
    z->esq = a;
    a->FB = 0;
    a = z;
    
    return a;
} 

Nodo* rotacao_dupla_direita(Nodo* a){
    Nodo *u, *v;
    
    u = a->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    a->esq = v->dir;
    v->dir = a;
    
    if (v->FB == 1) a->FB = -1;
    else a->FB = 0;
    
    if (v->FB == -1) u->FB = 1;
    else u->FB = 0;

    a = v;
    
    return a;
} 

Nodo* rotacao_dupla_esquerda(Nodo* a){
    Nodo *z, *y;

    z = a->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    a->dir = y->esq;
    y->esq = a;

    if (y->FB == -1) a->FB = 1;
    else a->FB = 0;

    if (y->FB == 1) z->FB = -1;
    else z->FB = 0;
    
    a = y;

    return a;
}

int AlturaAVL(Nodo* a)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
        return 0;
    else
    {
        Alt_Esq = AlturaAVL(a->esq);
        Alt_Dir = AlturaAVL(a->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}