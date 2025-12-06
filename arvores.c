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

//Splay
Nodo* Splay(Nodo* a, char* nome, int* rot) {
    if (a == NULL || strcmp(a->nome, nome) == 0)
        return a;

    if (strcmp(nome, a->nome) < 0) {
        if (a->esq == NULL)
            return a;

        // rotacao zig zig
        if (strcmp(nome, a->esq->nome) < 0) {
            a->esq->esq = Splay(a->esq->esq, nome, rot);
            (*rot)++;
            a = rotacao_direita(a);
        }
        // rotacao zig zag
        else if (strcmp(nome, a->esq->nome) > 0) {
            a->esq->dir = Splay(a->esq->dir, nome, rot);
            if (a->esq->dir != NULL){
                (*rot)++;
                a->esq = rotacao_esquerda(a->esq);
            }
        }

        if (a->esq == NULL){
            return a;
        } else {
            (*rot)++;
            return rotacao_direita(a);
        }
    }

    else {
        if (a->dir == NULL)
            return a;

        // rotacao zag zag
        if (strcmp(nome, a->dir->nome) > 0) {
            a->dir->dir = Splay(a->dir->dir, nome, rot);
            (*rot)++;
            a = rotacao_esquerda(a);
        }
        // rotacao zag zig
        else if (strcmp(nome, a->dir->nome) < 0) {
            a->dir->esq = Splay(a->dir->esq, nome, rot);
            if (a->dir->esq != NULL) {
                (*rot)++;
                a->dir = rotacao_direita(a->dir);
            }
        }

        if (a->dir == NULL){
            return a;
        } else {
            (*rot)++;
            return rotacao_esquerda(a);
        }
    }
}

Nodo* ConsultaNodo(Nodo* a, char* nome, int* rot, int* comp) {
    //coloca o nodo desejado como raiz
    (*comp)++;
    return Splay(a, nome, rot);
}

Nodo* InsereSplay(Nodo* a, char* n, float t, int* rot) {
    if (a == NULL) {
        a = CriaNodo(n, t);
    }

    //primeiro faz o splay, para trazer para a raiz o nodo mais proximo do buscado
    a = Splay(a, n, rot);

    //caso o nodo buscado ja exista, retorna ele
    if (strcmp(a->nome, n) == 0)
        return a;

    Nodo* novo = malloc(sizeof(Nodo));
    strcpy(novo->nome, n);
    novo->tempo = t;

    if (strcmp(n, a->nome) < 0) {
        novo->dir = a;
        novo->esq = a->esq;
        a->esq = NULL;
    }
    else {
        novo->esq = a;
        novo->dir = a->dir;
        a->dir = NULL;
    }

    return novo;
}
