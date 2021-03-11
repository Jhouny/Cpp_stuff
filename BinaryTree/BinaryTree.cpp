#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
    struct arvore* esq;
    struct arvore* dir;
    int info;
} Arvore;

Arvore* insert (Arvore* arv, int elem) {
    if(arv == NULL) {
        Arvore* novo = (Arvore*) malloc(sizeof(Arvore));
        novo->info = elem;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    } else {
        if(arv->info > elem) {
            arv->esq = insert(arv->esq, elem);
        } else {
            arv->dir = insert(arv->dir, elem);
        }
        return arv;
    }
}

void InOrdem(Arvore* arv) {
    if(arv != NULL) {
        InOrdem(arv->esq);
        printf("%d", arv->info);
        InOrdem(arv->dir);
    } 
}

void preOrdem(Arvore* arv) {
    if(arv != NULL) {
        printf("%d\n", arv->info);
        preOrdem(arv->esq);
        preOrdem(arv->dir);
    } 
}

int counter(Arvore* arv) {
    if(arv != NULL) {
        return 1+counter(arv->esq)+counter(arv->dir);
    } else {
        return 0;
    }
}

int max(int a, int b) {
    return(a>b?a:b);
}

int height(Arvore* arv) {
    if(arv != NULL) {
        return 1+max(height(arv->esq), height(arv->dir));

    } else {
        return -1;
    }
}

int main() {
    Arvore* minhaArv = NULL;
    minhaArv = insert(minhaArv, 10);
    minhaArv = insert(minhaArv, 14);
    minhaArv = insert(minhaArv, 3);
    minhaArv = insert(minhaArv, 20);
    minhaArv = insert(minhaArv, 12);
    InOrdem(minhaArv);
    printf("N. de nos: %d\n", counter(minhaArv));
    printf("Height: %d\n", height(minhaArv));
    
}