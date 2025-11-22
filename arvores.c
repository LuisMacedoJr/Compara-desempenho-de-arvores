#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "arvores.h"

Nodo* CriaABP(){
    return NULL;
}

Nodo* CriaNodoABP(char* n, float t){
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
    strcpy(novo->nome,n);
    novo->tempo = t;
    novo->dir = NULL;
    novo->esq = NULL;
    return novo;
}

void InsereABP(char* n, float t, Nodo** nodo){
    if (*nodo == NULL){
        *nodo = CriaNodoABP(n, t);
    } else if (strcmp((*nodo)->nome,n) < 0) {
        if ((*nodo)->dir == NULL) {
            (*nodo)->dir = CriaNodoABP(n, t);
        } else {
            InsereABP(n, t, &(*nodo)->dir);
        }
    } else if (strcmp((*nodo)->nome,n) > 0) {
        if ((*nodo)->esq == NULL) {
            (*nodo)->esq = CriaNodoABP(n, t);
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


float TempoNodoABP(Nodo* nodo, char* n, int* comp) {
    (*comp)++;
    if (nodo == NULL) {
        printf("Nao achou o jogo %s\n", n);
        return 0;
    } else if (strcmp(nodo->nome,n) < 0) {
        TempoNodoABP(nodo->dir, n, comp);
    } else if (strcmp(nodo->nome,n) > 0) {
        TempoNodoABP(nodo->esq, n, comp);
    } else if (strcmp(nodo->nome,n) == 0) {
        return nodo->tempo;
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

char* StringMinusculo(char *str){
    unsigned char *p = (unsigned char *)str;

    while (*p) {
        *p = tolower((unsigned char)*p);
        p++;
    }

    return str;
}